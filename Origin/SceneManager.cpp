#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "SceneManager.h"
#include "ImageFactory.h"
#include "PixelBitmap.h"
#include "DCBitmap.h"

#include "MainParent.h"

namespace Main {

SceneManager* SceneManager::mInst = 0;
int SceneManager::mWindowWidth = 0;
int SceneManager::mWindowHeight = 0;
int SceneManager::mIsMouseDown = FALSE;
int SceneManager::mIsAddWave = FALSE;

SceneManager* SceneManager::inst( void )
{
	return mInst;
}
void SceneManager::create( HWND& hwnd )
{
	if( mInst == 0 ) {
		mInst = new SceneManager( hwnd );
	}
}
void SceneManager::destroy( void )
{
	if( mInst != 0 ) {
		delete mInst;
		mInst = 0;
	}
}

SceneManager::SceneManager( HWND& hwnd )
{
	HDC hdc;
//	long black = RGB(0,0,0);
	long black = RGB(100, 100, 100);
	long white = RGB(255, 255, 255);

	ImageFactory::create();

	hdc = GetDC(hwnd);
	mWindowWidth = GetDeviceCaps(hdc, HORZRES);
	mWindowHeight = GetDeviceCaps(hdc, VERTRES);

	mBmpInfo = ( BITMAPINFO * )malloc( sizeof( BITMAPINFOHEADER ) + sizeof( RGBQUAD ) * 2 );
	mBmpInfo->bmiHeader.biSize = sizeof( BITMAPINFOHEADER );
	mBmpInfo->bmiHeader.biBitCount = 1;
	mBmpInfo->bmiHeader.biPlanes = 1;
	mBmpInfo->bmiHeader.biClrUsed = 2;
	mBmpInfo->bmiHeader.biClrImportant = 0;
	mBmpInfo->bmiHeader.biCompression = BI_RGB;
	mBmpInfo->bmiHeader.biSizeImage = 0;
	mBmpInfo->bmiHeader.biXPelsPerMeter = mWindowWidth;
	mBmpInfo->bmiHeader.biYPelsPerMeter = mWindowHeight;
	mBmpInfo->bmiHeader.biWidth = mWindowWidth;
	mBmpInfo->bmiHeader.biHeight = -mWindowHeight;
	CopyMemory( &mBmpInfo->bmiColors[0], &black, sizeof( RGBQUAD ) );
	CopyMemory( &mBmpInfo->bmiColors[1], &white, sizeof( RGBQUAD ) );

	mHBmp = CreateDIBSection( NULL, mBmpInfo, DIB_RGB_COLORS, ( void** )( &mWindowPixel ), NULL, 0 );
	mHdcBmp = CreateCompatibleDC( hdc );
	mHBmpOld = ( HBITMAP )SelectObject( mHdcBmp, mHBmp );

	mParent = new Sequence::MainParent( hdc );

	ReleaseDC( hwnd, hdc );

	for ( int i = 0; i < mWindowWidth * mWindowHeight / 32; ++i ) {
		mWindowPixel[i] = 0;
	}
}


SceneManager::~SceneManager( void )
{
	SelectObject( mHdcBmp, mHBmpOld );
	DeleteObject( mHBmp );
	DeleteDC( mHdcBmp );

	delete mParent;
	mParent = 0;

	free( mBmpInfo );

	ImageFactory::destroy();
}

int SceneManager::update( void )
{
	mParent->update();
	mIsAddWave = FALSE;
	return 0;
}

int SceneManager::draw( HDC& hdc )
{
	BitBlt(hdc, 0, 0, mWindowWidth, mWindowHeight, mHdcBmp, 0, 0, SRCCOPY);
	for ( int i = 0; i < mWindowWidth * mWindowHeight / 32; ++i ) {
		mWindowPixel[i] = 0;
	}
	mParent->draw( hdc );

	return 0;
}


} // namespace Main
