#include "RoomParent.h"
#include "BookCover.h"

#include "ImageFactory.h"
#include "SceneManager.h"
#include "HandManager.h"

#include "LayerData.h"
#include "DCBitmap.h"

namespace Sequence {
namespace Room {

BookCover::BookCover( HDC& hdc, RoomParent* parent ) :
mBookKind( 0 )
{
	Main::ImageFactory* imageFactory = Main::ImageFactory::inst();
	const int VIEW_WIDTH = Main::SceneManager::VIEW_WIDTH;
	const int VIEW_HEIGHT = Main::SceneManager::VIEW_HEIGHT;

	int i = -1;
	mCoverBmp[ ++i ] = ( Image::LayerData* )( imageFactory->load( hdc, IDR_DAD_BOOK1 ) );
	mCoverBmp[ ++i ] = ( Image::LayerData* )( imageFactory->load( hdc, IDR_DAD_BOOK2 ) );
	mCoverBmp[ ++i ] = ( Image::LayerData* )( imageFactory->load( hdc, IDR_DAD_BOOK3 ) );
	mCoverBmp[ ++i ] = ( Image::LayerData* )( imageFactory->load( hdc, IDR_DAD_BOOK4 ) );
	mCoverBmp[ ++i ] = ( Image::LayerData* )( imageFactory->load( hdc, IDR_DAD_BOOK5 ) );
	mCoverBmp[ ++i ] = ( Image::LayerData* )( imageFactory->load( hdc, IDR_DAD_BOOK6 ) );
	mCoverBmp[ ++i ] = ( Image::LayerData* )( imageFactory->load( hdc, IDR_DAD_BOOK7 ) );

	int setX = ( VIEW_WIDTH - mCoverBmp[ 0 ]->mWidth ) / 2;
	int setY = ( VIEW_HEIGHT - mCoverBmp[ 0 ]->mHeight ) / 2;
	for( int j = 0; j < 7; ++j ) {
		mCoverBmp[ j ]->mX = setX;
		mCoverBmp[ j ]->mY = setY;
	}
	mCoverBmp[ 0 ]->mDepth = -0.3;
	mCoverBmp[ 1 ]->mDepth = -0.3;
	mCoverBmp[ 2 ]->mDepth = 0.3;
	mCoverBmp[ 3 ]->mDepth = -0.2;
	mCoverBmp[ 4 ]->mDepth = -0.1;
	mCoverBmp[ 5 ]->mDepth = -0.3;
	mCoverBmp[ 6 ]->mDepth = -0.2;
}

BookCover::~BookCover()
{
	for( int i = 0; i < 7; ++i ) {
		delete mCoverBmp[ i ];
		mCoverBmp[ i ] = 0;
	}
}

void BookCover::update( RoomParent* parent )
{
	const int VIEW_WIDTH = Main::SceneManager::VIEW_WIDTH;
	const int VIEW_HEIGHT = Main::SceneManager::VIEW_HEIGHT;
	BOOL isClick = Main::HandManager::isClick;
	Main::HandManager* handManager = Main::HandManager::inst();
	int mouseX = handManager->getX();
	int mouseY = handManager->getY();

	handManager->setState( handManager->HAND_BACK );

	Image::LayerData* target = mCoverBmp[ mBookKind ];
	double setX = target->mX;
	double setY = target->mY;
	if( mouseX > setX && mouseX < setX + target->mWidth && mouseY > setY && mouseY < setY + target->mHeight ){
		handManager->setState( handManager->HAND_CHECK );
		if( isClick ) parent->moveTo( ( RoomParent::SeqID )( parent->SEQ_BOOK1 + mBookKind ) );
	} else {
		if( isClick ) parent->moveTo( parent->SEQ_ROOM3 );
	}
}

void BookCover::draw( HDC& hdc, RoomParent* parent, double depth, int fadeCount )
{
	mCoverBmp[ mBookKind ]->drawWindow();
}

} // namespace Room
} // namespace Sequence