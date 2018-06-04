#include "Distortion1.h"
#include "Track.h"

namespace Sound {

Distortion1::Distortion1( void ) :
EffectBase( 0 )
{
}

Distortion1::~Distortion1( void )
{
}

void Distortion1::reset( void )
{
	init( 0 );
}

// ディストーション（対称ハードクリッピング）
void Distortion1::apply( Track* track )
{
	double* waveData = track->getWaveData();

	double gain = mSetNum1 * 15.0;	/* 増幅率 */
	double level = mSetNum2;

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = waveData[i];

		s = s * gain; /* 音データの増幅 */
		if( s > 1.0 ) {
			s = 1.0; /* クリッピング */
		} else if( s < -1.0 ) {
			s = -1.0; /* クリッピング */
		}
		s *= level; /* 音の大きさを調節する */
		
		waveData[i] = s;
	}
}


} // namespace Sound