#ifndef INCLUDED_SEQUENCE_ROOM_BOOKCOVER_H
#define INCLUDED_SEQUENCE_ROOM_BOOKCOVER_H

#include "RoomChild.h"

namespace Image {
	class LayerData;
}

namespace Sequence {

class RoomParent;

namespace Room {

class BookCover : public RoomChild {
public:
	BookCover( HDC& hdc, RoomParent* parent );
	~BookCover( void );
	void update( RoomParent* parent );
	void draw( HDC& hdc, RoomParent* parent, double depth, int fadeCount );

	int mBookKind;

private:
	Image::LayerData* mCoverBmp[ 7 ];
};

} // namespace Room
} // namespace Sequence

#endif // INCLUDED_SEQUENCE_ROOM_BOOKCOVER_H
