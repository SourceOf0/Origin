#include "PlayButton.h"

#include "LayerData.h"
#include "HandManager.h"

namespace Sequence {

namespace Room {

void PlayButton::setData( PartsID signID, int x, int y, int signX, int signY, BOOL isOn )
{
	( isOn )? init( PARTS_BUTTON_PLAY_ON, x, y ) : init( PARTS_BUTTON_PLAY_OFF, x, y );
	mSign.setData( signID, signX, signY, TRUE );
	mIsSwitch = FALSE;
}

void PlayButton::setOn( void )
{
	if( mPartsID == PARTS_BUTTON_PLAY_ON ) return;
	setPartsSize( PARTS_BUTTON_PLAY_ON );
}
void PlayButton::setOff( void )
{
	if( mPartsID == PARTS_BUTTON_PLAY_OFF ) return;
	setPartsSize( PARTS_BUTTON_PLAY_OFF );
}

BOOL PlayButton::isSwitch( void )
{
	BOOL ret = mIsSwitch;
	mIsSwitch = FALSE;
	return ret;
}
BOOL PlayButton::isOn( void )
{
	return ( mPartsID == PARTS_BUTTON_PLAY_ON );
}


BOOL PlayButton::checkHit( void )
{
	Main::HandManager* handManager = Main::HandManager::inst();

	if( !isHit( handManager->getX(), handManager->getY() ) ) return FALSE;

	if( !Main::HandManager::isClick ) {
		handManager->setState( handManager->HAND_PUSH_BEFORE );
		return TRUE;
	}

	( mPartsID == PARTS_BUTTON_PLAY_OFF )? setPartsSize( PARTS_BUTTON_PLAY_ON ) : setPartsSize( PARTS_BUTTON_PLAY_OFF );
	mIsSwitch = TRUE;
	handManager->setState( handManager->HAND_PUSH_AFTER );

	return TRUE;
}

void PlayButton::draw( Image::LayerData *partsBmp )
{
	if( mPartsID == PARTS_BUTTON_PLAY_ON ) {
		partsBmp->drawWindow( mX, mY, mCutStartX, mCutStartY, mWidth, mHeight, CLR_RED | CLR_GREEN | CLR_BLUE );
	} else {
		partsBmp->drawWindow( mX, mY, mCutStartX, mCutStartY, mWidth, mHeight, CLR_GREEN_BLUE | CLR_BLUE_RED );
	}
	( mPartsID == PARTS_BUTTON_PLAY_ON )? mSign.fixPos( 0, 3 ) : mSign.fixPos( 0, 0 );
	mSign.draw( partsBmp );
}

} // namespace Room
} // namespace Sequence
