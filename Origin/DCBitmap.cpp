#include "DCBitmap.h"
#include "PixelBitmap.h"
#include "SceneManager.h"

namespace Common {

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
int DCBitmap::drawWindowAnd( void )
{
	BitBlt( Main::SceneManager::inst()->mHdcBmp, (int)( mX + 0.5 ), (int)( mY + 0.5 ), mWidth, mHeight, mHdcBmp, 0, 0, SRCAND );
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

} // namespace Common

