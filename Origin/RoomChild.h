#ifndef INCLUDED_SEQUENCE_ROOM_CHILD_H
#define INCLUDED_SEQUENCE_ROOM_CHILD_H

#include <windows.h>

namespace Image {
	class DCBitmap;
}

namespace Sequence {

class RoomParent;

namespace Room {

class RoomChild {
public:
	virtual ~RoomChild( void ) {} // 何もしない
	
	// 中身なし（派生クラスで定義されてないとエラー）
	virtual void update( Sequence::RoomParent* parent ) = 0; 
	virtual void draw( HDC& hdc, Sequence::RoomParent* parent, double depth, int fadeCount ) = 0;
	
	static Image::DCBitmap* mFadeBmp;

protected:
	int mX;
	int mY;
};

} // namespace Room
} // namespace Sequence

#endif // INCLUDED_SEQUENCE_ROOM_CHILD_H