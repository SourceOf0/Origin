#include "Distortion3.h"
#include "Track.h"

namespace Sound {

Distortion3::Distortion3( void )
{
	init( 0 );
}

Distortion3::~Distortion3( void )
{
}

void Distortion3::reset( void )
{
	init( 0 );
}

// ディストーション（全波整流＋対称ハードクリッピング）
void Distortion3::apply( Track* track )
{
	double* waveData = track->getWaveData();

	double gain = mSetNum1 * 15.0;	/* 増幅率 */
	double level = mSetNum2;

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = waveData[ i ];

		if( s < 0.0 ) {
			s *= -1.0; /* 音データの全波整流（絶対値） */
		}
		s = s * gain; /* 音データの増幅 */
		if( s > 1.0 ) {
			s = 1.0; /* クリッピング */
		} else if( s < -1.0 ) {
			s = -1.0; /* クリッピング */
		}
		s *= level; /* 音の大きさを調節する */
		
		waveData[ i ] = s;
	}
}


} // namespace Sound