#ifndef INCLUDED_SOUND_DELAY_H
#define INCLUDED_SOUND_DELAY_H

#include "EffectBase.h"

namespace Sound {

class Track;

class Delay : public EffectBase
{
public:
//	Delay( void );
	Delay( double** setWaveLog );
	~Delay( void );

	void reset( void );
	void apply( Track* track );

private:
	double getPrevData( int prevIndex );

	double mA;			/* Œ¸Š—¦ */
	double mDelayTime;	/* ’x‰„ŠÔ */
	int mRepeat;		/* ŒJ‚è•Ô‚µ‰ñ” */

	int mLogIndex;
	double** mWaveLog;
};

} // namespace Sound

#endif // INCLUDED_SOUND_DELAY_H