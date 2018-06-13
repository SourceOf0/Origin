#include "MainParent.h"
#include "MainChild.h"
#include "Debug2.h"

#include "ImageFactory.h"
#include "SceneManager.h"
#include "SoundManager.h"

#include "DCBitmap.h"
#include "LayerData.h"

namespace Sequence {

Debug2::Debug2( HDC& hdc, MainParent* parent )
{
	Main::ImageFactory* imageFactory = Main::ImageFactory::inst();
	const int VIEW_WIDTH = Main::SceneManager::VIEW_WIDTH;
	const int VIEW_HEIGHT = Main::SceneManager::VIEW_HEIGHT;

//	mBackBmp = new Image::DCBitmap( hdc, VIEW_WIDTH, VIEW_HEIGHT );
//	mBackBmp = new Image::DCBitmap( hdc, VIEW_WIDTH, VIEW_HEIGHT, 0xFF );
//	mBackBmp = imageFactory->loadDC( hdc, IDR_DAD_SYNTHE );
	mBackBmp = ( Image::LayerData* )( imageFactory->load( hdc, IDR_DAD_TEST ) );
	mBackBmp->mUseAlpha = FALSE;

	int loadFile[ 10 ];
	for( int i = 0; i < 10; ++i ) {
		loadFile[ i ] = IDR_DAD_SYNTHE;
	}

	for( int i = 0; i < DEBUG2_BMP_NUM; ++i ) {
//		mTempBmp[ i ] = imageFactory->loadAnime( hdc, 10, loadFile, FALSE );
		mTempBmp[ i ] = imageFactory->load( hdc, IDR_DAD_SYNTHE_PARTS );
		mTempBmp[ i ]->mX = ( static_cast< int >( VIEW_WIDTH ) - static_cast< int >( mTempBmp[ i ]->mWidth ) ) / 2 - ( i % 10 ) * 10 - ( i / 10 ) * 100;
		mTempBmp[ i ]->mY = ( static_cast< int >( VIEW_HEIGHT ) - static_cast< int >( mTempBmp[ i ]->mHeight ) ) / 2 - ( i % 10 ) * 10;
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

/*	for( int i = 0; i < DEBUG2_BMP_NUM; ++i ) {
		mTempBmp[ i ]->drawWindow();
	}*/
}


} // namespace Sequence