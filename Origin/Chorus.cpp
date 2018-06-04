#include "Chorus.h"
#include "SoundBase.h"
#include "Track.h"

#define _USE_MATH_DEFINES
#include <Math.h>

namespace Sound {

Chorus::Chorus( double** setWaveLog ) :
mD( 0.025 ),
mDepth( 0.01 ),
mRate( 0.1 ),
mLogIndex( 0 )
{
	mWaveLog = setWaveLog;

	mSetNum1 = 0;

	for( int i = 0; i < LOG_MAX_NUM; ++i ) {
		for( int j = 0; j < WAVE_DATA_LENGTH; ++j ) {
			mWaveLog[i][j] = 0;
		}
	}
}


Chorus::~Chorus( void )
{
}

void Chorus::reset( void )
{
	for( int i = 0; i < LOG_MAX_NUM; ++i ) {
		for( int j = 0; j < WAVE_DATA_LENGTH; ++j ) {
			mWaveLog[i][j] = 0;
		}
	}
}

// ƒR[ƒ‰ƒX
void Chorus::apply( Track* track )
{
	int time = track->getPlayTime();
	double* waveData = track->getWaveData();
	double delayTime = 0;
	double d = SAMPLES_PER_SEC * mD;
	double depth = SAMPLES_PER_SEC * mDepth;
	double t, delta, tau;
	int m;

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		mWaveLog[ mLogIndex ][ i ] = waveData[ i ];
	}

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = waveData[ i ];

		tau = d + depth * sin( 2.0 * M_PI * mRate * ( i + time ) / SAMPLES_PER_SEC );
		t = ( double )i - tau;
		m = ( int )t;
		delta = t - ( double )m;
		s += delta * getPrevData( m + 1 ) + ( 1.0 - delta ) * getPrevData( m ); 

		waveData[ i ] = s;
	}

	mLogIndex = ( mLogIndex + 1 ) % LOG_MAX_NUM;
}

double Chorus::getPrevData( int prevIndex )
{
	int dataIndex = ( ( prevIndex < 0 )? -prevIndex : prevIndex ) % WAVE_DATA_LENGTH;
	int blockIndex = mLogIndex + static_cast<int>( prevIndex / WAVE_DATA_LENGTH );
	if( blockIndex < 0 ) blockIndex = LOG_MAX_NUM + blockIndex;
	return mWaveLog[ blockIndex ][ dataIndex ];
}


} // namespace Sound