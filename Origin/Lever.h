#ifndef INCLUDED_SEQUENCE_ROOM_LEVER_H
#define INCLUDED_SEQUENCE_ROOM_LEVER_H

#include "PartsBase.h"

namespace Image {
	class LayerData;
}

namespace Sequence {

class RoomParent;

namespace Room {

class Lever : public PartsBase {
public:
	void setData( int x, int y, int val );

	BOOL checkHit( void );
	void draw( Image::LayerData *partsBmp );

	int getVal( void );
	BOOL isChangeVal( void );
	BOOL isHold( void );

private:
	int mDefX;
	BOOL mIsChangeVal;
	BOOL mIsHold;
};

} // namespace Room
} // namespace Sequence

#endif // INCLUDED_SEQUENCE_ROOM_LEVER_H
