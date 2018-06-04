#include "SceneManager.h"
#include "ImageFactory.h"
#include "PixelBitmap.h"
#include "DCBitmap.h"

#include "MainParent.h"

namespace Main {

SceneManager* SceneManager::mInst = 0;

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
//	PAINTSTRUCT ps;
	long black = RGB(0,0,0);
	int i = 0;

	ImageFactory::create();

	hdc = GetDC(hwnd);
	mWindowWidth = GetDeviceCaps(hdc, HORZRES);
	mWindowHeight = GetDeviceCaps(hdc, VERTRES);

	ZeroMemory(&mBmpInfo, sizeof(mBmpInfo));
	mBmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	mBmpInfo.bmiHeader.biBitCount = 1;
	mBmpInfo.bmiHeader.biPlanes = 1;
	mBmpInfo.bmiHeader.biWidth = mWindowWidth;
	mBmpInfo.bmiHeader.biHeight = -mWindowHeight;
	CopyMemory(&mBmpInfo.bmiColors[0], &black, sizeof(RGBQUAD));

	mHBmp = CreateDIBSection(NULL, &mBmpInfo, DIB_RGB_COLORS, (void **)(&mWindowPixel), NULL, 0);
	mHdcBmp = CreateCompatibleDC(hdc);
	mHBmpOld = (HBITMAP)SelectObject(mHdcBmp, mHBmp);

	mParent = new Sequence::MainParent( hdc );

	ReleaseDC(hwnd, hdc);

	for (i = 0;i < mWindowWidth * mWindowHeight / 32;i++) {
		mWindowPixel[i] = 0xFFFFFFFF;
	}
}


SceneManager::~SceneManager( void )
{
	SelectObject(mHdcBmp, mHBmpOld);
	DeleteObject(mHBmp);
	DeleteDC(mHdcBmp);

	delete mParent;
	mParent = 0;

	ImageFactory::destroy();
}


int SceneManager::draw( HDC& hdc )
{
	BitBlt(hdc, 0, 0, mWindowWidth, mWindowHeight, mHdcBmp, 0, 0, SRCCOPY);
	for ( int i = 0;i < mWindowWidth * mWindowHeight / 32;i++ ) {
		mWindowPixel[i] = 0xFFFFFFFF;
	}
	mParent->update( hdc );

	return 0;
}


} // namespace Main
