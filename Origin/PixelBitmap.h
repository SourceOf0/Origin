#ifndef INCLUDED_COMMON_PIXEL_BITMAP_H
#define INCLUDED_COMMON_PIXEL_BITMAP_H

#include <windows.h>

namespace Image {

class PixelBitmap
{
public:
	PixelBitmap( int width, int height, int dataLeng );
	~PixelBitmap( void );

	char getBit( int x, int y );
	int setData( int index, unsigned char data );
	int setBlack( int x, int y );
	int setWhite( int x, int y );
	int setRev( int x, int y );
	int drawWindow( void );

	float mX;
	float mY;
	int mWidth;
	int mHeight;
	unsigned char* mPixelData;

private:
	int mWidthIndex;
	int mHeightIndex;
	int mDataLeng;
};

} // namespace Image

#endif // INCLUDED_COMMON_PIXEL_BITMAP_H