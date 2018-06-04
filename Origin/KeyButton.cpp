#include "KeyButton.h"

#include "LayerData.h"
#include "HandManager.h"

namespace Sequence {

namespace Room {

void KeyButton::setData( int x, int y, BOOL isOn )
{
	init( PARTS_BUTTON_KEY_OFF, x, y );
	if( isOn ) setPartsSize( PARTS_BUTTON_KEY_ON );
	mHitX1 -= 1;
	mHitX2 += 2;
}

BOOL KeyButton::isOn( void )
{
	return ( mPartsID == PARTS_BUTTON_KEY_ON );
}


BOOL KeyButton::checkHit( void )
{
	Main::HandManager* handManager = Main::HandManager::inst();

	if( !isHit( handManager->getX(), handManager->getY() ) ) {
		if( mPartsID == PARTS_BUTTON_KEY_ON ) setPartsSize( PARTS_BUTTON_KEY_OFF );
		return FALSE;
	}
	if( Main::HandManager::isMouseDown ) {
		handManager->setState( handManager->HAND_PUSH_AFTER );
		if( mPartsID == PARTS_BUTTON_KEY_OFF ) setPartsSize( PARTS_BUTTON_KEY_ON );
	} else {
		handManager->setState( handManager->HAND_PUSH_BEFORE );
		if( mPartsID == PARTS_BUTTON_KEY_ON ) setPartsSize( PARTS_BUTTON_KEY_OFF );
	}
	return TRUE;
}

void KeyButton::draw( Image::LayerData *partsBmp )
{
	if( mPartsID == PARTS_BUTTON_KEY_ON ) {
		partsBmp->drawWindow( mX, mY, mCutStartX, mCutStartY, mWidth, mHeight, CLR_RED | CLR_GREEN | CLR_BLUE );
	} else {
		partsBmp->drawWindow( mX, mY, mCutStartX, mCutStartY, mWidth, mHeight, CLR_GREEN_BLUE | CLR_BLUE_RED );
	}
}


} // namespace Room
} // namespace Sequence
