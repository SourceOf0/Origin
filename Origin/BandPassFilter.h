#ifndef INCLUDED_SOUND_BAND_PASS_FILTER_H
#define INCLUDED_SOUND_BAND_PASS_FILTER_H

#include "EffectBase.h"

namespace Sound {

class Track;

class BandPassFilter : public EffectBase
{
public:
	BandPassFilter( void );
	~BandPassFilter( void );

	void reset( void );
	void apply( Track* track );

private:
	/* Band-Pass（帯域通過）フィルタ 　※特定の帯域を通過させる */
	void setBPF( double fe1, double fe2, double* w );
	void setState( void );

	double mWaveLog[ LOG_MAX_DATA_NUM ][ WAVE_DATA_LENGTH ];

	double* mB;
	double* mX;
	double* mY;
	int mL;
	int mJ;

	double mFe1;
	double mFe2;
	double mDelta;
};

} // namespace Sound

#endif // INCLUDED_SOUND_BAND_PASS_FILTER_H