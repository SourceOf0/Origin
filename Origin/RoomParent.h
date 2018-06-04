#ifndef INCLUDED_SEQUENCE_ROOM_PARENT_H
#define INCLUDED_SEQUENCE_ROOM_PARENT_H

#include "MainChild.h"

namespace Sequence {

class MainParent;

namespace Room {
	class RoomChild;
	class Synthesizer;
}

class RoomParent : public MainChild {
public:
	enum SeqID {
		SEQ_ROOM1,
		SEQ_ROOM1_SYNTHE,
		SEQ_ROOM2,
		SEQ_ROOM3,
		SEQ_ROOM4,
	
		SEQ_NONE
	};

	RoomParent( HDC& hdc, MainParent* parent );
	~RoomParent( void );
	void update( MainParent* parent );
	void draw( HDC& hdc, MainParent* parent );
	void moveTo( SeqID );

private:
	Room::RoomChild* mRoom1;
	Room::RoomChild* mRoom2;
	Room::RoomChild* mRoom3;
	Room::RoomChild* mRoom4;
	Room::Synthesizer* mSynthe;
	SeqID mNow;
};

} //namespace Sequence

#endif // INCLUDED_SEQUENCE_ROOM_PARENT_H
