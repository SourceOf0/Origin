#include "Delay.h"
#include "Track.h"

#define _USE_MATH_DEFINES
#include <Math.h>

namespace Sound {

Delay::Delay( double** setWaveLog ) :
mA( 0.3 ),
mDelayTime( 0.05 ),
mRepeat( 10 )
{
	init( setWaveLog, mDelayTime, 0, 0 );
}


Delay::~Delay( void )
{
}

void Delay::reset( void )
{
	init( mWaveLog, mDelayTime, 0, 0 );
}

// ディレイ
void Delay::apply( Track* track )
{
	double* waveData = track->getWaveData();
	double delayTime = mSetNum1 * SAMPLES_PER_SEC;

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = waveData[ i ];
		mWaveLog[ mLogIndex ][ i ] = s;
		
		for( int j = 1; j <= mRepeat; ++j ) {
			int m = static_cast<int>( static_cast<double>( i ) - static_cast<double>( j ) * delayTime );

			/* 過去の音データをミックスする */
			s += pow( mA, static_cast<double>( j ) ) * getPrevData( m );
		}

		waveData[ i ] = s;
	}

	mLogIndex = ( mLogIndex + 1 ) % LOG_MAX_DATA_NUM;
}


} // namespace Sound