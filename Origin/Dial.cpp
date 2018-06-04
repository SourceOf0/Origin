#include "Dial.h"

#include "Sign.h"
#include "LayerData.h"
#include "HandManager.h"

#define DIAL_ANIME_SPEED 5
#define DIAL_ANIME_COUNT 10

namespace Sequence {

namespace Room {

void Dial::setData( PartsID minSign, PartsID maxSign, int x, int y )
{
	mSign.setData( minSign, maxSign, x + 29, y - 19 );
	init( PARTS_DIAL_1, x, y );

	mHitX1 -= 5;
	mHitX2 += 5;
	mHitY1 -= 10;
	mHitY2 += 8;
	mAnimeCount = 0;
}

BOOL Dial::isChangeSign( void )
{
	return mSign.isChangeSign();
}

PartsID Dial::getSign( void )
{
	return mSign.getSign();
}

BOOL Dial::checkHit( void )
{
	Main::HandManager* handManager = Main::HandManager::inst();

	if( !isHit( handManager->getX(), handManager->getY() ) ) return FALSE;

	handManager->setState( handManager->HAND_PUSH_AFTER );
	if( handManager->getX() < mX + 30 ) {
		if( mSign.isMaxSign() ) return FALSE;
		if( Main::HandManager::isClick ){
			mSign.addTargetSign();
			return TRUE;
		}
	} else {
		if( mSign.isMinSign() ) return FALSE;
		if( Main::HandManager::isClick ){
			mSign.decTargetSign();
			return TRUE;
		}
	}

	return TRUE;
}

void Dial::update( void )
{
	mSign.update();

	if( !mSign.isMoveEnd() && mAnimeCount == 0 ) mAnimeCount = DIAL_ANIME_COUNT;
	if( mAnimeCount > 0 ) --mAnimeCount;
	if( mAnimeCount > DIAL_ANIME_SPEED ) {
		if( mPartsID == PARTS_DIAL_2 ) return;
		setPartsSize( PARTS_DIAL_2 );
	} else {
		if( mPartsID == PARTS_DIAL_1 ) return;
		setPartsSize( PARTS_DIAL_1 );
	}
}

void Dial::draw( Image::LayerData *partsBmp )
{
	mSign.draw( partsBmp );
	if( mAnimeCount == 0 ) return;
	partsBmp->drawWindow( mX, mY, mCutStartX, mCutStartY, mWidth, mHeight );
}

} // namespace Room
} // namespace Sequence
