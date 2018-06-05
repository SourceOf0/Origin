#ifndef INCLUDED_IMAGE_DC_BITMAP_H
#define INCLUDED_IMAGE_DC_BITMAP_H

#include <windows.h>
#include "BitmapBase.h"

namespace Image {

class PixelBitmap;

class DCBitmap : public BitmapBase
{
public:
	DCBitmap( HDC& hdc, PixelBitmap* target );
	DCBitmap( HDC& hdc, int width, int height, unsigned char setColor = 0 );
	~DCBitmap( void );

	int setData( int index, unsigned char data );
	
	void setBlack( void );
	void setBlack( int x, int y, unsigned int width, unsigned int height );
	void setWhite( void );
	void setWhite( int x, int y, unsigned int width, unsigned int height );

	void copyWindow( void );
	void drawWindow( void );
	void drawWindow( int x, int y );
	void drawWindow( int x, int y, int startX, int startY, int width, int height );
	void drawWindow( int x, int y, int width, int height, int startX, int startY, DWORD drawOperation );
	void drawWindowAnd( void );
	void drawWindowAnd( int x, int y );
	void drawWindowAnd( int x, int y, int startX, int startY, int width, int height );
	void drawWindowOr( void );
	void drawWindowOr( int x, int y );
	void drawWindowOr( int x, int y, int startX, int startY, int width, int height );
	void drawWindowInv( void );
	void drawWindowInv( int x, int y );
	void drawWindowInv( int x, int y, int startX, int startY, int width, int height );

	void drawImage( HDC& targetHdc, int x, int y );
	void drawImage( HDC& targetHdc, int x, int y, int startX, int startY, int width, int height );
	void drawImageAnd( HDC& targetHdc, int x, int y );
	void drawImageAnd( HDC& targetHdc, int x, int y, int startX, int startY, int width, int height );
	void drawImageOr( HDC& targetHdc, int x, int y );
	void drawImageOr( HDC& targetHdc, int x, int y, int startX, int startY, int width, int height );
	void drawImageInv( HDC& targetHdc, int x, int y );
	void drawImageInv( HDC& targetHdc, int x, int y, int startX, int startY, int width, int height );

	void drawBlock( HDC& targetHdc, int x, int y, int width, int index );
	void drawBlockAnd( HDC& targetHdc, int x, int y, int width, int index );
	void drawBlockOr( HDC& targetHdc, int x, int y, int width, int index );
	void drawBlockInv( HDC& targetHdc, int x, int y, int width, int index );

	static HDC mHdcBlackBmp;
	static HBITMAP mHBmpBlackPrev;
	static HDC mHdcWhiteBmp;
	static HBITMAP mHBmpWhitePrev;

	HDC mHdcBmp;

private:
	HBITMAP mHBmpPrev;
};

} // namespace Image

#endif // INCLUDED_IMAGE_DC_BITMAP_H