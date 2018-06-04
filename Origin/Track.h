#ifndef INCLUDED_SOUND_TRACK_H
#define INCLUDED_SOUND_TRACK_H

#include "SoundBase.h"

#define EFFECT_MAX_NUM	3	// �ǉ��ł���G�t�F�N�g�̍ő吔
#define LOG_MAX_NUM		30	// �o�b�t�@�̃��O�����ő吔

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
	int getPlayTime( void );
	double* getWaveData( void );

	int addEffect( EffectID id );
	EffectBase* getEffect( int index );

	int setWave( WaveID id );

private:
	double* mWaveData;
	int mPlayTime;
	double* mWaveLog[ LOG_MAX_NUM ];

	WaveID mWaveID;
	Wave* mWave;
	EffectBase* mEffectList[ EFFECT_MAX_NUM ];
};

} //namespace Sound

#endif // INCLUDED_SOUND_TRACK_H