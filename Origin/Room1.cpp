#include "RoomParent.h"
#include "Room1.h"

#include "ImageFactory.h"
#include "SceneManager.h"
#include "HandManager.h"

#include "LayerData.h"
#include "DCBitmap.h"

namespace Sequence {
namespace Room {

Room1::Room1( HDC& hdc, RoomParent* parent )
{
	Main::ImageFactory* imageFactory = Main::ImageFactory::inst();
	int windowWidth = Main::SceneManager::windowWidth;
	int windowHeight = Main::SceneManager::windowHeight;

	mBackBmp1 = ( Image::LayerData* )( imageFactory->load( hdc, "resource\\room1.dad" ) );
	mBackBmp1->mUseAlpha = FALSE;

	mBackBmp2 = ( Image::LayerData* )( imageFactory->load( hdc, "resource\\room1_2.dad" ) );
	mBackBmp2->mUseAlpha = FALSE;

	mX = ( windowWidth - mBackBmp1->mWidth ) / 2;
	mY = ( windowHeight - mBackBmp1->mHeight ) / 2;
}

Room1::~Room1()
{
	delete mBackBmp1;
	mBackBmp1 = 0;

	delete mBackBmp2;
	mBackBmp2 = 0;
}

void Room1::update( RoomParent* parent )
{
	int windowWidth = Main::SceneManager::windowWidth;
	int windowHeight = Main::SceneManager::windowHeight;
	BOOL isClick = Main::HandManager::isClick;
	Main::HandManager* handManager = Main::HandManager::inst();
	int mouseX = handManager->getX() - mX;
	int mouseY = handManager->getY() - mY;

	handManager->setState( handManager->HAND_NORMAL );

	if( mouseX > 380 && mouseX < 560 && mouseY > 380 && mouseY < 450 ) {
		handManager->setState( handManager->HAND_CHECK );
		if( isClick ) parent->moveTo( parent->SEQ_ROOM1_SYNTHE );
	} else if( !parent->mIsCloseCurtain && mouseX > 550 && mouseX < 600 && mouseY > 100 && mouseY < 350 ) {
		handManager->setState( handManager->HAND_HOLD_BEFORE );
		if( isClick ) parent->mIsCloseCurtain = TRUE;
	} else if( parent->mIsCloseCurtain && mouseX > 100 && mouseX < 600 && mouseY > 100 && mouseY < 350 ) {
		handManager->setState( handManager->HAND_HOLD_BEFORE );
		if( isClick ) parent->mIsCloseCurtain = FALSE;
	} else if( mouseX < 80 ){
		handManager->setState( handManager->HAND_LEFT );
		if( isClick ) parent->moveTo( parent->SEQ_ROOM2 );
	} else if( mouseX > static_cast< int >( mBackBmp1->mWidth ) - 100 ) {
		handManager->setState( handManager->HAND_RIGHT );
		if( isClick ) parent->moveTo( parent->SEQ_ROOM3 );
	}
}

void Room1::draw( HDC& hdc, RoomParent* parent, double depth, int fadeCount )
{
	mBackBmp1->mDepth = depth;
	mBackBmp2->mDepth = depth;

	if( fadeCount == 0 ) {
		mBackBmp1->drawWindow();
		return;
	} else if( fadeCount == TONE_NONE * 2 ) {
		mBackBmp2->drawWindow();
		return;
	}
	if( fadeCount < TONE_NONE ) {
		mBackBmp2->drawWindow();
		mFadeBmp->copyWindow();
		Image::BitmapBase::mTone[ fadeCount - 1 ]->drawImageOr( mFadeBmp->mHdcBmp, 0, 0 );
		mBackBmp1->drawWindow();
		mFadeBmp->drawWindowAnd();
	} else {
		mBackBmp1->drawWindow();
		mFadeBmp->copyWindow();
		Image::BitmapBase::mTone[ TONE_NONE * 2 - fadeCount - 1 ]->drawImageOr( mFadeBmp->mHdcBmp, 0, 0 );
		mBackBmp2->drawWindow();
		mFadeBmp->drawWindowAnd();
	}
}

} // namespace Room
} // namespace Sequence