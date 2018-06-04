#ifndef INCLUDED_SOUND_LOW_PASS_FILTER_H
#define INCLUDED_SOUND_LOW_PASS_FILTER_H

#include "EffectBase.h"

namespace Sound {

class Track;

class LowPassFilter : public EffectBase
{
public:
	LowPassFilter( double** setWaveLog );
	~LowPassFilter( void );

	void reset( void );
	void apply( Track* track );

private:
	/* Low-Pass�i���ʉ߁j�t�B���^ */
	void setLPF( double fe, double* w );
	void setState( void );

	double* mB;
	double* mX;
	double* mY;
	int mL;
	int mJ;

	double mFe;
	double mDelta;
};

} // namespace Sound

#endif // INCLUDED_SOUND_LOW_PASS_FILTER_H