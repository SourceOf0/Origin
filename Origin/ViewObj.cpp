#include "ViewObj.h"

#include "LayerData.h"
#include "HandManager.h"

namespace Sequence {

namespace Room {

void ViewObj::setData( PartsID partsID, int x, int y, BOOL isView )
{
	init( partsID, x, y );
	mDefX = x;
	mDefY = y;
	mIsView = isView;
}

void ViewObj::setPartsID( PartsID partsID )
{
	if( mPartsID == partsID ) return;
	setPartsSize( partsID );
}

void ViewObj::setView( BOOL isView )
{
	mIsView = isView;
}

void ViewObj::setPos( int x, int y )
{
	mX = x;
	mY = y;
}

void ViewObj::fixPos( int addX, int addY )
{
	mX = mDefX + addX;
	mY = mDefY + addY;
}

BOOL ViewObj::checkHit( void )
{
	Main::HandManager* handManager = Main::HandManager::inst();

	if( !isHit( handManager->getX(), handManager->getY() ) ) return FALSE;

	if( !Main::HandManager::isClick ) {
		handManager->setState( handManager->HAND_PUSH_BEFORE );
		return TRUE;
	}

	mIsView = !mIsView;
	handManager->setState( handManager->HAND_PUSH_AFTER );

	return TRUE;
}

void ViewObj::draw( Image::LayerData *partsBmp )
{
	if( !mIsView ) return;
	unsigned int skipColor = CLR_RED | CLR_RED_GREEN | CLR_GREEN | CLR_BLUE | CLR_BLUE_RED;
	partsBmp->drawWindow( mX, mY, mCutStartX, mCutStartY, mWidth, mHeight, skipColor );
}


} // namespace Room
} // namespace Sequence
