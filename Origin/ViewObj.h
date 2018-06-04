#ifndef INCLUDED_SEQUENCE_ROOM_VIEWOBJ_H
#define INCLUDED_SEQUENCE_ROOM_VIEWOBJ_H

#include "PartsBase.h"

namespace Image {
	class LayerData;
}

namespace Sequence {

class RoomParent;

namespace Room {

class ViewObj : public PartsBase {
public:
	void setData( PartsID partsID, int x, int y, BOOL isView );

	BOOL checkHit( void );
	void draw( Image::LayerData *partsBmp );

	void setPartsID( PartsID partsID );
	void setView( BOOL isView );
	void setPos( int x, int y );
	void fixPos( int addX, int addY );

private:
	int mDefX;
	int mDefY;

	BOOL mIsView;
};

} // namespace Room
} // namespace Sequence

#endif // INCLUDED_SEQUENCE_ROOM_VIEWOBJ_H
