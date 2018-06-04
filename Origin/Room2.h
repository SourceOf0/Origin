#ifndef INCLUDED_SEQUENCE_ROOM_ROOM2_H
#define INCLUDED_SEQUENCE_ROOM_ROOM2_H

#include "RoomChild.h"

namespace Image {
	class LayerData;
}

namespace Sequence {

class RoomParent;

namespace Room {

class Room2 : public RoomChild {
public:
	Room2( HDC& hdc, RoomParent* parent );
	~Room2( void );
	void update( RoomParent* parent );
	void draw( HDC& hdc, RoomParent* parent );

private:
	Image::LayerData* mBackBmp;
};

} // namespace Room
} // namespace Sequence

#endif // INCLUDED_SEQUENCE_ROOM_ROOM2_H
