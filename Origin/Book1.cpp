#include <time.h>

#include "MainParent.h"
#include "MainChild.h"
#include "Book1.h"

#include "ImageFactory.h"
#include "SceneManager.h"
#include "HandManager.h"
#include "NoteManager.h"

#include "DCBitmap.h"

#define STATE_MAX 14
#define REST_COUNT 50

#define DOT_ANIME_MAX_NUM 11

namespace Sequence {

Book1::Book1( HDC& hdc, MainParent* parent ) : 
mState( -1 ),
mToneIndex( 0 ),
mAnimeCount( 0 ),
mAnimeState( 0 ),
mScheduleIndex( VIEW_SCHEDULE_NUM )
{
	Main::ImageFactory* imageFactory = Main::ImageFactory::inst();
	const int VIEW_WIDTH = Main::SceneManager::VIEW_WIDTH;
	const int VIEW_HEIGHT = Main::SceneManager::VIEW_HEIGHT;

	srand( static_cast< unsigned >( time( NULL ) ) );

	for( int i = 0; i < BOOK1_IMAGE_NUM; ++i ) {
		mBmp[ i ] = imageFactory->loadDC( hdc, IDR_DAD_BOOK1_000 + i );
	}

	mDotBmp = imageFactory->loadDC( hdc, IDR_DAD_POINTMASK );

	mMaskBmp = new Image::DCBitmap( hdc, VIEW_WIDTH, VIEW_HEIGHT );
	mMaskBmp->setBlack();

	mMainBmp = new Image::DCBitmap( hdc, VIEW_WIDTH, VIEW_HEIGHT );
	mMainBmp->setBlack();
}

Book1::~Book1()
{
	for( int i = 0; i < BOOK1_IMAGE_NUM; ++i ) {
		delete mBmp[ i ];
		mBmp[ i ] = 0;
	}

	delete mDotBmp;
	mDotBmp = 0;

	delete mMaskBmp;
	mMaskBmp = 0;

	delete mMainBmp;
	mMainBmp = 0;
}

void Book1::nextMotion( void )
{
	const int VIEW_WIDTH = Main::SceneManager::VIEW_WIDTH;
	const int VIEW_HEIGHT = Main::SceneManager::VIEW_HEIGHT;

	int setX = 0;
	int setY = 0;

	ImageID image = IMAGE_NONE;
	MaskID mask = MASK_NONE;

	mAnimeCount = 0;
	mAnimeState = 0;
	mToneIndex = TONE_NONE - 1;
	if( mScheduleIndex == VIEW_SCHEDULE_NUM ) {
		if( mState >= 0 ) Main::NoteManager::inst()->setNextPage( NOTE_BOOK1_2 );
		setSchedule();
	}
	mState = mSchedule[ mScheduleIndex++ ];

	switch( mState ) {
		case 0:
			setImage( &mImage[ 0 ], 0, 0, 0, IMAGE_01 );
			image = IMAGE_02;
			setImage( &mImage[ 1 ], VIEW_WIDTH - mBmp[ image ]->mWidth, VIEW_HEIGHT - mBmp[ image ]->mHeight, 0, image );
			setImage( &mImage[ 2 ], 0, 0, 0, IMAGE_04 );

			mask = MASK_1;
			setX = VIEW_WIDTH - mBmp[ mask ]->mWidth;
			setY = VIEW_HEIGHT - mBmp[ mask ]->mHeight;
			for( int i = 0; i < 4; ++i ) {
				setMask( &mMask[ i ], ( i / 2 ) * setX, ( i % 2 ) * setY, i % 2, mask );
			}
			break;

		case 1:
			image = IMAGE_03;
			setX = static_cast< int >( ( VIEW_WIDTH - mBmp[ image ]->mWidth ) * 0.5 );
			setY = static_cast< int >( ( VIEW_HEIGHT - mBmp[ image ]->mHeight ) * 0.5 );
			setImage( &mImage[ 0 ], setX, setY, 0, image );
			break;

		case 2:
			setImage( &mImage[ 0 ], 0, 0, 0, IMAGE_05 );
			image = IMAGE_09;
			setImage( &mImage[ 1 ], VIEW_WIDTH - mBmp[ image ]->mWidth, VIEW_HEIGHT - mBmp[ image ]->mHeight, 0, image );
			
			mask = MASK_4;
			setX = mBmp[ mask ]->mWidth;
			setY = mBmp[ mask ]->mHeight;
			for( int i = 0; i < 8; ++i ) {
				setMask( &mMask[ i ], ( i / 2 ) * setX - setX, ( i % 2 ) * setY - setY, i % 2, mask );
			}
			break;

		case 3:
			image = IMAGE_07;
			setX = static_cast< int >( ( VIEW_WIDTH - mBmp[ image ]->mWidth ) * 0.5 );
			setY = static_cast< int >( ( VIEW_HEIGHT - mBmp[ image ]->mHeight ) * 0.5 );
			setImage( &mImage[ 0 ], setX, setY, 0, image );
			image = IMAGE_10;
			setX = static_cast< int >( ( VIEW_WIDTH - mBmp[ image ]->mWidth ) * 1.0 );
			setY = static_cast< int >( ( VIEW_HEIGHT - mBmp[ image ]->mHeight ) * 0.0 );
			setImage( &mImage[ 1 ], setX, setY, 0, image );
			setX = static_cast< int >( ( VIEW_WIDTH - mBmp[ image ]->mWidth ) * 0.7 );
			setY = static_cast< int >( ( VIEW_HEIGHT - mBmp[ image ]->mHeight ) * 0.3 );
			setImage( &mImage[ 2 ], setX, setY, 0, image );
			setX = static_cast< int >( ( VIEW_WIDTH - mBmp[ image ]->mWidth ) * 0.3 );
			setY = static_cast< int >( ( VIEW_HEIGHT - mBmp[ image ]->mHeight ) * 0.7 );
			setImage( &mImage[ 3 ], setX, setY, 0, image );
			setX = static_cast< int >( ( VIEW_WIDTH - mBmp[ image ]->mWidth ) * 0.0 );
			setY = static_cast< int >( ( VIEW_HEIGHT - mBmp[ image ]->mHeight ) * 1.0 );
			setImage( &mImage[ 4 ], setX, setY, 0, image );
			Main::NoteManager::inst()->setNextPage( NOTE_BOOK1_1 );
			break;

		case 4:
			image = IMAGE_06;
			setX = static_cast< int >( ( VIEW_WIDTH - mBmp[ image ]->mWidth ) * 0.5 );
			setImage( &mImage[ 0 ], setX, 0, 0, image );
			break;

		case 5:
			image = IMAGE_08;
			setX = static_cast< int >( ( VIEW_WIDTH - mBmp[ image ]->mWidth ) * 0.5 );
			setY = static_cast< int >( ( VIEW_HEIGHT - mBmp[ image ]->mHeight ) * 0.5 );
			setImage( &mImage[ 0 ], setX, setY, 0, image );
			break;

		case 6:
			image = IMAGE_12;
			setX = static_cast< int >( ( VIEW_WIDTH - mBmp[ image ]->mWidth ) * 0.5 );
			setY = static_cast< int >( ( VIEW_HEIGHT - mBmp[ image ]->mHeight ) * 0.5 );
			setImage( &mImage[ 0 ], setX, setY, 0, image );

			for( int i = 0; i < BOOK1_MASK_NUM; ++i ) {
				setMask( &mMask[ i ], 0, 0, i, MASK_NONE );
			}
			break;

		case 7:
			image = IMAGE_13;
			setX = static_cast< int >( ( VIEW_WIDTH - mBmp[ image ]->mWidth ) * 0.5 );
			setY = static_cast< int >( ( VIEW_HEIGHT - mBmp[ image ]->mHeight ) * 0.5 );
			setImage( &mImage[ 0 ], setX, setY, 0, image );
			mask = MASK_1;
			setX = static_cast< int >( ( VIEW_WIDTH - mBmp[ mask ]->mWidth ) * 0.3 );
			setY = - static_cast< int >( mBmp[ mask ]->mHeight * 0.9 );
			for( int i = 0; i < 3; ++i ) {
				setMask( &mMask[ i ], setX + i * 50, ( i + 1 ) * setY, 0, mask );
			}
			break;

		case 8:
			image = IMAGE_14;
			setX = static_cast< int >( ( VIEW_WIDTH - mBmp[ image ]->mWidth ) * 0.5 );
			setY = static_cast< int >( ( VIEW_HEIGHT - mBmp[ image ]->mHeight ) * 0.5 );
			setImage( &mImage[ 0 ], setX, setY, 0, image );
			mask = MASK_2;
			setMask( &mMask[ 0 ], ( rand() % VIEW_WIDTH ), ( rand() % VIEW_HEIGHT ), 0, mask );
			break;

		case 9:
			image = IMAGE_15;
			setX = static_cast< int >( ( VIEW_WIDTH - mBmp[ image ]->mWidth ) * 0.5 );
			setY = static_cast< int >( ( VIEW_HEIGHT - mBmp[ image ]->mHeight ) * 0.5 );
			setImage( &mImage[ 0 ], setX, setY, 0, image );
			Main::NoteManager::inst()->setNextPage( NOTE_BOOK1_3 );
			break;

		case 10:
			image = IMAGE_16;
			setX = static_cast< int >( ( VIEW_WIDTH - mBmp[ image ]->mWidth ) * 0.5 );
			setY = static_cast< int >( ( VIEW_HEIGHT - mBmp[ image ]->mHeight ) * 0.5 );
			setImage( &mImage[ 0 ], setX, setY, 0, image );
			mask = MASK_3;
			setX = static_cast< int >( mBmp[ mask ]->mWidth / 2 );
			setY = static_cast< int >( mBmp[ image ]->mHeight );
			for( int i = 0; i < 5; ++i ) {
				setMask( &mMask[ i ], ( rand() % VIEW_WIDTH ) - setX, setY + setY / 2 * ( rand() % 3 ), ( rand() % 3 ) + 2, mask );
			}
			break;

		case 11:
			image = IMAGE_17;
			setX = static_cast< int >( ( VIEW_WIDTH - mBmp[ image ]->mWidth ) * 0.5 );
			setY = static_cast< int >( ( VIEW_HEIGHT - mBmp[ image ]->mHeight ) * 0.5 );
			setImage( &mImage[ 0 ], setX, setY, 0, image );
			Main::NoteManager::inst()->setNextPage( NOTE_BOOK1_1 );
			break;

		case 12:
			image = IMAGE_11;
			setX = static_cast< int >( ( VIEW_WIDTH - mBmp[ image ]->mWidth ) * 0.5 );
			setY = static_cast< int >( ( VIEW_HEIGHT - mBmp[ image ]->mHeight ) * 0.5 );
			setImage( &mImage[ 0 ], setX, setY, 0, image );
			mState = 5;
			Main::NoteManager::inst()->setNextPage( NOTE_BOOK1_1 );
			break;

		case 13:
			image = IMAGE_00;
			setX = static_cast< int >( ( VIEW_WIDTH - mBmp[ image ]->mWidth ) * 0.5 );
			setY = static_cast< int >( ( VIEW_HEIGHT - mBmp[ image ]->mHeight ) * 0.5 );
			setImage( &mImage[ 0 ], setX, setY, 0, image );
			mState = 5;
			Main::NoteManager::inst()->setNextPage( NOTE_BOOK1_3 );
			break;
	}
}

void Book1::setSchedule( void )
{
	BOOL setState[ STATE_MAX ];
	BOOL isFailure = TRUE;

	mScheduleIndex = 0;

/*	mSchedule[ 0 ] = 0;
	mSchedule[ 1 ] = 1;
	mSchedule[ 2 ] = 4;
	mSchedule[ 3 ] = 7;
	mSchedule[ 4 ] = 8;
	mSchedule[ 5 ] = 9;
	mSchedule[ 6 ] = 10;
	mSchedule[ 7 ] = 11;
	mSchedule[ 8 ] = 12;
	mSchedule[ 9 ] = 13;*/

	for( int i = 0; i < STATE_MAX; ++i ) {
		setState[ i ] = FALSE;
	}
	for( int j = 0; j < VIEW_SCHEDULE_NUM; ++j ) {
		isFailure = TRUE;
		for( int i = 0; i < STATE_MAX; ++i ) {
			if( setState[ i ] ) continue;
			if( rand() % 3 > 0 ) continue;
			isFailure = FALSE;
			setState[ i ] = TRUE;
			mSchedule[ j ] = i;
			break;
		}
		if( isFailure ) {
			for( int i = 0; i < STATE_MAX; ++i ) {
				if( setState[ i ] ) continue;
				isFailure = FALSE;
				setState[ i ] = TRUE;
				mSchedule[ j ] = i;
				break;
			}
		}
	}
}

void Book1::setImage( ImageState* target, int x, int y, int count, ImageID kind )
{
	target->x = x;
	target->y = y;
	target->count = count;
	target->kind = kind;
}
void Book1::setMask( MaskState* target, int x, int y, int count, MaskID kind )
{
	target->x = x;
	target->y = y;
	target->count = count;
	target->kind = kind;
}

void Book1::drawTone( HDC& targetHDC, int kind )
{
	Image::BitmapBase::mTone[ kind ]->drawImageAnd( targetHDC, 0, 0 );
}
void Book1::drawToneOr( HDC& targetHDC, int kind )
{
	Image::BitmapBase::mTone[ kind ]->drawImageOr( targetHDC, 0, 0 );
}

void Book1::drawDot( HDC& targetHDC, int x, int y, int kind )
{
	mDotBmp->drawBlockOr( targetHDC, x, y, static_cast< int >( mDotBmp->mWidth / DOT_ANIME_MAX_NUM ), kind );
}
void Book1::drawDotAnd( HDC& targetHDC, int x, int y, int kind )
{
	mDotBmp->drawBlockAnd( targetHDC, x, y, static_cast< int >( mDotBmp->mWidth / DOT_ANIME_MAX_NUM ), kind );
}

BOOL Book1::fadeIn( int partition )
{
	if( mAnimeCount == TONE_NONE * partition - 1 ) return TRUE;
	if( ++mAnimeCount % partition == 0 ) --mToneIndex;
	return FALSE;
}
BOOL Book1::fadeOut( int partition )
{
	if( --mAnimeCount == 0 ) return TRUE;
	if( mAnimeCount % partition == 0 ) ++mToneIndex;
	return FALSE;
}


#include "Book1Motion.h"

void Book1::update( MainParent* parent )
{
	switch( mState ) {
		case -1:
			if( ++mAnimeCount > 50 ) {
				nextMotion();
			}
			break;
		case 0:
			motion1();
			break;
		case 1:
			motion2();
			break;
		case 2:
			motion3();
			break;
		case 3:
			motion4();
			break;
		case 4:
			motion5();
			break;
		case 5:
			motion6();
			break;
		case 6:
			motion7();
			break;
		case 7:
			motion8();
			break;
		case 8:
			motion9();
			break;
		case 9:
			motion10();
			break;
		case 10:
			motion11();
			break;
		case 11:
			motion12();
			break;
	}

	Main::HandManager::inst()->setState( Main::HandManager::HAND_NORMAL );
	if( Main::HandManager::inst()->getX() > Main::SceneManager::VIEW_WIDTH - BOOK_CORNAR_HIT_SIZE && Main::HandManager::inst()->getY() > Main::SceneManager::VIEW_HEIGHT - BOOK_CORNAR_HIT_SIZE ) {
		if( Main::HandManager::isClick ) {
			parent->moveTo( parent->SEQ_ROOM );
		} else {
			Main::HandManager::inst()->setState( Main::HandManager::HAND_CLOSE );
		}
	}
}

void Book1::draw( HDC& hdc, MainParent* parent )
{
	mMainBmp->drawWindow();
}

} // namespace Sequence