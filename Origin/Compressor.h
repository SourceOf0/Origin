#ifndef INCLUDED_SOUND_COMPRESSOR_H
#define INCLUDED_SOUND_COMPRESSOR_H

#include "EffectBase.h"

namespace Sound {

class Track;

class Compressor : public EffectBase
{
public:
	Compressor( void );
	~Compressor( void );

	void reset( void );
	void apply( Track* track );

private:
	double mThreshold;	 /* ÇµÇ´Ç¢íl */
	double mRatio;
	double mGain;		 /* ëùïùó¶ */
};

} // namespace Sound

#endif // INCLUDED_SOUND_COMPRESSOR_H