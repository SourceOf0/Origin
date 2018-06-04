#ifndef INCLUDED_SEQUENCE_BOOK6_H
#define INCLUDED_SEQUENCE_BOOK6_H

#include "MainChild.h"

#define BUTTON_MAX_NUM 14

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
		CAR_TURN_LEFT,
		CAR_TURN_RIGHT,
		CAR_NONE
	};

	enum DirectionID {
		DIR_UPSIDE,
		DIR_DOWNSIDE,
		DIR_LEFTSIDE,
		DIR_RIGHTSIDE,
		DIR_NONE
	};

	typedef struct _CAR_STATE {
		int x;
		int y;
		double rotation;
		DirectionID direction;
		CarStateID state;
	} CarState;

	typedef struct _BUTTON_STATE {
		int x;
		int y;
		int partsSize;
		CarStateID instruction;
	} ButtonState;

	void drawPanel( int setX, int setY );
	void drawCar( void );
	void drawButton( void );

	void updateButton( void );

	void checkNext( void );
	void endMove( void );
	void updateCar( void );
	void forwardCar( void );
	void turnLeftCar( void );
	void turnRightCar( void );
	void moveCar( void );

	Image::DCBitmap* mBackBmp;
	Image::DCBitmap* mCarBmp;
	Image::DCBitmap* mButtonBmp;

	BOOL mIsMove;
	CarState mCarState;
	ButtonState mButtonState[ BUTTON_MAX_NUM ];
	ButtonState mStartButton;
};

} //namespace Sequence

#endif // INCLUDED_SEQUENCE_BOOK6_H
