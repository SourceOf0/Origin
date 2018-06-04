#include "Distortion2.h"
#include "Track.h"

#define _USE_MATH_DEFINES
#include <Math.h>

namespace Sound {

Distortion2::Distortion2( void )
{
	init( 0 );
}


Distortion2::~Distortion2( void )
{
}

void Distortion2::reset( void )
{
	init( 0 );
}

// ディストーション（対称ソフトクリッピング）
void Distortion2::apply( Track* track )
{
	double* waveData = track->getWaveData();

	double gain = mSetNum1 * 15.0;	/* 増幅率 */
	double level = mSetNum2;

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = waveData[i];

		s = s * gain; /* 音データの増幅 */
		if( s >= 0.0 ) {
			s = atan( s ) / ( M_PI / 2.0 ); /* クリッピング */
		} else if ( s < -0.0 ) {
			s = atan( s ) / ( M_PI / 2.0 ) * 1; /* クリッピング */
		}
		s *= level; /* 音の大きさを調節する */
		
		waveData[i] = s;
	}
}

} // namespace Sound