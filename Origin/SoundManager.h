#ifndef INCLUDED_MAIN_SOUND_MANAGER_H
#define INCLUDED_MAIN_SOUND_MANAGER_H

#include <windows.h>

namespace Sound {
	class Track;
	class WaveBase;
	class EffectBase;
}


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
	int setSound( int index );
	Sound::Track* getTrack( int index );
	int makeWave( void );

private:
	SoundManager( HWND& hwnd );
	SoundManager( SoundManager& );
	~SoundManager( void );

	double clipping( double s );

	static SoundManager* mInst;

	Sound::Track* mTrack1;
	Sound::Track* mTrack2;

	int test;
	int mSetBufferIndex;
	int mSetBufferNum;
	BOOL mIsPlay;

	HWAVEOUT mHWaveOut;
	WAVEHDR mWaveHeader[2];
	LPBYTE mLpWave[2];
};

} // namespace Main

#endif // INCLUDED_MAIN_SOUND_MANAGER_H
