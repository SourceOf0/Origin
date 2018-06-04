#include "MainParent.h"
#include "MainChild.h"

#include "Title.h"

namespace Sequence {

MainParent::MainParent( HDC& hdc ) : 
mChild(),
mNext( SEQ_NONE )
{
	mChild = new Title( hdc );
}

MainParent::~MainParent( void )
{
	delete mChild;
	mChild = 0;
}

void MainParent::update( HDC& hdc )
{
	mChild->update( hdc, this );

	switch( mNext ) {
		case SEQ_TITLE:
//			SAFE_DELETE( mChild );
//			mChild = new Title();
			break;
//		case SEQ_GAME:
//			SAFE_DELETE( mChild );
//			ASSERT( mStageID != 0 );
//			mChild = new Game::Parent( mStageID );
			break;
	}
	mNext = SEQ_NONE;
}

void MainParent::moveTo( SeqID next )
{
	mNext = next;
}


} //namespace Sequence


