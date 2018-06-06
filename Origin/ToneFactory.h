#ifndef INCLUDED_MAIN_TONE_FACTORY_H
#define INCLUDED_MAIN_TONE_FACTORY_H

#include <windows.h>
#include "common.h"

namespace Main {

class ToneFactory
{
public:
	static ToneFactory* inst( void );
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
