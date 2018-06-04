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
#define STAY_COUNT 30

namespace Sequence {

Book7::Book7( HDC& hdc, MainParent* parent ) :
mMoveTarget( 0 )
{
	Main::ImageFactory* imageFactory = Main::ImageFactory::inst();
	int windowWidth = Main::SceneManager::windowWidth;
	int windowHeight = Main::SceneManager::windowHeight;
	int i = -1;

	mManImageArr[ ++i ] = imageFactory->loadDC( hdc, "resource\\man_stay.dad" );
	mManImageArr[ ++i ] = imageFactory->loadDC( hdc, "resource\\man_walk.dad" );
	mManImageArr[ ++i ] = imageFactory->loadDC( hdc, "resource\\man_ladder.dad" );

	mObjImage = imageFactory->loadDC( hdc, "resource\\map_objects.dad" );

	for( int y = 0; y < OBJ_Y_NUM; ++y ) {
		for( int x = 0; x < OBJ_X_NUM; ++x ) {
			ObjState* target = &mObjState[ y ][ x ];
			target->x = x * USE_OBJ_IMAGE_WIDTH;
			target->y = y * USE_OBJ_IMAGE_HEIGHT;
			target->image = IMAGE_OBJ_NONE;
			target->useNum = 0;
			target->isHold = FALSE;
		}
	}
	mObjState[ 5 ][ 10 ].image = IMAGE_OBJ_LADDER;
	mObjState[ 6 ][ 6 ].image = IMAGE_OBJ_WALL;

	mObjState[ 7 ][ 7 ].image = IMAGE_OBJ_ENTRANCE;
	mEntranceState[ 0 ].indexX = 7;
	mEntranceState[ 0 ].indexY = 7;
	mEntranceState[ 0 ].target = &mObjState[ 7 ][ 7 ];

	mObjState[ 10 ][ 10 ].image = IMAGE_OBJ_ENTRANCE;
	mEntranceState[ 1 ].indexX = 10;
	mEntranceState[ 1 ].indexY = 10;
	mEntranceState[ 1 ].target = &mObjState[ 10 ][ 10 ];

	for( int i = 0; i < MAN_NUM; ++i ) {
		ManState* target = &mManState[ i ];
		target->x = USE_OBJ_IMAGE_WIDTH * 20;
		target->line = 9 + i * 2;
		target->image = IMAGE_MAN_STAY;
		target->count = 0;
		target->state = 0;
		target->target = 0;
		target->isLeft = TRUE;
		target->isEnter = FALSE;
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
//	int windowHeight = Main::SceneManager::windowHeight;
	POINT mousePos;
	GetCursorPos( &mousePos );
	int mouseX = mousePos.x;
	int mouseY = mousePos.y;
	BOOL isClick = Main::SceneManager::isClick;
	BOOL isMouseDown = Main::SceneManager::isMouseDown;
	BOOL wasHit = FALSE;

	Main::HandManager::inst()->setState( Main::HandManager::HAND_NORMAL );

	if( mMoveTarget == 0 ) {
		ObjState* target = &mObjState[ mouseY / USE_OBJ_IMAGE_HEIGHT ][ mouseX / USE_OBJ_IMAGE_WIDTH ];
		if( target->image != IMAGE_OBJ_NONE && target->useNum == 0 ) {
			if( isMouseDown ) {
				mMoveTarget = target;
				target->isHold = TRUE;
				target->x = mouseX - USE_OBJ_IMAGE_WIDTH_HALF;
				target->y = mouseY - USE_OBJ_IMAGE_HEIGHT_HALF;
				Main::HandManager::inst()->setState( Main::HandManager::HAND_HOLD_AFTER );
			} else {
				Main::HandManager::inst()->setState( Main::HandManager::HAND_HOLD_BEFORE );
			}
		}
	} else {
		if( isMouseDown ) {
			mMoveTarget->x = mouseX - USE_OBJ_IMAGE_WIDTH_HALF;
			mMoveTarget->y = mouseY - USE_OBJ_IMAGE_HEIGHT_HALF;
			Main::HandManager::inst()->setState( Main::HandManager::HAND_HOLD_AFTER );
		} else {
			ObjState* target = &mObjState[ mouseY / USE_OBJ_IMAGE_HEIGHT ][ mouseX / USE_OBJ_IMAGE_WIDTH ];
			if( target->image == IMAGE_OBJ_NONE ) {
				BOOL isHitMan = FALSE;
				if( target->image != IMAGE_OBJ_LADDER ) {
					int targetX = mouseX / USE_OBJ_IMAGE_WIDTH;
					int targetY = mouseY / USE_OBJ_IMAGE_HEIGHT;
					for( int i = 0; i < MAN_NUM; ++i ) {
						if( ( mManState[ i ].x / USE_OBJ_IMAGE_WIDTH ) != targetX || mManState[ i ].line != targetY ) continue;
						isHitMan = TRUE;
						break;
					}
				}
				if( !isHitMan ) {
					if( mEntranceState[ 0 ].target == mMoveTarget ) {
						mEntranceState[ 0 ].indexX = mouseX / USE_OBJ_IMAGE_WIDTH;
						mEntranceState[ 0 ].indexY = mouseY / USE_OBJ_IMAGE_HEIGHT;
						mEntranceState[ 0 ].target = target;
					} else if( mEntranceState[ 1 ].target == mMoveTarget ) {
						mEntranceState[ 1 ].indexX = mouseX / USE_OBJ_IMAGE_WIDTH;
						mEntranceState[ 1 ].indexY = mouseY / USE_OBJ_IMAGE_HEIGHT;
						mEntranceState[ 1 ].target = target;
					}
					target->image = mMoveTarget->image;
					mMoveTarget->image = IMAGE_OBJ_NONE;
				}
			}
			mMoveTarget->x = 0;
			mMoveTarget->y = 0;
			mMoveTarget->isHold = FALSE;
			mMoveTarget = 0;
			Main::HandManager::inst()->setState( Main::HandManager::HAND_HOLD_BEFORE );
		}
	}

	for( int i = 0; i < MAN_NUM; ++i ) {
		moveMan( &mManState[ i ] );
	}
}

void Book7::draw( HDC& hdc, MainParent* parent )
{
	for( int y = 0 ; y < OBJ_Y_NUM; ++y ) {
		for( int x = 0 ; x < OBJ_X_NUM; ++x ) {
			ObjState* target = &mObjState[ y ][ x ];
			mObjImage->drawWindowOr( x * USE_OBJ_IMAGE_WIDTH, y * USE_OBJ_IMAGE_HEIGHT, IMAGE_OBJ_FLOOR * USE_OBJ_IMAGE_WIDTH, 0, USE_OBJ_IMAGE_WIDTH, USE_OBJ_IMAGE_HEIGHT );
			if( target->image == IMAGE_OBJ_NONE ) continue;
			if( target->isHold ) {
				mObjImage->drawWindowOr( target->x, target->y, target->image * USE_OBJ_IMAGE_WIDTH, 0, USE_OBJ_IMAGE_WIDTH, USE_OBJ_IMAGE_HEIGHT );
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