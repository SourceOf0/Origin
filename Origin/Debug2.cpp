#include "MainParent.h"
#include "MainChild.h"
#include "Debug2.h"

#include "ImageFactory.h"
#include "SceneManager.h"
#include "SoundManager.h"

#include "DCBitmap.h"

namespace Sequence {

Debug2::Debug2( HDC& hdc, MainParent* parent )
{
	Main::ImageFactory* imageFactory = Main::ImageFactory::inst();
	int windowWidth = Main::SceneManager::windowWidth;
	int windowHeight = Main::SceneManager::windowHeight;

//	mBackBmp = new Image::DCBitmap( hdc, windowWidth, windowHeight );
//	mBackBmp = new Image::DCBitmap( hdc, windowWidth, windowHeight, 0xFF );
	mBackBmp = imageFactory->loadDC( hdc, "resource\\synthe.dad" );

	const char* loadFile[ 10 ];
	for( int i = 0; i < 10; ++i ) {
		loadFile[ i ] = "resource\\synthe.dad";
	}

	for( int i = 0; i < DEBUG2_BMP_NUM; ++i ) {
//		mTempBmp[ i ] = imageFactory->loadAnime( hdc, 10, loadFile, FALSE );
		mTempBmp[ i ] = imageFactory->load( hdc, "resource\\synthe_parts.dad" );
		mTempBmp[ i ]->mX = ( static_cast< int >( windowWidth ) - static_cast< int >( mTempBmp[ i ]->mWidth ) ) / 2 - ( i % 10 ) * 10 - ( i / 10 ) * 100;
		mTempBmp[ i ]->mY = ( static_cast< int >( windowHeight ) - static_cast< int >( mTempBmp[ i ]->mHeight ) ) / 2 - ( i % 10 ) * 10;
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