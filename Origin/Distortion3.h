#ifndef INCLUDED_SOUND_DISTORTION3_H
#define INCLUDED_SOUND_DISTORTION3_H

#include "EffectBase.h"

namespace Sound {

class Track;

class Distortion3 : public EffectBase
{
public:
	Distortion3( void );
	~Distortion3( void );

	void reset( void );
	void apply( Track* track );

private:
};

} // namespace Sound

#endif // INCLUDED_SOUND_DISTORTION1_H