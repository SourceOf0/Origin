#include "NoiseGate.h"
#include "Track.h"

namespace Sound {

NoiseGate::NoiseGate( void )
{
	init( 0 );
}


NoiseGate::~NoiseGate( void )
{
}

void NoiseGate::reset( void )
{
	init( 0 );
}

// ノイズゲート
void NoiseGate::apply( Track* track )
{
	double* waveData = track->getWaveData();

	double threshold = mSetNum1;

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = waveData[ i ];

		if( s <= threshold && s >= -threshold ) {
			s = 0.0; /* しきい値以下を0にする */
		}

		waveData[ i ] = s;
	}
}

} // namespace Sound