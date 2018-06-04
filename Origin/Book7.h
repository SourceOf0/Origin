#ifndef INCLUDED_SEQUENCE_BOOK7_H
#define INCLUDED_SEQUENCE_BOOK7_H

#include "MainChild.h"

#define OBJ_X_NUM 32
#define OBJ_Y_NUM 12
#define MAN_NUM 2
#define ENTRANCE_NUM 2

namespace Image {
	class DCBitmap;
}

namespace Sequence {

class MainParent;

class Book7 : public MainChild {
public:
	Book7( HDC& hdc, MainParent* parent );
	~Book7( void );
	void update( MainParent* parent );
	void draw( HDC& hdc, MainParent* parent );

private:
	enum ManImageID {
		IMAGE_MAN_STAY,
		IMAGE_MAN_WALK,
		IMAGE_MAN_LADDER,

		IMAGE_MAN_NONE
	};
	enum ObjImageID {
		IMAGE_OBJ_FLOOR,
		IMAGE_OBJ_ENTRANCE,
		IMAGE_OBJ_LADDER,
		IMAGE_OBJ_WALL,

		IMAGE_OBJ_NONE
	};

	typedef struct _OBJ_STATE {
		int x;
		int y;
		int useNum;
		BOOL isHold;
		ObjImageID image;
	} ObjState;

	typedef struct _ENTRANCE_STATE {
		int indexX;
		int indexY;
		ObjState* target;
	} EntranceState;

	typedef struct _MAN_STATE {
		int x;
		int line;
		int count;
		int state;
		ObjState* target;
		BOOL isLeft;
		BOOL isEnter;
		ManImageID image;
	} ManState;

	void drawMan( ManState* target );
	void moveMan( ManState* target );
	void moveManStay( ManState* target );
	void moveManWalk( ManState* target );
	void moveManLadder( ManState* target );

	BOOL checkEntrance( ManState* target );
	BOOL checkLadder( ManState* target );
	BOOL checkWall( ManState* target );

	Image::DCBitmap* mManImageArr[ IMAGE_MAN_NONE ];
	Image::DCBitmap* mObjImage;

	ObjState mObjState[ OBJ_Y_NUM ][ OBJ_X_NUM ];
	ObjState* mMoveTarget;
	EntranceState mEntranceState[ ENTRANCE_NUM ];

	ManState mManState[ MAN_NUM ];
};

} //namespace Sequence

#endif // INCLUDED_SEQUENCE_BOOK7_H
