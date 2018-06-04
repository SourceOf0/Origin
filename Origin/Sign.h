#ifndef INCLUDED_SEQUENCE_ROOM_SIGN_H
#define INCLUDED_SEQUENCE_ROOM_SIGN_H

#include "PartsBase.h"

namespace Image {
	class LayerData;
}

namespace Sequence {

class RoomParent;

namespace Room {

class Sign : public PartsBase {
public:
	void setData( PartsID minSign, PartsID maxSign, int x, int y );

	BOOL checkHit( void );
	void update( void );
	void draw( Image::LayerData *partsBmp );

	BOOL isChangeSign( void );
	PartsID getSign( void );

	void addTargetSign( void );
	void decTargetSign( void );
	BOOL isMoveEnd( void );

private:
	int mDefX;

	BOOL mIsChangeSign;
	PartsID mTargetSign;
	PartsID mMinSign;
	PartsID mMaxSign;

};

} // namespace Room
} // namespace Sequence

#endif // INCLUDED_SEQUENCE_ROOM_SIGN_H
