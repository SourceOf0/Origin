#ifndef INCLUDED_SOUND_CHORUS_H
#define INCLUDED_SOUND_CHORUS_H

#include "EffectBase.h"

namespace Sound {

class Track;

class Chorus : public EffectBase
{
public:
	Chorus( void );
	~Chorus( void );

	void reset( void );
	void apply( Track* track );

private:
	double mWaveLog[ LOG_MAX_DATA_NUM ][ WAVE_DATA_LENGTH ];
};

} // namespace Sound

#endif // INCLUDED_SOUND_CHORUS_H