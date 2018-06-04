#ifndef INCLUDED_SEQUENCE_ROOM_PARENT_H
#define INCLUDED_SEQUENCE_ROOM_PARENT_H

#include "MainChild.h"
#include "MainParent.h"

namespace Sequence {

namespace Room {
	class RoomChild;
	class Synthesizer;
	class BookCover;
	class TrashCan;
	class Note;
}

class RoomParent : public MainChild {
public:
	enum SeqID {
		SEQ_ROOM1,
		SEQ_ROOM1_SYNTHE,
		SEQ_ROOM2,
		SEQ_ROOM3,
		SEQ_ROOM4,
		
		SEQ_COVER_BOOK1,
		SEQ_COVER_BOOK2,
		SEQ_COVER_BOOK3,
		SEQ_COVER_BOOK4,
		SEQ_COVER_BOOK5,
		SEQ_COVER_BOOK6,
		SEQ_COVER_BOOK7,

		SEQ_TRASHCAN,
		SEQ_NOTE,

		// 上位シーケンス
		SEQ_BOOK1,
		SEQ_BOOK2,
		SEQ_BOOK3,
		SEQ_BOOK4,
		SEQ_BOOK5,
		SEQ_BOOK6,
		SEQ_BOOK7,
	
		SEQ_NONE
	};

	RoomParent( HDC& hdc, MainParent* parent );
	~RoomParent( void );
	void update( MainParent* parent );
	void draw( HDC& hdc, MainParent* parent );
	void moveTo( SeqID next );
	void setParentSeq( MainParent::SeqID setSeq );

	void playSound( void );

	BOOL mIsCloseCurtain;
	BOOL mIsOnLight;
	BOOL mIsConnectSocket;

private:
	Room::RoomChild* mRoom1;
	Room::RoomChild* mRoom2;
	Room::RoomChild* mRoom3;
	Room::RoomChild* mRoom4;
	Room::Synthesizer* mSynthe;
	Room::BookCover* mBookCover;
	Room::TrashCan* mTrashCan;
	Room::Note* mNote;
	SeqID mNow;

	double mDepth;
	int mDepthCount;
	int mFadeCount;

	unsigned int mWriteCount;
	unsigned int mWaitCount;
	unsigned int mCheckState;
};

} //namespace Sequence

#endif // INCLUDED_SEQUENCE_ROOM_PARENT_H
