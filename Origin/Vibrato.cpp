#include "Vibrato.h"
#include "Track.h"

#define _USE_MATH_DEFINES
#include <Math.h>

namespace Sound {

Vibrato::Vibrato( double** setWaveLog ) : 
mD( 0.002 ),
mDepth( 0.002 ),
mRate( 1.0 )
{
	init( setWaveLog, 0, 0, 0 );
}


Vibrato::~Vibrato( void )
{
}

void Vibrato::reset( void )
{
	init( mWaveLog, 0, 0, 0 );
}

// ビブラート
void Vibrato::apply( Track* track )
{
	double* waveData = track->getWaveData();
	double d = SAMPLES_PER_SEC * mD;
	double depth = SAMPLES_PER_SEC * mDepth;
	double t, delta, tau;
	int fixIndex = mLogIndex * WAVE_DATA_LENGTH;
	int m;

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = waveData[ i ];
		mWaveLog[ mLogIndex ][ i ] = s;

		t = i + fixIndex;
		tau = d + depth * sin( 2.0 * M_PI * mRate * t / SAMPLES_PER_SEC );
		t -= tau;
		m = static_cast< int >( t );
		delta = t - static_cast< double >( m );
		m -= fixIndex;
		s = delta * getPrevData( m + 1 ) + ( 1.0 - delta ) * getPrevData( m );

		waveData[ i ] = s;
	}

	mLogIndex = ( mLogIndex + 1 ) % LOG_MAX_DATA_NUM;
}


} // namespace Sound