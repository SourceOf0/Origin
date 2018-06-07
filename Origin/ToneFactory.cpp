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
	const unsigned int VIEW_WIDTH = Main::SceneManager::VIEW_WIDTH;
	const unsigned int VIEW_HEIGHT = Main::SceneManager::VIEW_HEIGHT;

	int toneNum = TONE_NONE;
	DCBitmap** setTone = new DCBitmap*[ toneNum ];
	DCBitmap* newData = 0;
	DCBitmap* filter = imageFactory->loadDC( hdc, "resource\\tone.dad" );

	int setToneIndex = 0;
	int setToneNum = 15;
	int blockWidth = filter->mWidth / setToneNum;
	for( int i = 0; i < setToneNum; ++i ) {
		newData = new DCBitmap( hdc, VIEW_WIDTH, VIEW_HEIGHT, 0xFF );
		if( i == 0 ) {
			setTone[ setToneIndex++ ] = newData;
			continue;
		}
		for( unsigned int y = 0; y < VIEW_HEIGHT; y += blockWidth ) {
			for( unsigned int x = 0; x < VIEW_WIDTH; x += blockWidth ) {
				filter->drawBlock( newData->mHdcBmp, x, y, blockWidth, ( i - 1 ) % setToneNum );
			}
		}
		setTone[ setToneIndex++ ] = newData;
	}
	delete filter;
	filter = 0;

	filter = imageFactory->loadDC( hdc, "resource\\smallFilter.dad" );

	setToneNum = 5;
	blockWidth = filter->mWidth / setToneNum;
	for( int i = setToneNum - 1; i >= 0; --i ) {
		newData = new DCBitmap( hdc, VIEW_WIDTH, VIEW_HEIGHT, 0xFF );
		for( unsigned int y = 0; y < VIEW_HEIGHT; y += blockWidth ) {
			for( unsigned int x = 0; x < VIEW_WIDTH; x += blockWidth ) {
				filter->drawBlock( newData->mHdcBmp, x, y, blockWidth, ( i ) % setToneNum );
			}
		}
		setTone[ setToneIndex++ ] = newData;
	}
	delete filter;
	filter = 0;

	BitmapBase::mTone = setTone;
}

ToneFactory::~ToneFactory( void )
{
	for( int i = 0; i < TONE_NONE; ++i ) {
		delete BitmapBase::mTone[ i ];
		BitmapBase::mTone[ i ] = 0;
	}
	delete[] BitmapBase::mTone;
	BitmapBase::mTone = 0;
}


} // namespace Main
