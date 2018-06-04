#ifndef INCLUDED_SEQUENCE_BOOK5_H
#define INCLUDED_SEQUENCE_BOOK5_H

#include "MainChild.h"

#define LINE_NUM 14

namespace Image {
	class DCBitmap;
}

namespace Sequence {

class MainParent;

class Book5 : public MainChild {
public:
	Book5( HDC& hdc, MainParent* parent );
	~Book5( void );
	void update( MainParent* parent );
	void draw( HDC& hdc, MainParent* parent );

private:
	enum DotStateID {
		DOT_BLACK,
		DOT_WHITE,
		DOT_NONE
	};

	typedef struct _DOT_STATE {
		int x;
		int y;
		int sizeX;
		int sizeY;
		float ratioW;
		float ratioB;
		DotStateID state;
	} DotState;

	void updateBoard( void );
	void clickDot( DotState* target, int x, int y );
	void changeDot( DotState* target );

	Image::DCBitmap* mBoardBmp;
	
	DotState mDotState[ LINE_NUM ][ LINE_NUM ];
};

} //namespace Sequence

#endif // INCLUDED_SEQUENCE_BOOK5_H
