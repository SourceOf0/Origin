#ifndef INCLUDED_SEQUENCE_ROOM_FADERV_H
#define INCLUDED_SEQUENCE_ROOM_FADERV_H

#include "PartsBase.h"

namespace Image {
	class LayerData;
}

namespace Sequence {

class RoomParent;

namespace Room {

class FaderV : public PartsBase {
public:
	void setData( int x, int y, int fixX1, int fixY1, int fixX2, int fixY2 );

	BOOL checkHit( void );
	void draw( Image::LayerData *partsBmp );

	double getVal( void );
	void setVal( double val );
	BOOL isHold( void );

private:
	int mDefY;
	BOOL mIsHold;
};

} // namespace Room
} // namespace Sequence

#endif // INCLUDED_SEQUENCE_ROOM_FADERH_H
