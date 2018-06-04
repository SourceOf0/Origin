#include <time.h>

#include "MainParent.h"
#include "MainChild.h"
#include "Book1.h"

#include "ImageFactory.h"
#include "SceneManager.h"
#include "HandManager.h"

#include "DCBitmap.h"

#define STATE_MAX 14
#define REST_COUNT 50

#define DOT_ANIME_MAX_NUM 11
#define FILTER_ANIME_MAX_NUM 5

namespace Sequence {

Book1::Book1( HDC& hdc, MainParent* parent ) : 
mToneMaxNum( TONE_NONE + FILTER_ANIME_MAX_NUM ),
mState( 0 ),
mToneIndex( 0 ),
mAnimeCount( 0 ),
mAnimeState( 0 ),
mScheduleIndex( VIEW_SCHEDULE_NUM )
{
	Main::ImageFactory* imageFactory = Main::ImageFactory::inst();
	int windowWidth = Main::SceneManager::windowWidth;
	int windowHeight = Main::SceneManager::windowHeight;

	srand( static_cast< unsigned >( time( NULL ) ) );

	char str[] = "resource\\book1_000.dad";
	for( int i = 0; i < BOOK1_IMAGE_NUM; ++i ) {
		str[ 16 ] = static_cast< char >( ( i / 10 ) + '0' );
		str[ 17 ] = static_cast< char >( ( i % 10 ) + '0' );
		mBmp[ i ] = imageFactory->loadDC( hdc, str );
	}

	mFilterBmp = imageFactory->loadDC( hdc, "resource\\smallFilter.dad" );
	mDotBmp = imageFactory->loadDC( hdc, "resource\\pointMask.dad" );

	mMaskBmp = new Image::DCBitmap( hdc, windowWidth, windowHeight );
	mMaskBmp->setBlack();

	mMainBmp = new Image::DCBitmap( hdc, windowWidth, windowHeight );
	mMainBmp->setBlack();

	nextMotion();
}

Book1::~Book1()
{
	for( int i = 0; i < BOOK1_IMAGE_NUM; ++i ) {
		delete mBmp[ i ];
		mBmp[ i ] = 0;
	}

	delete mFilterBmp;
	mFilterBmp = 0;

	delete mDotBmp;
	mDotBmp = 0;

	delete mMaskBmp;
	mMaskBmp = 0;

	delete mMainBmp;
	mMainBmp = 0;
}

void Book1::nextMotion( void )
{
	int windowWidth = Main::SceneManager::windowWidth;
	int windowHeight = Main::SceneManager::windowHeight;

	int setX = 0;
	int setY = 0;

	ImageID image = IMAGE_NONE;
	MaskID mask = MASK_NONE;

	mAnimeCount = 0;
	mAnimeState = 0;
	mToneIndex = mToneMaxNum - 1;
//	mState = STATE_MAX - 1;
	if( mScheduleIndex == VIEW_SCHEDULE_NUM ) {
		setSchedule();
	}
	mState = mSchedule[ mScheduleIndex++ ];

	switch( mState ) {
		case 0:
			setImage( &mImage[ 0 ], 0, 0, 0, IMAGE_01 );
			image = IMAGE_02;
			setImage( &mImage[ 1 ], windowWidth - mBmp[ image ]->mWidth, windowHeight - mBmp[ image ]->mHeight, 0, image );
			setImage( &mImage[ 2 ], 0, 0, 0, IMAGE_04 );

			mask = MASK_1;
			setX = windowWidth - mBmp[ mask ]->mWidth;
			setY = windowHeight - mBmp[ mask ]->mHeight;
			for( int i = 0; i < 4; ++i ) {
				setMask( &mMask[ i ], ( i / 2 ) * setX, ( i % 2 ) * setY, i % 2, mask );
			}
			break;

		case 1:
			image = IMAGE_03;
			setX = static_cast< int >( ( windowWidth - mBmp[ image ]->mWidth ) * 0.5 );
			setY = static_cast< int >( ( windowHeight - mBmp[ image ]->mHeight ) * 0.5 );
			setImage( &mImage[ 0 ], setX, setY, 0, image );
			break;

		case 2:
			setImage( &mImage[ 0 ], 0, 0, 0, IMAGE_05 );
			image = IMAGE_09;
			setImage( &mImage[ 1 ], windowWidth - mBmp[ image ]->mWidth, windowHeight - mBmp[ image ]->mHeight, 0, image );
			
			mask = MASK_4;
			setX = mBmp[ mask ]->mWidth;
			setY = mBmp[ mask ]->mHeight;
			for( int i = 0; i < 8; ++i ) {
				setMask( &mMask[ i ], ( i / 2 ) * setX - setX, ( i % 2 ) * setY - setY, i % 2, mask );
			}
			break;

		case 3:
			image = IMAGE_07;
			setX = static_cast< int >( ( windowWidth - mBmp[ image ]->mWidth ) * 0.5 );
			setY = static_cast< int >( ( windowHeight - mBmp[ image ]->mHeight ) * 0.5 );
			setImage( &mImage[ 0 ], setX, setY, 0, image );
			image = IMAGE_10;
			setX = static_cast< int >( ( windowWidth - mBmp[ image ]->mWidth ) * 1.0 );
			setY = static_cast< int >( ( windowHeight - mBmp[ image ]->mHeight ) * 0.0 );
			setImage( &mImage[ 1 ], setX, setY, 0, image );
			setX = static_cast< int >( ( windowWidth - mBmp[ image ]->mWidth ) * 0.7 );
			setY = static_cast< int >( ( windowHeight - mBmp[ image ]->mHeight ) * 0.3 );
			setImage( &mImage[ 2 ], setX, setY, 0, image );
			setX = static_cast< int >( ( windowWidth - mBmp[ image ]->mWidth ) * 0.3 );
			setY = static_cast< int >( ( windowHeight - mBmp[ image ]->mHeight ) * 0.7 );
			setImage( &mImage[ 3 ], setX, setY, 0, image );
			setX = static_cast< int >( ( windowWidth - mBmp[ image ]->mWidth ) * 0.0 );
			setY = static_cast< int >( ( windowHeight - mBmp[ image ]->mHeight ) * 1.0 );
			setImage( &mImage[ 4 ], setX, setY, 0, image );
			break;

		case 4:
			image = IMAGE_06;
			setX = static_cast< int >( ( windowWidth - mBmp[ image ]->mWidth ) * 0.5 );
			setImage( &mImage[ 0 ], setX, 0, 0, image );
			break;

		case 5:
			image = IMAGE_08;
			setX = static_cast< int >( ( windowWidth - mBmp[ image ]->mWidth ) * 0.5 );
			setY = static_cast< int >( ( windowHeight - mBmp[ image ]->mHeight ) * 0.5 );
			setImage( &mImage[ 0 ], setX, setY, 0, image );
			break;

		case 6:
			image = IMAGE_12;
			setX = static_cast< int >( ( windowWidth - mBmp[ image ]->mWidth ) * 0.5 );
			setY = static_cast< int >( ( windowHeight - mBmp[ image ]->mHeight ) * 0.5 );
			setImage( &mImage[ 0 ], setX, setY, 0, image );

			setX -= mFilterBmp->mWidth / FILTER_ANIME_MAX_NUM;
			for( int i = 0; i < BOOK1_MASK_NUM; ++i ) {
				setMask( &mMask[ i ], setX, -static_cast< int >( mFilterBmp->mWidth / FILTER_ANIME_MAX_NUM ), i, MASK_NONE );
			}
			break;

		case 7:
			image = IMAGE_13;
			setX = static_cast< int >( ( windowWidth - mBmp[ image ]->mWidth ) * 0.5 );
			setY = static_cast< int >( ( windowHeight - mBmp[ image ]->mHeight ) * 0.5 );
			setImage( &mImage[ 0 ], setX, setY, 0, image );
			mask = MASK_1;
			setX = static_cast< int >( ( windowWidth - mBmp[ mask ]->mWidth ) * 0.3 );
			setY = - static_cast< int >( mBmp[ mask ]->mHeight * 0.9 );
			for( int i = 0; i < 3; ++i ) {
				setMask( &mMask[ i ], setX + i * 50, ( i + 1 ) * setY, 0, mask );
			}
			break;

		case 8:
			image = IMAGE_14;
			setX = static_cast< int >( ( windowWidth - mBmp[ image ]->mWidth ) * 0.5 );
			setY = static_cast< int >( ( windowHeight - mBmp[ image ]->mHeight ) * 0.5 );
			setImage( &mImage[ 0 ], setX, setY, 0, image );
			mask = MASK_2;
			setMask( &mMask[ 0 ], ( rand() % windowWidth ), ( rand() % windowHeight ), 0, mask );
			break;

		case 9:
			image = IMAGE_15;
			setX = static_cast< int >( ( windowWidth - mBmp[ image ]->mWidth ) * 0.5 );
			setY = static_cast< int >( ( windowHeight - mBmp[ image ]->mHeight ) * 0.5 );
			setImage( &mImage[ 0 ], setX, setY, 0, image );
			break;

		case 10:
			image = IMAGE_16;
			setX = static_cast< int >( ( windowWidth - mBmp[ image ]->mWidth ) * 0.5 );
			setY = static_cast< int >( ( windowHeight - mBmp[ image ]->mHeight ) * 0.5 );
			setImage( &mImage[ 0 ], setX, setY, 0, image );
			mask = MASK_3;
			setX = static_cast< int >( mBmp[ mask ]->mWidth / 2 );
			setY = static_cast< int >( mBmp[ image ]->mHeight );
			for( int i = 0; i < BOOK1_MASK_NUM; ++i ) {
				setMask( &mMask[ i ], ( rand() % windowWidth ) - setX, setY + setY / 2 * ( rand() % 3 ) , ( rand() % 3 ) + 1, mask );
			}
			break;

		case 11:
			image = IMAGE_17;
			setX = static_cast< int >( ( windowWidth - mBmp[ image ]->mWidth ) * 0.5 );
			setY = static_cast< int >( ( windowHeight - mBmp[ image ]->mHeight ) * 0.5 );
			setImage( &mImage[ 0 ], setX, setY, 0, image );
			break;

		case 12:
			image = IMAGE_11;
			setX = static_cast< int >( ( windowWidth - mBmp[ image ]->mWidth ) * 0.5 );
			setY = static_cast< int >( ( windowHeight - mBmp[ image ]->mHeight ) * 0.5 );
			setImage( &mImage[ 0 ], setX, setY, 0, image );
			mState = 5;
			break;

		case 13:
			image = IMAGE_00;
			setX = static_cast< int >( ( windowWidth - mBmp[ image ]->mWidth ) * 0.5 );
			setY = static_cast< int >( ( windowHeight - mBmp[ image ]->mHeight ) * 0.5 );
			setImage( &mImage[ 0 ], setX, setY, 0, image );
			mState = 5;
			break;
	}
}

void Book1::setSchedule( void )
{
	BOOL setState[ STATE_MAX ];
	BOOL isFailure = TRUE;

	mScheduleIndex = 0;

	for( int i = 0; i < STATE_MAX; ++i ) {
		setState[ i ] = FALSE;
	}
	for( int j = 0; j < VIEW_SCHEDULE_NUM; ++j ) {
		isFailure = TRUE;
		while( isFailure ) {
			for( int i = 0; i < STATE_MAX; ++i ) {
				if( setState[ i ] ) continue;
				if( rand() % 3 > 0 ) continue;
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
	if( kind < TONE_NONE ) {
		Image::BitmapBase::mTone[ kind ]->drawImageAnd( targetHDC, 0, 0 );
		return;
	}
	int windowWidth = Main::SceneManager::windowWidth;
	int windowHeight = Main::SceneManager::windowHeight;
	int blockWidth = mFilterBmp->mWidth / FILTER_ANIME_MAX_NUM;
	kind = FILTER_ANIME_MAX_NUM - kind + TONE_NONE - 1;
	for( int y = 0; y < windowHeight; y += blockWidth ) {
		for( int x = 0; x < windowWidth; x += blockWidth ) {
			mFilterBmp->drawBlockAnd( targetHDC, x, y, blockWidth, kind );
		}
	}
}
void Book1::drawToneOr( HDC& targetHDC, int kind )
{
	if( kind < TONE_NONE ) {
		Image::BitmapBase::mTone[ kind ]->drawImageOr( targetHDC, 0, 0 );
		return;
	}
	int windowWidth = Main::SceneManager::windowWidth;
	int windowHeight = Main::SceneManager::windowHeight;
	int blockWidth = mFilterBmp->mWidth / FILTER_ANIME_MAX_NUM;
	kind = FILTER_ANIME_MAX_NUM - kind + TONE_NONE - 1;
	for( int y = 0; y < windowHeight; y += blockWidth ) {
		for( int x = 0; x < windowWidth; x += blockWidth ) {
			mFilterBmp->drawBlockOr( targetHDC, x, y, blockWidth, kind );
		}
	}
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
	if( mAnimeCount == mToneMaxNum * partition - 1 ) return TRUE;
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
	if( Main::HandManager::inst()->getX() > Main::SceneManager::windowWidth - 64 && Main::HandManager::inst()->getY() > Main::SceneManager::windowHeight - 64 ) {
		if( Main::SceneManager::isClick ) {
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