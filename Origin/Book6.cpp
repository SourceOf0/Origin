#include "MainParent.h"
#include "MainChild.h"
#include "Book6.h"

#include "DCBitmap.h"

#include "SceneManager.h"
#include "HandManager.h"

#define MOVE_SPEED 4

namespace Sequence {

Book6::Book6( HDC& hdc, MainParent* parent )
{
	int windowWidth = Main::SceneManager::windowWidth;
	int windowHeight = Main::SceneManager::windowHeight;

	mPanelBmp = new Image::DCBitmap( hdc, windowWidth, windowHeight, 0x00 );

	mPanelBmp->setBlack();

	HPEN hPen = CreatePen( PS_SOLID, 1, RGB( 255, 255, 255 ) );
	HBRUSH hBrushW = CreateSolidBrush( RGB( 255, 255, 255 ) );
	HBRUSH hBrushB = CreateSolidBrush( RGB( 0, 0, 0 ) );

	SelectObject( mPanelBmp->mHdcBmp, hPen );
	SelectObject( mPanelBmp->mHdcBmp, hBrushW );
	
	drawPanel( 100, 100, 200, 200 );

	DeleteObject( hPen );
	DeleteObject( hBrushW );
	DeleteObject( hBrushB );
}

Book6::~Book6()
{
	delete mPanelBmp;
	mPanelBmp = 0;
}

void Book6::update( MainParent* parent )
{
	int windowWidth = Main::SceneManager::windowWidth;
	int windowHeight = Main::SceneManager::windowHeight;

	Main::HandManager::inst()->setState( Main::HandManager::HAND_NORMAL );

}

void Book6::drawPanel( int x1, int y1, int x2, int y2 )
{
	int fixX = static_cast< int >( ( x2 - x1 ) * 0.1 );
	int fixY = static_cast< int >( ( y2 - y1 ) * 0.1 );

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
	pos[ 6 ].y = y2 - fixX;
	pos[ 7 ].x = x1;
	pos[ 7 ].y = y1 + fixY;

	Polygon( mPanelBmp->mHdcBmp, pos, 8 );
	
}

void Book6::updateCar( void )
{
	int windowHeight = Main::SceneManager::windowHeight;

	int mouseX = Main::HandManager::inst()->getX();
	int mouseY = Main::HandManager::inst()->getY();
	BOOL isClick = Main::SceneManager::isClick;

}

void Book6::draw( HDC& hdc, MainParent* parent )
{
	mPanelBmp->drawWindowOr();
}

} // namespace Sequence