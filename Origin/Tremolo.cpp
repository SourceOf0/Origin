#include "Tremolo.h"
#include "Track.h"

namespace Sound {

Tremolo::Tremolo( void )
{
	init( 0 );
}


Tremolo::~Tremolo( void )
{
}

void Tremolo::reset( void )
{
	init( 0 );
}

// ƒgƒŒƒ‚ƒ
void Tremolo::apply( Track* track )
{
	double* waveData = track->getWaveData();
	double time = track->getPlayTime();

	double depth = mSetNum1;
	double rate = mSetNum2 * 20.0;

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = waveData[ i ];

		s *= 1.0 + depth * customSin( 2.0 * M_PI * rate * time / SAMPLES_PER_SEC );
		time += 1;

		waveData[i] = s;
	}
}

} // namespace Sound