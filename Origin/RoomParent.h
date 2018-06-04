#ifndef INCLUDED_SEQUENCE_ROOM_PARENT_H
#define INCLUDED_SEQUENCE_ROOM_PARENT_H

#include "MainChild.h"

namespace Sequence {

class MainParent;

namespace Room {
	class RoomChild;
}

class RoomParent : public MainChild {
public:
	enum SeqID {
		SEQ_DEBUG1,
		SEQ_DEBUG2,
		SEQ_BOOK2,
	
		SEQ_NONE
	};

	RoomParent( HDC& hdc, MainParent* parent );
	~RoomParent( void );
	void update( MainParent* parent );
	void draw( HDC& hdc, MainParent* parent );

private:
	Room::RoomChild* mChild;
};

} //namespace Sequence

#endif // INCLUDED_SEQUENCE_ROOM_PARENT_H
