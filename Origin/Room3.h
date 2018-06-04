#ifndef INCLUDED_SEQUENCE_ROOM_ROOM3_H
#define INCLUDED_SEQUENCE_ROOM_ROOM3_H

#include "RoomChild.h"

namespace Image {
	class LayerData;
}

namespace Sequence {

class RoomParent;

namespace Room {

class Room3 : public RoomChild {
public:
	Room3( HDC& hdc, RoomParent* parent );
	~Room3( void );
	void update( RoomParent* parent );
	void draw( HDC& hdc, RoomParent* parent );

private:
	Image::LayerData* mBackBmp;
};

} // namespace Room
} // namespace Sequence

#endif // INCLUDED_SEQUENCE_ROOM_ROOM3_H
