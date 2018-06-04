#ifndef INCLUDED_SOUND_TRACK_H
#define INCLUDED_SOUND_TRACK_H

#include <windows.h>
#include "SoundBase.h"

namespace Sound {

class EffectBase;
class AutoPan;
class Equalizer;
class Wave;

class Track {

public:
	Track( void );
	~Track( void );

	void reset( void );
	int update( void );

	void setF( double f );
	void setVol( double vol );
	void setPan( double vol );
	void setAutoPan( BOOL isUse );
	void setEQKind( int index, EQID kind );
	void setEQState( int index, double fc, double g );
	double getPlayTime( void );
	double* getWaveData( void );
	double* getPlayData( void );
	double getPlayDataL( int index );
	double getPlayDataR( int index );

	int addEffect( int index, EffectID id );
	EffectBase* getEffect( int index );

	int setWave( WaveID id );

private:
	double* mWaveData;
	double* mWaveLog[ LOG_MAX_INDEX_NUM ][ LOG_MAX_DATA_NUM ];

	double mVolL;
	double mVolR;

	double* mPlayData;
	double mPlayTime;
	AutoPan* mAutoPan;
	Equalizer* mEQ;

	BOOL mIsUpdate;

	WaveID mWaveID;
	Wave* mWave;
	EffectBase* mEffectList[ EFFECT_MAX_NUM ];
};

} //namespace Sound

#endif // INCLUDED_SOUND_TRACK_H
