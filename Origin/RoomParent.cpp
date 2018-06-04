#include "MainParent.h"
#include "MainChild.h"
#include "RoomParent.h"

#include "Room1.h"
#include "Room2.h"
#include "Room3.h"
#include "Room4.h"
#include "Synthesizer.h"

#include "SoundManager.h"

namespace Sequence {

RoomParent::RoomParent( HDC& hdc, MainParent* parent ) :
mRoom1( 0 ),
mRoom2( 0 ),
mRoom3( 0 ),
mRoom4( 0 ),
mSynthe( 0 ),
mNow( SEQ_NONE )
{
	mRoom1 = new Room::Room1( hdc, this );
	mRoom2 = new Room::Room2( hdc, this );
	mRoom3 = new Room::Room3( hdc, this );
	mRoom4 = new Room::Room4( hdc, this );
	mSynthe = new Room::Synthesizer( hdc, this );
	mSynthe->update( this );

	mNow = SEQ_ROOM1;
}

RoomParent::~RoomParent()
{
	if( mRoom1 != 0 ) {
		delete mRoom1;
		mRoom1 = 0;
	}
	if( mRoom2 != 0 ) {
		delete mRoom2;
		mRoom2 = 0;
	}
	if( mRoom3 != 0 ) {
		delete mRoom3;
		mRoom3 = 0;
	}
	if( mRoom4 != 0 ) {
		delete mRoom4;
		mRoom4 = 0;
	}

	if( mSynthe != 0 ) {
		delete mSynthe;
		mSynthe = 0;
	}
}

void RoomParent::update( MainParent* parent )
{
	switch( mNow ) {
		case SEQ_ROOM1:
			mRoom1->update( this );
			break;
		case SEQ_ROOM2:
			mRoom2->update( this );
			break;
		case SEQ_BOOK1:
		case SEQ_BOOK2:
		case SEQ_BOOK3:
		case SEQ_BOOK4:
		case SEQ_BOOK5:
		case SEQ_BOOK6:
		case SEQ_BOOK7:
			Main::SoundManager::inst()->play();
			mNow = SEQ_ROOM3;
		case SEQ_ROOM3:
			mRoom3->update( this );
			break;
		case SEQ_ROOM4:
			mRoom4->update( this );
			break;
		case SEQ_ROOM1_SYNTHE:
			mSynthe->update( this );
			break;
	}
	switch( mNow ) {
		case SEQ_BOOK1:
			Main::SoundManager::inst()->stop();
			parent->moveTo( parent->SEQ_BOOK1 );
			break;
		case SEQ_BOOK2:
			Main::SoundManager::inst()->stop();
			parent->moveTo( parent->SEQ_BOOK2 );
			break;
		case SEQ_BOOK3:
			Main::SoundManager::inst()->stop();
			parent->moveTo( parent->SEQ_BOOK3 );
			break;
		case SEQ_BOOK4:
			Main::SoundManager::inst()->stop();
			parent->moveTo( parent->SEQ_BOOK4 );
			break;
		case SEQ_BOOK5:
			Main::SoundManager::inst()->stop();
			parent->moveTo( parent->SEQ_BOOK5 );
			break;
		case SEQ_BOOK6:
			Main::SoundManager::inst()->stop();
			parent->moveTo( parent->SEQ_BOOK6 );
			break;
		case SEQ_BOOK7:
			Main::SoundManager::inst()->stop();
			parent->moveTo( parent->SEQ_BOOK7 );
			break;
		default:
			mSynthe->playTrack();
			break;
	}
}

void RoomParent::draw( HDC& hdc, MainParent* parent )
{
	switch( mNow ) {
		case SEQ_ROOM1:
			mRoom1->draw( hdc, this );
			break;
		case SEQ_ROOM2:
			mRoom2->draw( hdc, this );
			break;
		case SEQ_ROOM3:
			mRoom3->draw( hdc, this );
			break;
		case SEQ_ROOM4:
			mRoom4->draw( hdc, this );
			break;
		case SEQ_ROOM1_SYNTHE:
			mSynthe->draw( hdc, this );
			break;
	}
}

void RoomParent::moveTo( SeqID next )
{
	mNow = next;
}

void RoomParent::setParentSeq( MainParent::SeqID setSeq )
{
	switch( setSeq ) {
		case MainParent::SEQ_BOOK1:
			mNow = SEQ_BOOK1;
			break;
		case MainParent::SEQ_BOOK2:
			mNow = SEQ_BOOK2;
			break;
		case MainParent::SEQ_BOOK3:
			mNow = SEQ_BOOK3;
			break;
		case MainParent::SEQ_BOOK4:
			mNow = SEQ_BOOK4;
			break;
		case MainParent::SEQ_BOOK5:
			mNow = SEQ_BOOK5;
			break;
		case MainParent::SEQ_BOOK6:
			mNow = SEQ_BOOK6;
			break;
		case MainParent::SEQ_BOOK7:
			mNow = SEQ_BOOK7;
			break;
	}
}


} // namespace Sequence