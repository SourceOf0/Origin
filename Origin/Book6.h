#ifndef INCLUDED_SEQUENCE_BOOK6_H
#define INCLUDED_SEQUENCE_BOOK6_H

#include "MainChild.h"

namespace Image {
	class DCBitmap;
}

namespace Sequence {

class MainParent;

class Book6 : public MainChild {
public:
	Book6( HDC& hdc, MainParent* parent );
	~Book6( void );
	void update( MainParent* parent );
	void draw( HDC& hdc, MainParent* parent );

private:
	enum CarStateID {
		CAR_FORWARD,
		CAR_NONE
	};

	void drawPanel( int x1, int y1, int x2, int y2 );
	void updateCar( void );

	Image::DCBitmap* mPanelBmp;
};

} //namespace Sequence

#endif // INCLUDED_SEQUENCE_BOOK6_H
