#include "MainParent.h"
#include "MainChild.h"

#include "Title.h"
#include "Book2.h"

#include "DebugLoading.h"
#include "Debug1.h"
#include "Debug2.h"

namespace Sequence {

MainParent* MainParent::mInst = 0;

MainParent::MainParent(	HWND& hwnd, HDC& hdc, int windowWidth, int windowHeight ) : 
mHWnd( hwnd ),
mChild( 0 ),
mThreadState( 1 ),
mNext( SEQ_NONE ),
mWindowWidth( windowWidth ),
mWindowHeight( windowHeight ),
mIsMouseDown( FALSE ),
mIsAddWave( FALSE )
{
	DWORD id;

	mInst = this;

	mDebugLoading = new DebugLoading( hdc, this );

	mNext = SEQ_DEBUG2;

	mHLoadThread = CreateThread( NULL, 0, LoadThread, mHWnd , 0, &id );
}

MainParent::~MainParent( void )
{
	while( MainParent::mInst->mThreadState == 1 ) {
		Sleep( 10 );
	}

	delete mDebugLoading;
	mDebugLoading = 0;

	if( mChild != 0 ) {
		delete mChild;
		mChild = 0;
	}
}

DWORD WINAPI MainParent::LoadThread( LPVOID hWnd )
{
	MainParent* inst = MainParent::mInst;
	if( inst->mChild != 0 ) {
		delete inst->mChild;
		inst->mChild = 0;
	}

	HDC hdc = GetDC( inst->mHWnd );
	switch( inst->mNext ) {
		case SEQ_DEBUG1:
			inst->mChild = new Debug1( hdc, inst );
			break;
		case SEQ_DEBUG2:
			inst->mChild = new Debug2( hdc, inst );
			break;
		case SEQ_TITLE:
			inst->mChild = new Title( hdc, inst );
			break;
		case SEQ_BOOK2:
			inst->mChild = new Book2( hdc, inst );
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

	if( mThreadState == 1 ) {
		mDebugLoading->update( this );
		return;
	} else if( mThreadState == 2 ) {
		mThreadState = 0;
	}
	mChild->update( this );

	if( mNext != SEQ_NONE ) {
		mThreadState = 1;
		mHLoadThread = CreateThread( NULL, 0, LoadThread, mHWnd , 0, &id );
	}

	mIsAddWave = FALSE;
}

void MainParent::draw( HDC& hdc )
{
	if( mThreadState == 0 ) {
		mChild->draw( hdc, this );
	} else {
		mDebugLoading->draw( hdc, this );
	}
}

void MainParent::moveTo( SeqID next )
{
	mNext = next;
}


} //namespace Sequence


