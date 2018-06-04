#ifndef INCLUDED_SEQUENCE_ROOM_PLAYBUTTON_H
#define INCLUDED_SEQUENCE_ROOM_PLAYBUTTON_H

#include "PartsBase.h"
#include "ViewObj.h"

namespace Image {
	class LayerData;
}

namespace Sequence {

class RoomParent;

namespace Room {

class PlayButton : public PartsBase {
public:
	void setData( PartsID signID, int x, int y, int signX, int signY, BOOL isOn = FALSE );

	BOOL checkHit( void );
	void draw( Image::LayerData *partsBmp );

	void setOn( void );
	void setOff( void );
	BOOL isSwitch( void );
	BOOL isOn( void );

private:
	ViewObj mSign;
	BOOL mIsSwitch;
};

} // namespace Room
} // namespace Sequence

#endif // INCLUDED_SEQUENCE_ROOM_PLAYBUTTON_H
