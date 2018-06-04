#ifndef INCLUDED_IMAGE_PIXEL_BITMAP_H
#define INCLUDED_IMAGE_PIXEL_BITMAP_H

#include <windows.h>

#define PIXEL_CHAR_DATA_MAX 1000000

namespace Image {

class PixelBitmap
{
public:
	PixelBitmap( int width, int height, unsigned char setColor = 0 );
	~PixelBitmap( void );

	void reset( int width, int height, unsigned char setColor = 0 );

	char getBit( int x, int y );
	int setData( unsigned int index, unsigned char data );
	int setBlack( int x, int y );
	int setBlack( unsigned int index );
	int setWhite( int x, int y );
	int setWhite( unsigned int index );
	int setRev( int x, int y );

	float mX;
	float mY;
	int mWidth;
	int mHeight;
	unsigned char mPixelData[ PIXEL_CHAR_DATA_MAX ];

private:
	int mWidthIndex;
	int mHeightIndex;
	unsigned int mDataLeng;
};

} // namespace Image

#endif // INCLUDED_IMAGE_PIXEL_BITMAP_H