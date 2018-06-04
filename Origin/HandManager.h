#ifndef INCLUDED_MAIN_HAND_MANAGER_H
#define INCLUDED_MAIN_HAND_MANAGER_H

#include <windows.h>

namespace Image {
	class LayerData;
}

namespace Main {

class HandManager
{
public:
	enum HandState {
		HAND_NORMAL,
		HAND_CHECK,
		HAND_PUSH_BEFORE,
		HAND_PUSH_AFTER,
		HAND_HOLD_BEFORE,
		HAND_HOLD_AFTER,
		HAND_CLOSE,

		HAND_BACK,
		HAND_LEFT,
		HAND_RIGHT,
		HAND_UP,
		HAND_DOWN,

		HAND_NONE
	};

	enum ImageState {
		HAND_IMAGE_NORMAL,
		HAND_IMAGE_PUSH,
		HAND_IMAGE_HOLD_BEFORE,
		HAND_IMAGE_HOLD_AFTER,
		HAND_IMAGE_CLOSE,
		HAND_IMAGE_BACK,
		HAND_IMAGE_RIGHT,
		HAND_IMAGE_LEFT,
		HAND_IMAGE_UP,

		HAND_IMAGE_CHECK,

		HAND_IMAGE_NONE
	};

	static HandManager* inst();
	static void create( HDC& hdc );
	static void destroy( void );

	void update( BOOL isLoading );
	void draw( void );

	int getX( void );
	int getY( void );

	void mouseDown( void );
	void mouseUp( void );
	void endUpdate( void );

	void setState( HandState state );
	void lockX( void );
	void lockY( void );
	void setRangeX( int min, int max );
	void setRangeY( int min, int max );

	static BOOL isMouseDown;
	static BOOL isClick;

private:
	HandManager( HDC& hdc );
	HandManager( HandManager& );
	~HandManager( void );

	static HandManager* mInst;

	int mX;
	int mY;
	int mMouseX;
	int mMouseY;
	int mLockX;
	int mLockY;
	int mMinX;
	int mMaxX;
	int mMinY;
	int mMaxY;
	BOOL mIsLockX;
	BOOL mIsLockY;

	HandState mState;
	ImageState mImageState;
	int mAnimeCount;

	Image::LayerData* mHandBmp;
	Image::LayerData* mCheckHandBmp;
};

} // namespace Main

#endif // INCLUDED_MAIN_HAND_MANAGER_H
