#ifndef INCLUDED_SOUND_CHORUS_H
#define INCLUDED_SOUND_CHORUS_H

#include "EffectBase.h"

namespace Sound {

class Track;

class Chorus : public EffectBase
{
public:
	Chorus( double** setWaveLog );
	~Chorus( void );

	void reset( void );
	void apply( Track* track );

private:
	double getPrevData( int prevIndex );

	double mD;
	double mDepth;
	double mRate;

	int mLogIndex;
	double** mWaveLog;
};

} // namespace Sound

#endif // INCLUDED_SOUND_CHORUS_H