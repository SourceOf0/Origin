#include "TimeLamp.h"

#include "LayerData.h"
#include "HandManager.h"

namespace Sequence {

namespace Room {

void TimeLamp::setData( int x, int y, BOOL isOn )
{
	init( PARTS_LAMP_TIME, x, y );
	if( !isOn ) mPartsID = PARTS_NONE;

	mHitX1 -= 2;
	mHitX2 += 2;
	mHitY1 -= 2;
	mHitY2 += 5;
	mIsSwitch = FALSE;
}

void TimeLamp::setOn( void )
{
	mPartsID = PARTS_LAMP_TIME;
}
void TimeLamp::setOff( void )
{
	mPartsID = PARTS_NONE;
}

BOOL TimeLamp::isSwitch( void )
{
	BOOL ret = mIsSwitch;
	mIsSwitch = FALSE;
	return ret;
}
BOOL TimeLamp::isOn( void )
{
	return ( mPartsID == PARTS_LAMP_TIME );
}


BOOL TimeLamp::checkHit( void )
{
	Main::HandManager* handManager = Main::HandManager::inst();

	if( !isHit( handManager->getX(), handManager->getY() ) ) return FALSE;

	if( !Main::HandManager::isClick ) {
		handManager->setState( handManager->HAND_PUSH_BEFORE );
		return TRUE;
	}

	handManager->setState( handManager->HAND_PUSH_AFTER );
	mPartsID = PARTS_LAMP_TIME;
	mIsSwitch = TRUE;

	return TRUE;
}

void TimeLamp::draw( Image::LayerData *partsBmp )
{
	if( mPartsID == PARTS_NONE ) return;
	partsBmp->drawWindow( mX, mY, mCutStartX, mCutStartY, mWidth, mHeight, CLR_RED );
}


} // namespace Room
} // namespace Sequence
