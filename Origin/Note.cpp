#include "RoomParent.h"
#include "Note.h"

#include "ImageFactory.h"
#include "SceneManager.h"
#include "HandManager.h"

#include "LayerData.h"
#include "DCBitmap.h"

#define TURN_PAGE_SPEED 50

namespace Sequence {
namespace Room {

Note::Note( HDC& hdc, RoomParent* parent ) :
mViewPageIndex( 0 ),
mTurnPageCount( 0 ),
mTurnPageState( 0 )
{
	Main::ImageFactory* imageFactory = Main::ImageFactory::inst();

	mBackBmp = ( Image::LayerData* )( imageFactory->load( hdc, "resource\\note.dad" ) );
	mBackBmp->mUseAlpha = FALSE;

	mPencilBmp = ( Image::LayerData* )( imageFactory->load( hdc, "resource\\note_pencil.dad" ) );
	mPencilBmp->mUseAlpha = FALSE;
	mPencilBmp->drawWindow();

	mNowPageBmp = Main::ImageFactory::inst()->loadDC( hdc, "resource\\page_room_1.dad" );
	mNextPageBmp = 0;

	mTurnPageCount = mNowPageBmp->mWidth;
}

Note::~Note()
{
	delete mBackBmp;
	mBackBmp = 0;

	delete mPencilBmp;
	mPencilBmp = 0;

	delete mNowPageBmp;
	mNowPageBmp = 0;

	if( mNextPageBmp != 0 ) {
		delete mNextPageBmp;
		mNextPageBmp = 0;
	}
}

void Note::update( RoomParent* parent )
{
	BOOL isClick = Main::HandManager::isClick;
	Main::HandManager* handManager = Main::HandManager::inst();
	int mouseX = handManager->getX();
	int mouseY = handManager->getY();

	handManager->setState( handManager->HAND_NORMAL );

	if( mTurnPageState != 0 ) {
		if( mTurnPageCount < mNowPageBmp->mWidth ) {
			mTurnPageCount += TURN_PAGE_SPEED;
			if( mTurnPageCount >= mNowPageBmp->mWidth ) {
				mTurnPageCount = mNowPageBmp->mWidth;
				mTurnPageState = 0;
			}
		}
	}

	if( mouseX > 50 && mouseX < 950 && mouseY > 50 && mouseY < 700 ){
		if( mouseX > 500 ) {
			if( mViewPageIndex == Main::NoteManager::inst()->getNowPageNum() - 1 ) return;
			handManager->setState( handManager->HAND_RIGHT );
			if( !isClick ) return;
			++mViewPageIndex;
			if( mNextPageBmp != 0 ) {
				delete mNextPageBmp;
				mNextPageBmp = 0;
			}
			mTurnPageState = 1;
			mTurnPageCount = 0;
		} else {
			if( mViewPageIndex == 0 ) return;
			handManager->setState( handManager->HAND_LEFT );
			if( !isClick ) return;
			--mViewPageIndex;
			if( mNextPageBmp != 0 ) {
				delete mNextPageBmp;
				mNextPageBmp = 0;
			}
			mTurnPageState = -1;
			mTurnPageCount = 0;
		}
	} else {
		handManager->setState( handManager->HAND_BACK );
		if( !isClick ) return;
		parent->moveTo( parent->SEQ_ROOM2 );
		mTurnPageCount = mNowPageBmp->mWidth;
		mTurnPageState = 0;
	}
}

void Note::write( BOOL isTurnPage )
{
	int setIndex = Main::NoteManager::inst()->write();
	if( setIndex == -1 ) return;
	mViewPageIndex = setIndex;
	if( mNextPageBmp != 0 ) {
		delete mNextPageBmp;
		mNextPageBmp = 0;
	}
	if( !isTurnPage ) return;
	mTurnPageState = 1;
	mTurnPageCount = 0;
}

void Note::draw( HDC& hdc, RoomParent* parent, double depth, int fadeCount )
{
	mBackBmp->mDepth = depth;
	mBackBmp->drawWindow();

	if( !Main::HandManager::inst()->checkState( Main::HandManager::HAND_HIDE ) ) {
		mPencilBmp->mDepth = depth;
		mPencilBmp->drawWindow( 864, 0 );
	}

	if( mNextPageBmp == 0 ) {
		switch( Main::NoteManager::inst()->getNowPage( mViewPageIndex ) ) {
			case NOTE_ROOM_1:
				mNextPageBmp = Main::ImageFactory::inst()->loadDC( hdc, "resource\\page_room_1.dad" );
				break;
			case NOTE_ROOM_2:
				mNextPageBmp = Main::ImageFactory::inst()->loadDC( hdc, "resource\\page_room_2.dad" );
				break;
			case NOTE_ROOM_3:
				mNextPageBmp = Main::ImageFactory::inst()->loadDC( hdc, "resource\\page_room_3.dad" );
				break;
			case NOTE_BOOK1_1:
				mNextPageBmp = Main::ImageFactory::inst()->loadDC( hdc, "resource\\page_book1_1.dad" );
				break;
			case NOTE_BOOK1_2:
				mNextPageBmp = Main::ImageFactory::inst()->loadDC( hdc, "resource\\page_book1_2.dad" );
				break;
			case NOTE_BOOK1_3:
				mNextPageBmp = Main::ImageFactory::inst()->loadDC( hdc, "resource\\page_book1_3.dad" );
				break;
			case NOTE_BOOK2_1:
				mNextPageBmp = Main::ImageFactory::inst()->loadDC( hdc, "resource\\page_book2_1.dad" );
				break;
			case NOTE_BOOK2_2:
				mNextPageBmp = Main::ImageFactory::inst()->loadDC( hdc, "resource\\page_book2_2.dad" );
				break;
			case NOTE_BOOK2_3:
				mNextPageBmp = Main::ImageFactory::inst()->loadDC( hdc, "resource\\page_book2_3.dad" );
				break;
			case NOTE_BOOK3_1:
				mNextPageBmp = Main::ImageFactory::inst()->loadDC( hdc, "resource\\page_book3_1.dad" );
				break;
			case NOTE_BOOK3_2:
				mNextPageBmp = Main::ImageFactory::inst()->loadDC( hdc, "resource\\page_book3_2.dad" );
				break;
			case NOTE_BOOK3_3:
				mNextPageBmp = Main::ImageFactory::inst()->loadDC( hdc, "resource\\page_book3_3.dad" );
				break;
			case NOTE_BOOK4_1:
				mNextPageBmp = Main::ImageFactory::inst()->loadDC( hdc, "resource\\page_book4_1.dad" );
				break;
			case NOTE_BOOK4_2:
				mNextPageBmp = Main::ImageFactory::inst()->loadDC( hdc, "resource\\page_book4_2.dad" );
				break;
			case NOTE_BOOK4_3:
				mNextPageBmp = Main::ImageFactory::inst()->loadDC( hdc, "resource\\page_book4_3.dad" );
				break;
			case NOTE_BOOK5_1:
				mNextPageBmp = Main::ImageFactory::inst()->loadDC( hdc, "resource\\page_book5_1.dad" );
				break;
			case NOTE_BOOK5_2:
				mNextPageBmp = Main::ImageFactory::inst()->loadDC( hdc, "resource\\page_book5_2.dad" );
				break;
			case NOTE_BOOK5_3:
				mNextPageBmp = Main::ImageFactory::inst()->loadDC( hdc, "resource\\page_book5_3.dad" );
				break;
			case NOTE_BOOK6_1:
				mNextPageBmp = Main::ImageFactory::inst()->loadDC( hdc, "resource\\page_book6_1.dad" );
				break;
			case NOTE_BOOK6_2:
				mNextPageBmp = Main::ImageFactory::inst()->loadDC( hdc, "resource\\page_book6_2.dad" );
				break;
			case NOTE_BOOK6_3:
				mNextPageBmp = Main::ImageFactory::inst()->loadDC( hdc, "resource\\page_book6_3.dad" );
				break;
			case NOTE_BOOK7_1:
				mNextPageBmp = Main::ImageFactory::inst()->loadDC( hdc, "resource\\page_book7_1.dad" );
				break;
			case NOTE_BOOK7_2:
				mNextPageBmp = Main::ImageFactory::inst()->loadDC( hdc, "resource\\page_book7_2.dad" );
				break;
			case NOTE_BOOK7_3:
				mNextPageBmp = Main::ImageFactory::inst()->loadDC( hdc, "resource\\page_book7_3.dad" );
				break;
			case NOTE_END:
				mNextPageBmp = Main::ImageFactory::inst()->loadDC( hdc, "resource\\page_end.dad" );
				break;
			case NOTE_TITLE:
				mNextPageBmp = Main::ImageFactory::inst()->loadDC( hdc, "resource\\page_title.dad" );
				break;
		}
	}

	if( mTurnPageState == 0 ) {
		mNextPageBmp->drawImage( mNowPageBmp->mHdcBmp, 0, 0 );
		mNextPageBmp->drawWindowAnd( 90, 80 );
	} else if( mTurnPageState == 1 ) {
		unsigned int setX = mNowPageBmp->mWidth - mTurnPageCount;
		mNextPageBmp->drawImage( mNowPageBmp->mHdcBmp, setX, 0, setX, 0, mTurnPageCount, mNowPageBmp->mHeight );
		mNowPageBmp->drawWindowAnd( 90, 80 );
	} else if( mTurnPageState == -1 ) {
		mNextPageBmp->drawImage( mNowPageBmp->mHdcBmp, 0, 0, 0, 0, mTurnPageCount, mNowPageBmp->mHeight );
		mNowPageBmp->drawWindowAnd( 90, 80 );
	}
}

} // namespace Room
} // namespace Sequence