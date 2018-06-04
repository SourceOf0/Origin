#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "SceneManager.h"
#include "ImageFactory.h"
#include "HandManager.h"
#include "NoteManager.h"
#include "PixelBitmap.h"
#include "DCBitmap.h"

#include "MainParent.h"

namespace Main {

SceneManager* SceneManager::mInst = 0;
int SceneManager::windowWidth = 0;
int SceneManager::windowHeight = 0;
int SceneManager::deviceWidth = 0;
int SceneManager::deviceHeight = 0;
BOOL SceneManager::isAddWave = FALSE;

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
void SceneManager::setWindowSize( void )
{
	windowWidth = 1024;
	windowHeight = 768;
	//deviceWidth = GetDeviceCaps( hdc, HORZRES );
	//deviceHeight = GetDeviceCaps( hdc, VERTRES );
	deviceWidth = 1024;
	deviceHeight = 768;
}

SceneManager::SceneManager( HWND& hwnd ) :
mFrameRate( 40 ),
mWasDraw( FALSE )
{
	HDC hdc;
//	long black = RGB( 100, 100, 100 );
	long black = RGB( 10, 10, 10 );
	long white = RGB( 255, 255, 255 );

	ShowCursor( FALSE );

	hdc = GetDC( hwnd );

	mBmpInfo = ( BITMAPINFO * )malloc( sizeof( BITMAPINFOHEADER ) + sizeof( RGBQUAD ) * 2 );
	mBmpInfo->bmiHeader.biSize = sizeof( BITMAPINFOHEADER );
	mBmpInfo->bmiHeader.biBitCount = 1;
	mBmpInfo->bmiHeader.biPlanes = 1;
	mBmpInfo->bmiHeader.biClrUsed = 2;
	mBmpInfo->bmiHeader.biClrImportant = 0;
	mBmpInfo->bmiHeader.biCompression = BI_RGB;
	mBmpInfo->bmiHeader.biSizeImage = 0;
	mBmpInfo->bmiHeader.biXPelsPerMeter = deviceWidth;
	mBmpInfo->bmiHeader.biYPelsPerMeter = deviceHeight;
	mBmpInfo->bmiHeader.biWidth = deviceWidth;
	mBmpInfo->bmiHeader.biHeight = -deviceHeight;
	CopyMemory( &mBmpInfo->bmiColors[0], &black, sizeof( RGBQUAD ) );
	CopyMemory( &mBmpInfo->bmiColors[1], &white, sizeof( RGBQUAD ) );

	mHBmp = CreateDIBSection( NULL, mBmpInfo, DIB_RGB_COLORS, ( void** )( &mWindowPixel ), NULL, 0 );
	mHdcBmp = CreateCompatibleDC( hdc );
	mHBmpOld = ( HBITMAP )SelectObject( mHdcBmp, mHBmp );

	mParent = new Sequence::MainParent( hwnd, hdc, windowWidth, windowHeight );

	for ( int i = 0; i < deviceWidth * deviceHeight / 32; ++i ) {
		mWindowPixel[i] = 0;
	}

	ImageFactory::create( hdc );

	HBITMAP setHBmp = 0;
	Image::PixelBitmap* pixelData = new Image::PixelBitmap( windowWidth, windowHeight );
	
	Image::DCBitmap::mHdcBlackBmp = CreateCompatibleDC( hdc );
	setHBmp = CreateBitmap( windowWidth, windowHeight, 1, 1, pixelData->mPixelData );
	Image::DCBitmap::mHBmpBlackPrev = ( HBITMAP )SelectObject( Image::DCBitmap::mHdcBlackBmp, setHBmp );

	pixelData->reset( windowWidth, windowHeight, 0xFF );

	Image::DCBitmap::mHdcWhiteBmp = CreateCompatibleDC( hdc );
	setHBmp = CreateBitmap( windowWidth, windowHeight, 1, 1, pixelData->mPixelData );
	Image::DCBitmap::mHBmpWhitePrev = ( HBITMAP )SelectObject( Image::DCBitmap::mHdcWhiteBmp, setHBmp );

	delete pixelData;
	pixelData = 0;

	pixelData = new Image::PixelBitmap( deviceWidth, deviceHeight, 0 );
	Image::DCBitmap::mHdcMaskBmp = CreateCompatibleDC( hdc );
	setHBmp = CreateBitmap( deviceWidth, deviceHeight, 1, 1, pixelData->mPixelData );
	Image::DCBitmap::mHBmpMaskPrev = ( HBITMAP )SelectObject( Image::DCBitmap::mHdcMaskBmp, setHBmp );

	BitBlt( Image::DCBitmap::mHdcMaskBmp, (deviceWidth-windowWidth)/2, (deviceHeight-windowHeight)/2, windowWidth, windowHeight, Image::DCBitmap::mHdcWhiteBmp, 0, 0, SRCCOPY );

	delete pixelData;
	pixelData = 0;

	HandManager::create( hdc );
	NoteManager::create();

	ReleaseDC( hwnd, hdc );

	GetLocalTime( &mLocalTime );
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
	HandManager::destroy();
	NoteManager::destroy();

	HBITMAP hbmp = 0;
	hbmp = ( HBITMAP )SelectObject( Image::DCBitmap::mHdcBlackBmp, Image::DCBitmap::mHBmpBlackPrev );
	DeleteObject( hbmp );
	DeleteObject( Image::DCBitmap::mHdcBlackBmp );

	hbmp = ( HBITMAP )SelectObject( Image::DCBitmap::mHdcWhiteBmp, Image::DCBitmap::mHBmpWhitePrev );
	DeleteObject( hbmp );
	DeleteObject( Image::DCBitmap::mHdcWhiteBmp );

	hbmp = ( HBITMAP )SelectObject( Image::DCBitmap::mHdcMaskBmp, Image::DCBitmap::mHBmpMaskPrev );
	DeleteObject( hbmp );
	DeleteObject( Image::DCBitmap::mHdcMaskBmp );
}

void SceneManager::endSetWave( void )
{
	isAddWave = TRUE;
	mParent->playSound();
}

int SceneManager::update()
{
	if( !mWasDraw ) return 1;
	mParent->update();
	HandManager::inst()->endUpdate();
	isAddWave = FALSE;
	mWasDraw = FALSE;
	return 0;
}

int SceneManager::draw( HDC& hdc )
{
	int nowTime;
	SYSTEMTIME localTime;
	GetLocalTime( &localTime );
	nowTime = ( localTime.wSecond == mLocalTime.wSecond )? localTime.wMilliseconds : ( 1000 + localTime.wMilliseconds );
	while( nowTime - mLocalTime.wMilliseconds < mFrameRate ) {
		Sleep( 5 );
		GetLocalTime( &localTime );
		nowTime = ( localTime.wSecond == mLocalTime.wSecond )? localTime.wMilliseconds : ( 1000 + localTime.wMilliseconds );
	}
	GetLocalTime( &localTime );
	mLocalTime = localTime;

	for ( int i = 0; i < deviceWidth * deviceHeight / 32; ++i ) {
		mWindowPixel[i] = 0;
	}
	mParent->draw( hdc );
	BitBlt( mHdcBmp, 0, 0, deviceWidth, deviceHeight, Image::DCBitmap::mHdcMaskBmp, 0, 0, SRCAND );
	BitBlt( hdc, 0, 0, deviceWidth, deviceHeight, mHdcBmp, 0, 0, SRCCOPY );

	mWasDraw = TRUE;

	return 0;
}


} // namespace Main
