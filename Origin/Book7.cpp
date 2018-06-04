#include <time.h>

#include "MainParent.h"
#include "MainChild.h"
#include "Book7.h"

#include "ImageFactory.h"
#include "SceneManager.h"
#include "HandManager.h"

#include "DCBitmap.h"

#define USE_OBJ_IMAGE_WIDTH 32
#define USE_OBJ_IMAGE_WIDTH_HALF 16
#define USE_OBJ_IMAGE_HEIGHT 64
#define USE_OBJ_IMAGE_HEIGHT_HALF 32
#define USE_MAN_IMAGE_WIDTH 32
#define USE_MAN_IMAGE_HEIGHT 64
#define USE_MAN_IMAGE_LADDER_HEIGHT 128
#define ANIME_SPEED 4

#define WALK_SPEED 2
#define STAY_COUNT 30

namespace Sequence {

Book7::Book7( HDC& hdc, MainParent* parent ) :
mMoveTarget( 0 )
{
	Main::ImageFactory* imageFactory = Main::ImageFactory::inst();
	int windowWidth = Main::SceneManager::windowWidth;
	int windowHeight = Main::SceneManager::windowHeight;
	int entCount = 0;
	int i = -1;

	srand( static_cast< unsigned >( time( NULL ) ) );

	mManImageArr[ ++i ] = imageFactory->loadDC( hdc, "resource\\man_stay.dad" );
	mManImageArr[ ++i ] = imageFactory->loadDC( hdc, "resource\\man_walk.dad" );
	mManImageArr[ ++i ] = imageFactory->loadDC( hdc, "resource\\man_ladder.dad" );

	mObjImage = imageFactory->loadDC( hdc, "resource\\map_objects.dad" );

	for( int y = 0; y < OBJ_Y_NUM; ++y ) {
		for( int x = 0; x < OBJ_X_NUM; ++x ) {
			ObjState* target = &mObjState[ y ][ x ];
			target->holdX = 0;
			target->holdY = 0;
			target->indexX = x;
			target->indexY = y;
			target->useNum = 0;
			target->isHold = FALSE;
			if( target->image != IMAGE_OBJ_ENTRANCE ) {
				if( x >= OBJ_X_NUM - 2 && y == OBJ_Y_NUM - 1 ) {
					target->image = IMAGE_OBJ_NONE;
				} else if( static_cast< double >( rand() ) / RAND_MAX < 0.8 ) {
					target->image = IMAGE_OBJ_NONE;
				} else if( static_cast< double >( rand() ) / RAND_MAX < 0.3 ) {
					target->image = IMAGE_OBJ_WALL;
				} else if( static_cast< double >( rand() ) / RAND_MAX < 0.2 ) {
					target->image = IMAGE_OBJ_LADDER;
				} else if( entCount < ENTRANCE_PAIR_NUM && static_cast< double >( rand() ) / RAND_MAX < 0.1 ) {
					int randX = static_cast< int >( ( static_cast< double >( rand() ) / RAND_MAX ) * ( OBJ_X_NUM - 1 ) );
					int randY = static_cast< int >( ( static_cast< double >( rand() ) / RAND_MAX ) * ( OBJ_Y_NUM - 1 ) );
					ObjState* pairEnt = &mObjState[ randY ][ randX ];
					while( pairEnt->image != IMAGE_OBJ_NONE && randX >= OBJ_X_NUM - 2 && randY == OBJ_Y_NUM - 1 ) {
						randX = static_cast< int >( ( static_cast< double >( rand() ) / RAND_MAX ) * ( OBJ_X_NUM - 1 ) );
						randY = static_cast< int >( ( static_cast< double >( rand() ) / RAND_MAX ) * ( OBJ_Y_NUM - 1 ) );
						pairEnt = &mObjState[ randY ][ randX ];
					}
					target->image = IMAGE_OBJ_ENTRANCE;
					mEntranceState[ entCount ][ 0 ] = target;
					pairEnt->image = IMAGE_OBJ_ENTRANCE;
					mEntranceState[ entCount ][ 1 ] = pairEnt;
					++entCount;
				} else {
					target->image = IMAGE_OBJ_NONE;
				}
			}
		}
	}

	for( int i = 0; i < MAN_NUM; ++i ) {
		ManState* target = &mManState[ i ];
		target->x = USE_OBJ_IMAGE_WIDTH * static_cast< int >( ( static_cast< double >( rand() ) / RAND_MAX ) * ( OBJ_X_NUM - 1 ) );
		target->line = static_cast< int >( ( static_cast< double >( rand() ) / RAND_MAX ) * ( OBJ_Y_NUM - 1 ) );
		while( mObjState[ target->line ][ ( target->x / OBJ_X_NUM ) ].image != IMAGE_OBJ_NONE ) {
			target->x = static_cast< int >( ( static_cast< double >( rand() ) / RAND_MAX ) * ( OBJ_X_NUM - 1 ) );
			target->line = static_cast< int >( ( static_cast< double >( rand() ) / RAND_MAX ) * ( OBJ_Y_NUM - 1 ) );
		}
		target->count = 0;
		target->animeState = 0;
		target->target = 0;
		target->isLeft = ( rand() < RAND_MAX * 0.5 )? TRUE : FALSE;
		target->image = IMAGE_MAN_STAY;
		target->state = MAN_STAY_REST;
	}
}

Book7::~Book7()
{
	for( int i = 0; i < IMAGE_MAN_NONE; ++i ) {
		delete mManImageArr[ i ];
		mManImageArr[ i ] = 0;
	}

	delete mObjImage;
	mObjImage = 0;
}

void Book7::update( MainParent* parent )
{
	int mouseX = Main::HandManager::inst()->getX();
	int mouseY = Main::HandManager::inst()->getY();
	BOOL isClick = Main::HandManager::isClick;
	BOOL isMouseDown = Main::HandManager::isMouseDown;
	BOOL wasHit = FALSE;

	Main::HandManager::inst()->setState( Main::HandManager::HAND_NORMAL );

	if( mMoveTarget == 0 ) {
		if( isMouseDown ) {
			takeObj( mouseX, mouseY );
		} else {
			checkHitObj( mouseX, mouseY );
		}
	} else {
		if( isMouseDown ) {
			moveObj( mouseX, mouseY );
		} else {
			putObj( mouseX, mouseY );
		}
	}

	for( int i = 0; i < MAN_NUM; ++i ) {
		moveMan( &mManState[ i ] );
	}

	if( mouseX > Main::SceneManager::windowWidth - BOOK_CORNAR_HIT_SIZE && mouseY > Main::SceneManager::windowHeight - BOOK_CORNAR_HIT_SIZE ) {
		if( Main::HandManager::isClick ) {
			Main::HandManager::inst()->setState( Main::HandManager::HAND_NORMAL );
			parent->moveTo( parent->SEQ_ROOM );
		} else {
			Main::HandManager::inst()->setState( Main::HandManager::HAND_CLOSE );
		}
	}
}

void Book7::checkHitObj( int mouseX, int mouseY )
{
	ObjState* target = &mObjState[ mouseY / USE_OBJ_IMAGE_HEIGHT ][ mouseX / USE_OBJ_IMAGE_WIDTH ];
	if( target->image == IMAGE_OBJ_NONE ) return;
	if( target->useNum != 0 ) return;
	Main::HandManager::inst()->setState( Main::HandManager::HAND_HOLD_BEFORE );
}

void Book7::takeObj( int mouseX, int mouseY )
{
	ObjState* target = &mObjState[ mouseY / USE_OBJ_IMAGE_HEIGHT ][ mouseX / USE_OBJ_IMAGE_WIDTH ];
	if( target->image == IMAGE_OBJ_NONE ) return;
	if( target->useNum != 0 ) return;
	mMoveTarget = target;
	target->isHold = TRUE;
	target->holdX = mouseX - USE_OBJ_IMAGE_WIDTH_HALF;
	target->holdY = mouseY - USE_OBJ_IMAGE_HEIGHT_HALF;
	Main::HandManager::inst()->setState( Main::HandManager::HAND_HOLD_AFTER );
}

void Book7::moveObj( int mouseX, int mouseY )
{
	mMoveTarget->holdX = mouseX - USE_OBJ_IMAGE_WIDTH_HALF;
	mMoveTarget->holdY = mouseY - USE_OBJ_IMAGE_HEIGHT_HALF;
	Main::HandManager::inst()->setState( Main::HandManager::HAND_HOLD_AFTER );
}

void Book7::putObj( int mouseX, int mouseY )
{
	int targetX = mouseX / USE_OBJ_IMAGE_WIDTH;
	int targetY = mouseY / USE_OBJ_IMAGE_HEIGHT;
	
	if( targetX < OBJ_X_NUM - 2 || targetY != OBJ_Y_NUM - 1 ) {
		switch( mMoveTarget->image ) {
			case IMAGE_OBJ_ENTRANCE:
				putEntrance( targetX, targetY );
				break;
			case IMAGE_OBJ_WALL:
				putWall( targetX, targetY );
				break;
			case IMAGE_OBJ_LADDER:
				putLadder( targetX, targetY );
				break;
		}
	}

	mMoveTarget->isHold = FALSE;
	mMoveTarget = 0;
	Main::HandManager::inst()->setState( Main::HandManager::HAND_HOLD_BEFORE );
}

void Book7::putEntrance( int targetX, int targetY )
{
	ObjState* target = &mObjState[ targetY ][ targetX ];
	if( target->image != IMAGE_OBJ_NONE ) return;

	BOOL isHitMan = FALSE;
	for( int i = 0; i < MAN_NUM; ++i ) {
		int checkX = mManState[ i ].x / USE_OBJ_IMAGE_WIDTH + ( ( mManState[ i ].isLeft )? 0 : 1 );
		if( checkX != targetX || mManState[ i ].line != targetY ) continue;
		isHitMan = TRUE;
		break;
	}

	if( isHitMan ) return;

	for( int i = 0; i < ENTRANCE_PAIR_NUM; ++i ) {
		for( int j = 0; j < 2; ++j ) {
			if( mEntranceState[ i ][ j ] != mMoveTarget ) continue;
			mEntranceState[ i ][ j ] = target;
			break;
		}
	}
	target->image = mMoveTarget->image;
	mMoveTarget->image = IMAGE_OBJ_NONE;
}

void Book7::putLadder( int targetX, int targetY )
{
	ObjState* target = &mObjState[ targetY ][ targetX ];
	if( target->image != IMAGE_OBJ_NONE ) return;
	target->image = mMoveTarget->image;
	mMoveTarget->image = IMAGE_OBJ_NONE;
}

void Book7::putWall( int targetX, int targetY )
{
	ObjState* target = &mObjState[ targetY ][ targetX ];
	if( target->image != IMAGE_OBJ_NONE ) return;

	BOOL isHitMan = FALSE;
	for( int i = 0; i < MAN_NUM; ++i ) {
		int checkX = mManState[ i ].x / USE_OBJ_IMAGE_WIDTH + ( ( mManState[ i ].isLeft )? 0 : 1 );
		if( ( checkX != targetX && checkX != targetX + 1 ) || mManState[ i ].line != targetY ) continue;
		isHitMan = TRUE;
		break;
	}

	if( isHitMan ) return;

	target->image = mMoveTarget->image;
	mMoveTarget->image = IMAGE_OBJ_NONE;
}

void Book7::draw( HDC& hdc, MainParent* parent )
{
	for( int y = 0 ; y < OBJ_Y_NUM; ++y ) {
		for( int x = 0 ; x < OBJ_X_NUM; ++x ) {
			ObjState* target = &mObjState[ y ][ x ];
			mObjImage->drawWindowOr( x * USE_OBJ_IMAGE_WIDTH, y * USE_OBJ_IMAGE_HEIGHT, IMAGE_OBJ_FLOOR * USE_OBJ_IMAGE_WIDTH, 0, USE_OBJ_IMAGE_WIDTH, USE_OBJ_IMAGE_HEIGHT );
			if( target->image == IMAGE_OBJ_NONE ) continue;
			if( target->isHold ) {
				mObjImage->drawWindowOr( target->holdX, target->holdY, target->image * USE_OBJ_IMAGE_WIDTH, 0, USE_OBJ_IMAGE_WIDTH, USE_OBJ_IMAGE_HEIGHT );
			} else {
				mObjImage->drawWindowOr( x * USE_OBJ_IMAGE_WIDTH, y * USE_OBJ_IMAGE_HEIGHT, target->image * USE_OBJ_IMAGE_WIDTH, 0, USE_OBJ_IMAGE_WIDTH, USE_OBJ_IMAGE_HEIGHT );
			}
		}
	}
	
	for( int i = 0; i < MAN_NUM; ++i ) {
		drawMan( &mManState[ i ] );
	}
}

#include "Book7Man.h"


} // namespace Sequence