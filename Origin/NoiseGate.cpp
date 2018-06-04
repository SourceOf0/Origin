#include "NoiseGate.h"
#include "Track.h"

namespace Sound {

NoiseGate::NoiseGate( void ) : 
mThreshold( 0.2 )
{
}


NoiseGate::~NoiseGate( void )
{
}

void NoiseGate::reset( void )
{
}

// ノイズゲート
void NoiseGate::apply( Track* track )
{
	double* waveData = track->getWaveData();

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = waveData[ i ];

		if( s <= mThreshold && s >= -mThreshold ) {
			s = 0.0; /* しきい値以下を0にする */
		}

		waveData[ i ] = s;
	}
}

} // namespace Sound