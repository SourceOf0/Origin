#ifndef INCLUDED_SOUND_HIGH_PASS_FILTER_H
#define INCLUDED_SOUND_HIGH_PASS_FILTER_H

#include "EffectBase.h"

namespace Sound {

class Track;

class HighPassFilter : public EffectBase
{
public:
	HighPassFilter( double** setWaveLog );
	~HighPassFilter( void );

	void reset( void );
	void apply( Track* track );

private:
	/* High-Pass（高域通過）フィルタ */
	void setHPF( double fe, double* w );

	double* mB;
	double* mX;
	double* mY;
	int mL;
	int mJ;

	double mFe;
	double mDelta;
};

} // namespace Sound

#endif // INCLUDED_SOUND_HIGH_PASS_FILTER_H