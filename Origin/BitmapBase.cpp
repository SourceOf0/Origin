#include "BitmapBase.h"

namespace Image {

void BitmapBase::init( unsigned int width, unsigned int height )
{
	mX = 0;
	mY = 0;
	mWidth = width;
	mHeight = height;
	mUseColor = 0;
}

} // Image