#ifndef INCLUDED_SEQUENCE_MAIN_PARENT_H
#define INCLUDED_SEQUENCE_MAIN_PARENT_H

#include <windows.h>

namespace Image {
	class DCBitmap;
}

namespace Sequence {
	
class MainChild;
class RoomParent;

class MainParent {
public:
	enum SeqID {
		SEQ_DEBUG1,
		SEQ_DEBUG2,
		SEQ_ROOM,
		SEQ_BOOK1,
		SEQ_BOOK2,
		SEQ_BOOK3,
		SEQ_BOOK4,
		SEQ_BOOK5,
		SEQ_BOOK6,
		SEQ_BOOK7,
	
		SEQ_NONE
	};
	static DWORD WINAPI LoadThread( LPVOID hWnd );

	MainParent( HWND& hwnd, HDC& hdc, int windowWidth, int windowHeight);
	~MainParent( void );
	void update( void );
	void draw( HDC& hdc );
	void moveTo( SeqID );

private:
	static MainParent* getInst( void );
	static MainParent* mInst;

	HWND mHWnd;
	HANDLE mHLoadThread;
	BYTE mThreadState;

	MainChild* mChild;
	RoomParent* mRoom;
	MainChild* mDebugLoading;

	Image::DCBitmap* mBookCornerBmp;

	SeqID mNext;
};

} //namespace Sequence

#endif // INCLUDED_SEQUENCE_MAIN_PARENT_H
