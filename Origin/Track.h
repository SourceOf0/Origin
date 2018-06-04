#ifndef INCLUDED_SOUND_TRACK_H
#define INCLUDED_SOUND_TRACK_H

#include "SoundBase.h"

namespace Sound {

class EffectBase;
class AutoPan;
class Wave;

class Track {

public:
	Track( void );
	~Track( void );

	void reset( void );
	int update( void );

	void setF( double f );
	int getPlayTime( void );
	double* getWaveData( void );
	double* getPlayData( void );
	double getPlayDataL( int index );
	double getPlayDataR( int index );

	int addEffect( EffectID id );
	EffectBase* getEffect( int index );

	int setWave( WaveID id );

private:
	double* mWaveData;
	double* mWaveLog[ LOG_MAX_INDEX_NUM ][ LOG_MAX_DATA_NUM ];

	double mVolL;
	double mVolR;

	double* mPlayData;
	int mPlayTime;
	char mUseLog;

	WaveID mWaveID;
	Wave* mWave;
	EffectBase* mEffectList[ EFFECT_MAX_NUM ];
	AutoPan* mAutoPan;
};

} //namespace Sound

#endif // INCLUDED_SOUND_TRACK_H
