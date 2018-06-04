#include "TrackButton.h"

#include "LayerData.h"
#include "HandManager.h"

namespace Sequence {

namespace Room {

void TrackButton::setData( int x, int y, BOOL isOn )
{
	init( PARTS_BUTTON_TRACK_ON, x, y );
	if( !isOn ) setPartsSize( PARTS_BUTTON_TRACK_OFF );

	mIsSwitch = FALSE;
}

void TrackButton::setOn( void )
{
	if( mPartsID == PARTS_BUTTON_TRACK_ON ) return;
	setPartsSize( PARTS_BUTTON_TRACK_ON );
}
void TrackButton::setOff( void )
{
	if( mPartsID == PARTS_BUTTON_TRACK_OFF ) return;
	setPartsSize( PARTS_BUTTON_TRACK_OFF );
}

BOOL TrackButton::isSwitch( void )
{
	BOOL ret = mIsSwitch;
	mIsSwitch = FALSE;
	return ret;
}
BOOL TrackButton::isOn( void )
{
	return ( mPartsID == PARTS_BUTTON_TRACK_ON );
}


BOOL TrackButton::checkHit( void )
{
	Main::HandManager* handManager = Main::HandManager::inst();

	if( !isHit( handManager->getX(), handManager->getY() ) ) return FALSE;

	if( !Main::HandManager::isClick ) {
		handManager->setState( handManager->HAND_PUSH_BEFORE );
		return TRUE;
	}

	handManager->setState( handManager->HAND_PUSH_AFTER );
	setPartsSize( PARTS_BUTTON_TRACK_ON );
	mIsSwitch = TRUE;

	return TRUE;
}

void TrackButton::draw( Image::LayerData *partsBmp )
{
	if( mPartsID == PARTS_BUTTON_TRACK_ON ) {
		partsBmp->drawWindow( mX, mY, mCutStartX, mCutStartY, mWidth, mHeight, CLR_RED | CLR_GREEN | CLR_BLUE );
	} else {
		partsBmp->drawWindow( mX, mY, mCutStartX, mCutStartY, mWidth, mHeight, CLR_GREEN_BLUE | CLR_BLUE_RED );
	}
}


} // namespace Room
} // namespace Sequence
