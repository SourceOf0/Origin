#include "MainParent.h"
#include "MainChild.h"
#include "RoomParent.h"

#include "Room1.h"
#include "Room2.h"
#include "Room3.h"
#include "Room4.h"
#include "Synthesizer.h"
#include "BookCover.h"

#include "DCBitmap.h"

#include "SceneManager.h"
#include "SoundManager.h"

namespace Sequence {

Image::DCBitmap* Room::RoomChild::mFadeBmp = 0;

RoomParent::RoomParent( HDC& hdc, MainParent* parent ) :
mRoom1( 0 ),
mRoom2( 0 ),
mRoom3( 0 ),
mRoom4( 0 ),
mSynthe( 0 ),
mNow( SEQ_NONE ),
mDepth( 0.2 ),
mDepthCount( 0 ),
mFadeCount( 0 ),
mIsCloseCurtain( FALSE ),
mIsOnLight( TRUE ),
mIsConnectSocket( TRUE )
{
	mRoom1 = new Room::Room1( hdc, this );
	mRoom2 = new Room::Room2( hdc, this );
	mRoom3 = new Room::Room3( hdc, this );
	mRoom4 = new Room::Room4( hdc, this );
	mSynthe = new Room::Synthesizer( hdc, this );
	mSynthe->playTrack( this );
	mBookCover = new Room::BookCover( hdc, this );

	Room::RoomChild::mFadeBmp = new Image::DCBitmap( hdc, Main::SceneManager::windowWidth, Main::SceneManager::windowHeight );

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

	if( mBookCover != 0 ) {
		delete mBookCover;
		mBookCover = 0;
	}

	delete Room::RoomChild::mFadeBmp;
	Room::RoomChild::mFadeBmp = 0;
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
			if( mIsConnectSocket ) Main::SoundManager::inst()->play();
			mNow = ( RoomParent::SeqID )( mNow - SEQ_BOOK1 + SEQ_COVER_BOOK1 );
			mBookCover->mBookKind = mNow - SEQ_COVER_BOOK1;
			mBookCover->update( this );
			break;
		case SEQ_ROOM3:
			mRoom3->update( this );
			( mIsConnectSocket )? Main::SoundManager::inst()->play() : Main::SoundManager::inst()->stop();
			break;
		case SEQ_ROOM4:
			mRoom4->update( this );
			break;
		case SEQ_ROOM1_SYNTHE:
			mSynthe->update( this );
			break;
		case SEQ_COVER_BOOK1:
		case SEQ_COVER_BOOK2:
		case SEQ_COVER_BOOK3:
		case SEQ_COVER_BOOK4:
		case SEQ_COVER_BOOK5:
		case SEQ_COVER_BOOK6:
		case SEQ_COVER_BOOK7:
			mBookCover->mBookKind = mNow - SEQ_COVER_BOOK1;
			mBookCover->update( this );
			break;
	}

	Sequence::MainParent::SeqID id = parent->SEQ_NONE;
	switch( mNow ) {
		case SEQ_BOOK1:
			id = parent->SEQ_BOOK1;
			break;
		case SEQ_BOOK2:
			id = parent->SEQ_BOOK2;
			break;
		case SEQ_BOOK3:
			id = parent->SEQ_BOOK3;
			break;
		case SEQ_BOOK4:
			id = parent->SEQ_BOOK4;
			break;
		case SEQ_BOOK5:
			id = parent->SEQ_BOOK5;
			break;
		case SEQ_BOOK6:
			id = parent->SEQ_BOOK6;
			break;
		case SEQ_BOOK7:
			id = parent->SEQ_BOOK7;
			break;
	}
	if( id != parent->SEQ_NONE ) {
		Main::SoundManager::inst()->stop();
		parent->moveTo( id );
	} else {
		mSynthe->playTrack( this );
	}

	mDepth = ( mIsOnLight )? 0.15 : -0.1;
	if( mIsCloseCurtain ) {
		if( mFadeCount < TONE_NONE * 2 ) {
			mFadeCount += 2;
			if( mFadeCount >= TONE_NONE * 2 ) mFadeCount = TONE_NONE * 2;
		}
	} else {
		++mDepthCount;
		if( mFadeCount > 0 ) {
			mFadeCount -= 2;
			if( mFadeCount <= 0 ) mFadeCount = 0;
		}
	}
	mDepth -= mFadeCount / ( TONE_NONE * 20.0 );
	if( mDepthCount <= 220 ) {
	} else if( mDepthCount <= 240 ) {
		mDepth += 0.02;
	} else if( mDepthCount <= 260 ) {
		mDepth += 0.04;
	} else if( mDepthCount <= 280 ) {
		mDepth += 0.05;
	} else if( mDepthCount <= 300 ) {
		mDepth += 0.07;
	} else if( mDepthCount <= 620 ) {
		mDepth += 0.09;
	} else if( mDepthCount <= 660 ) {
		mDepth += 0.07;
	} else if( mDepthCount <= 680 ) {
		mDepth += 0.05;
	} else if( mDepthCount <= 700 ) {
		mDepth += 0.04;
	} else if( mDepthCount <= 720 ) {
		mDepth += 0.02;
	} else {
		mDepthCount = 0;
	}
}

void RoomParent::draw( HDC& hdc, MainParent* parent )
{
	switch( mNow ) {
		case SEQ_ROOM1:
			mRoom1->draw( hdc, this, mDepth, mFadeCount );
			break;
		case SEQ_ROOM2:
			mRoom2->draw( hdc, this, mDepth, mFadeCount );
			break;
		case SEQ_ROOM3:
			mRoom3->draw( hdc, this, mDepth, mFadeCount );
			break;
		case SEQ_ROOM4:
			mRoom4->draw( hdc, this, mDepth, mFadeCount );
			break;
		case SEQ_ROOM1_SYNTHE:
			mSynthe->draw( hdc, this, mDepth, mFadeCount );
			break;
		case SEQ_COVER_BOOK1:
		case SEQ_COVER_BOOK2:
		case SEQ_COVER_BOOK3:
		case SEQ_COVER_BOOK4:
		case SEQ_COVER_BOOK5:
		case SEQ_COVER_BOOK6:
		case SEQ_COVER_BOOK7:
			mRoom3->draw( hdc, this, mDepth, mFadeCount );
			mBookCover->mBookKind = mNow - SEQ_COVER_BOOK1;
			mBookCover->draw( hdc, this, mDepth, mFadeCount );
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