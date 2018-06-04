#include "Lever.h"

#include "LayerData.h"
#include "HandManager.h"

namespace Sequence {

namespace Room {

void Lever::setData( int x, int y, int val )
{
	init( PARTS_LEVER_4, x, y );
	mDefX = x;
	mIsChangeVal = FALSE;

	mHitY1 += 5;
	mHitX2 += 32;
	mHitY2 += -12;

	mIsHold = FALSE;

	switch( val ) {
		case 1:
			setPartsSize( PARTS_LEVER_1 );
			mX = mHitX2 - 20;
			break;
		case 2:
			setPartsSize( PARTS_LEVER_2 );
			mX = mDefX + 23;
			break;
		case 3:
			setPartsSize( PARTS_LEVER_3 );
			mX = mDefX + 12;
			break;
		case 4:
			setPartsSize( PARTS_LEVER_4 );
			mX = mDefX;
			break;
	}
}

int Lever::getVal( void )
{
	return ( mPartsID - PARTS_LEVER_1 + 1 );
}
BOOL Lever::isChangeVal( void )
{
	BOOL ret = mIsChangeVal;
	mIsChangeVal = FALSE;
	return ret;
}
BOOL Lever::isHold( void )
{
	return mIsHold;
}

BOOL Lever::checkHit( void )
{
	Main::HandManager* handManager = Main::HandManager::inst();

	if( !isHit( handManager->getX(), handManager->getY() ) && !mIsHold ) return FALSE;

	if( Main::HandManager::isClick ) mIsHold = TRUE;

	if( !Main::HandManager::isMouseDown || !mIsHold ) {
		handManager->setState( handManager->HAND_HOLD_BEFORE );
		mIsHold = FALSE;
		return TRUE;
	}

	int setX = handManager->getX() - 12;
	if( setX <= mDefX ) {
		if( mPartsID != PARTS_LEVER_4 ) {
			mIsChangeVal = TRUE;
			setPartsSize( PARTS_LEVER_4 );
		}
		setX = mDefX;
	} else if( setX <= mDefX + 12 ) {
		if( mPartsID != PARTS_LEVER_3 ) {
			mIsChangeVal = TRUE;
			setPartsSize( PARTS_LEVER_3 );
		}
		setX = mDefX + 12;
	} else if( setX <= mDefX + 23 ) {
		if( mPartsID != PARTS_LEVER_2 ) {
			mIsChangeVal = TRUE;
			setPartsSize( PARTS_LEVER_2 );
		}
		setX = mDefX + 23;
	} else {
		if( mPartsID != PARTS_LEVER_1 ) {
			mIsChangeVal = TRUE;
			setPartsSize( PARTS_LEVER_1 );
		}
		setX = mHitX2 - 20;
	}
	mX = setX;
	handManager->lockY();
	handManager->setRangeX( mDefX + 8, mHitX2 - 4 );
	handManager->setState( handManager->HAND_HOLD_AFTER );
	
	return TRUE;
}

void Lever::draw( Image::LayerData *partsBmp )
{
	partsBmp->drawWindow( mX, mY, mCutStartX, mCutStartY, mWidth, mHeight, CLR_GREEN_BLUE | CLR_BLUE_RED );
}


} // namespace Room
} // namespace Sequence
