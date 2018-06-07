#include "MainParent.h"
#include "MainChild.h"
#include "Book6.h"

#include "DCBitmap.h"

#include "SceneManager.h"
#include "HandManager.h"
#include "NoteManager.h"

#include <Math.h>

#define PANEL_SIZE 48
#define PANEL_SIZE_HALF 24
#define PANEL_SIZE_TWICE 96
#define PANEL_X_NUM 7
#define PANEL_Y_NUM 7
#define FIELD_LINE_SIZE 18
#define FIELD_LINE_SIZE_HALF 9

#define ROTATION_UP_NUM 1.570796
#define ROTATION_DOWN_NUM 4.712388
#define ROTATION_LEFT_NUM 3.141592
#define ROTATION_RIGHT_NUM 0.0
#define ROTATION_MAX_NUM 6.283184

#define BUTTON_SIZE 80
#define BUTTON_SIZE_HALF 40
#define BUTTON_LINE_SIZE 5

#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 80
#define BUTTON_MOVE_COUNT_MAX 8 

#define MOVE_SPEED 4
#define TURN_SPEED 0.08

namespace Sequence {

Book6::Book6( HDC& hdc, MainParent* parent ) : 
mIsMove( FALSE ),
mMaxMoveNum( 0 )
{
	const int VIEW_WIDTH = Main::SceneManager::VIEW_WIDTH;
	const int VIEW_HEIGHT = Main::SceneManager::VIEW_HEIGHT;
	int fieldWidth = PANEL_SIZE * ( PANEL_X_NUM * 2 - 1 ) + FIELD_LINE_SIZE * 2 + 1;
	int fieldHeight = PANEL_SIZE * ( PANEL_Y_NUM * 2 - 1 ) + FIELD_LINE_SIZE * 2 + 1;

	mCarState.x = PANEL_SIZE * 6;
	mCarState.y = PANEL_SIZE * 6;
	mCarState.rotation = ROTATION_UP_NUM;
	mCarState.direction = DIR_UPSIDE;
	mCarState.state = CAR_NONE;

	for( int i = 0; i < BUTTON_MAX_NUM; ++i ) {
		ButtonState *target = &mButtonState[ i ];
		target->x = static_cast< int >( BUTTON_SIZE * 1.5 * ( i / 7 ) + fieldWidth + 100 );
		target->y = static_cast< int >( BUTTON_SIZE * 1.0 * ( i % 7 ) + 160 );
		target->partsSize = static_cast< int >( BUTTON_SIZE * 0.3 );
		target->instruction = CAR_NONE;
	}

	mCarBmp = new Image::DCBitmap( hdc, PANEL_SIZE, PANEL_SIZE, 0 );
	mCarBmp->setBlack();

	mButtonBmp = new Image::DCBitmap( hdc, VIEW_WIDTH - fieldWidth - PANEL_SIZE_HALF, VIEW_HEIGHT, 0 );
	mButtonBmp->mX = PANEL_SIZE + fieldWidth;
	mButtonBmp->setBlack();

	mBackBmp = new Image::DCBitmap( hdc, fieldWidth, VIEW_HEIGHT, 0 );
	mBackBmp->mX = PANEL_SIZE;
	mBackBmp->mY = PANEL_SIZE;
	mBackBmp->setBlack();

	HPEN hPenB = CreatePen( PS_SOLID, 1, RGB( 0, 0, 0 ) );
	HPEN hPenW1 = CreatePen( PS_SOLID, BUTTON_LINE_SIZE, RGB( 255, 255, 255 ) );
	HPEN hPenW2 = CreatePen( PS_INSIDEFRAME, FIELD_LINE_SIZE, RGB( 255, 255, 255 ) );
	HBRUSH hBrushB = CreateSolidBrush( RGB( 0, 0, 0 ) );
	HBRUSH hBrushW = CreateSolidBrush( RGB( 255, 255, 255 ) );

	SelectObject( mBackBmp->mHdcBmp, hPenW2 );
	SelectObject( mBackBmp->mHdcBmp, hBrushB );

	Rectangle( mBackBmp->mHdcBmp, 0, 0, fieldWidth, fieldHeight );

	SelectObject( mBackBmp->mHdcBmp, hPenB );
	SelectObject( mBackBmp->mHdcBmp, hBrushW );
	
	for( int j = 0; j < PANEL_Y_NUM; ++j ) {
		for( int i = 0; i < PANEL_X_NUM; ++i ) {
			drawPanel( PANEL_SIZE_TWICE * i + FIELD_LINE_SIZE, PANEL_SIZE_TWICE * j + FIELD_LINE_SIZE );
		}
	}

	DeleteObject( hPenB );
	DeleteObject( hPenW1 );
	DeleteObject( hPenW2 );
	DeleteObject( hBrushB );
	DeleteObject( hBrushW );

	mStartButton.x = static_cast< int >( fieldWidth + 100 );
	mStartButton.y = static_cast< int >( mButtonBmp->mY + 40 );
	mStartButton.partsSize = 0;

	drawCar();
}

Book6::~Book6()
{
	delete mBackBmp;
	mBackBmp = 0;

	delete mCarBmp;
	mCarBmp = 0;

	delete mButtonBmp;
	mButtonBmp = 0;

	if( mMaxMoveNum == 0 ) {
	} else if( mMaxMoveNum < 4 ) {
		Main::NoteManager::inst()->setNextPage( NOTE_BOOK6_1 );
	} else if( mMaxMoveNum < 8 ) {
		Main::NoteManager::inst()->setNextPage( NOTE_BOOK6_2 );
	} else {
		Main::NoteManager::inst()->setNextPage( NOTE_BOOK6_3 );
	}
}

void Book6::drawPanel( int setX, int setY )
{
	int x1 = setX;
	int y1 = setY;
	int x2 = setX + PANEL_SIZE;
	int y2 = setY + PANEL_SIZE;
	int fixX = static_cast< int >( PANEL_SIZE * 0.2 );
	int fixY = static_cast< int >( PANEL_SIZE * 0.2 );

	POINT pos[ 8 ];

	pos[ 0 ].x = x1 + fixX;
	pos[ 0 ].y = y1;
	pos[ 1 ].x = x2 - fixX;
	pos[ 1 ].y = y1;
	pos[ 2 ].x = x2;
	pos[ 2 ].y = y1 + fixY;
	pos[ 3 ].x = x2;
	pos[ 3 ].y = y2 - fixY;
	pos[ 4 ].x = x2 - fixX;
	pos[ 4 ].y = y2;
	pos[ 5 ].x = x1 + fixX;
	pos[ 5 ].y = y2;
	pos[ 6 ].x = x1;
	pos[ 6 ].y = y2 - fixY;
	pos[ 7 ].x = x1;
	pos[ 7 ].y = y1 + fixY;

	Polygon( mBackBmp->mHdcBmp, pos, 8 );
	
}

#include "Book6Button.h"
#include "Book6Car.h"

void Book6::update( MainParent* parent )
{
	Main::HandManager::inst()->setState( Main::HandManager::HAND_NORMAL );

	if( Main::HandManager::inst()->getX() > Main::SceneManager::VIEW_WIDTH - BOOK_CORNAR_HIT_SIZE && Main::HandManager::inst()->getY()> Main::SceneManager::VIEW_HEIGHT - BOOK_CORNAR_HIT_SIZE ) {
		if( Main::HandManager::isClick ) {
			Main::HandManager::inst()->setState( Main::HandManager::HAND_NORMAL );
			parent->moveTo( parent->SEQ_ROOM );
		} else {
			Main::HandManager::inst()->setState( Main::HandManager::HAND_CLOSE );
		}
	}

	updateButton();
	updateCar();
}

void Book6::draw( HDC& hdc, MainParent* parent )
{
	mBackBmp->drawWindow();
	mButtonBmp->drawWindowOr();
	mCarBmp->drawWindowInv( mCarState.x + FIELD_LINE_SIZE + static_cast< int >( mBackBmp->mX ), mCarState.y + FIELD_LINE_SIZE + static_cast< int >( mBackBmp->mY ) );
}

} // namespace Sequence