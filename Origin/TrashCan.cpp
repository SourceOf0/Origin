#include "RoomParent.h"
#include "TrashCan.h"

#include "ImageFactory.h"
#include "SceneManager.h"
#include "HandManager.h"
#include "NoteManager.h"

#include "LayerData.h"
#include "DCBitmap.h"

namespace Sequence {
namespace Room {

TrashCan::TrashCan( HDC& hdc, RoomParent* parent ) :
mViewIndex( 0 ),
mPrevIndex( 0 )
{
	Main::ImageFactory* imageFactory = Main::ImageFactory::inst();
	int windowWidth = Main::SceneManager::windowWidth;
	int windowHeight = Main::SceneManager::windowHeight;

	mBackBmp = ( Image::LayerData* )( imageFactory->load( hdc, "resource\\trashCan.dad" ) );
	mBackBmp->mUseAlpha = FALSE;

	mShadowBmp = ( Image::LayerData* )( imageFactory->load( hdc, "resource\\trashCan_shadow.dad" ) );

	mTrashBmp = ( Image::LayerData* )( imageFactory->load( hdc, "resource\\trash1.dad" ) );
}

TrashCan::~TrashCan()
{
	delete mBackBmp;
	mBackBmp = 0;

	delete mShadowBmp;
	mShadowBmp = 0;

	if( mTrashBmp != 0 ) {
		delete mTrashBmp;
		mTrashBmp = 0;
	}
}

void TrashCan::update( RoomParent* parent )
{
	BOOL isClick = Main::HandManager::isClick;
	Main::HandManager* handManager = Main::HandManager::inst();
	int mouseX = handManager->getX();
	int mouseY = handManager->getY();

	handManager->setState( handManager->HAND_NORMAL );

	if( mouseX < 300 || mouseX > 800 || mouseY < 200 || mouseY > 500 ){
		handManager->setState( handManager->HAND_BACK );
		if( isClick ) parent->moveTo( parent->SEQ_ROOM2 );
	}
}

void TrashCan::draw( HDC& hdc, RoomParent* parent, double depth, int fadeCount )
{
	mBackBmp->mDepth = depth;
	mBackBmp->drawWindow();

	if( !Main::HandManager::inst()->checkState( Main::HandManager::HAND_HIDE ) ) {
		mShadowBmp->mDepth = depth;
		mShadowBmp->drawWindow();
	}

	mViewIndex = Main::NoteManager::inst()->getTrashCount();
	if( mViewIndex == 0 ) return;

	if( mViewIndex != mPrevIndex ) {
		mPrevIndex = mViewIndex;
		delete mTrashBmp;
		mTrashBmp = 0;
		switch( mViewIndex ) {
			case 1:
				mTrashBmp = ( Image::LayerData* )( Main::ImageFactory::inst()->load( hdc, "resource\\trash1.dad" ) );
				break;
			case 2:
				mTrashBmp = ( Image::LayerData* )( Main::ImageFactory::inst()->load( hdc, "resource\\trash2.dad" ) );
				break;
			case 3:
				mTrashBmp = ( Image::LayerData* )( Main::ImageFactory::inst()->load( hdc, "resource\\trash3.dad" ) );
				break;
			case 4:
				mTrashBmp = ( Image::LayerData* )( Main::ImageFactory::inst()->load( hdc, "resource\\trash4.dad" ) );
				break;
			case 5:
				mTrashBmp = ( Image::LayerData* )( Main::ImageFactory::inst()->load( hdc, "resource\\trash5.dad" ) );
				break;
			case 6:
				mTrashBmp = ( Image::LayerData* )( Main::ImageFactory::inst()->load( hdc, "resource\\trash6.dad" ) );
				break;
			case 7:
				mTrashBmp = ( Image::LayerData* )( Main::ImageFactory::inst()->load( hdc, "resource\\trash7.dad" ) );
				break;
			case 8:
				mTrashBmp = ( Image::LayerData* )( Main::ImageFactory::inst()->load( hdc, "resource\\trash8.dad" ) );
				break;
		}
	}

	mTrashBmp->mDepth = depth;
	mTrashBmp->drawWindow( 345, 228 );
}

} // namespace Room
} // namespace Sequence