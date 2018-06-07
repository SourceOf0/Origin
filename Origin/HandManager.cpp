#include "HandManager.h"
#include "ImageFactory.h"
#include "SceneManager.h"

#include "LayerData.h"

namespace Main {

HandManager* HandManager::mInst = 0;
BOOL HandManager::isMouseDown = FALSE;
BOOL HandManager::isClick = FALSE;
BOOL HandManager::isMove = FALSE;

HandManager* HandManager::inst( void )
{
	return mInst;
}
void HandManager::create( HDC& hdc )
{
	if( mInst == 0 ) {
		mInst = new HandManager( hdc );
	}
}
void HandManager::destroy( void )
{
	if( mInst != 0 ) {
		delete mInst;
		mInst = 0;
	}
}

HandManager::HandManager( HDC& hdc ) :
mX( 0 ),
mY( 0 ),
mMouseX( 0 ),
mMouseY( 0 ),
mLockX( -1000 ),
mLockY( -1000 ),
mMinX( -1000 ),
mMaxX( -1000 ),
mMinY( -1000 ),
mMaxY( -1000 ),
mShowCursorCount( 0 ),
mIsLockX( FALSE ),
mIsLockY( FALSE ),
mState( HAND_NORMAL ),
mImageState( HAND_IMAGE_NORMAL ),
mAnimeCount( 0 )
{
	Main::ImageFactory* imageFactory = Main::ImageFactory::inst();

	mHandBmp = ( Image::LayerData* )( imageFactory->load( hdc, "resource\\hands.dad" ) );
	mCheckHandBmp = ( Image::LayerData* )( imageFactory->load( hdc, "resource\\checkHand.dad" ) );

	mHandBmp->mDepth = 0.2;
	mCheckHandBmp->mDepth = 0.2;

	mShowCursorCount = ShowCursor( FALSE );
}

HandManager::~HandManager( void )
{
	delete mHandBmp;
	mHandBmp = 0;

	delete mCheckHandBmp;
	mCheckHandBmp = 0;
}

void HandManager::mouseDown( void )
{
	isClick = TRUE;
	isMouseDown = TRUE;
}
void HandManager::mouseUp( void )
{
	isMouseDown = FALSE;
}
void HandManager::endUpdate( void )
{
	isClick = FALSE;
}

void HandManager::update( HWND& hwnd, BOOL isLoading )
{
	const int VIEW_WIDTH = Main::SceneManager::VIEW_WIDTH;
	const int VIEW_HEIGHT = Main::SceneManager::VIEW_HEIGHT;
	const int viewPosX = Main::SceneManager::getViewPosX();
	const int viewPosY = Main::SceneManager::getViewPosY();

	POINT mousePos = getScreenToClientPos( hwnd );
	int mouseX = mousePos.x - viewPosX;
	int mouseY = mousePos.y - viewPosY;

	if( mouseX >= 0 && mouseX < VIEW_WIDTH && mouseY >= 0 && mouseY < VIEW_HEIGHT ) {
		while(mShowCursorCount >= 0) {
			mShowCursorCount = ShowCursor( FALSE );
		}
	} else {
		while(mShowCursorCount < 0) {
			mShowCursorCount = ShowCursor( TRUE );
		}
	}

	if( isLoading ) {
		isMouseDown = FALSE;
		isClick = FALSE;
	}

	if( mIsLockX ) {
		if( mLockX == -1000 ) {
			mLockX = mouseX;
		}
		mouseX = mLockX;
	} else {
		mLockX = -1000;
	}
	if( mIsLockY ) {
		if( mLockY == -1000 ) {
			mLockY = mouseY;
		}
		mouseY = mLockY;
	} else {
		mLockY = -1000;
	}

	if( mMinX != -1000 || mMaxX != -1000 ) {
		if( mouseX <= mMinX ) mouseX = mMinX;
		if( mouseX >= mMaxX ) mouseX = mMaxX;
	}
	if( mMinY != -1000 || mMaxY != -1000 ) {
		if( mouseY <= mMinY ) mouseY = mMinY;
		if( mouseY >= mMaxY ) mouseY = mMaxY;
	}

	mIsLockX = FALSE;
	mIsLockY = FALSE;
	mMaxX = -1000;
	mMinX = -1000;
	mMaxY = -1000;
	mMinY = -1000;

	if( mMouseX == mouseX && mMouseY == mouseY && !isMouseDown ) {
		isMove = FALSE;
	} else {
		isMove = TRUE;
	}

	setClientToScreenPos( hwnd, mouseX + viewPosX, mouseY + viewPosY );
	mMouseX = mouseX;
	mMouseY = mouseY;

	mouseX -= mX;
	mouseY -= mY;

	int fixX = 32;
	int fixY = 32;
	switch( mState ) {
		case HAND_NORMAL:
			mImageState = HAND_IMAGE_NORMAL;
			break;
		case HAND_CHECK:
			mImageState = HAND_IMAGE_CHECK;
			fixX = 48;
			fixY = 48;
			break;
		case HAND_PUSH_AFTER:
		case HAND_PUSH_BEFORE:
			mImageState = HAND_IMAGE_PUSH;
			break;
		case HAND_HOLD_BEFORE:
			mImageState = HAND_IMAGE_HOLD_BEFORE;
			break;
		case HAND_HOLD_AFTER:
			mImageState = HAND_IMAGE_HOLD_AFTER;
			break;
		case HAND_CLOSE:
			mImageState = HAND_IMAGE_CLOSE;
			fixX = 12;
			fixY = 12;
			break;

		case HAND_BACK:
			mImageState = HAND_IMAGE_BACK;
			break;
		case HAND_LEFT:
			mImageState = HAND_IMAGE_LEFT;
			fixX = 72;
			break;
		case HAND_RIGHT:
			mImageState = HAND_IMAGE_RIGHT;
			fixX = -12;
			break;
		case HAND_UP:
			mImageState = HAND_IMAGE_UP;
			break;
//		case HAND_DOWN:
//			break;
	}

	mHandBmp->mX = mouseX - fixX;
	mHandBmp->mY = mouseY - fixY;
}

void HandManager::draw( void )
{
	int fixX = 0;
	int fixY = 0;

	if( mState == HAND_HIDE ) return;

	switch( mImageState ) {
		case HAND_IMAGE_NORMAL:
			if( mMouseY < 13 ) {
				fixY = 13 - mMouseY;
			} else if( mMouseY > SceneManager::windowHeight - 19 ) {
				fixY = SceneManager::windowHeight - 19 - mMouseY;
			}
			break;
		case HAND_IMAGE_PUSH:
			fixX = 8;
			fixY = 10;
			break;
		case HAND_IMAGE_HOLD_BEFORE:
		case HAND_IMAGE_HOLD_AFTER:
			break;
		case HAND_IMAGE_CLOSE:
			fixX = -32;
			fixY = -28;
			break;
		case HAND_IMAGE_BACK:
			// TODO: amend
			if( mMouseX < 16 ) {
				fixX = 16 - mMouseX;
			} else if( mMouseX > SceneManager::VIEW_WIDTH - 16 ) {
				fixX = SceneManager::VIEW_WIDTH - 16 - mMouseX;
			}
			if( mMouseY < 13 ) {
				fixY = 13 - mMouseY;
			} else if( mMouseY > SceneManager::VIEW_HEIGHT - 19 ) {
				fixY = SceneManager::VIEW_HEIGHT - 19 - mMouseY;
			}
			break;
		case HAND_IMAGE_RIGHT:
			fixX = -32;
			if( mMouseY < 13 ) {
				fixY = 13 - mMouseY;
			} else if( mMouseY > SceneManager::VIEW_HEIGHT - 19 ) {
				fixY = SceneManager::VIEW_HEIGHT - 19 - mMouseY;
			}
			break;
		case HAND_IMAGE_LEFT:
			fixX = 32;
			if( mMouseY < 13 ) {
				fixY = 13 - mMouseY;
			} else if( mMouseY > SceneManager::VIEW_HEIGHT - 19 ) {
				fixY = SceneManager::VIEW_HEIGHT - 19 - mMouseY;
			}
			break;
		case HAND_IMAGE_UP:
			break;
		case HAND_IMAGE_CHECK:
			mCheckHandBmp->drawWindow( static_cast< int >( mHandBmp->mX + 0.5 ), static_cast< int >( mHandBmp->mY + 0.5 ), 0, 0, 96, 96 );
			return;
			break;
	}
	mHandBmp->drawWindow( static_cast< int >( mHandBmp->mX + 0.5 + fixX ), static_cast< int >( mHandBmp->mY + 0.5 + fixY ), 0, mImageState * 64, 64, 64 );
}

int HandManager::getX( void )
{
	return mMouseX;
}
int HandManager::getY( void )
{
	return mMouseY;
}
void HandManager::setRangeX( int min, int max )
{
	mMinX = min;
	mMaxX = max;
}
void HandManager::setRangeY( int min, int max )
{
	mMinY = min;
	mMaxY = max;
}

BOOL HandManager::checkState( HandState state )
{
	return ( mState == state );
}
void HandManager::setState( HandState state )
{
	mState = state;
}

void HandManager::setPos( int x, int y )
{
	mMouseX = x;
	mMouseY = y;
	SetCursorPos( x, y );
}

void HandManager::lockX( void )
{
	mIsLockX = TRUE;
}
void HandManager::lockY( void )
{
	mIsLockY = TRUE;
}


POINT HandManager::getScreenToClientPos( HWND& hwnd )
{
	POINT mousePos;
	GetCursorPos( &mousePos );
	ScreenToClient( hwnd, &mousePos );
	return mousePos;
}
void HandManager::setClientToScreenPos( HWND& hwnd, int x, int y )
{
	POINT mousePos = { x, y };
	ClientToScreen( hwnd, &mousePos );
	SetCursorPos( mousePos.x, mousePos.y );
}

} // namespace Main
