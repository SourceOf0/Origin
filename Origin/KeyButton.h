#ifndef INCLUDED_SEQUENCE_ROOM_KEYBUTTON_H
#define INCLUDED_SEQUENCE_ROOM_KEYBUTTON_H

#include "PartsBase.h"

namespace Image {
	class LayerData;
}

namespace Sequence {

class RoomParent;

namespace Room {

class KeyButton : public PartsBase {
public:
	void setData( int x, int y, BOOL isOn = FALSE );

	void reset( void );
	BOOL isOn( void );
	void setOn( void );

	BOOL checkHit( void );
	void draw( Image::LayerData *partsBmp );

private:
};

} // namespace Room
} // namespace Sequence

#endif // INCLUDED_SEQUENCE_ROOM_KEYBUTTON_H
