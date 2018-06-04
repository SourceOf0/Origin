#ifndef INCLUDED_SEQUENCE_ROOM_NOTE_H
#define INCLUDED_SEQUENCE_ROOM_NOTE_H

#include "RoomChild.h"
#include "NoteManager.h"

namespace Image {
	class LayerData;
	class DCBitmap;
}

namespace Sequence {

class RoomParent;

namespace Room {

class Note : public RoomChild {
public:
	Note( HDC& hdc, RoomParent* parent );
	~Note( void );
	void update( RoomParent* parent );
	void draw( HDC& hdc, RoomParent* parent, double depth, int fadeCount );

	void write( BOOL isTurnPage );

private:
	Image::LayerData* mBackBmp;
	Image::LayerData* mPencilBmp;
	Image::DCBitmap* mNowPageBmp;
	Image::DCBitmap* mNextPageBmp;

	int mViewPageIndex;
	unsigned int mTurnPageCount;
	int mTurnPageState;
};

} // namespace Room
} // namespace Sequence

#endif // INCLUDED_SEQUENCE_ROOM_NOTE_H
