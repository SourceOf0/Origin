#include "MainParent.h"
#include "MainChild.h"
#include "Debug1.h"

#include "SceneManager.h"
#include "SoundManager.h"
#include "HandManager.h"

#include "DCBitmap.h"
#include "Track.h"

namespace Sequence {

Debug1::Debug1( HDC& hdc, MainParent* parent )
{
	Main::SceneManager* sceneManager = Main::SceneManager::inst();
	mBackBmp = new Image::DCBitmap( hdc, Main::SceneManager::VIEW_WIDTH, Main::SceneManager::VIEW_HEIGHT );
}

Debug1::~Debug1()
{
	delete mBackBmp;
	mBackBmp = 0;
}

void Debug1::update( MainParent* parent )
{
	Main::SoundManager* soundManager = Main::SoundManager::inst();
	if( Main::HandManager::isMouseDown ) {
		soundManager->play();
		soundManager->getTrack( 0 )->setWave( WAVE_SQUARE );
		soundManager->getTrack( 1 )->setWave( WAVE_SQUARE );
		soundManager->getTrack( 2 )->setWave( WAVE_SQUARE );
	} else {
		soundManager->getTrack( 0 )->setWave( WAVE_NONE );
		soundManager->getTrack( 1 )->setWave( WAVE_NONE );
		soundManager->getTrack( 2 )->setWave( WAVE_NONE );
	}

	if( !Main::SceneManager::isAddWave ) return;

	double* waveLog1 = soundManager->getTrack( 0 )->getPlayData();
	double* waveLog2 = soundManager->getTrack( 1 )->getPlayData();

	HPEN hPen1 = CreatePen( PS_SOLID, 1, RGB( 255, 255, 255 ) );
	HPEN hPen2 = CreatePen( PS_SOLID, 1, RGB( 0, 0, 0 ) );
	HBRUSH hBrush = CreateSolidBrush( RGB( 0, 0, 0 ) );

	SelectObject( mBackBmp->mHdcBmp, hBrush );
	SelectObject( mBackBmp->mHdcBmp, hPen2 );
	Rectangle( mBackBmp->mHdcBmp, 20, 200, WAVE_DATA_LENGTH / 3 + 20, 400 );
	Rectangle( mBackBmp->mHdcBmp, 20, 400, WAVE_DATA_LENGTH / 3 + 20, 600 );

	SelectObject( mBackBmp->mHdcBmp, hPen1 );
	MoveToEx( mBackBmp->mHdcBmp , 20, static_cast<int>( waveLog1[ 0 ] * 50 + 300 ), NULL );
	for( int i = 1; i < WAVE_DATA_LENGTH; ++i ) {
		LineTo( mBackBmp->mHdcBmp , static_cast<int>( i / 3 ) + 20, static_cast<int>( waveLog1[i] * 50 + 300 ) );
	}

	MoveToEx( mBackBmp->mHdcBmp , 20, static_cast<int>( waveLog2[ 0 ] * 50 + 500 ), NULL );
	for( int i = 1; i < WAVE_DATA_LENGTH; ++i ) {
		LineTo( mBackBmp->mHdcBmp , static_cast<int>( i / 3 ) + 20, static_cast<int>( waveLog2[i] * 50 + 500 ) );
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