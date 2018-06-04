#ifndef INCLUDED_SEQUENCE_BOOK7_H
#define INCLUDED_SEQUENCE_BOOK7_H

#include "MainChild.h"

#define OBJ_X_NUM 32
#define OBJ_Y_NUM 12
#define MAN_NUM 10
#define ENTRANCE_PAIR_NUM 3

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

	enum ManStateID {
		MAN_WALK,
		MAN_ENTER_START,
		MAN_ENTER_END,
		MAN_STAY_TURN,
		MAN_STAY_REST,
		MAN_LADDER_UP,
		MAN_LADDER_DOWN,

		MAN_NONE
	};

	typedef struct _OBJ_STATE {
		int holdX;
		int holdY;
		int indexX;
		int indexY;
		int useNum;
		BOOL isHold;
		ObjImageID image;
	} ObjState;

	typedef struct _MAN_STATE {
		int x;
		int line;
		int count;
		int animeState;
		ObjState* target;
		BOOL isLeft;
		ManImageID image;
		ManStateID state;
	} ManState;

	void drawMan( ManState* target );
	void moveMan( ManState* target );
	void moveManWalk( ManState* target );
	void moveManEnterStart( ManState* target );
	void moveManEnterEnd( ManState* target );
	void moveManRest( ManState* target );
	void moveManTurn( ManState* target );
	void moveManLadderUp( ManState* target );
	void moveManLadderDown( ManState* target );

	BOOL checkEntrance( ManState* target, BOOL isSet = TRUE );
	BOOL checkWall( ManState* target, BOOL isSet = TRUE );
	BOOL checkLadder( ManState* target, BOOL isSet = TRUE );

	int getCount( int count );
	int getMaxCount( ManImageID image );
	void setManState( ManState* target, ManStateID state );
	void addTarget( ManState* targetMan, ObjState* targetObj );
	void removeTarget( ManState* targetMan );

	void checkHitObj( int mouseX, int mouseY );
	void takeObj( int mouseX, int mouseY );
	void moveObj( int mouseX, int mouseY );
	void putObj( int targetX, int targetY );
	void putEntrance( int targetX, int targetY );
	void putLadder( int targetX, int targetY );
	void putWall( int targetX, int targetY );

	Image::DCBitmap* mManImageArr[ IMAGE_MAN_NONE ];
	Image::DCBitmap* mObjImage;

	ObjState mObjState[ OBJ_Y_NUM ][ OBJ_X_NUM ];
	ObjState* mMoveTarget;
	ObjState* mEntranceState[ ENTRANCE_PAIR_NUM ][ 2 ];

	ManState mManState[ MAN_NUM ];
};

} //namespace Sequence

#endif // INCLUDED_SEQUENCE_BOOK7_H
