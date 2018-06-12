#include "Chorus.h"
#include "Track.h"

namespace Sound {

Chorus::Chorus() :
EffectBase( mWaveLog )
{
}


Chorus::~Chorus( void )
{
}

void Chorus::reset( void )
{
	init( mWaveLog );
}

// ƒR[ƒ‰ƒX
void Chorus::apply( Track* track )
{
	double time = track->getPlayTime();
	double* waveData = track->getWaveData();

	double rate = 0.1;
	double d = SAMPLES_PER_SEC * mSetNum1 * 0.1 + WAVE_DATA_LENGTH;
	double depth = SAMPLES_PER_SEC * mSetNum2 * 0.01;
	double t, delta, tau;
	int m;

	memcpy( mWaveLog[ mLogIndex ], waveData, WAVE_DATA_LENGTH * sizeof( double ) );

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = waveData[ i ];

		tau = d + depth * customSin( 2.0 * M_PI * rate * ( time + i ) / SAMPLES_PER_SEC );
		t = static_cast< double >( i ) - tau;
		m = static_cast< int >( t );
		delta = t - static_cast< double >( m );
		s += delta * getPrevData( mWaveLog, m + 1 ) + ( 1.0 - delta ) * getPrevData( mWaveLog, m );
		waveData[ i ] = s;
	}

	mLogIndex = ( mLogIndex + 1 ) % LOG_MAX_DATA_NUM;
}


} // namespace Sound