#ifndef INCLUDED_MAIN_SOUND_MANAGER_H
#define INCLUDED_MAIN_SOUND_MANAGER_H

#include <windows.h>
#include "common.h"
#include "SoundBase.h"

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
	void setSysVol( void );

	static SoundManager* mInst;

	Sound::Track* mTrack1;
	Sound::Track* mTrack2;
	Sound::Track* mTrack3;

	int mSetBufferIndex;
	int mSetBufferNum;
	BOOL mIsPlay;

	unsigned int mSysVol;
	double mMainVol;
	double mMainVolL;
	double mMainVolR;

	HWAVEOUT mHWaveOut;
	WAVEHDR mWaveHeader[ BUFFER_MAX_NUM ];
	short mLpWave[ BUFFER_MAX_NUM ][ BUFFER_SIZE ];
};

} // namespace Main

#endif // INCLUDED_MAIN_SOUND_MANAGER_H
