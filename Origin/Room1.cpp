#include "RoomParent.h"
#include "Room1.h"

#include "ImageFactory.h"
#include "SceneManager.h"
#include "HandManager.h"

#include "LayerData.h"

namespace Sequence {
namespace Room {

Room1::Room1( HDC& hdc, RoomParent* parent )
{
	Main::ImageFactory* imageFactory = Main::ImageFactory::inst();
	int windowWidth = Main::SceneManager::windowWidth;
	int windowHeight = Main::SceneManager::windowHeight;

	mBackBmp = ( Image::LayerData* )( imageFactory->load( hdc, "resource\\room1.dad" ) );
	mBackBmp->mUseAlpha = FALSE;

	mX = ( windowWidth - mBackBmp->mWidth ) / 2;
	mY = ( windowHeight - mBackBmp->mHeight ) / 2;
}

Room1::~Room1()
{
	delete mBackBmp;
	mBackBmp = 0;
}

void Room1::update( RoomParent* parent )
{
	int windowWidth = Main::SceneManager::windowWidth;
	int windowHeight = Main::SceneManager::windowHeight;
	BOOL isClick = Main::SceneManager::isClick;
	Main::HandManager* handManager = Main::HandManager::inst();
	int mouseX = handManager->getX() - mX;
	int mouseY = handManager->getY() - mY;

	handManager->setState( handManager->HAND_NORMAL );

	if( mouseX > 380 && mouseX < 560 && mouseY > 380 && mouseY < 450 ) {
		if( isClick ) {
			parent->moveTo( parent->SEQ_ROOM1_SYNTHE );
		} else {
			handManager->setState( handManager->HAND_CHECK );
		}
	} else if( mouseX < 100 ){
		if( isClick ) {
			parent->moveTo( parent->SEQ_ROOM2 );
		} else {
			handManager->setState( handManager->HAND_LEFT );
		}
	} else if( mouseX > static_cast< int >( mBackBmp->mWidth ) - 100 ) {
		if( isClick ) {
			parent->moveTo( parent->SEQ_ROOM3 );
		} else {
			handManager->setState( handManager->HAND_RIGHT );
		}
	}
}

void Room1::draw( HDC& hdc, RoomParent* parent )
{
	mBackBmp->drawWindow();
}

} // namespace Room
} // namespace Sequence