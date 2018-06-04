#ifndef INCLUDED_IMAGE_CMP_BITMAP_H
#define INCLUDED_IMAGE_CMP_BITMAP_H

#include <windows.h>
#include "BitmapBase.h"

namespace Image {

class PixelBitmap;
class DCBitmap;

class CmpBitmap : public BitmapBase
{
public:
	CmpBitmap( unsigned int width, unsigned int height, char colorNum, unsigned int dataNum );
	~CmpBitmap( void );

	int setData( unsigned char color, unsigned int count );
	int drawData( PixelBitmap* target );
	int drawData( HDC& hdc );

	void drawWindow( void );
	void drawWindow( int x, int y );

	char mColorNum;

private :
	typedef struct _COLOR_DATA {
		unsigned char color;
		unsigned int count;
	} ColorData;

	DCBitmap** mLayer;
	PixelBitmap* mPixelBitmap;

	unsigned int mMaxDataNum;
	unsigned int mSetDataNum;
	ColorData** mColorData;
};

} // namespace Image

#endif // INCLUDED_IMAGE_CMP_BITMAP_H