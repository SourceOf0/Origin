#include "Compressor.h"
#include "SoundBase.h"
#include "Track.h"

namespace Sound {

Compressor::Compressor( void ) :
mThreshold( 0.2 ),
mRatio( 1.0 / 10.0 )
{
	mGain = 1.0 / ( mThreshold + (1.0 - mThreshold) * mRatio );
}


Compressor::~Compressor( void )
{
}

void Compressor::reset( void )
{
}

// ƒRƒ“ƒvƒŒƒbƒT
void Compressor::apply( Track* track )
{
	double* wave = track->getAdjWave();

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = wave[i];

		if( s > mThreshold ) {
			s = mThreshold + (s - mThreshold) * mRatio; /* U•‚Ìˆ³k */
		} else if( s < -mThreshold ) {
			s = -mThreshold + (s + mThreshold) * mRatio; /* U•‚Ìˆ³k */
		}
		s *= mGain; /* U•‚Ì‘• */
		
		wave[i] = s;
	}
}

} // namespace Sound