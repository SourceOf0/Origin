#include "Distortion1.h"
#include "SoundBase.h"
#include "Track.h"

namespace Sound {

Distortion1::Distortion1( void ) :
mGain( 10.0 ),
mLevel( 0.5 )
{
}

Distortion1::~Distortion1( void )
{
}

void Distortion1::reset( void )
{
}

// ディストーション（対称ハードクリッピング）
void Distortion1::apply( Track* track )
{
	double* wave = track->getAdjWave();

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = wave[i];

		s = s * mGain; /* 音データの増幅 */
		if( s > 1.0 ) {
			s = 1.0; /* クリッピング */
		} else if( s < -1.0 ) {
			s = -1.0; /* クリッピング */
		}
		s *= mLevel; /* 音の大きさを調節する */
		
		wave[i] = s;
	}
}


} // namespace Sound