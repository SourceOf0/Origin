#ifndef INCLUDED_SOUND_TREMOLO_H
#define INCLUDED_SOUND_TREMOLO_H

#include "EffectBase.h"

namespace Sound {

class Track;

class Tremolo : public EffectBase
{
public:
	Tremolo( void );
	~Tremolo( void );

	void reset( void );
	void apply( Track* track );

private:
};

} // namespace Sound

#endif // INCLUDED_SOUND_TREMOLO_H