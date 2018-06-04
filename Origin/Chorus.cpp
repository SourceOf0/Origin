#include "Chorus.h"
#include "Track.h"

#define _USE_MATH_DEFINES
#include <Math.h>

namespace Sound {

Chorus::Chorus( double** setWaveLog ) :
mD( 0.025 ),
mDepth( 0.01 ),
mRate( 0.1 )
{
	init( setWaveLog, 0, 0, 0 );
}


Chorus::~Chorus( void )
{
}

void Chorus::reset( void )
{
	init( mWaveLog, 0, 0, 0 );
}

// �R�[���X
void Chorus::apply( Track* track )
{
	int time = track->getPlayTime();
	double* waveData = track->getWaveData();
	double d = SAMPLES_PER_SEC * mD;
	double depth = SAMPLES_PER_SEC * mDepth;
	double t, delta, tau;
	int m;

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		mWaveLog[ mLogIndex ][ i ] = waveData[ i ];
	}

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = waveData[ i ];

		tau = d + depth * sin( 2.0 * M_PI * mRate * ( time + i ) / SAMPLES_PER_SEC );
		t = ( double )i - tau;
		m = ( int )t;
		delta = t - ( double )m;
		s += delta * getPrevData( m + 1 ) + ( 1.0 - delta ) * getPrevData( m ); 

		waveData[ i ] = s;
	}

	mLogIndex = ( mLogIndex + 1 ) % LOG_MAX_DATA_NUM;
}


} // namespace Sound