#ifndef INCLUDED_SOUND_TRACK_H
#define INCLUDED_SOUND_TRACK_H

#include "SoundBase.h"

#define EFFECT_MAX_NUM	3	// 追加できるエフェクトの最大数
#define LOG_MAX_NUM		30	// バッファのログを取る最大数

namespace Sound {

class EffectBase;
class Wave;

class Track {

public:
	Track( void );
	~Track( void );

	void reset( void );
	int update( void );

	void setF( double f );
	double getPlayTime( void );
	double getPrevData( int prevIndex );

	double* getAdjWave( void );
	double* getPlayWave( void );

	int addEffect( EffectBase* newEffect );
	int setWave( WaveID id );

private:
	double* mAdjWave;
	double mPlayTime;

	int mLogIndex;
	double* mWaveLog[ LOG_MAX_NUM ];

	WaveID mWaveID;
	Wave* mWave;
	EffectBase* mEffectList[ EFFECT_MAX_NUM ];
};

} //namespace Sound

#endif // INCLUDED_SOUND_TRACK_H
