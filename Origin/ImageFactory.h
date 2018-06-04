#ifndef INCLUDED_MAIN_IMAGE_FACTORY_H
#define INCLUDED_MAIN_IMAGE_FACTORY_H

#include <windows.h>
#include "BitmapBase.h"

namespace Image {
	class DCBitmap;
	class PixelBitmap;
	class BitmapBase;
}

namespace Main {

class ImageFactory
{
public:
	static ImageFactory* inst( void );
	static void create( HDC& hdc );
	static void destroy( void );

	Image::BitmapBase* loadAnime( HDC& hdc, int animeNum, const char* fileName[], BOOL isDC );
	Image::DCBitmap* loadDC( HDC& hdc, const char* fileName );
	Image::BitmapBase* load( HDC& hdc, const char* fileName );

private:
	ImageFactory( HDC& hdc );
	ImageFactory( ImageFactory& );
	~ImageFactory( void );

	ColorID getColor( unsigned char color );
	unsigned int setBlack( Image::PixelBitmap* target, unsigned int count, unsigned int index );
	unsigned int setWhite( Image::PixelBitmap* target, unsigned int count, unsigned int index );
	unsigned int setTone( Image::PixelBitmap* target, unsigned int count, unsigned int index );

	static ImageFactory* mInst;
	Image::PixelBitmap* mLayerData[ COLOR_KIND_NUM ];
};

} // namespace Main

#endif // INCLUDED_MAIN_IMAGE_FACTORY_H
