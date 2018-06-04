#ifndef INCLUDED_SEQUENCE_ROOM_TRASH_CAN_H
#define INCLUDED_SEQUENCE_ROOM_TRASH_CAN_H

#include "RoomChild.h"

namespace Image {
	class LayerData;
}

namespace Sequence {

class RoomParent;

namespace Room {

class TrashCan : public RoomChild {
public:
	TrashCan( HDC& hdc, RoomParent* parent );
	~TrashCan( void );
	void update( RoomParent* parent );
	void draw( HDC& hdc, RoomParent* parent, double depth, int fadeCount );

private:
	Image::LayerData* mBackBmp;
	Image::LayerData* mTrashBmp;
	Image::LayerData* mShadowBmp;

	int mViewIndex;
	int mPrevIndex;
};

} // namespace Room
} // namespace Sequence

#endif // INCLUDED_SEQUENCE_ROOM_TRASH_CAN_H
