#include "FaderH.h"

#include "LayerData.h"
#include "HandManager.h"

namespace Sequence {

namespace Room {

void FaderH::setData( int x, int y, int fixX1, int fixY1, int fixX2, int fixY2 )
{
	init( PARTS_FADER_H, x, y );
	mDefX = x;
	mHitX1 += fixX1;
	mHitY1 += fixY1 - 5;
	mHitX2 += fixX2;
	mHitY2 += fixY2 + 5;

	mIsHold = FALSE;
}

double FaderH::getVal( void )
{
	return ( static_cast< double >( mX - mDefX ) / ( mHitX2 - 10 - mDefX ) );
}
void FaderH::setVal( double val )
{
	if( val > 1.0 ) val = 1.0;
	if( val < 0.0 ) val = 0.0;
	mX = static_cast< int >( val * ( mHitX2 - 10 - mDefX ) + mDefX );
}
BOOL FaderH::isHold( void )
{
	return mIsHold;
}

BOOL FaderH::checkHit( void )
{
	Main::HandManager* handManager = Main::HandManager::inst();
	BOOL isMouseDown = Main::HandManager::isMouseDown;
	int mouseX = handManager->getX();
	int mouseY = handManager->getY();

	if( !isHit( mouseX, mouseY ) && !mIsHold ) return FALSE;

	if( Main::HandManager::isClick ) mIsHold = TRUE;

	if( !Main::HandManager::isMouseDown || !mIsHold ) {
		handManager->setState( handManager->HAND_HOLD_BEFORE );
		mIsHold = FALSE;
		return TRUE;
	}

	int setX = mouseX - 5;
	if( setX < mDefX ) setX = mDefX;
	if( setX > mHitX2 - 10 ) setX = mHitX2 - 10;
	mX = setX;
	handManager->lockY();
	handManager->setRangeX( mDefX + 5, mHitX2 - 5 );
	handManager->setState( handManager->HAND_HOLD_AFTER );

	return TRUE;
}

void FaderH::draw( Image::LayerData *partsBmp )
{
	partsBmp->drawWindow( mX, mY, mCutStartX, mCutStartY, mWidth, mHeight, CLR_GREEN_BLUE | CLR_BLUE_RED );
}


} // namespace Room
} // namespace Sequence
