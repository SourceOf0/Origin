#ifndef INCLUDED_IMAGE_DC_BITMAP_H
#define INCLUDED_IMAGE_DC_BITMAP_H

#include <windows.h>

namespace Image {

class PixelBitmap;

class DCBitmap
{
public:
	DCBitmap( HDC& hdc, PixelBitmap* target );
	~DCBitmap( void );

	int setData( int index, unsigned char data );
	int drawWindow( void );
	int drawWindowAnd( void );
	int drawBlock( HDC& targetHdc, int x, int y, int width, int index );
	int drawBlockAnd( HDC& targetHdc, int x, int y, int width, int index );
	int drawBlockOr( HDC& targetHdc, int x, int y, int width, int index );

	float mX;
	float mY;
	int mWidth;
	int mHeight;
	HDC mHdcBmp;

private:
	HBITMAP mHBmpPrev;
};

} // namespace Image

#endif // INCLUDED_IMAGE_DC_BITMAP_H