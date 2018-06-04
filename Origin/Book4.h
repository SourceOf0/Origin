#ifndef INCLUDED_SEQUENCE_BOOK4_H
#define INCLUDED_SEQUENCE_BOOK4_H

#include "MainChild.h"

#define MAX_SPLASH_NUM 30
#define MAX_PIECE_NUM 30

namespace Image {
	class DCBitmap;
}

namespace Sequence {

class MainParent;

class Book4 : public MainChild {
public:
	Book4( HDC& hdc, MainParent* parent );
	~Book4( void );
	void update( MainParent* parent );
	void draw( HDC& hdc, MainParent* parent );

private:
	enum BallImageID {
		IMAGE_BALL_NORMAL,
		IMAGE_BALL_LEFT,
		IMAGE_BALL_RIGHT,
		IMAGE_BALL_STOP,
		IMAGE_BALL_JUMP,
		IMAGE_BALL_FALL,
		IMAGE_BALL_SHAKE,

		IMAGE_BALL_NONE
	};
	enum BallStateID {
		STATE_BALL_SETTING,
		STATE_BALL_FALL,
		STATE_BALL_JUMP_START,
		STATE_BALL_JUMP,

		STATE_BALL_NONE
	};

	typedef struct _BALL_STATE {
		int x;
		int y;
		int vy;
		int count;
		BallStateID state;
		BallImageID image;
	} BallState;

	typedef struct _BOARD_STATE {
		int x;
		int y;
		int count;
		int state;
	} BoardState;

	typedef struct _SPLASH_STATE {
		int x;
		int y;
		int vx;
		int vy;
		int count;
		int kind;
	} SplashState;

	typedef struct _PIECE_STATE {
		int x;
		int y;
		int vx;
		int vy;
		int count;
		int kind;
	} PieceState;

	void moveBall( void );
	void moveBallNormal( BOOL isClick, int mouseX, int mouseY );
	void moveBallLeft( BOOL isClick, int mouseX, int mouseY );
	void moveBallRight( BOOL isClick, int mouseX, int mouseY );
	void moveBallStop( BOOL isClick, int mouseX, int mouseY );
	void moveBallJump( BOOL isClick, int mouseX, int mouseY );
	void moveBallFall( BOOL isClick, int mouseX, int mouseY );
	void moveBallShake( BOOL isClick, int mouseX, int mouseY );
	void resetBall( void );
	BOOL isHitBoard( int mouseX, int mouseY );
	void breakBallX( void );
	void breakBallY( void );

	Image::DCBitmap* mBallImageArr[ IMAGE_BALL_NONE ];
	Image::DCBitmap* mBoardImage;
	Image::DCBitmap* mSplashImage;
	Image::DCBitmap* mPieceImage;

	BallState mBallState;
	BoardState mBoardState;
	SplashState mSplashState[ MAX_SPLASH_NUM ];
	PieceState mPieceState[ MAX_PIECE_NUM ];

	BOOL mWasFall;
	BOOL mWasKeep;
};

} //namespace Sequence

#endif // INCLUDED_SEQUENCE_BOOK4_H
