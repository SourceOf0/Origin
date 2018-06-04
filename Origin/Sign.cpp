#include "Sign.h"

#include "LayerData.h"

#define SIGN_MOVE_SPEED 5

namespace Sequence {

namespace Room {

void Sign::setData( PartsID minSign, PartsID maxSign, int x, int y )
{
	init( minSign, x, y );
	mDefX = x;

	mIsChangeSign = FALSE;
	mTargetSign = minSign;
	mMinSign = minSign;
	mMaxSign = maxSign;
}

BOOL Sign::isChangeSign( void )
{
	BOOL ret = mIsChangeSign;
	mIsChangeSign = FALSE;
	return ret;
}

PartsID Sign::getSign( void )
{
	return mPartsID;
}

BOOL Sign::isMaxSign( void )
{
	return ( mTargetSign == mMaxSign );
}
BOOL Sign::isMinSign( void )
{
	return ( mTargetSign == mMinSign );
}

void Sign::addTargetSign( void )
{
	mTargetSign = ( mTargetSign < mMaxSign )? ( PartsID )( mTargetSign + 1 ) : mMaxSign;
}
void Sign::decTargetSign( void )
{
	mTargetSign = ( mTargetSign > mMinSign )? ( PartsID )( mTargetSign - 1 ) : mMinSign;
}

BOOL Sign::isMoveEnd( void )
{
	return ( mTargetSign == mPartsID );
}

BOOL Sign::checkHit( void )
{
	return FALSE;
}

void Sign::update( void )
{
	if( mTargetSign == mPartsID ) {
		if( mX == mDefX ) return;
		if( mX > mDefX ) {
			mX -= SIGN_MOVE_SPEED;
			if( mX <= mDefX ) mX = mDefX;
		} else {
			mX += SIGN_MOVE_SPEED;
			if( mX >= mDefX ) mX = mDefX;
		}
		return;
	}
	
	if( mTargetSign < mPartsID ) {
		mX += SIGN_MOVE_SPEED;
		if( mX <= mDefX + 18 ) return;
		mX = mDefX - 18;
		setPartsSize( ( PartsID )( mPartsID - 1 ) );
		mIsChangeSign = TRUE;
		return;
	}
	
	if( mTargetSign > mPartsID ) {
		mX -= SIGN_MOVE_SPEED;
		if( mX >= mDefX - 18 ) return;
		mX = mDefX + 18;
		setPartsSize( ( PartsID )( mPartsID + 1 ) );
		mIsChangeSign = TRUE;
		return;
	}
}

void Sign::draw( Image::LayerData *partsBmp )
{
	unsigned int skipColor = CLR_RED | CLR_RED_GREEN | CLR_GREEN | CLR_GREEN_BLUE | CLR_BLUE | CLR_BLUE_RED;

	if( mX < mDefX - 5 ) {
		int fixX = mDefX - 5 - mX;
		if( mWidth <= fixX ) return;
		partsBmp->drawWindow( mX + fixX - mWidth / 2, mY - mHeight / 2, mCutStartX + fixX, mCutStartY, mWidth - fixX, mHeight, skipColor );
	} else if( mX > mDefX + 5 ) {
		int fixX = mX - mDefX - 5;
		if( mWidth <= fixX ) return;
		partsBmp->drawWindow( mX - mWidth / 2, mY - mHeight / 2, mCutStartX, mCutStartY, mWidth - fixX, mHeight, skipColor );
	} else {
		partsBmp->drawWindow( mX - mWidth / 2, mY - mHeight / 2, mCutStartX, mCutStartY, mWidth, mHeight, skipColor );
	}
}


} // namespace Room
} // namespace Sequence
