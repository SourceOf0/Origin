#include "Tremolo.h"
#include "SoundBase.h"
#include "Track.h"

#define _USE_MATH_DEFINES
#include <Math.h>

namespace Sound {

Tremolo::Tremolo( void ) : 
mDepth( 0.5 ),
mRate( 5.0 )
{
}


Tremolo::~Tremolo( void )
{
}

void Tremolo::reset( void )
{
}

// ƒgƒŒƒ‚ƒ
void Tremolo::apply( Track* track )
{
	double* wave = track->getAdjWave();
	double time = track->getPlayTime();

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = wave[i];

		s *= 1.0 + mDepth * sin(2.0 * M_PI * mRate * time / SAMPLES_PER_SEC);
		
		wave[i] = s;

		time += 1;
		if( time > SAMPLES_PER_SEC ) time -= SAMPLES_PER_SEC;
	}
}

} // namespace Sound