#include "HandManager.h"
#include "ImageFactory.h"
#include "SceneManager.h"

#include "LayerData.h"

namespace Main {

HandManager* HandManager::mInst = 0;

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
mIsLockX( FALSE ),
mIsLockY( FALSE ),
mState( HAND_NORMAL ),
mImageState( HAND_IMAGE_NORMAL ),
mAnimeCount( 0 )
{
	Main::ImageFactory* imageFactory = Main::ImageFactory::inst();
	unsigned int windowWidth = Main::SceneManager::windowWidth;
	unsigned int windowHeight = Main::SceneManager::windowHeight;

	mHandBmp = ( Image::LayerData* )( imageFactory->load( hdc, "resource\\hands.dad" ) );

	POINT mousePos;
	GetCursorPos( &mousePos );
	mMouseX = mousePos.x;
	mMouseY = mousePos.y;
}

HandManager::~HandManager( void )
{
	delete mHandBmp;
	mHandBmp = 0;
}

void HandManager::update( void )
{
	POINT mousePos;
	GetCursorPos( &mousePos );
	int mouseX = mousePos.x;
	int mouseY = mousePos.y;

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

	SetCursorPos( mouseX, mouseY );
	mMouseX = mouseX;
	mMouseY = mouseY;

	mouseX -= mX;
	mouseY -= mY;

	mHandBmp->mX = mouseX - 32;
	mHandBmp->mY = mouseY - 32;

	switch( mState ) {
		case HAND_NORMAL:
			mImageState = HAND_IMAGE_NORMAL;
			break;
		case HAND_POINT:
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
			break;

		case HAND_BACK:
			mImageState = HAND_IMAGE_BACK;
			break;
		case HAND_LEFT:
			mImageState = HAND_IMAGE_LEFT;
			break;
		case HAND_RIGHT:
			mImageState = HAND_IMAGE_RIGHT;
			break;
		case HAND_UP:
			mImageState = HAND_IMAGE_UP;
			break;
//		case HAND_DOWN:
//			break;
	}
}

void HandManager::draw( void )
{
//	mHandBmp->drawWindow( mHandBmp->mX, mHandBmp->mY, size.startX, size.startY, size.width, size.height, isTransparent );
//	if( mImageState != HAND_IMAGE_NORMAL && mImageState != HAND_IMAGE_PUSH ) {
		mHandBmp->drawWindow( static_cast< int >( mHandBmp->mX + 0.5 ), static_cast< int >( mHandBmp->mY + 0.5 ), 0, mImageState * 64, 64, 64 );
//	} else {
//		mHandBmp->drawWindow( static_cast< int >( mHandBmp->mX + 8 + 0.5 ), static_cast< int >( mHandBmp->mY + 16 + 0.5 ), 0, mImageState * 64, 64, 64 );
//	}
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

void HandManager::setState( HandState state )
{
	mState = state;
}

void HandManager::lockX( void )
{
	mIsLockX = TRUE;
}
void HandManager::lockY( void )
{
	mIsLockY = TRUE;
}

} // namespace Main
