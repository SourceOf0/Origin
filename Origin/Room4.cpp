#include "RoomParent.h"
#include "Room4.h"

#include "ImageFactory.h"
#include "SceneManager.h"
#include "HandManager.h"

#include "LayerData.h"
#include "DCBitmap.h"

namespace Sequence {
namespace Room {

Room4::Room4( HDC& hdc, RoomParent* parent )
{
	Main::ImageFactory* imageFactory = Main::ImageFactory::inst();
	int windowWidth = Main::SceneManager::windowWidth;
	int windowHeight = Main::SceneManager::windowHeight;

	mBackBmp1 = ( Image::LayerData* )( imageFactory->load( hdc, "resource\\room4.dad" ) );
	mBackBmp1->mUseAlpha = FALSE;

	mBackBmp2 = ( Image::LayerData* )( imageFactory->load( hdc, "resource\\room4_2.dad" ) );
	mBackBmp2->mUseAlpha = FALSE;

	mSwitchBmp = ( Image::LayerData* )( imageFactory->load( hdc, "resource\\room4_switch.dad" ) );
	mSwitchBmp->mUseAlpha = FALSE;
	mSwitchBmp->mX = 344;
	mSwitchBmp->mY = 327;
}

Room4::~Room4()
{
	delete mBackBmp1;
	mBackBmp1 = 0;

	delete mBackBmp2;
	mBackBmp2 = 0;

	delete mSwitchBmp;
	mSwitchBmp = 0;
}

void Room4::update( RoomParent* parent )
{
	int windowWidth = Main::SceneManager::windowWidth;
	int windowHeight = Main::SceneManager::windowHeight;
	BOOL isClick = Main::HandManager::isClick;
	Main::HandManager* handManager = Main::HandManager::inst();
	int mouseX = handManager->getX();
	int mouseY = handManager->getY();

	handManager->setState( handManager->HAND_NORMAL );

	if( mouseX > 340 && mouseX < 380 && mouseY > 320 && mouseY < 380 ){
		if( isClick ) {
			parent->mIsOnLight = !parent->mIsOnLight;
			handManager->setState( handManager->HAND_PUSH_AFTER );
		} else {
			handManager->setState( handManager->HAND_PUSH_BEFORE );
		}
	} else if( mouseX < 100 ) {
		handManager->setState( handManager->HAND_LEFT );
		if( isClick ) parent->moveTo( parent->SEQ_ROOM3 );
	} else if( mouseX > static_cast< int >( mBackBmp1->mWidth ) - 100 ) {
		handManager->setState( handManager->HAND_RIGHT );
		if( isClick ) parent->moveTo( parent->SEQ_ROOM2 );
	}
}

void Room4::draw( HDC& hdc, RoomParent* parent, double depth, int fadeCount )
{
	mBackBmp1->mDepth = depth;
	mBackBmp2->mDepth = depth;
	mSwitchBmp->mDepth = depth;

	mSwitchBmp->drawWindow();
	if( fadeCount == 0 ) {
		mBackBmp1->drawWindow();
	} else if( fadeCount == TONE_NONE * 2 ) {
		mBackBmp2->drawWindow();
	} else if( fadeCount < TONE_NONE ) {
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
	if( !parent->mIsOnLight ) mSwitchBmp->drawWindow();
}

} // namespace Room
} // namespace Sequence