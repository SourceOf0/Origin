#include "DCBitmap.h"
#include "PixelBitmap.h"

#include "SceneManager.h"

namespace Image {

DCBitmap::DCBitmap( HDC& hdc, PixelBitmap* target ) : 
mX( 0 ),
mY( 0 )
{
	mWidth = target->mWidth;
	mHeight = target->mHeight;

	mHdcBmp = CreateCompatibleDC( hdc );
	HBITMAP hbmp = CreateBitmap( mWidth, mHeight, 1, 1, target->mPixelData );
	mHBmpPrev = (HBITMAP)SelectObject( mHdcBmp, hbmp );
}

DCBitmap::DCBitmap( HDC& hdc, int width, int height ) : 
mX( 0 ),
mY( 0 )
{
	mWidth = width;
	mHeight = height;

	Image::PixelBitmap* setBmp = new Image::PixelBitmap( width, height, width * height / 8 );

	mHdcBmp = CreateCompatibleDC( hdc );
	HBITMAP hbmp = CreateBitmap( mWidth, mHeight, 1, 1, setBmp->mPixelData );
	mHBmpPrev = (HBITMAP)SelectObject( mHdcBmp, hbmp );

	delete setBmp;
	setBmp = 0;
}

DCBitmap::~DCBitmap( void )
{
	HBITMAP hbmp = (HBITMAP)SelectObject( mHdcBmp, mHBmpPrev );
	DeleteObject( hbmp );
	DeleteObject( mHdcBmp );
}

int DCBitmap::drawWindow( void )
{
	BitBlt( Main::SceneManager::inst()->mHdcBmp, (int)( mX + 0.5 ), (int)( mY + 0.5 ), mWidth, mHeight, mHdcBmp, 0, 0, SRCCOPY );
	return 0;
}
int DCBitmap::drawWindow( int x, int y )
{
	BitBlt( Main::SceneManager::inst()->mHdcBmp, x, y, mWidth, mHeight, mHdcBmp, 0, 0, SRCCOPY );
	return 0;
}
int DCBitmap::drawWindowAnd( void )
{
	BitBlt( Main::SceneManager::inst()->mHdcBmp, (int)( mX + 0.5 ), (int)( mY + 0.5 ), mWidth, mHeight, mHdcBmp, 0, 0, SRCAND );
	return 0;
}
int DCBitmap::drawWindowAnd( int x, int y )
{
	BitBlt( Main::SceneManager::inst()->mHdcBmp, x, y, mWidth, mHeight, mHdcBmp, 0, 0, SRCAND );
	return 0;
}
int DCBitmap::drawWindowOr( void )
{
	BitBlt( Main::SceneManager::inst()->mHdcBmp, (int)( mX + 0.5 ), (int)( mY + 0.5 ), mWidth, mHeight, mHdcBmp, 0, 0, SRCPAINT );
	return 0;
}
int DCBitmap::drawWindowOr( int x, int y )
{
	BitBlt( Main::SceneManager::inst()->mHdcBmp, x, y, mWidth, mHeight, mHdcBmp, 0, 0, SRCPAINT );
	return 0;
}
int DCBitmap::drawBlock( HDC& targetHdc, int x, int y, int width, int index )
{
	BitBlt( targetHdc, x, y, width, mHeight, mHdcBmp, width * index, 0, SRCCOPY );
	return 0;
}
int DCBitmap::drawBlockAnd( HDC& targetHdc, int x, int y, int width, int index )
{
	BitBlt( targetHdc, x, y, width, mHeight, mHdcBmp, width * index, 0, SRCAND );
	return 0;
}
int DCBitmap::drawBlockOr( HDC& targetHdc, int x, int y, int width, int index )
{
	BitBlt( targetHdc, x, y, width, mHeight, mHdcBmp, width * index, 0, SRCPAINT );
	return 0;
}

} // namespace Image

