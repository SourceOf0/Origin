#include <memory.h>

#include "Vibrato.h"
#include "Track.h"

namespace Sound {

Vibrato::Vibrato( void ) :
mTime( 0 )
{
	init( mWaveLog );
}


Vibrato::~Vibrato( void )
{
}

void Vibrato::reset( void )
{
	init( mWaveLog );
}

// ビブラート
void Vibrato::apply( Track* track )
{
	double* waveData = track->getWaveData();
	double t, delta, tau;
	int fixIndex = mLogIndex * WAVE_DATA_LENGTH;
	int m = 0;

	double rate = mSetNum1 * 10.0;
	double d = SAMPLES_PER_SEC * 0.002;
	double depth = SAMPLES_PER_SEC * mSetNum2 * 0.01 + 0.001;

	memcpy( mWaveLog[ mLogIndex ], waveData, WAVE_DATA_LENGTH * sizeof( double ) );

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = waveData[ i ];

		t = mTime;
		tau = d + depth * customSin( 2.0 * M_PI * rate * t / SAMPLES_PER_SEC );
		t -= tau;
		m = static_cast< int >( t );
		delta = t - static_cast< double >( m );
		m -= fixIndex;
		s = delta * getPrevData( mWaveLog, m + 1 ) + ( 1.0 - delta ) * getPrevData( mWaveLog, m );

		++mTime;

		waveData[ i ] = s;
	}

	mLogIndex = ( mLogIndex + 1 ) % LOG_MAX_DATA_NUM;
	if( mTime >= LOG_MAX_DATA_NUM * WAVE_DATA_LENGTH ) {
		mTime -= LOG_MAX_DATA_NUM * WAVE_DATA_LENGTH;
	}
}


} // namespace Sound