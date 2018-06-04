#include "AutoPanButton.h"

#include "LayerData.h"
#include "HandManager.h"

namespace Sequence {

namespace Room {

void AutoPanButton::setData( int x, int y, BOOL isOn )
{
	init( PARTS_BUTTON_AUTOPAN_ON, x, y );
	if( !isOn ) setPartsSize( PARTS_BUTTON_AUTOPAN_OFF );
	
	mIsSwitch = FALSE;
}

void AutoPanButton::setOn( void )
{
	if( mPartsID == PARTS_BUTTON_AUTOPAN_ON ) return;
	setPartsSize( PARTS_BUTTON_AUTOPAN_ON );
}
void AutoPanButton::setOff( void )
{
	if( mPartsID == PARTS_BUTTON_AUTOPAN_OFF ) return;
	setPartsSize( PARTS_BUTTON_AUTOPAN_OFF );
}

BOOL AutoPanButton::isSwitch( void )
{
	BOOL ret = mIsSwitch;
	mIsSwitch = FALSE;
	return ret;
}
BOOL AutoPanButton::isOn( void )
{
	return ( mPartsID == PARTS_BUTTON_AUTOPAN_ON );
}


BOOL AutoPanButton::checkHit( void )
{
	Main::HandManager* handManager = Main::HandManager::inst();

	if( !isHit( handManager->getX(), handManager->getY() ) ) return FALSE;

	if( !Main::HandManager::isClick ) {
		handManager->setState( handManager->HAND_PUSH_BEFORE );
		return TRUE;
	}

	( mPartsID == PARTS_BUTTON_AUTOPAN_OFF )? setPartsSize( PARTS_BUTTON_AUTOPAN_ON ) : setPartsSize( PARTS_BUTTON_AUTOPAN_OFF );
	mIsSwitch = TRUE;
	handManager->setState( handManager->HAND_PUSH_AFTER );

	return TRUE;
}

void AutoPanButton::draw( Image::LayerData *partsBmp )
{
	if( mPartsID == PARTS_BUTTON_AUTOPAN_ON ) {
		partsBmp->drawWindow( mX, mY, mCutStartX, mCutStartY, mWidth, mHeight, CLR_RED | CLR_GREEN | CLR_BLUE );
	} else {
		partsBmp->drawWindow( mX, mY, mCutStartX, mCutStartY, mWidth, mHeight, CLR_GREEN_BLUE | CLR_BLUE_RED );
	}
}


} // namespace Room
} // namespace Sequence
