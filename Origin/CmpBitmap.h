#ifndef INCLUDED_IMAGE_CMP_BITMAP_H
#define INCLUDED_IMAGE_CMP_BITMAP_H

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

class PixelBitmap;
class DCBitmap;

class CmpBitmap
{
public:
	CmpBitmap( unsigned int width, unsigned int height, char colorNum );
	~CmpBitmap( void );

	int setData( unsigned char color, unsigned int count );
	int drawData( PixelBitmap* target );
	int drawData( HDC& hdc );
	int drawWindow( void );

	float mX;
	float mY;
	unsigned int mWidth;
	unsigned int mHeight;
	char mColorNum;
	unsigned char mUseColor;

private :
	typedef struct _COLOR_NODE {
		ColorID color;
		unsigned int count;
		_COLOR_NODE* next;
	} ColorNode;

	DCBitmap** mLayer;
	PixelBitmap* mPixelBitmap;
	ColorNode* mFirstNode;
	ColorNode* mNowNode;
};

} // namespace Image

#endif // INCLUDED_IMAGE_CMP_BITMAP_H