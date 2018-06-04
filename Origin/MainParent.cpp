#include "MainParent.h"
#include "MainChild.h"

#include "RoomParent.h"
#include "Book1.h"
#include "Book2.h"
#include "Book3.h"
#include "Book4.h"
#include "Book5.h"
#include "Book6.h"
#include "Book7.h"

#include "DebugLoading.h"
#include "Debug1.h"
#include "Debug2.h"

#include "DCBitmap.h"

#include "HandManager.h"
#include "BitmapBase.h"
#include "ImageFactory.h"
#include "SceneManager.h"

namespace Sequence {

MainParent* MainParent::mInst = 0;

MainParent::MainParent(	HWND& hwnd, HDC& hdc, int windowWidth, int windowHeight ) : 
mHWnd( hwnd ),
mRoom( 0 ),
mChild( 0 ),
mDebugLoading( 0 ),
mThreadState( 3 ),
mNext( SEQ_NONE ),
mBookCornerBmp( 0 )
{
	mInst = this;

	mDebugLoading = new DebugLoading( hdc, this );

	mNext = SEQ_ROOM;
}

MainParent::~MainParent( void )
{
	while( MainParent::mInst->mThreadState == 1 ) {
		Sleep( 10 );
	}

	delete mDebugLoading;
	mDebugLoading = 0;

	if( mRoom != 0 ) {
		delete mRoom;
		mRoom = 0;
	}

	if( mChild != 0 ) {
		delete mChild;
		mChild = 0;
	}

	delete mBookCornerBmp;
	mBookCornerBmp = 0;
}

DWORD WINAPI MainParent::LoadThread( LPVOID hWnd )
{
	MainParent* inst = MainParent::mInst;
	if( inst->mChild != 0 ) {
		delete inst->mChild;
		inst->mChild = 0;
	}

	HDC hdc = GetDC( inst->mHWnd );
	if( inst->mBookCornerBmp == 0 ) {
		inst->mBookCornerBmp = Main::ImageFactory::inst()->loadDC( hdc, "resource\\bookCorner.dad" );
		Image::DCBitmap* target = inst->mBookCornerBmp;
		target->mX = Main::SceneManager::windowWidth - 64;
		target->mY = Main::SceneManager::windowHeight - 64;
	}

	switch( inst->mNext ) {
		case SEQ_DEBUG1:
			inst->mChild = new Debug1( hdc, inst );
			break;
		case SEQ_DEBUG2:
			inst->mChild = new Debug2( hdc, inst );
			break;
		case SEQ_ROOM:
			if( inst->mRoom == 0 ) {
				inst->mRoom = new RoomParent( hdc, inst );
			}
			break;
		case SEQ_BOOK1:
			inst->mChild = new Book1( hdc, inst );
			break;
		case SEQ_BOOK2:
			inst->mChild = new Book2( hdc, inst );
			break;
		case SEQ_BOOK3:
			inst->mChild = new Book3( hdc, inst );
			break;
		case SEQ_BOOK4:
			inst->mChild = new Book4( hdc, inst );
			break;
		case SEQ_BOOK5:
			inst->mChild = new Book5( hdc, inst );
			break;
		case SEQ_BOOK6:
			inst->mChild = new Book6( hdc, inst );
			break;
		case SEQ_BOOK7:
			inst->mChild = new Book7( hdc, inst );
			break;
	}
	ReleaseDC( inst->mHWnd, hdc );

	inst->mThreadState = 2;
	inst->mNext = SEQ_NONE;
	ExitThread( 1 );
}

void MainParent::update( void )
{
	DWORD id;

	switch( mThreadState ) {
		case 2:
			mThreadState = 0;
		case 0:
			if( mChild == 0 ) {
				mRoom->update( this );
			} else {
				mChild->update( this );
			}
			if( mNext != SEQ_NONE ) {
				mRoom->setParentSeq( mNext );
				mThreadState = 1;
				mHLoadThread = CreateThread( NULL, 0, LoadThread, mHWnd, 0, &id );
			}
			break;

		case 3:
			mThreadState = 1;
			mHLoadThread = CreateThread( NULL, 0, LoadThread, mHWnd , 0, &id );
		case 1:
			mDebugLoading->update( this );
			break;

	}

	Main::HandManager::inst()->update();
}

void MainParent::draw( HDC& hdc )
{
	if( mThreadState == 0 ) {
		if( mChild == 0 ) {
			mRoom->draw( hdc, this );
		} else {
			mChild->draw( hdc, this );
			mBookCornerBmp->drawWindowOr();
		}
	} else {
		mDebugLoading->draw( hdc, this );
	}
	Main::HandManager::inst()->draw();
}

void MainParent::moveTo( SeqID next )
{
	mNext = next;
}

} //namespace Sequence


