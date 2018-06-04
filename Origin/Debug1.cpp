#include "MainParent.h"
#include "MainChild.h"
#include "Debug1.h"

#include "ImageFactory.h"
#include "SceneManager.h"
#include "SoundManager.h"

#include "PixelBitmap.h"
#include "DCBitmap.h"
#include "Track.h"

#include <stdlib.h>

namespace Sequence {

Debug1::Debug1( HDC& hdc )
{
	Main::ImageFactory* imageFactory = Main::ImageFactory::inst();
	Main::SceneManager* sceneManager = Main::SceneManager::inst();
	int windowWidth = sceneManager->mWindowWidth;
	int windowHeight = sceneManager->mWindowHeight;

	Image::PixelBitmap* tempBmp;

	tempBmp = new Image::PixelBitmap( windowWidth, windowHeight );

	mBackBmp = new Image::DCBitmap( hdc, tempBmp );
	delete tempBmp;

}

Debug1::~Debug1()
{
	delete mBackBmp;
	mBackBmp = 0;
}

void Debug1::update( MainParent* parent )
{
	if( !Main::SceneManager::inst()->mIsAddWave ) return;

	Main::SoundManager* soundManager = Main::SoundManager::inst();
	double* waveLog1 = soundManager->getTrack(1)->getWaveData();
	double* waveLog2 = soundManager->getTrack(2)->getWaveData();

	HPEN hPen1 = CreatePen( PS_SOLID, 1, RGB(255, 255, 255) );
	HPEN hPen2 = CreatePen( PS_SOLID, 1, RGB(0, 0, 0) );
	HBRUSH hBrush = CreateSolidBrush( RGB(0, 0, 0) );

	SelectObject( mBackBmp->mHdcBmp, hBrush );
	SelectObject( mBackBmp->mHdcBmp, hPen2 );
	Rectangle( mBackBmp->mHdcBmp, 20, 200, WAVE_DATA_LENGTH / 3 + 20, 400 );
	Rectangle( mBackBmp->mHdcBmp, 20, 400, WAVE_DATA_LENGTH / 3 + 20, 600 );

	SelectObject( mBackBmp->mHdcBmp, hPen1 );
	MoveToEx( mBackBmp->mHdcBmp , 20, static_cast<int>( waveLog1[0] * 50 + 300 ), NULL );
	for( int i = 1; i < WAVE_DATA_LENGTH; ++i ) {
		LineTo( mBackBmp->mHdcBmp , static_cast<int>(i / 3) + 20, static_cast<int>( waveLog1[i] * 50 + 300 ) );
	}

	MoveToEx( mBackBmp->mHdcBmp , 20, static_cast<int>( waveLog2[0] * 50 + 500 ), NULL );
	for( int i = 1; i < WAVE_DATA_LENGTH; ++i ) {
		LineTo( mBackBmp->mHdcBmp , static_cast<int>(i / 3) + 20, static_cast<int>( waveLog2[i] * 50 + 500 ) );
	}

	DeleteObject( hPen1 );
	DeleteObject( hPen2 );
	DeleteObject( hBrush );
}

void Debug1::draw( HDC& hdc, MainParent* parent )
{
	mBackBmp->drawWindow( 0, 0 );
}


} // namespace Sequence