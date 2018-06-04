#ifndef INCLUDED_IMAGE_BITMAP_BASE_H
#define INCLUDED_IMAGE_BITMAP_BASE_H

#include <windows.h>

typedef enum _COLOR_ID {
	CLR_BLACK = 1 << 0,
	CLR_WHITE = 1 << 1,
	CLR_RED = 1 << 2,
	CLR_RED_GREEN = 1 << 3,
	CLR_GREEN = 1 << 4,
	CLR_GREEN_BLUE = 1 << 5,
	CLR_BLUE = 1 << 6,
	CLR_BLUE_RED = 1 << 7,
	
	CLR_OTHER = 0,
} ColorID;


namespace Image {

class BitmapBase
{
public:
	virtual ~BitmapBase( void ) {};

	void init( unsigned int width, unsigned int height );

	virtual void drawWindow( void ) = 0;
	virtual void drawWindow( int x, int y ) = 0;

	float mX;
	float mY;
	unsigned int mWidth;
	unsigned int mHeight;
	unsigned char mUseColor;
};

} // namespace Image

#endif // INCLUDED_IMAGE_BITMAP_BASE_H