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
	if( mHdcBmp == NULL ) {
		MessageBox( NULL, TEXT( "mHdcbmpが作れてないっす。" ), TEXT( "Origin" ), MB_OK );
	}
	HBITMAP hbmp = CreateBitmap( mWidth, mHeight, 1, 1, target->mPixelData );
	if( hbmp == NULL ) {
		MessageBox( NULL, TEXT( "hbmpが作れてないっす。" ), TEXT( "Origin" ), MB_OK );
	}
	mHBmpPrev = (HBITMAP)SelectObject( mHdcBmp, hbmp );
	if( mHBmpPrev == NULL ) {
		MessageBox( NULL, TEXT( "mHBmpPrevが作れてないっす。" ), TEXT( "Origin" ), MB_OK );
	}
}

DCBitmap::DCBitmap( HDC& hdc, int width, int height, unsigned char setColor )
{
	init( width, height );

	Image::PixelBitmap* setBmp = new Image::PixelBitmap( width, height, setColor );

	mHdcBmp = CreateCompatibleDC( hdc );
	if( mHdcBmp == NULL ) {
		MessageBox( NULL, TEXT( "mHdcbmpが作れてないっす。" ), TEXT( "Origin" ), MB_OK );
	}
	HBITMAP hbmp = CreateBitmap( mWidth, mHeight, 1, 1, setBmp->mPixelData );
	if( hbmp == NULL ) {
		MessageBox( NULL, TEXT( "hbmpが作れてないっす。" ), TEXT( "Origin" ), MB_OK );
	}
	mHBmpPrev = ( HBITMAP )SelectObject( mHdcBmp, hbmp );
	if( mHBmpPrev == NULL ) {
		MessageBox( NULL, TEXT( "mHBmpPrevが作れてないっす。" ), TEXT( "Origin" ), MB_OK );
	}

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
	unsigned int windowWidth = Main::SceneManager::windowWidth;
	unsigned int windowHeight = Main::SceneManager::windowHeight;
	if( mWidth <= windowWidth ) {
		if( mHeight <= windowHeight ) {
			BitBlt( mHdcBmp, 0, 0, mWidth, mHeight, mHdcBlackBmp, 0, 0, SRCCOPY );
		} else {
			for( unsigned int i = 0; i < mHeight + windowHeight; i += windowHeight ) {
				BitBlt( mHdcBmp, 0, i, mWidth, windowHeight, mHdcBlackBmp, 0, 0, SRCCOPY );
			}
		}
	} else {
		if( mHeight <= windowHeight ) {
			for( unsigned int i = 0; i < mWidth + windowWidth; i += windowWidth ) {
				BitBlt( mHdcBmp, i, 0, windowWidth, mHeight, mHdcBlackBmp, 0, 0, SRCCOPY );
			}
		} else {
			for( unsigned int i = 0; i < mWidth + windowWidth; i += windowWidth ) {
				for( unsigned int j = 0; j < mHeight + windowHeight; j += windowHeight ) {
					BitBlt( mHdcBmp, i, j, windowWidth, windowHeight, mHdcBlackBmp, 0, 0, SRCCOPY );
				}
			}
		}
	}
}
void DCBitmap::setBlack( int x, int y, unsigned int width, unsigned int height )
{
	unsigned int windowWidth = Main::SceneManager::windowWidth;
	unsigned int windowHeight = Main::SceneManager::windowHeight;
	if( width <= windowWidth ) {
		if( height <= windowHeight ) {
			BitBlt( mHdcBmp, x, y, width, height, mHdcBlackBmp, 0, 0, SRCCOPY );
		} else {
			for( unsigned int i = 0; i < height + windowHeight; i += windowHeight ) {
				BitBlt( mHdcBmp, x, y + i, width, windowHeight, mHdcBlackBmp, 0, 0, SRCCOPY );
			}
		}
	} else {
		if( height <= windowHeight ) {
			for( unsigned int i = 0; i < width + windowWidth; i += windowWidth ) {
				BitBlt( mHdcBmp, x + i, y, windowWidth, mHeight, mHdcBlackBmp, 0, 0, SRCCOPY );
			}
		} else {
			for( unsigned int i = 0; i < width + windowWidth; i += windowWidth ) {
				for( unsigned int j = 0; j < height + windowHeight; j += windowHeight ) {
					BitBlt( mHdcBmp, x + i, y + j, windowWidth, windowHeight, mHdcBlackBmp, 0, 0, SRCCOPY );
				}
			}
		}
	}
}
void DCBitmap::setWhite( void )
{
	unsigned int windowWidth = Main::SceneManager::windowWidth;
	unsigned int windowHeight = Main::SceneManager::windowHeight;
	if( mWidth <= windowWidth ) {
		if( mHeight <= windowHeight ) {
			BitBlt( mHdcBmp, 0, 0, mWidth, mHeight, mHdcWhiteBmp, 0, 0, SRCCOPY );
		} else {
			for( unsigned int i = 0; i < mHeight + windowHeight; i += windowHeight ) {
				BitBlt( mHdcBmp, 0, i, mWidth, windowHeight, mHdcWhiteBmp, 0, 0, SRCCOPY );
			}
		}
	} else {
		if( mHeight <= windowHeight ) {
			for( unsigned int i = 0; i < mWidth + windowWidth; i += windowWidth ) {
				BitBlt( mHdcBmp, i, 0, windowWidth, mHeight, mHdcWhiteBmp, 0, 0, SRCCOPY );
			}
		} else {
			for( unsigned int i = 0; i < mWidth + windowWidth; i += windowWidth ) {
				for( unsigned int j = 0; j < mHeight + windowHeight; j += windowHeight ) {
					BitBlt( mHdcBmp, i, j, windowWidth, windowHeight, mHdcWhiteBmp, 0, 0, SRCCOPY );
				}
			}
		}
	}}
void DCBitmap::setWhite( int x, int y, unsigned int width, unsigned int height )
{
	unsigned int windowWidth = Main::SceneManager::windowWidth;
	unsigned int windowHeight = Main::SceneManager::windowHeight;
	if( width <= windowWidth ) {
		if( height <= windowHeight ) {
			BitBlt( mHdcBmp, x, y, width, height, mHdcWhiteBmp, 0, 0, SRCCOPY );
		} else {
			for( unsigned int i = 0; i < height + windowHeight; i += windowHeight ) {
				BitBlt( mHdcBmp, x, y + i, width, windowHeight, mHdcWhiteBmp, 0, 0, SRCCOPY );
			}
		}
	} else {
		if( height <= windowHeight ) {
			for( unsigned int i = 0; i < width + windowWidth; i += windowWidth ) {
				BitBlt( mHdcBmp, x + i, y, windowWidth, mHeight, mHdcWhiteBmp, 0, 0, SRCCOPY );
			}
		} else {
			for( unsigned int i = 0; i < width + windowWidth; i += windowWidth ) {
				for( unsigned int j = 0; j < height + windowHeight; j += windowHeight ) {
					BitBlt( mHdcBmp, x + i, y + j, windowWidth, windowHeight, mHdcWhiteBmp, 0, 0, SRCCOPY );
				}
			}
		}
	}
}

void DCBitmap::copyWindow( void )
{
	BitBlt( mHdcBmp, 0, 0, mWidth, mHeight, Main::SceneManager::inst()->mHdcBmp, 0, 0, SRCCOPY );
}
void DCBitmap::drawWindow( void )
{
	BitBlt( Main::SceneManager::inst()->mHdcBmp, static_cast< int >( mX + 0.5 ), static_cast< int >( mY + 0.5 ), mWidth, mHeight, mHdcBmp, 0, 0, SRCCOPY );
}
void DCBitmap::drawWindow( int x, int y )
{
	BitBlt( Main::SceneManager::inst()->mHdcBmp, x, y, mWidth, mHeight, mHdcBmp, 0, 0, SRCCOPY );
}
void DCBitmap::drawWindow( int x, int y, int startX, int startY, int width, int height )
{
	BitBlt( Main::SceneManager::inst()->mHdcBmp, x, y, width, height, mHdcBmp, startX, startY, SRCCOPY );
}

void DCBitmap::drawWindowAnd( void )
{
	BitBlt( Main::SceneManager::inst()->mHdcBmp, static_cast< int >( mX + 0.5 ), static_cast< int >( mY + 0.5 ), mWidth, mHeight, mHdcBmp, 0, 0, SRCAND );
}
void DCBitmap::drawWindowAnd( int x, int y )
{
	BitBlt( Main::SceneManager::inst()->mHdcBmp, x, y, mWidth, mHeight, mHdcBmp, 0, 0, SRCAND );
}
void DCBitmap::drawWindowAnd( int x, int y, int startX, int startY, int width, int height )
{
	BitBlt( Main::SceneManager::inst()->mHdcBmp, x, y, width, height, mHdcBmp, startX, startY, SRCAND );
}

void DCBitmap::drawWindowOr( void )
{
	BitBlt( Main::SceneManager::inst()->mHdcBmp, static_cast< int >( mX + 0.5 ), static_cast< int >( mY + 0.5 ), mWidth, mHeight, mHdcBmp, 0, 0, SRCPAINT );
}
void DCBitmap::drawWindowOr( int x, int y )
{
	BitBlt( Main::SceneManager::inst()->mHdcBmp, x, y, mWidth, mHeight, mHdcBmp, 0, 0, SRCPAINT );
}
void DCBitmap::drawWindowOr( int x, int y, int startX, int startY, int width, int height )
{
	BitBlt( Main::SceneManager::inst()->mHdcBmp, x, y, width, height, mHdcBmp, startX, startY, SRCPAINT );
}

void DCBitmap::drawWindowInv( void )
{
	BitBlt( Main::SceneManager::inst()->mHdcBmp, static_cast< int >( mX + 0.5 ), static_cast< int >( mY + 0.5 ), mWidth, mHeight, mHdcBmp, 0, 0, SRCINVERT );
}
void DCBitmap::drawWindowInv( int x, int y )
{
	BitBlt( Main::SceneManager::inst()->mHdcBmp, x, y, mWidth, mHeight, mHdcBmp, 0, 0, SRCINVERT );
}
void DCBitmap::drawWindowInv( int x, int y, int startX, int startY, int width, int height )
{
	BitBlt( Main::SceneManager::inst()->mHdcBmp, x, y, width, height, mHdcBmp, startX, startY, SRCINVERT );
}


void DCBitmap::drawImage( HDC& targetHdc, int x, int y )
{
	BitBlt( targetHdc, x, y, mWidth, mHeight, mHdcBmp, 0, 0, SRCCOPY );
}
void DCBitmap::drawImage( HDC& targetHdc, int x, int y, int startX, int startY, int width, int height )
{
	BitBlt( targetHdc, x, y, width, height, mHdcBmp, startX, startY, SRCCOPY );
}
void DCBitmap::drawImageAnd( HDC& targetHdc, int x, int y )
{
	BitBlt( targetHdc, x, y, mWidth, mHeight, mHdcBmp, 0, 0, SRCAND );
}
void DCBitmap::drawImageAnd( HDC& targetHdc, int x, int y, int startX, int startY, int width, int height )
{
	BitBlt( targetHdc, x, y, width, height, mHdcBmp, startX, startY, SRCAND );
}
void DCBitmap::drawImageOr( HDC& targetHdc, int x, int y )
{
	BitBlt( targetHdc, x, y, mWidth, mHeight, mHdcBmp, 0, 0, SRCPAINT );
}
void DCBitmap::drawImageOr( HDC& targetHdc, int x, int y, int startX, int startY, int width, int height )
{
	BitBlt( targetHdc, x, y, width, height, mHdcBmp, startX, startY, SRCPAINT );
}
void DCBitmap::drawImageInv( HDC& targetHdc, int x, int y )
{
	BitBlt( targetHdc, x, y, mWidth, mHeight, mHdcBmp, 0, 0, SRCINVERT );
}
void DCBitmap::drawImageInv( HDC& targetHdc, int x, int y, int startX, int startY, int width, int height )
{
	BitBlt( targetHdc, x, y, width, height, mHdcBmp, startX, startY, SRCINVERT );
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

