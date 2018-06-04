#ifndef INCLUDED_MAIN_SCENE_MANAGER_H
#define INCLUDED_MAIN_SCENE_MANAGER_H

#include <windows.h>

namespace Sequence {
	class MainParent;
}

namespace Main {

class SceneManager
{
public:
	static SceneManager* inst();
	static void create( HWND& hwnd );
	static void destroy( void );

	int update( void );
	int draw( HDC& hdc );

	void endSetWave( void );

	static int windowWidth;
	static int windowHeight;

	static BOOL isAddWave;

	LPDWORD mWindowPixel;
	HDC mHdcBmp;

	SYSTEMTIME mLocalTime;
	int mFrameRate;

private:
	SceneManager( HWND& hwnd );
	SceneManager( SceneManager& );
	~SceneManager( void );
	static SceneManager* mInst;

	Sequence::MainParent* mParent;

	HBITMAP mHBmp;
	HBITMAP mHBmpOld;
	BITMAPINFO* mBmpInfo;
};

} // namespace Main

#endif // INCLUDED_MAIN_SCENE_MANAGER_H
