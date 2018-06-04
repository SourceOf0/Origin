#ifndef INCLUDED_SEQUENCE_TITLE_H
#define INCLUDED_SEQUENCE_TITLE_H

#include "MainChild.h"

#define POINT_TRACK_NUM 50

namespace Common {
	class PixelBitmap;
	class DCBitmap;
}

namespace Sequence {
class MainParent;

class Title : public MainChild {
	public:
		Title( HDC& hdc );
		~Title( void );
		void update( HDC& hdc, MainParent* parent );
private:

	typedef struct _POINT_TRACK {
		int x;
		int y;
		int count;
	} PointTrack;

	int setPointMask( void );

	Common::DCBitmap* mBackBmp1;
	Common::DCBitmap* mBackBmp2;
	Common::DCBitmap* mBackBmp3;
	Common::DCBitmap* mFrontBmp;
	Common::DCBitmap* mMaskBmp;
	Common::DCBitmap* mMaskBlockBmp;
	Common::DCBitmap* mPointBmp;

	int mCount;
	int mChangeCount;
	int mBackIndex;
	POINT mOldMousePos;
	PointTrack mPointTrack[POINT_TRACK_NUM];
};

} //namespace Sequence

#endif
