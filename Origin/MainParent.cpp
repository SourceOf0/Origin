#include "MainParent.h"
#include "MainChild.h"

#include "Title.h"
#include "Debug1.h"

namespace Sequence {

MainParent::MainParent( HDC& hdc ) : 
mChild(),
mNext( SEQ_NONE )
{
//	mChild = new Title( hdc );
	mChild = new Debug1( hdc );
}

MainParent::~MainParent( void )
{
	delete mChild;
	mChild = 0;
}

void MainParent::update( void )
{
	mChild->update( this );

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

void MainParent::draw( HDC& hdc )
{
	mChild->draw( hdc, this );
}

void MainParent::moveTo( SeqID next )
{
	mNext = next;
}


} //namespace Sequence


