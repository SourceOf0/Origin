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

	static ColorID getColor( unsigned char color );
	static unsigned int setBlack( PixelBitmap* target, unsigned int count, unsigned int index );
	static unsigned int setWhite( PixelBitmap* target, unsigned int count, unsigned int index );
	static unsigned int setTone( PixelBitmap* target, unsigned int count, unsigned int index );

	DCBitmap* getDCBitmap( HDC& hdc );
	void setData( unsigned char color, unsigned int count );
	void drawData( HDC& hdc );

	void drawWindow( void );
	void drawWindow( int x, int y );

	char mColorNum;

private :
	typedef struct _COLOR_DATA {
		unsigned char color;
		unsigned int count;
	} ColorData;

	DCBitmap** mLayer;

	unsigned int mMaxDataNum;
	unsigned int mSetDataNum;
	ColorData** mColorData;
};

} // namespace Image

#endif // INCLUDED_IMAGE_CMP_BITMAP_H