#ifndef INCLUDED_SOUND_VIBRATO_H
#define INCLUDED_SOUND_VIBRATO_H

#include "EffectBase.h"

namespace Sound {

class Track;

class Vibrato : public EffectBase
{
public:
	Vibrato( double** setWaveLog );
	~Vibrato( void );

	void reset( void );
	void apply( Track* track );

private:
	double mD;
	double mDepth;
	double mRate;
};

} // namespace Sound

#endif // INCLUDED_SOUND_VIBRATO_H