#ifndef INCLUDED_SOUND_DISTORTION1_H
#define INCLUDED_SOUND_DISTORTION1_H

#include "EffectBase.h"

namespace Sound {

class Track;

class Distortion1 : public EffectBase
{
public:
	Distortion1( void );
	~Distortion1( void );

	void reset( void );
	void apply( Track* track );

private:
	double mGain;	/* ëùïùó¶ */
	double mLevel;
};

} // namespace Sound

#endif // INCLUDED_SOUND_DISTORTION1_H