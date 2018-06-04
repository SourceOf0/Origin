#include "MainParent.h"
#include "MainChild.h"
#include "RoomParent.h"

#include "Synthesizer.h"

namespace Sequence {

RoomParent::RoomParent( HDC& hdc, MainParent* parent ) :
mChild( 0 )
{
	mChild = new Room::Synthesizer( hdc, this );
}

RoomParent::~RoomParent()
{
	if( mChild != 0 ) {
		delete mChild;
		mChild = 0;
	}
}

void RoomParent::update( MainParent* parent )
{
	mChild->update( this );
}

void RoomParent::draw( HDC& hdc, MainParent* parent )
{
	mChild->draw( hdc, this );
}


} // namespace Sequence