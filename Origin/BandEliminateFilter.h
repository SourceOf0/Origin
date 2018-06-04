#ifndef INCLUDED_SOUND_BAND_ELIMINATE_FILTER_H
#define INCLUDED_SOUND_BAND_ELIMINATE_FILTER_H

#include "EffectBase.h"

namespace Sound {

class Track;

class BandEliminateFilter : public EffectBase
{
public:
	BandEliminateFilter( double** setWaveLog );
	~BandEliminateFilter( void );

	void reset( void );
	void apply( Track* track );

private:
	/* Band-Eliminate�i�ш�j�~�j�t�B���^ �@������̑ш��j�~���� */
	void setBEF( double fe1, double fe2, double* w );

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

#endif // INCLUDED_SOUND_BAND_ELIMINATE_FILTER_H