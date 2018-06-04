#include "ToneFactory.h"
#include "ImageFactory.h"
#include "SceneManager.h"

using namespace Image;

#include "DCBitmap.h"
#include "PixelBitmap.h"

namespace Main {

ToneFactory* ToneFactory::mInst = 0;

ToneFactory* ToneFactory::inst( void )
{
	return mInst;
}
void ToneFactory::create( HDC& hdc )
{
	if( mInst == 0 ) {
		mInst = new ToneFactory( hdc );
	}
}
void ToneFactory::destroy( void )
{
	if( mInst != 0 ) {
		delete mInst;
		mInst = 0;
	}
}

ToneFactory::ToneFactory( HDC& hdc )
{
	Main::ImageFactory* imageFactory = Main::ImageFactory::inst();
	Main::SceneManager* sceneManager = Main::SceneManager::inst();
	unsigned int windowWidth = sceneManager->mWindowWidth;
	unsigned int windowHeight = sceneManager->mWindowHeight;

	int toneNum = TONE_NONE;
	DCBitmap** setTone = new DCBitmap*[ toneNum ];
	DCBitmap* filter = imageFactory->loadDC( hdc, "resource\\tone.dad" );
	DCBitmap* newData = 0;

	int blockWidth = filter->mWidth / 15;
	for( int i = 0; i < toneNum; ++i ) {
		newData = new DCBitmap( hdc, windowWidth, windowHeight, 0xFF );
		if( i == 0 ) {
			setTone[ 0 ] = newData;
			continue;
		}
		for( unsigned int y = 0; y < windowHeight; y += blockWidth ) {
			for( unsigned int x = 0; x < windowWidth; x += blockWidth ) {
				filter->drawBlock( newData->mHdcBmp, x, y, blockWidth, ( i - 1 ) % 15 );
			}
		}
		setTone[ i ] = newData;
	}

	BitmapBase::mTone = setTone;

	delete filter;
	filter = 0;
}

ToneFactory::~ToneFactory()
{
	for( int i = 0; i < TONE_NONE; ++i ) {
		delete BitmapBase::mTone[ i ];
		BitmapBase::mTone[ i ] = 0;
	}
	delete[] BitmapBase::mTone;
	BitmapBase::mTone = 0;
}


} // namespace Main
