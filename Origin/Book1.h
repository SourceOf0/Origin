#ifndef INCLUDED_SEQUENCE_BOOK1_H
#define INCLUDED_SEQUENCE_BOOK1_H

#include "MainChild.h"

#define BOOK1_IMAGE_NUM 22
#define BOOK1_VIEW_IMAGE_NUM 5
#define BOOK1_MASK_NUM 10
#define VIEW_SCHEDULE_NUM 10

namespace Image {
	class DCBitmap;
}

namespace Sequence {

class MainParent;

class Book1 : public MainChild {
public:
	Book1( HDC& hdc, MainParent* parent );
	~Book1( void );
	void update( MainParent* parent );
	void draw( HDC& hdc, MainParent* parent );

private:
	enum ImageID {
		IMAGE_00 = 0,
		IMAGE_01 = 5,
		IMAGE_02 = 6,
		IMAGE_03 = 7,
		IMAGE_04 = 8,
		IMAGE_05 = 9,
		IMAGE_06 = 10,
		IMAGE_07 = 11,
		IMAGE_08 = 12,
		IMAGE_09 = 13,
		IMAGE_10 = 14,
		IMAGE_11 = 15,
		IMAGE_12 = 16,
		IMAGE_13 = 17,
		IMAGE_14 = 18,
		IMAGE_15 = 19,
		IMAGE_16 = 20,
		IMAGE_17 = 21,

		IMAGE_NONE = BOOK1_IMAGE_NUM
	};

	enum MaskID {
		MASK_1 = 1,
		MASK_2 = 2,
		MASK_3 = 3,
		MASK_4 = 4,

		MASK_NONE = BOOK1_IMAGE_NUM
	};


	typedef struct _IMAGE_STATE {
		int x;
		int y;
		int count;
		ImageID kind;
	} ImageState;

	typedef struct _MASK_STATE {
		int x;
		int y;
		int count;
		MaskID kind;
	} MaskState;

	void nextMotion( void );
	void setSchedule( void );
	void setImage( ImageState* target, int x, int y, int count, ImageID kind );
	void setMask( MaskState* target, int x, int y, int count, MaskID kind );
	void drawTone( HDC& targetHDC, int kind );
	void drawToneOr( HDC& targetHDC, int kind );
	void drawDot( HDC& targetHDC, int x, int y, int kind );
	void drawDotAnd( HDC& targetHDC, int x, int y, int kind );

	BOOL fadeIn( int partition );
	BOOL fadeOut( int partition );

	void motion1( void );
	void motion2( void );
	void motion3( void );
	void motion4( void );
	void motion5( void );
	void motion6( void );
	void motion7( void );
	void motion8( void );
	void motion9( void );
	void motion10( void );
	void motion11( void );
	void motion12( void );

	int mState;
	int mToneIndex;
	int mAnimeCount;
	int mAnimeState;

	int mSchedule[ VIEW_SCHEDULE_NUM ];
	int mScheduleIndex;

	ImageState mImage[ BOOK1_VIEW_IMAGE_NUM ];
	MaskState mMask[ BOOK1_MASK_NUM ];

	Image::DCBitmap* mBmp[ BOOK1_IMAGE_NUM ];
	Image::DCBitmap* mDotBmp;

	Image::DCBitmap* mMaskBmp;
	Image::DCBitmap* mMainBmp;

};

} //namespace Sequence

#endif // INCLUDED_SEQUENCE_BOOK1_H
