#include "MainParent.h"
#include "MainChild.h"
#include "DebugLoading.h"

#include "SceneManager.h"
#include "DCBitmap.h"

#include <stdlib.h>

namespace Sequence {

DebugLoading::DebugLoading( HDC& hdc, MainParent* parent )
{
	int windowWidth = parent->mWindowWidth;
	int windowHeight = parent->mWindowHeight;

	mBackBmp = new Image::DCBitmap( hdc, windowWidth, windowHeight );

	mState = 0;

	mTargetX1 = static_cast< int >( windowWidth * 0.2 );
	mTargetY1 = static_cast< int >( windowHeight * 0.2 );
	mX1 = mTargetX1;
	mY1 = mTargetY1;

	mTargetX2 = static_cast< int >( windowWidth * 0.8 );
	mTargetY2 = static_cast< int >( windowHeight * 0.8 );
	mX2 = mTargetX2;
	mY2 = mTargetY2;
}

DebugLoading::~DebugLoading()
{
	delete mBackBmp;
	mBackBmp = 0;
}

void DebugLoading::update( MainParent* parent )
{
	int windowWidth = parent->mWindowWidth;
	int windowHeight = parent->mWindowHeight;
	
	HPEN hPen1 = CreatePen( PS_SOLID, 1, RGB( 0, 0, 0 ) );
	HPEN hPen2 = CreatePen( PS_SOLID, 1, RGB( 255, 255, 255 ) );
	HBRUSH hBrush1 = CreateSolidBrush( RGB( 0, 0, 0 ) );
	HBRUSH hBrush2 = CreateSolidBrush( RGB( 255, 255, 255 ) );

	SelectObject( mBackBmp->mHdcBmp, hBrush1 );
	SelectObject( mBackBmp->mHdcBmp, hPen1 );
	Rectangle( mBackBmp->mHdcBmp, mTargetX1, mTargetY1, mTargetX2, mTargetY2 );

	if( mState == 3 || mState == 4 ) SelectObject( mBackBmp->mHdcBmp, hBrush2 );
	SelectObject( mBackBmp->mHdcBmp, hPen2 );
	Rectangle( mBackBmp->mHdcBmp, mX1, mY1, mX2, mY2 );

	DeleteObject( hPen1 );
	DeleteObject( hPen2 );
	DeleteObject( hBrush1 );
	DeleteObject( hBrush2 );

	switch( mState ) {
		case 4:
		case 0:
			mX1 += 2;
			if( mX1 >= mTargetX2 ) {
				mX1 = mTargetX2 - 1;
				++mState;
			}
			break;
		case 5:
		case 1:
			mY1 += 2;
			if( mY1 >= mTargetY2 ) {
				mY1 = mTargetY2 - 1;
				++mState;
			}
			break;
		case 6:
		case 2:
			mX1 -= 2;
			if( mX1 <= mTargetX1 ) {
				mX1 = mTargetX1;
				++mState;
			}
			break;
		case 7:
		case 3:
			mY1 -= 2;
			if( mY1 <= mTargetY1 ) {
				mY1 = mTargetY1;
				mState = ( mState + 1 ) % 7;
			}
			break;
	}
}

void DebugLoading::draw( HDC& hdc, MainParent* parent )
{
	mBackBmp->drawWindow();
}


} // namespace Sequence