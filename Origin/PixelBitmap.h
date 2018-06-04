#ifndef INCLUDED_IMAGE_PIXEL_BITMAP_H
#define INCLUDED_IMAGE_PIXEL_BITMAP_H

#include <windows.h>

namespace Image {

class PixelBitmap
{
public:
	PixelBitmap( int width, int height );
	~PixelBitmap( void );

	int drawWindow( void );

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
	unsigned char* mPixelData;

private:
	int mWidthIndex;
	int mHeightIndex;
	unsigned int mDataLeng;
};

} // namespace Image

#endif // INCLUDED_IMAGE_PIXEL_BITMAP_H