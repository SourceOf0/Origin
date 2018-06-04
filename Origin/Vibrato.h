#ifndef INCLUDED_SOUND_VIBRATO_H
#define INCLUDED_SOUND_VIBRATO_H

#include "EffectBase.h"

namespace Sound {

class Track;

class Vibrato : public EffectBase
{
public:
	Vibrato( void );
	~Vibrato( void );

	void reset( void );
	void apply( Track* track );

private:
	double mTime;
	double mWaveLog[ LOG_MAX_DATA_NUM ][ WAVE_DATA_LENGTH ];
};

} // namespace Sound

#endif // INCLUDED_SOUND_VIBRATO_H