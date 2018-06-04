#ifndef INCLUDED_SEQUENCE_ROOM_ROOM4_H
#define INCLUDED_SEQUENCE_ROOM_ROOM4_H

#include "RoomChild.h"

namespace Image {
	class LayerData;
}

namespace Sequence {

class RoomParent;

namespace Room {

class Room4 : public RoomChild {
public:
	Room4( HDC& hdc, RoomParent* parent );
	~Room4( void );
	void update( RoomParent* parent );
	void draw( HDC& hdc, RoomParent* parent );

private:
	Image::LayerData* mBackBmp;
};

} // namespace Room
} // namespace Sequence

#endif // INCLUDED_SEQUENCE_ROOM_ROOM4_H
