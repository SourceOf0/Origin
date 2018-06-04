#include "Delay.h"
#include "Track.h"

#define _USE_MATH_DEFINES
#include <Math.h>

namespace Sound {

Delay::Delay( double** setWaveLog )
{
	init( setWaveLog );
}


Delay::~Delay( void )
{
}

void Delay::reset( void )
{
	init( mWaveLog );
}

// �f�B���C
void Delay::apply( Track* track )
{
	double* waveData = track->getWaveData();

	double a = mSetNum1;			/* ������ */
	double delayTime = SAMPLES_PER_SEC * mSetNum2 * 0.2;	/* �x������ */
	int repeat = 10;		/* �J��Ԃ��� */

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = waveData[ i ];
		mWaveLog[ mLogIndex ][ i ] = s;
		
		for( int j = 1; j <= repeat; ++j ) {
			int m = static_cast< int >( static_cast< double >( i ) - static_cast< double >( j ) * delayTime );

			/* �ߋ��̉��f�[�^���~�b�N�X���� */
			s += pow( a, static_cast< double >( j ) ) * getPrevData( m );
		}

		waveData[ i ] = s;
	}

	mLogIndex = ( mLogIndex + 1 ) % LOG_MAX_DATA_NUM;
}


} // namespace Sound