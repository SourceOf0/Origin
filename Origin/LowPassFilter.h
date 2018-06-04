#ifndef INCLUDED_SOUND_LOW_PASS_FILTER_H
#define INCLUDED_SOUND_LOW_PASS_FILTER_H

#include "EffectBase.h"

namespace Sound {

class Track;

class LowPassFilter : public EffectBase
{
public:
	LowPassFilter( void );
	~LowPassFilter( void );

	void reset( void );
	void apply( Track* track );

private:
	/* Low-Pass（低域通過）フィルタ */
	void setLPF( double fe, double* w );
	void setState( void );

	double mWaveLog[ LOG_MAX_DATA_NUM ][ WAVE_DATA_LENGTH ];

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