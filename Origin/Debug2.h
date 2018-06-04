#ifndef INCLUDED_SEQUENCE_DEBUG2_H
#define INCLUDED_SEQUENCE_DEBUG2_H

#include "MainChild.h"

#define DEBUG2_BMP_NUM 1

namespace Image {
	class BitmapBase;
	class DCBitmap;
}

namespace Sequence {

class MainParent;

class Debug2 : public MainChild {
public:
	Debug2( HDC& hdc, MainParent* parent );
	~Debug2( void );
	void update( MainParent* parent );
	void draw( HDC& hdc, MainParent* parent );

private:
	Image::BitmapBase* mTempBmp[ DEBUG2_BMP_NUM ];
	Image::DCBitmap* mBackBmp;
};

} //namespace Sequence

#endif // INCLUDED_SEQUENCE_DEBUG2_H
