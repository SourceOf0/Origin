#include "Delay.h"
#include "SoundBase.h"
#include "Track.h"

#define _USE_MATH_DEFINES
#include <Math.h>

namespace Sound {

Delay::Delay( void ) :
mA( 0.5 ),
mDelayTime( SAMPLES_PER_SEC * 0.375 ),
mRepeat( 2 )
{
}


Delay::~Delay( void )
{
}

void Delay::reset( void )
{
}

// ディレイ
void Delay::apply( Track* track )
{
	double* wave = track->getAdjWave();

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = wave[i];
		
		for( int j = 1; j <= mRepeat; ++j ) {
			int m = static_cast<int>( i - j * mDelayTime );

			/* 過去の音データをミックスする */
			s += pow( mA, j ) * track->getPrevData(m);
		}

		wave[i] = s;
	}
}

} // namespace Sound