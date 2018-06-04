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

// �m�C�Y�Q�[�g
void NoiseGate::apply( Track* track )
{
	double* waveData = track->getWaveData();

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = waveData[ i ];

		if( s <= mThreshold && s >= -mThreshold ) {
			s = 0.0; /* �������l�ȉ���0�ɂ��� */
		}

		waveData[ i ] = s;
	}
}

} // namespace Sound