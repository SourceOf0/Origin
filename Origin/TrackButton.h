#ifndef INCLUDED_SEQUENCE_ROOM_TRACKBUTTON_H
#define INCLUDED_SEQUENCE_ROOM_TRACKBUTTON_H

#include "PartsBase.h"

namespace Image {
	class LayerData;
}

namespace Sequence {

class RoomParent;

namespace Room {

class TrackButton : public PartsBase {
public:
	void setData( int x, int y, BOOL isOn = FALSE );

	BOOL checkHit( void );
	void update( void );
	void draw( Image::LayerData *partsBmp );

	void setOn( void );
	void setOff( void );
	BOOL isSwitch( void );
	BOOL isOn( void );

private:
	BOOL mIsSwitch;
};

} // namespace Room
} // namespace Sequence

#endif // INCLUDED_SEQUENCE_ROOM_TRACKBUTTON_H
