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
	int setBuffer();
	int setSound( int index );
	int makeWave( void );

private:
	SoundManager( HWND& hwnd );
	SoundManager( SoundManager& );
	~SoundManager( void );

	double clipping( double s );
	double sound01( double A, double f0, double fs, double t );
	double effect01( double s );
	double effect02( double s );
	double effect03( double s );

	static const double M_PI;
	int BUFFER_SIZE;
	static SoundManager* mInst;

	int mPlayingIndex;
	int mSetBufferIndex;
	int mSetBufferNum;
	BOOL mIsPlay;
	double mA;
	double mAddA;
	double mSetWaveLeng;
	double mF;

	HWAVEOUT mHWaveOut;
	WAVEHDR mWaveHeader[2];
	LPBYTE mLpWave[2];
};

} // namespace Main

#endif // INCLUDED_MAIN_SOUND_MANAGER_H
