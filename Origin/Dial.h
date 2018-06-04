#ifndef INCLUDED_SEQUENCE_ROOM_DIAL_H
#define INCLUDED_SEQUENCE_ROOM_DIAL_H

#include "PartsBase.h"
#include "Sign.h"

namespace Image {
	class LayerData;
}

namespace Sequence {

class RoomParent;

namespace Room {

class Dial : public PartsBase {
public:
	void setData( PartsID minSign, PartsID maxSign, int x, int y );

	BOOL checkHit( void );
	void update( void );
	void draw( Image::LayerData *partsBmp );

	BOOL isChangeSign( void );
	PartsID getSign( void );

private:
	Sign mSign;
	
	int mAnimeCount;
};

} // namespace Room
} // namespace Sequence

#endif // INCLUDED_SEQUENCE_ROOM_DIAL_H
