#ifndef INCLUDED_SEQUENCE_ROOM_ROOM1_H
#define INCLUDED_SEQUENCE_ROOM_ROOM1_H

#include "RoomChild.h"

namespace Image {
	class LayerData;
}

namespace Sequence {

class RoomParent;

namespace Room {

class Room1 : public RoomChild {
public:
	Room1( HDC& hdc, RoomParent* parent );
	~Room1( void );
	void update( RoomParent* parent );
	void draw( HDC& hdc, RoomParent* parent );

private:
	Image::LayerData* mBackBmp;
};

} // namespace Room
} // namespace Sequence

#endif // INCLUDED_SEQUENCE_ROOM_ROOM1_H
