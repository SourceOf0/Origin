#include "MainParent.h"
#include "MainChild.h"
#include "Book5.h"

#include "DCBitmap.h"

#include "SceneManager.h"
#include "HandManager.h"
#include "NoteManager.h"

#define LINE_START_X 700
#define LINE_START_Y 350
#define LINE_RATIO 1.0
#define LINE_ADD_RATIO 0.46

#define ADD_RATIO_SPEED 0.2f
#define MOVE_SPEED 8

namespace Sequence {

Book5::Book5( HDC& hdc, MainParent* parent ) :
mUseNum( 0 )
{
	int windowWidth = Main::SceneManager::windowWidth;
	int windowHeight = Main::SceneManager::windowHeight;

	mBoardBmp = new Image::DCBitmap( hdc, windowWidth, windowHeight, 0x00 );

	for( int y = 0; y < LINE_NUM; ++y ) {
		for( int x = 0; x < LINE_NUM; ++x ) {
			DotState* target = &mDotState[ y ][ x ];
			target->x = 0;
			target->y = 0;
			target->sizeX = 0;
			target->sizeY = 0;
			target->ratioB = 0.0;
			target->ratioW = 0.0;
			target->state = DOT_NONE;
		}
	}

	double ratio1 = LINE_RATIO;
	double ratio2 = LINE_RATIO;
	for( int indexY = 0; indexY < LINE_NUM; ++indexY ) {
		ratio1 = LINE_RATIO;
		for( int indexX = 0; indexX < LINE_NUM; ++indexX ) {
			double a = ( windowHeight + LINE_START_Y ) / ( windowHeight * ratio1 );
			double b = LINE_START_X * a - LINE_START_Y;
			double c = ( windowHeight + LINE_START_Y ) / ( -windowHeight * ratio2 );
			double d = -( LINE_START_X + windowWidth ) * c - LINE_START_Y;
			double x = ( d - b ) / ( a - c );
			double y = a * x + b;

			ratio1 += LINE_ADD_RATIO;
	
			DotState* target = &mDotState[ indexY ][ indexX ];
			target->x = static_cast< int >( x + 0.5 );
			target->y = static_cast< int >( y + 0.5 );
		}
		ratio2 += LINE_ADD_RATIO;
	}
}

Book5::~Book5()
{
	delete mBoardBmp;
	mBoardBmp = 0;

	if( mUseNum == 5 ) {
		Main::NoteManager::inst()->setNextPage( NOTE_BOOK5_1 );
	} else if( mUseNum > 10 && mUseNum < 100 ) {
		Main::NoteManager::inst()->setNextPage( NOTE_BOOK5_2 );
	} else if( mUseNum >= 100 ) {
		Main::NoteManager::inst()->setNextPage( NOTE_BOOK5_3 );
	}
}

void Book5::update( MainParent* parent )
{
	int windowWidth = Main::SceneManager::windowWidth;
	int windowHeight = Main::SceneManager::windowHeight;

	Main::HandManager::inst()->setState( Main::HandManager::HAND_NORMAL );

	mBoardBmp->setBlack();

	HPEN hPen = CreatePen( PS_SOLID, 1, RGB( 255, 255, 255 ) );
	HBRUSH hBrushW = CreateSolidBrush( RGB( 255, 255, 255 ) );
	HBRUSH hBrushB = CreateSolidBrush( RGB( 0, 0, 0 ) );

	SelectObject( mBoardBmp->mHdcBmp, hPen );
	
	double ratio = LINE_RATIO;
	double setX = windowHeight * ratio;
	for( int i = 0; i < LINE_NUM; ++i ) {
		MoveToEx( mBoardBmp->mHdcBmp, -LINE_START_X, -LINE_START_Y, NULL );
		LineTo( mBoardBmp->mHdcBmp, static_cast< int >( -LINE_START_X + setX ), windowHeight );
		MoveToEx( mBoardBmp->mHdcBmp, LINE_START_X + windowWidth, -LINE_START_Y, NULL );
		LineTo( mBoardBmp->mHdcBmp, static_cast< int >( LINE_START_X + windowWidth - setX ), windowHeight );
		ratio += LINE_ADD_RATIO;
		setX = windowHeight * ratio;
	}

	updateBoard();

	int useNum = LINE_NUM * LINE_NUM;
	for( int y = 0; y < LINE_NUM; ++y ) {
		for( int x = 0; x < LINE_NUM; ++x ) {
			DotState* target = &mDotState[ y ][ x ];

			switch( target->state ) {
				case DOT_BLACK:
					if( target->ratioB < 1.0 ) {
						target->ratioB += ADD_RATIO_SPEED;
						if( target->ratioB >= 1.0 ) target->ratioB = 1.0;
					}
					if( target->ratioW > 0.0 ) {
						target->ratioW -= ADD_RATIO_SPEED;
						if( target->ratioW <= 0.0 ) target->ratioW = 0.0;
					}
					break;

				case DOT_WHITE:
					if( target->ratioB < 1.0 ) {
						target->ratioB += ADD_RATIO_SPEED;
						if( target->ratioB >= 1.0 ) target->ratioB = 1.0;
					}
					if( target->ratioW < 1.0 ) {
						target->ratioW += ADD_RATIO_SPEED;
						if( target->ratioW >= 1.0 ) target->ratioW = 1.0;
					}
					break;

				case DOT_NONE:
					--useNum;
					if( target->ratioB > 0.0 ) {
						target->ratioB -= ADD_RATIO_SPEED;
						if( target->ratioB <= 0.0 ) target->ratioB = 0.0;
					}
					if( target->ratioW > 0.0 ) {
						target->ratioW -= ADD_RATIO_SPEED;
						if( target->ratioW <= 0.0 ) target->ratioW = 0.0;
					}
					break;
			}

			int setSizeX = static_cast< int >( target->sizeX * target->ratioB );
			int setSizeY = static_cast< int >( target->sizeY * target->ratioB );
			SelectObject( mBoardBmp->mHdcBmp, hBrushB );
			Ellipse( mBoardBmp->mHdcBmp, target->x - setSizeX, target->y - setSizeY, target->x + setSizeX, target->y + setSizeY );
			
			setSizeX = static_cast< int >( target->sizeX * target->ratioW );
			setSizeY = static_cast< int >( target->sizeY * target->ratioW );
			SelectObject( mBoardBmp->mHdcBmp, hBrushW );
			Ellipse( mBoardBmp->mHdcBmp, target->x - setSizeX, target->y - setSizeY, target->x + setSizeX, target->y + setSizeY );
		}
	}
	if( useNum > mUseNum ) {
		mUseNum = useNum;
	}

	DeleteObject( hPen );
	DeleteObject( hBrushW );
	DeleteObject( hBrushB );

	if( Main::HandManager::inst()->getX() > windowWidth - BOOK_CORNAR_HIT_SIZE && Main::HandManager::inst()->getY() > windowHeight - BOOK_CORNAR_HIT_SIZE ) {
		if( Main::HandManager::isClick ) {
			Main::HandManager::inst()->setState( Main::HandManager::HAND_NORMAL );
			parent->moveTo( parent->SEQ_ROOM );
		} else {
			Main::HandManager::inst()->setState( Main::HandManager::HAND_CLOSE );
		}
	}
}

void Book5::updateBoard( void )
{
	int windowHeight = Main::SceneManager::windowHeight;

	int mouseX = Main::HandManager::inst()->getX();
	int mouseY = Main::HandManager::inst()->getY();
	BOOL isClick = Main::HandManager::isClick;

	for( int y = 0; y < LINE_NUM; ++y ) {
		for( int x = 0; x < LINE_NUM; ++x ) {
			DotState* target = &mDotState[ y ][ x ];
			double ratio = static_cast< double >( target->y ) / ( windowHeight + 100 );
			int sizeX = static_cast< int >( ratio * 20 ) + 10;
			int sizeY = static_cast< int >( sizeX * ratio ) + 5;
			int setX1 = target->x - sizeX - 10;
			int setY1 = target->y - sizeY - 10;
			int setX2 = target->x + sizeX + 10;
			int setY2 = target->y + sizeY + 10;
			if( sizeY > sizeX ) sizeY = sizeX;
			target->sizeX = sizeX;
			target->sizeY = sizeY;
			if( mouseX > setX1 && mouseX < setX2 && mouseY > setY1 && mouseY < setY2 ) {
				if( isClick ) {
					clickDot( target, x, y );
					Main::HandManager::inst()->setState( Main::HandManager::HAND_PUSH_AFTER );
				} else {
					Main::HandManager::inst()->setState( Main::HandManager::HAND_PUSH_BEFORE );
				}
			}
		}
	}
}

void Book5::clickDot( DotState* target, int x, int y )
{
	changeDot( target );
	if( ( x - 1 ) >= 0 ) {
		changeDot( &mDotState[ y ][ x - 1 ] );
	}
	if( ( x + 1 ) < LINE_NUM ) {
		changeDot( &mDotState[ y ][ x + 1 ] );
	}
	if( ( y - 1 ) >= 0 ) {
		changeDot( &mDotState[ y - 1 ][ x ] );
	}
	if( ( y + 1 ) < LINE_NUM ) {
		changeDot( &mDotState[ y + 1 ][ x ] );
	}
}

void Book5::changeDot( DotState* target )
{
	switch( target->state ) {
		case DOT_BLACK:
			target->state = DOT_WHITE;
			break;
		case DOT_WHITE:
			target->state = DOT_NONE;
			break;
		case DOT_NONE:
			target->state = DOT_BLACK;
			break;
	}
}

void Book5::draw( HDC& hdc, MainParent* parent )
{
	mBoardBmp->drawWindowOr();
}

} // namespace Sequence