#ifndef INCLUDED_MAIN_SOUND_MANAGER_H
#define INCLUDED_MAIN_SOUND_MANAGER_H

#include <windows.h>

namespace Main {

class SoundManager
{
public:
	static SoundManager* inst( void );
	static void create( HWND& hwnd );
	static void destroy( void );

	int play( void );
	int stop( void );
	int setBuffer( void );

private:
	SoundManager( HWND& hwnd );
	SoundManager( SoundManager& );
	~SoundManager( void );
	static SoundManager* mInst;

	HWAVEOUT mHWaveOut;
	WAVEHDR mWaveHeader;
	LPBYTE mLpWave;
	BOOL isReset;
};

} // namespace Main

#endif // INCLUDED_MAIN_SOUND_MANAGER_H
