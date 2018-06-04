#ifndef INCLUDED_SEQUENCE_BOOK2_H
#define INCLUDED_SEQUENCE_BOOK2_H

#include "MainChild.h"

#define POINT_TRACK_NUM 50

namespace Image {
	class DCBitmap;
}

namespace Sequence {

class MainParent;

class Book2 : public MainChild {
public:
	Book2( HDC& hdc, MainParent* parent );
	~Book2( void );
	void update( MainParent* parent );
	void draw( HDC& hdc, MainParent* parent );

private:
	typedef struct _POINT_TRACK {
		int x;
		int y;
		int count;
	} PointTrack;

	int setPointMask( void );

	Image::DCBitmap* mBackBmp1;
	Image::DCBitmap* mBackBmp2;
	Image::DCBitmap* mBackBmp3;
	Image::DCBitmap* mFrontBmp;
	Image::DCBitmap* mMaskBmp;
	Image::DCBitmap* mMaskBlockBmp;
	Image::DCBitmap* mPointBmp;

	int mCount;
	int mChangeCount;
	int mBackIndex;
	POINT mOldMousePos;
	PointTrack mPointTrack[ POINT_TRACK_NUM ];
};

} //namespace Sequence

#endif // INCLUDED_SEQUENCE_BOOK2_H
