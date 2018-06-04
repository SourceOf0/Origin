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
	void setVol( double vol );
	void setPan( double vol );
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
	Sound::Track* mTrack3;

	int mSetBufferIndex;
	int mSetBufferNum;
	BOOL mIsPlay;
	BOOL mWasReset;

	double mMainVol;
	double mMainVolL;
	double mMainVolR;

	HWAVEOUT mHWaveOut;
	WAVEHDR mWaveHeader[ 2 ];
	LPBYTE mLpWave[ 2 ];
//	short* mLpWave[ 2 ];
};

} // namespace Main

#endif // INCLUDED_MAIN_SOUND_MANAGER_H
