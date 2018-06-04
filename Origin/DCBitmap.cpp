#include "DCBitmap.h"
#include "PixelBitmap.h"

#include "SceneManager.h"

namespace Image {

HDC DCBitmap::mHdcBlackBmp = 0;
HBITMAP DCBitmap::mHBmpBlackPrev = 0;
HDC DCBitmap::mHdcWhiteBmp = 0;
HBITMAP DCBitmap::mHBmpWhitePrev = 0;

DCBitmap::DCBitmap( HDC& hdc, PixelBitmap* target )
{
	init( target->mWidth, target->mHeight );

	mHdcBmp = CreateCompatibleDC( hdc );
	HBITMAP hbmp = CreateBitmap( mWidth, mHeight, 1, 1, target->mPixelData );
	mHBmpPrev = (HBITMAP)SelectObject( mHdcBmp, hbmp );
}

DCBitmap::DCBitmap( HDC& hdc, int width, int height, unsigned char setColor )
{
	init( width, height );

	Image::PixelBitmap* setBmp = new Image::PixelBitmap( width, height, setColor );

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

void DCBitmap::setBlack( void )
{
	BitBlt( mHdcBmp, 0, 0, mWidth, mHeight, mHdcBlackBmp, 0, 0, SRCCOPY );
}

void DCBitmap::setWhite( void )
{
	BitBlt( mHdcBmp, 0, 0, mWidth, mHeight, mHdcWhiteBmp, 0, 0, SRCCOPY );
}

void DCBitmap::drawWindow( void )
{
	BitBlt( Main::SceneManager::inst()->mHdcBmp, static_cast< int >( mX + 0.5 ), static_cast< int >( mY + 0.5 ), mWidth, mHeight, mHdcBmp, 0, 0, SRCCOPY );
}
void DCBitmap::drawWindow( int x, int y )
{
	BitBlt( Main::SceneManager::inst()->mHdcBmp, x, y, mWidth, mHeight, mHdcBmp, 0, 0, SRCCOPY );
}
void DCBitmap::drawWindowAnd( void )
{
	BitBlt( Main::SceneManager::inst()->mHdcBmp, static_cast< int >( mX + 0.5 ), static_cast< int >( mY + 0.5 ), mWidth, mHeight, mHdcBmp, 0, 0, SRCAND );
}
void DCBitmap::drawWindowAnd( int x, int y )
{
	BitBlt( Main::SceneManager::inst()->mHdcBmp, x, y, mWidth, mHeight, mHdcBmp, 0, 0, SRCAND );
}
void DCBitmap::drawWindowOr( void )
{
	BitBlt( Main::SceneManager::inst()->mHdcBmp, static_cast< int >( mX + 0.5 ), static_cast< int >( mY + 0.5 ), mWidth, mHeight, mHdcBmp, 0, 0, SRCPAINT );
}
void DCBitmap::drawWindowOr( int x, int y )
{
	BitBlt( Main::SceneManager::inst()->mHdcBmp, x, y, mWidth, mHeight, mHdcBmp, 0, 0, SRCPAINT );
}
void DCBitmap::drawWindowInv( void )
{
	BitBlt( Main::SceneManager::inst()->mHdcBmp, static_cast< int >( mX + 0.5 ), static_cast< int >( mY + 0.5 ), mWidth, mHeight, mHdcBmp, 0, 0, SRCINVERT );
}
void DCBitmap::drawWindowInv( int x, int y )
{
	BitBlt( Main::SceneManager::inst()->mHdcBmp, x, y, mWidth, mHeight, mHdcBmp, 0, 0, SRCINVERT );
}
void DCBitmap::drawBlock( HDC& targetHdc, int x, int y, int width, int index )
{
	BitBlt( targetHdc, x, y, width, mHeight, mHdcBmp, width * index, 0, SRCCOPY );
}
void DCBitmap::drawBlockAnd( HDC& targetHdc, int x, int y, int width, int index )
{
	BitBlt( targetHdc, x, y, width, mHeight, mHdcBmp, width * index, 0, SRCAND );
}
void DCBitmap::drawBlockOr( HDC& targetHdc, int x, int y, int width, int index )
{
	BitBlt( targetHdc, x, y, width, mHeight, mHdcBmp, width * index, 0, SRCPAINT );
}
void DCBitmap::drawBlockInv( HDC& targetHdc, int x, int y, int width, int index )
{
	BitBlt( targetHdc, x, y, width, mHeight, mHdcBmp, width * index, 0, SRCINVERT );
}


} // namespace Image

