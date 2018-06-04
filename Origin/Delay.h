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
	double mA;			/* Œ¸Š—¦ */
	double mDelayTime;	/* ’x‰„ŠÔ */
	int mRepeat;		/* ŒJ‚è•Ô‚µ‰ñ” */
};

} // namespace Sound

#endif // INCLUDED_SOUND_DELAY_H