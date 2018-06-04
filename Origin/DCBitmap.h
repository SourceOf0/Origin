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
	void drawWindow( void );
	void drawWindow( int x, int y );
	void drawWindowAnd( void );
	void drawWindowAnd( int x, int y );
	void drawWindowOr( void );
	void drawWindowOr( int x, int y );
	void drawBlock( HDC& targetHdc, int x, int y, int width, int index );
	void drawBlockAnd( HDC& targetHdc, int x, int y, int width, int index );
	void drawBlockOr( HDC& targetHdc, int x, int y, int width, int index );

	HDC mHdcBmp;

private:
	HBITMAP mHBmpPrev;
};

} // namespace Image

#endif // INCLUDED_IMAGE_DC_BITMAP_H