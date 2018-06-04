#include "MainParent.h"
#include "MainChild.h"
#include "Title.h"

#include "ImageFactory.h"
#include "SceneManager.h"
#include "SoundManager.h"

#include "PixelBitmap.h"
#include "DCBitmap.h"

#include <stdlib.h>

#define POINT_MASK_ANIME_NUM 11
#define POINT_MASK_FRAME_COUNT 2
#define POINT_TRACK_DIS 20
#define CHANGE_COUNT_MAX 200
#define FILTER_FRAME_COUNT 2

namespace Sequence {

Title::Title( HDC& hdc )
{
	Main::ImageFactory* imageFactory = Main::ImageFactory::inst();
	Main::SceneManager* sceneManager = Main::SceneManager::inst();
	int windowWidth = sceneManager->mWindowWidth;
	int windowHeight = sceneManager->mWindowHeight;

	for( int i = 0; i < POINT_TRACK_NUM; ++i ) {
		mPointTrack[i].x = -1;
		mPointTrack[i].y = -1;
		mPointTrack[i].count = 0;
	}

	Image::PixelBitmap* tempBmp;

	tempBmp = imageFactory->load( "pic03.dad" );
	mBackBmp1 = new Image::DCBitmap( hdc, tempBmp );
	delete tempBmp;
	mBackBmp1->mX = ( float )( windowWidth - mBackBmp1->mWidth ) / 2;
	mBackBmp1->mY = ( float )( windowHeight - mBackBmp1->mHeight ) / 2;

	tempBmp = imageFactory->load( "pic02.dad" );
	mBackBmp2 = new Image::DCBitmap( hdc, tempBmp );
	delete tempBmp;
	mBackBmp2->mX = ( float )( windowWidth - mBackBmp2->mWidth ) / 2;
	mBackBmp2->mY = ( float )( windowHeight - mBackBmp2->mHeight ) / 2;

	tempBmp = imageFactory->load( "pic01.dad" );
	mBackBmp3 = new Image::DCBitmap( hdc, tempBmp );
	delete tempBmp;
	mBackBmp3->mX = ( float )( windowWidth - mBackBmp3->mWidth ) / 2;
	mBackBmp3->mY = ( float )( windowHeight - mBackBmp3->mHeight ) / 2;

	tempBmp = imageFactory->load( "frame.dad" );
	mFrontBmp = new Image::DCBitmap( hdc, tempBmp );
	delete tempBmp;
	mFrontBmp->mX = ( float )( windowWidth - mFrontBmp->mWidth ) / 2;
	mFrontBmp->mY = ( float )( windowHeight - mFrontBmp->mHeight ) / 2;

	tempBmp = new Image::PixelBitmap( windowWidth, windowHeight, windowWidth * windowHeight / 8 );
	mMaskBmp = new Image::DCBitmap( hdc, tempBmp );
	delete tempBmp;

	tempBmp = imageFactory->load( "smallFilter.dad" );
	mMaskBlockBmp = new Image::DCBitmap( hdc, tempBmp );
	delete tempBmp;

	tempBmp = imageFactory->load( "pointMask.dad" );
	mPointBmp = new Image::DCBitmap( hdc, tempBmp );
	delete tempBmp;

	mCount = FILTER_FRAME_COUNT;
	mChangeCount = CHANGE_COUNT_MAX;
	mBackIndex = 1;
	mOldMousePos.x = -1;
	mOldMousePos.y = -1;
}

Title::~Title()
{
	delete mBackBmp1;
	mBackBmp1 = 0;

	delete mBackBmp2;
	mBackBmp2 = 0;

	delete mBackBmp3;
	mBackBmp3 = 0;

	delete mFrontBmp;
	mFrontBmp = 0;

	delete mMaskBmp;
	mMaskBmp = 0;

	delete mMaskBlockBmp;
	mMaskBlockBmp = 0;

	delete mPointBmp;
	mPointBmp = 0;
}

void Title::update( HDC& hdc, MainParent* parent )
{
	Main::SceneManager* sceneManager = Main::SceneManager::inst();
	int windowWidth = sceneManager->mWindowWidth;
	int windowHeight = sceneManager->mWindowHeight;
	
	if( mCount < 0 ) {
		( rand() * 1.0 / RAND_MAX > 0.05 ) ? mCount = FILTER_FRAME_COUNT : mCount = FILTER_FRAME_COUNT * 5 ;
	}
	--mCount;
	int blockWidth = mMaskBlockBmp->mWidth / 5;
	for( int y = 0; y < windowHeight; y += blockWidth ) {
		for( int x = 0; x < windowWidth; x += blockWidth ) {
			mMaskBlockBmp->drawBlock( mMaskBmp->mHdcBmp, x, y, blockWidth, (int)(mCount / FILTER_FRAME_COUNT) );
		}
	}

	if( sceneManager->mIsMouseDown ) {
//		Main::SoundManager::inst()->play();
		setPointMask();
		mChangeCount = CHANGE_COUNT_MAX;
	} else {
		mOldMousePos.x = -1;
		mOldMousePos.y = -1;
//		Main::SoundManager::inst()->stop();
	}
	int setCount = POINT_MASK_ANIME_NUM * POINT_MASK_FRAME_COUNT;
	int pointWidth = mPointBmp->mWidth / POINT_MASK_ANIME_NUM;
	for( int i = 0; i < POINT_TRACK_NUM; ++i ) {
		if( mPointTrack[i].count <= 0 ) continue;
		if( mPointTrack[i].count >= setCount ) {
			mPointBmp->drawBlockOr( mMaskBmp->mHdcBmp, mPointTrack[i].x - pointWidth / 2, mPointTrack[i].y - pointWidth / 2, pointWidth, POINT_MASK_ANIME_NUM - 1 - (int)( ( mPointTrack[i].count - setCount ) / POINT_MASK_FRAME_COUNT ) );
		} else {
			mPointBmp->drawBlockOr( mMaskBmp->mHdcBmp, mPointTrack[i].x - pointWidth / 2, mPointTrack[i].y - pointWidth / 2, pointWidth, (int)( mPointTrack[i].count / POINT_MASK_FRAME_COUNT ) );
		}
		--mPointTrack[i].count;
	}

	--mChangeCount;
	if( mChangeCount <= 0 ) {
		mChangeCount = CHANGE_COUNT_MAX;
		mCount = FILTER_FRAME_COUNT * 5;
		++mBackIndex;
	}
	switch( mBackIndex ) {
		case 4:
			mBackIndex = 1;
		case 1:
			mBackBmp1->drawWindow();
			break;
		case 2:
			mBackBmp2->drawWindow();
			break;
		case 3:
			mBackBmp3->drawWindow();
			break;
	}
	mMaskBmp->drawWindowAnd();
	mFrontBmp->drawWindowAnd();
}

int Title::setPointMask( void )
{
	POINT mousePos;
	GetCursorPos( &mousePos );

	int setCount = POINT_MASK_ANIME_NUM * POINT_MASK_FRAME_COUNT;
	if( ( mOldMousePos.x < mousePos.x - POINT_TRACK_DIS || mOldMousePos.x > mousePos.x + POINT_TRACK_DIS )
		|| ( mOldMousePos.y < mousePos.y - POINT_TRACK_DIS || mOldMousePos.y > mousePos.y + POINT_TRACK_DIS ) ) { 
		for( int i = 0; i < POINT_TRACK_NUM; ++i ) {
			if( mPointTrack[i].count > 0 ) continue;
			mPointTrack[i].x = mousePos.x;
			mPointTrack[i].y = mousePos.y;
			mPointTrack[i].count = setCount * 2;
			break;
		}
		mOldMousePos.x = mousePos.x;
		mOldMousePos.y = mousePos.y;
	}

	return 0;
}

} // namespace Sequence