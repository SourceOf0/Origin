#include "Distortion2.h"
#include "SoundBase.h"
#include "Track.h"

#define _USE_MATH_DEFINES
#include <Math.h>

namespace Sound {

Distortion2::Distortion2( void ) :
mGain( 10.0 ),
mLevel( 0.5 )
{
}


Distortion2::~Distortion2( void )
{
}

void Distortion2::reset( void )
{
}

// ディストーション（非対称ソフトクリッピング）
void Distortion2::apply( Track* track )
{
	double* waveData = track->getWaveData();

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = waveData[i];

		s = s * mGain; /* 音データの増幅 */
		if( s >= 0.0 ) {
			s = atan(s) / ( M_PI / 2.0 ); /* クリッピング */
		} else if ( s < -0.0 ) {
			s = atan(s) / ( M_PI / 2.0 ) * 0.1; /* クリッピング */
		}
		s *= mLevel; /* 音の大きさを調節する */
		
		waveData[i] = s;
	}
}

} // namespace Sound