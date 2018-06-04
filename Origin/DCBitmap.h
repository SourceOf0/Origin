#ifndef INCLUDED_COMMON_DC_BITMAP_H
#define INCLUDED_COMMON_DC_BITMAP_H

#include <windows.h>

namespace Common {

class PixelBitmap;

class DCBitmap
{
public:
	DCBitmap( HDC& hdc, PixelBitmap* target );
	~DCBitmap( void );

	int setData( int index, unsigned char data );
	int drawWindow( void );

	float mX;
	float mY;
	int mWidth;
	int mHeight;

private:
	HDC mHdcBmp;
	HBITMAP mHBmpPrev;
};

} // namespace Common

#endif // INCLUDED_COMMON_DC_BITMAP_H