#include "Chorus.h"
#include "Track.h"

#define _USE_MATH_DEFINES
#include <Math.h>

namespace Sound {

Chorus::Chorus( double** setWaveLog )
{
	init( setWaveLog );
}


Chorus::~Chorus( void )
{
}

void Chorus::reset( void )
{
	init( mWaveLog );
}

// ÉRÅ[ÉâÉX
void Chorus::apply( Track* track )
{
	int time = static_cast< int >( track->getPlayTime() );
	double* waveData = track->getWaveData();

	double rate = 0.1;
	double d = SAMPLES_PER_SEC * mSetNum1 * 0.1;
	double depth = SAMPLES_PER_SEC * mSetNum2 * 0.05;
	double t, delta, tau;
	int m;

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		mWaveLog[ mLogIndex ][ i ] = waveData[ i ];
	}

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = waveData[ i ];

		tau = d + depth * sin( 2.0 * M_PI * rate * ( time + i ) / SAMPLES_PER_SEC );
		t = ( double )i - tau;
		m = ( int )t;
		delta = t - ( double )m;
		s += delta * getPrevData( m + 1 ) + ( 1.0 - delta ) * getPrevData( m ); 

		waveData[ i ] = s;
	}

	mLogIndex = ( mLogIndex + 1 ) % LOG_MAX_DATA_NUM;
}


} // namespace Sound