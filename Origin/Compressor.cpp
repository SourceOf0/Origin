#include "Compressor.h"
#include "Track.h"

namespace Sound {

Compressor::Compressor( void ) :
EffectBase( 0 )
{
}


Compressor::~Compressor( void )
{
}

void Compressor::reset( void )
{
	init( 0 );
}

// �R���v���b�T
void Compressor::apply( Track* track )
{
	double* waveData = track->getWaveData();

	double threshold = mSetNum1 + 0.000001;	 /* �������l */
	double ratio = mSetNum2;
	double gain = 1.0 / ( threshold + ( 1.0 - threshold ) * ratio );		 /* ������ */

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = waveData[ i ];

		if( s > threshold ) {
			s = threshold + ( s - threshold ) * ratio; /* �U���̈��k */
		} else if( s < -threshold ) {
			s = -threshold + ( s + threshold ) * ratio; /* �U���̈��k */
		}
		s *= gain; /* �U���̑��� */
		
		waveData[i] = s;
	}
}

} // namespace Sound