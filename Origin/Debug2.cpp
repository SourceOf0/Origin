#include "MainParent.h"
#include "MainChild.h"
#include "Debug2.h"

#include "ImageFactory.h"
#include "SceneManager.h"
#include "SoundManager.h"

#include "DCBitmap.h"

#include <stdlib.h>

namespace Sequence {

Debug2::Debug2( HDC& hdc, MainParent* parent )
{
	Main::ImageFactory* imageFactory = Main::ImageFactory::inst();
	int windowWidth = parent->mWindowWidth;
	int windowHeight = parent->mWindowHeight;

	mBackBmp = new Image::DCBitmap( hdc, windowWidth, windowHeight );
//	mBackBmp = new Image::DCBitmap( hdc, windowWidth, windowHeight, 0xFF );

	for( int i = 0; i < DEBUG2_BMP_NUM; ++i ) {
		mTempBmp[ i ] = imageFactory->load( hdc, "resource\\test.dad" );
		mTempBmp[ i ]->mX = static_cast< float >( windowWidth - mTempBmp[ i ]->mWidth - i * 10 );
		mTempBmp[ i ]->mY = static_cast< float >( windowHeight - mTempBmp[ i ]->mHeight - i * 10 );
	}
}

Debug2::~Debug2()
{
	delete mBackBmp;
	mBackBmp = 0;

	for( int i = 0; i < DEBUG2_BMP_NUM; ++i ) {
		delete mTempBmp[ i ];
		mTempBmp[ i ] = 0;
	}
}

void Debug2::update( MainParent* parent )
{
}

void Debug2::draw( HDC& hdc, MainParent* parent )
{
	mBackBmp->drawWindow();

	for( int i = 0; i < DEBUG2_BMP_NUM; ++i ) {
		mTempBmp[ i ]->drawWindow();
	}
}


} // namespace Sequence