#include "FaderV.h"

#include "LayerData.h"
#include "HandManager.h"

namespace Sequence {

namespace Room {

void FaderV::setData( int x, int y, int fixX1, int fixY1, int fixX2, int fixY2 )
{
	init( PARTS_FADER_V, x, y );
	mDefY = y;
	mHitX1 += fixX1 - 5;
	mHitY1 += fixY1;
	mHitX2 += fixX2 + 5;
	mHitY2 += fixY2;

	mIsHold = FALSE;
}

double FaderV::getVal( void )
{
	return ( static_cast< double >( mY - mDefY ) / ( mHitY2 - 10 - mDefY ) );
}
void FaderV::setVal( double val )
{
	if( val > 1.0 ) val = 1.0;
	if( val < 0.0 ) val = 0.0;
	mX = static_cast< int >( val * ( mHitY2 - 10 - mDefY ) + mDefY );
}
BOOL FaderV::isHold( void )
{
	return mIsHold;
}

BOOL FaderV::checkHit( void )
{
	Main::HandManager* handManager = Main::HandManager::inst();
	int mouseX = handManager->getX();
	int mouseY = handManager->getY();

	if( !isHit( mouseX, mouseY ) && !mIsHold ) return FALSE;

	if( Main::HandManager::isClick ) mIsHold = TRUE;

	if( !Main::HandManager::isMouseDown || !mIsHold ) {
		handManager->setState( handManager->HAND_HOLD_BEFORE );
		mIsHold = FALSE;
		return TRUE;
	}

	int setY = mouseY - 5;
	if( setY < mDefY ) setY = mDefY;
	if( setY > mHitY2 - 10 ) setY = mHitY2 - 10;
	mY = setY;
	handManager->lockX();
	handManager->setRangeY( mDefY + 5, mHitY2 - 5 );
	handManager->setState( handManager->HAND_HOLD_AFTER );

	return TRUE;
}

void FaderV::draw( Image::LayerData *partsBmp )
{
	partsBmp->drawWindow( mX, mY, mCutStartX, mCutStartY, mWidth, mHeight, CLR_GREEN_BLUE | CLR_BLUE_RED );
}


} // namespace Room
} // namespace Sequence
