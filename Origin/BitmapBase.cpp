#include "BitmapBase.h"
#include "DCBitmap.h"

namespace Image {

DCBitmap** BitmapBase::mTone = 0;

void BitmapBase::init( unsigned int width, unsigned int height )
{
	mX = 0;
	mY = 0;
	mWidth = width;
	mHeight = height;
	mUseColor = 0;
}


} // namespace Image