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
//	long black = RGB( 0, 0, 0 );
	long black = RGB( 100, 100, 100 );
	long white = RGB( 255, 255, 255 );

	hdc = GetDC( hwnd );
	mWindowWidth = GetDeviceCaps( hdc, HORZRES );
	mWindowHeight = GetDeviceCaps( hdc, VERTRES );

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

	mParent = new Sequence::MainParent( hwnd, hdc, mWindowWidth, mWindowHeight );

	for ( int i = 0; i < mWindowWidth * mWindowHeight / 32; ++i ) {
		mWindowPixel[i] = 0;
	}

	ImageFactory::create( hdc );

	HBITMAP setHBmp = 0;
	Image::PixelBitmap* pixelData = new Image::PixelBitmap( mWindowWidth, mWindowHeight );
	
	Image::DCBitmap::mHdcBlackBmp = CreateCompatibleDC( hdc );
	setHBmp = CreateBitmap( mWindowWidth, mWindowHeight, 1, 1, pixelData->mPixelData );
	Image::DCBitmap::mHBmpBlackPrev = (HBITMAP)SelectObject( Image::DCBitmap::mHdcBlackBmp, setHBmp );

	pixelData->reset( mWindowWidth, mWindowHeight, 0xFF );

	Image::DCBitmap::mHdcWhiteBmp = CreateCompatibleDC( hdc );
	setHBmp = CreateBitmap( mWindowWidth, mWindowHeight, 1, 1, pixelData->mPixelData );
	Image::DCBitmap::mHBmpWhitePrev = (HBITMAP)SelectObject( Image::DCBitmap::mHdcWhiteBmp, setHBmp );

	delete pixelData;
	pixelData = 0;

	ReleaseDC( hwnd, hdc );
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

	HBITMAP hbmp = 0;
	hbmp = (HBITMAP)SelectObject( Image::DCBitmap::mHdcBlackBmp, Image::DCBitmap::mHBmpBlackPrev );
	DeleteObject( hbmp );
	DeleteObject( Image::DCBitmap::mHdcBlackBmp );

	hbmp = (HBITMAP)SelectObject( Image::DCBitmap::mHdcWhiteBmp, Image::DCBitmap::mHBmpWhitePrev );
	DeleteObject( hbmp );
	DeleteObject( Image::DCBitmap::mHdcWhiteBmp );
}

void SceneManager::mouseDown( void )
{
	mParent->mIsMouseDown = TRUE;
}

void SceneManager::mouseUp( void )
{
	mParent->mIsMouseDown = FALSE;
}

void SceneManager::endSetWave( void )
{
	mParent->mIsAddWave = TRUE;
}

int SceneManager::update()
{
	mParent->update();
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
