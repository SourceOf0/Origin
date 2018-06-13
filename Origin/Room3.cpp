#include "RoomParent.h"
#include "Room3.h"

#include "ImageFactory.h"
#include "SceneManager.h"
#include "HandManager.h"

#include "LayerData.h"
#include "DCBitmap.h"

namespace Sequence {
namespace Room {

Room3::Room3( HDC& hdc, RoomParent* parent )
{
	Main::ImageFactory* imageFactory = Main::ImageFactory::inst();
	int windowWidth = Main::SceneManager::windowWidth;
	int windowHeight = Main::SceneManager::windowHeight;

	mBackBmp1 = ( Image::LayerData* )( imageFactory->load( hdc, IDR_DAD_ROOM3 ) );
	mBackBmp1->mUseAlpha = FALSE;

	mBackBmp2 = ( Image::LayerData* )( imageFactory->load( hdc, IDR_DAD_ROOM3_2 ) );
	mBackBmp2->mUseAlpha = FALSE;
	
	mSocketBmp = ( Image::LayerData* )( imageFactory->load( hdc, IDR_DAD_ROOM3_SOCKET ) );
	mSocketBmp->mUseAlpha = FALSE;
	mSocketBmp->mX = 855;
	mSocketBmp->mY = 605;

	mSocketBmp->drawWindow();
}

Room3::~Room3()
{
	delete mBackBmp1;
	mBackBmp1 = 0;

	delete mBackBmp2;
	mBackBmp2 = 0;

	delete mSocketBmp;
	mSocketBmp = 0;
}

void Room3::update( RoomParent* parent )
{
	int windowWidth = Main::SceneManager::windowWidth;
	int windowHeight = Main::SceneManager::windowHeight;
	BOOL isClick = Main::HandManager::isClick;
	Main::HandManager* handManager = Main::HandManager::inst();
	int mouseX = handManager->getX();
	int mouseY = handManager->getY();

	handManager->setState( handManager->HAND_NORMAL );

/*	if( mouseX > 210 && mouseX < 680 ) {
		if( mouseY > 150 && mouseY < 250 ) {
			if( isClick ) {
				parent->moveTo( parent->SEQ_BOOK2 );
			} else {
				handManager->setState( handManager->HAND_CHECK );
			}
		} else if( mouseY > 280 && mouseY < 350 ) {
			if( isClick ) {
				parent->moveTo( parent->SEQ_BOOK3 );
			} else {
				handManager->setState( handManager->HAND_CHECK );
			}
		} else if( mouseY > 370 && mouseY < 450 ) {
			if( isClick ) {
				parent->moveTo( parent->SEQ_BOOK4 );
			} else {
				handManager->setState( handManager->HAND_CHECK );
			}
		} else if( mouseY > 465 && mouseY < 550 ) {
			if( isClick ) {
				parent->moveTo( parent->SEQ_BOOK5 );
			} else {
				handManager->setState( handManager->HAND_CHECK );
			}
		} else if( mouseY > 570 && mouseY < 650 ) {
			if( isClick ) {
				parent->moveTo( parent->SEQ_BOOK7 );
			} else {
				handManager->setState( handManager->HAND_CHECK );
			}
		}
	} else if( mouseX < 100 ){
		if( isClick ) {
			parent->moveTo( parent->SEQ_ROOM1 );
		} else {
			handManager->setState( handManager->HAND_LEFT );
		}
	} else if( mouseX > static_cast< int >( mBackBmp->mWidth ) - 100 ) {
		if( isClick ) {
			parent->moveTo( parent->SEQ_ROOM4 );
		} else {
			handManager->setState( handManager->HAND_RIGHT );
		}
	}*/

	if( mouseY > 370 && mouseY < 450 ) {
		if( mouseX > 235 && mouseX < 275 ) {
			( isClick ) ? parent->moveTo( parent->SEQ_COVER_BOOK1 ) : handManager->setState( handManager->HAND_CHECK );
		} else if( mouseX > 305 && mouseX < 335 ) {
			( isClick ) ? parent->moveTo( parent->SEQ_COVER_BOOK2 ) : handManager->setState( handManager->HAND_CHECK );
		} else if( mouseX > 345 && mouseX < 375 ) {
			( isClick ) ? parent->moveTo( parent->SEQ_COVER_BOOK3 ) : handManager->setState( handManager->HAND_CHECK );
		} else if( mouseX > 405 && mouseX < 435 ) {
			( isClick ) ? parent->moveTo( parent->SEQ_COVER_BOOK4 ) : handManager->setState( handManager->HAND_CHECK );
		} else if( mouseX > 445 && mouseX < 475 ) {
			( isClick ) ? parent->moveTo( parent->SEQ_COVER_BOOK5 ) : handManager->setState( handManager->HAND_CHECK );
		} else if( mouseX > 485 && mouseX < 515 ) {
			( isClick ) ? parent->moveTo( parent->SEQ_COVER_BOOK6 ) : handManager->setState( handManager->HAND_CHECK );
		} else if( mouseX > 585 && mouseX < 625 ) {
			( isClick ) ? parent->moveTo( parent->SEQ_COVER_BOOK7 ) : handManager->setState( handManager->HAND_CHECK );
		}
	}

	if( mouseX > 900 && mouseX < 970 && mouseY > 600 && mouseY < 680 ){
		if( isClick ) {
			parent->mIsConnectSocket = !parent->mIsConnectSocket;
			handManager->setState( handManager->HAND_PUSH_AFTER );
		} else {
			handManager->setState( handManager->HAND_PUSH_BEFORE );
		}
	} else if( mouseX < 100 ){
		handManager->setState( handManager->HAND_LEFT );
		if( isClick ) parent->moveTo( parent->SEQ_ROOM1 );
	} else if( mouseX > static_cast< int >( mBackBmp1->mWidth ) - 100 ) {
		handManager->setState( handManager->HAND_RIGHT );
		if( isClick ) parent->moveTo( parent->SEQ_ROOM4 );
	}
}

void Room3::draw( HDC& hdc, RoomParent* parent, double depth, int fadeCount )
{
	mBackBmp1->mDepth = depth;
	mBackBmp2->mDepth = depth;
	mSocketBmp->mDepth = depth;

	mSocketBmp->drawWindow();
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
	
	if( !parent->mIsConnectSocket ) mSocketBmp->drawWindow();
}

} // namespace Room
} // namespace Sequence