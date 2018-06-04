#include "RoomParent.h"
#include "Room4.h"

#include "ImageFactory.h"
#include "SceneManager.h"
#include "HandManager.h"

#include "LayerData.h"

namespace Sequence {
namespace Room {

Room4::Room4( HDC& hdc, RoomParent* parent )
{
	Main::ImageFactory* imageFactory = Main::ImageFactory::inst();
	int windowWidth = Main::SceneManager::windowWidth;
	int windowHeight = Main::SceneManager::windowHeight;

	mBackBmp = ( Image::LayerData* )( imageFactory->load( hdc, "resource\\room4.dad" ) );
	mBackBmp->mUseAlpha = FALSE;

	mX = ( windowWidth - mBackBmp->mWidth ) / 2;
	mY = ( windowHeight - mBackBmp->mHeight ) / 2;
}

Room4::~Room4()
{
	delete mBackBmp;
	mBackBmp = 0;
}

void Room4::update( RoomParent* parent )
{
	int windowWidth = Main::SceneManager::windowWidth;
	int windowHeight = Main::SceneManager::windowHeight;
	BOOL isClick = Main::SceneManager::isClick;
	Main::HandManager* handManager = Main::HandManager::inst();
	int mouseX = handManager->getX() - mX;
	int mouseY = handManager->getY() - mY;

	handManager->setState( handManager->HAND_NORMAL );

	if( mouseX < 100 ){
		if( isClick ) {
			parent->moveTo( parent->SEQ_ROOM3 );
		} else {
			handManager->setState( handManager->HAND_LEFT );
		}
	} else if( mouseX > static_cast< int >( mBackBmp->mWidth ) - 100 ) {
		if( isClick ) {
			parent->moveTo( parent->SEQ_ROOM2 );
		} else {
			handManager->setState( handManager->HAND_RIGHT );
		}
	}
}

void Room4::draw( HDC& hdc, RoomParent* parent )
{
	mBackBmp->drawWindow();
}

} // namespace Room
} // namespace Sequence