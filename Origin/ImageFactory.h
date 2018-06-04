#ifndef INCLUDED_MAIN_IMAGE_FACTORY_H
#define INCLUDED_MAIN_IMAGE_FACTORY_H

#include <windows.h>

namespace Image {
	class PixelBitmap;
}

namespace Main {

class ImageFactory
{
public:
	static ImageFactory* inst();
	static void create( void );
	static void destroy( void );

	Image::PixelBitmap* load( const char* fileName );

private:
	ImageFactory( void );
	ImageFactory( ImageFactory& );
	~ImageFactory( void );

	static ImageFactory* mInst;
};

} // namespace Main

#endif // INCLUDED_MAIN_IMAGE_FACTORY_H
