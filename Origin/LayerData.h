#ifndef INCLUDED_IMAGE_LAYER_DATA_H
#define INCLUDED_IMAGE_LAYER_DATA_H

#include <windows.h>
#include "BitmapBase.h"

namespace Image {

class DCBitmap;

class LayerData : public BitmapBase
{
public:
	LayerData( HDC& hdc, unsigned int width, unsigned int height );
	~LayerData( void );

	void drawWindow( void );
	void drawWindow( int x, int y );
	void drawDCBitmap( DCBitmap* target, int x, int y, int width, int index );

	DCBitmap* mLayer[ COLOR_KIND_NUM ];
	DCBitmap* mViewTone;

private :
};

} // namespace Image

#endif // INCLUDED_IMAGE_LAYER_DATA_H