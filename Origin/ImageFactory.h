#ifndef INCLUDED_MAIN_IMAGE_FACTORY_H
#define INCLUDED_MAIN_IMAGE_FACTORY_H

#include <windows.h>

namespace Image {
	class DCBitmap;
	class PixelBitmap;
	class CmpBitmap;
	class BitmapBase;
}

namespace Main {

class ImageFactory
{
public:
	static ImageFactory* inst( void );
	static void create( HDC& hdc );
	static void destroy( void );

	Image::DCBitmap* loadDC( HDC& hdc, const char* fileName );
	Image::CmpBitmap* loadCmp( HDC& hdc, const char* fileName );
	Image::BitmapBase* load( HDC& hdc, const char* fileName );

private:
	ImageFactory( HDC& hdc );
	ImageFactory( ImageFactory& );
	~ImageFactory( void );

	static ImageFactory* mInst;
};

} // namespace Main

#endif // INCLUDED_MAIN_IMAGE_FACTORY_H
