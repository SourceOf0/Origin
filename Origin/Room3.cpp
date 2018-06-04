#include "RoomParent.h"
#include "Room3.h"

#include "ImageFactory.h"
#include "SceneManager.h"
#include "HandManager.h"

#include "LayerData.h"

namespace Sequence {
namespace Room {

Room3::Room3( HDC& hdc, RoomParent* parent )
{
	Main::ImageFactory* imageFactory = Main::ImageFactory::inst();
	int windowWidth = Main::SceneManager::windowWidth;
	int windowHeight = Main::SceneManager::windowHeight;

	mBackBmp = ( Image::LayerData* )( imageFactory->load( hdc, "resource\\room3.dad" ) );
	mBackBmp->mUseAlpha = FALSE;

	mX = ( windowWidth - mBackBmp->mWidth ) / 2;
	mY = ( windowHeight - mBackBmp->mHeight ) / 2;
}

Room3::~Room3()
{
	delete mBackBmp;
	mBackBmp = 0;
}

void Room3::update( RoomParent* parent )
{
	int windowWidth = Main::SceneManager::windowWidth;
	int windowHeight = Main::SceneManager::windowHeight;
	BOOL isClick = Main::SceneManager::isClick;
	Main::HandManager* handManager = Main::HandManager::inst();
	int mouseX = handManager->getX() - mX;
	int mouseY = handManager->getY() - mY;

	handManager->setState( handManager->HAND_NORMAL );

	if( mouseX > 210 && mouseX < 680 ) {
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
	}
}

void Room3::draw( HDC& hdc, RoomParent* parent )
{
	mBackBmp->drawWindow();
}

} // namespace Room
} // namespace Sequence