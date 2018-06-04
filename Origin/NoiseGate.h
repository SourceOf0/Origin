#ifndef INCLUDED_SOUND_NOISE_GATE_H
#define INCLUDED_SOUND_NOISE_GATE_H

#include "EffectBase.h"

namespace Sound {

class Track;

class NoiseGate : public EffectBase
{
public:
	NoiseGate( void );
	~NoiseGate( void );

	void reset( void );
	void apply( Track* track );

private:
};

} // namespace Sound

#endif // INCLUDED_SOUND_NOISE_GATE_H