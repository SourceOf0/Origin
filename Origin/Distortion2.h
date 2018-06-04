#ifndef INCLUDED_SOUND_DISTORTION2_H
#define INCLUDED_SOUND_DISTORTION2_H

#include "EffectBase.h"

namespace Sound {

class Track;

class Distortion2 : public EffectBase
{
public:
	Distortion2( void );
	~Distortion2( void );

	void reset( void );
	void apply( Track* track );

private:

};

} // namespace Sound

#endif // INCLUDED_SOUND_DISTORTION2_H