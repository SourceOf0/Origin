#ifndef INCLUDED_SEQUENCE_MAIN_PARENT_H
#define INCLUDED_SEQUENCE_MAIN_PARENT_H

#include <windows.h>

namespace Sequence {
	
class MainChild;

class MainParent {
public:
	enum SeqID {
		SEQ_DEBUG1,
		SEQ_DEBUG2,
		SEQ_TITLE,
		SEQ_BOOK2,
	
		SEQ_NONE
	};
	MainParent( HWND& hwnd, HDC& hdc, int windowWidth, int windowHeight);
	~MainParent( void );
	void update( void );
	void draw( HDC& hdc );
	void moveTo( SeqID );

	int mWindowWidth;
	int mWindowHeight;

	BOOL mIsMouseDown;
	BOOL mIsAddWave;

private:
	static DWORD WINAPI LoadThread( LPVOID hWnd );
	static MainParent* getInst( void );
	static MainParent* mInst;

	HWND mHWnd;
	HANDLE mHLoadThread;
	BYTE mThreadState;

	MainChild* mChild;
	MainChild* mDebugLoading;

	SeqID mNext;
};

} //namespace Sequence

#endif // INCLUDED_SEQUENCE_MAIN_PARENT_H
