#ifndef INCLUDED_IMAGE_BITMAP_BASE_H
#define INCLUDED_IMAGE_BITMAP_BASE_H

#include <windows.h>

typedef enum _COLOR_ID {
	CLR_OTHER = 0,

	CLR_BLACK = 1 << 0,
	CLR_WHITE = 1 << 1,
	CLR_RED = 1 << 2,
	CLR_RED_GREEN = 1 << 3,
	CLR_GREEN = 1 << 4,
	CLR_GREEN_BLUE = 1 << 5,
	CLR_BLUE = 1 << 6,
	CLR_BLUE_RED = 1 << 7,
} ColorID;

#define COLOR_KIND_NUM 8

enum ToneID {
	TONE_001,
	TONE_002,
	TONE_003,
	TONE_004,
	TONE_005,
	TONE_006,
	TONE_007,
	TONE_008,
	TONE_009,
	TONE_010,
	TONE_011,
	TONE_012,
	TONE_013,
	TONE_014,
	TONE_015,

	TONE_NONE
};

namespace Image {

class DCBitmap;

class BitmapBase
{
public:
	virtual ~BitmapBase( void ) {};

	static DCBitmap** mTone;

	void init( unsigned int width, unsigned int height );

	virtual void drawWindow( void ) = 0;
	virtual void drawWindow( int x, int y ) = 0;

	double mX;
	double mY;
	unsigned int mWidth;
	unsigned int mHeight;
	unsigned char mUseColor;
};

} // namespace Image

#endif // INCLUDED_IMAGE_BITMAP_BASE_H