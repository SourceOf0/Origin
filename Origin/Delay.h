#ifndef INCLUDED_SOUND_DELAY_H
#define INCLUDED_SOUND_DELAY_H

#include "EffectBase.h"

namespace Sound {

class Track;

class Delay : public EffectBase
{
public:
	Delay( void );
	~Delay( void );

	void reset( void );
	void apply( Track* track );

private:
	double mWaveLog[ LOG_MAX_DATA_NUM ][ WAVE_DATA_LENGTH ];
};

} // namespace Sound

#endif // INCLUDED_SOUND_DELAY_H