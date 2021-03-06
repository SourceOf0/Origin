#include "MainParent.h"
#include "MainChild.h"
#include "Book4.h"

#include "ImageFactory.h"
#include "SceneManager.h"
#include "HandManager.h"
#include "NoteManager.h"

#include "DCBitmap.h"

#define USE_BALL_IMAGE_SIZE 128
#define USE_BALL_IMAGE_SIZE_HALF 64
#define USE_BOARD_IMAGE_SIZE 288
#define USE_SPLASH_IMAGE_SIZE 32
#define USE_PIECE_IMAGE_SIZE 32
#define ANIME_SPEED 4
#define MOVE_SPEED 8
#define FALL_SPEED 13

namespace Sequence {

Book4::Book4( HDC& hdc, MainParent* parent ) :
mWasFall( FALSE ),
mWasKeep( FALSE )
{
	Main::ImageFactory* imageFactory = Main::ImageFactory::inst();
	const int VIEW_HEIGHT = Main::SceneManager::VIEW_HEIGHT;
	int i = -1;

	mBallImageArr[ ++i ] = imageFactory->loadDC( hdc, IDR_DAD_BALL );
	mBallImageArr[ ++i ] = imageFactory->loadDC( hdc, IDR_DAD_BALL_LEFT );
	mBallImageArr[ ++i ] = imageFactory->loadDC( hdc, IDR_DAD_BALL_RIGHT );
	mBallImageArr[ ++i ] = imageFactory->loadDC( hdc, IDR_DAD_BALL_STOP );
	mBallImageArr[ ++i ] = imageFactory->loadDC( hdc, IDR_DAD_BALL_JUMP );
	mBallImageArr[ ++i ] = imageFactory->loadDC( hdc, IDR_DAD_BALL_FALL );
	mBallImageArr[ ++i ] = imageFactory->loadDC( hdc, IDR_DAD_BALL_SHAKE );

	mBoardImage = imageFactory->loadDC( hdc, IDR_DAD_BOARD );

	mSplashImage = imageFactory->loadDC( hdc, IDR_DAD_SPLASH );

	mPieceImage = imageFactory->loadDC( hdc, IDR_DAD_PIECE );

	resetBall();

	mBoardState.x = 0;
	mBoardState.y = ( VIEW_HEIGHT - USE_BOARD_IMAGE_SIZE ) / 2 + 50;
	mBoardState.state = 0;
	mBoardState.count = 0;

	for( int i = 0; i < MAX_SPLASH_NUM; ++i ) {
		SplashState* target = &mSplashState[ i ];
		target->x = 0;
		target->y = 0;
		target->vx = 0;
		target->vy = 0;
		target->count = 0;
		target->kind = -1;
	}

	for( int i = 0; i < MAX_PIECE_NUM; ++i ) {
		PieceState* target = &mPieceState[ i ];
		target->x = 0;
		target->y = 0;
		target->vx = 0;
		target->vy = 0;
		target->count = 0;
		target->kind = -1;
	}
}

Book4::~Book4()
{
	for( int i = 0; i < IMAGE_BALL_NONE; ++i ) {
		delete mBallImageArr[ i ];
		mBallImageArr[ i ] = 0;
	}

	delete mBoardImage;
	mBoardImage = 0;

	delete mSplashImage;
	mSplashImage = 0;

	delete mPieceImage;
	mPieceImage = 0;

	if( mWasFall ) {
		if( mWasKeep ) {
			Main::NoteManager::inst()->setNextPage( NOTE_BOOK4_2 );
		} else {
			Main::NoteManager::inst()->setNextPage( NOTE_BOOK4_1 );
		}
	} else if( mWasKeep ) {
		Main::NoteManager::inst()->setNextPage( NOTE_BOOK4_3 );
	}
}

void Book4::update( MainParent* parent )
{
	const int VIEW_HEIGHT = Main::SceneManager::VIEW_HEIGHT;
	int mouseX = Main::HandManager::inst()->getX();
	int mouseY = Main::HandManager::inst()->getY();
	BOOL isClick = Main::HandManager::isClick;
	BOOL isMouseDown = Main::HandManager::isMouseDown;
	BOOL wasHit = FALSE;

	Main::HandManager::inst()->setState( Main::HandManager::HAND_NORMAL );

	moveBall();

	if( mBoardState.state == 1 ) {
		mBoardState.count += 2;
		if( mBoardState.count >= static_cast< int >( ( mBoardImage->mWidth / USE_BOARD_IMAGE_SIZE - 1 ) * ANIME_SPEED ) ) {
			mBoardState.state = 0;
			mBoardState.count = 0;
		}
	}

	for( int i = 0 ; i < MAX_SPLASH_NUM; ++i ) {
		SplashState* target = &mSplashState[ i ];
		if( target->kind < 0 ) continue;
		target->x += target->vx;
		target->y += target->vy;
		target->vy += 1;
		if( target->count < static_cast< int >( ( mSplashImage->mWidth / USE_SPLASH_IMAGE_SIZE - 1 ) * ANIME_SPEED ) ) {
			++target->count;
		} else {
			if( target->kind > 3 && target->kind < 7 ) {
				++target->kind;
				target->count = static_cast< int >( ( mSplashImage->mWidth / USE_SPLASH_IMAGE_SIZE - 2 ) * ANIME_SPEED );
			} else {
				target->count = static_cast< int >( ( mSplashImage->mWidth / USE_SPLASH_IMAGE_SIZE - 1 ) * ANIME_SPEED );
			}
		}
		if( target->y > VIEW_HEIGHT ) target->kind = -1;
	}

	for( int i = 0 ; i < MAX_PIECE_NUM; ++i ) {
		PieceState* target = &mPieceState[ i ];
		if( target->kind < 0 ) continue;
		target->x += target->vx;
		target->y += target->vy;
		target->vy += 1;
		target->count += ANIME_SPEED;
		if( target->count >= static_cast< int >( ( mSplashImage->mWidth / USE_SPLASH_IMAGE_SIZE ) * ANIME_SPEED ) ) {
			target->count = 0;
		}
		if( target->y > VIEW_HEIGHT ) target->kind = -1;
	}

	if( mouseX > Main::SceneManager::VIEW_WIDTH - BOOK_CORNAR_HIT_SIZE && mouseY > VIEW_HEIGHT - BOOK_CORNAR_HIT_SIZE ) {
		if( Main::HandManager::isClick ) {
			Main::HandManager::inst()->setState( Main::HandManager::HAND_NORMAL );
			parent->moveTo( parent->SEQ_ROOM );
		} else {
			Main::HandManager::inst()->setState( Main::HandManager::HAND_CLOSE );
		}
	}
}

void Book4::draw( HDC& hdc, MainParent* parent )
{
	mBallImageArr[ mBallState.image ]->drawWindowOr( mBallState.x, mBallState.y, static_cast< int >( mBallState.count / ANIME_SPEED ) * USE_BALL_IMAGE_SIZE, 0, USE_BALL_IMAGE_SIZE, USE_BALL_IMAGE_SIZE );

	mBoardImage->drawWindowOr( mBoardState.x, mBoardState.y, mBoardImage->mWidth - USE_BOARD_IMAGE_SIZE, 0, USE_BOARD_IMAGE_SIZE, USE_BOARD_IMAGE_SIZE );
	mBoardImage->drawWindowOr( USE_BOARD_IMAGE_SIZE + mBoardState.x, mBoardState.y, static_cast< int >( mBoardState.count / ANIME_SPEED ) * USE_BOARD_IMAGE_SIZE, 0, USE_BOARD_IMAGE_SIZE, USE_BOARD_IMAGE_SIZE );
	
	for( int i = 0 ; i < MAX_SPLASH_NUM; ++i ) {
		SplashState* target = &mSplashState[ i ];
		if( target->kind < 0 ) continue;
		mSplashImage->drawWindowOr( target->x, target->y, static_cast< int >( target->count / ANIME_SPEED ) * USE_SPLASH_IMAGE_SIZE, target->kind * USE_SPLASH_IMAGE_SIZE, USE_SPLASH_IMAGE_SIZE, USE_SPLASH_IMAGE_SIZE );
	}

	for( int i = 0 ; i < MAX_PIECE_NUM; ++i ) {
		PieceState* target = &mPieceState[ i ];
		if( target->kind < 0 ) continue;
		mPieceImage->drawWindowOr( target->x, target->y, static_cast< int >( target->count / ANIME_SPEED ) * USE_PIECE_IMAGE_SIZE, target->kind * USE_PIECE_IMAGE_SIZE, USE_PIECE_IMAGE_SIZE, USE_PIECE_IMAGE_SIZE );
	}
}

#include "Book4Ball.h"

} // namespace Sequence