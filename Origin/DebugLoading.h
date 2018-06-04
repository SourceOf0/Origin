#ifndef INCLUDED_SEQUENCE_DEBUG_LOADING_H
#define INCLUDED_SEQUENCE_DEBUG_LOADING_H

#include "MainChild.h"

namespace Image {
	class DCBitmap;
}

namespace Sequence {

class MainParent;

class DebugLoading : public MainChild {
public:
	DebugLoading( HDC& hdc, MainParent* parent );
	~DebugLoading( void );
	void update( MainParent* parent );
	void draw( HDC& hdc, MainParent* parent );

private:
	Image::DCBitmap* mBackBmp;

	char mState;
	int mTargetX1;
	int mTargetY1;
	int mTargetX2;
	int mTargetY2;

	int mX1;
	int mY1;
	int mX2;
	int mY2;
};

} //namespace Sequence

#endif // INCLUDED_SEQUENCE_DEBUG2_H
