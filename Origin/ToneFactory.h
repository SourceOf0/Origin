#ifndef INCLUDED_MAIN_TONE_FACTORY_H
#define INCLUDED_MAIN_TONE_FACTORY_H

#include <windows.h>

namespace Image {
	class DCBitmap;
}

namespace Main {

class ToneFactory
{
public:
	static ToneFactory* inst();
	static void create( HDC& hdc );
	static void destroy( void );

private:
	ToneFactory( HDC& hdc );
	ToneFactory( ToneFactory& );
	~ToneFactory( void );

	static ToneFactory* mInst;
};

} // namespace Main

#endif // INCLUDED_MAIN_IMAGE_FACTORY_H
