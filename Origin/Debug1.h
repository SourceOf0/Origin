#ifndef INCLUDED_SEQUENCE_DEBUG1_H
#define INCLUDED_SEQUENCE_DEBUG1_H

#include "MainChild.h"

namespace Image {
	class PixelBitmap;
	class DCBitmap;
}

namespace Sequence {

class MainParent;

class Debug1 : public MainChild {
public:
	Debug1( HDC& hdc );
	~Debug1( void );
	void update( MainParent* parent );
	void draw( HDC& hdc, MainParent* parent );

private:

	Image::DCBitmap* mBackBmp;
};

} //namespace Sequence

#endif // INCLUDED_SEQUENCE_DEBUG1_H
