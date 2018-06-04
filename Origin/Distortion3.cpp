#include "Distortion3.h"
#include "SoundBase.h"
#include "Track.h"

namespace Sound {

Distortion3::Distortion3( void ) :
mGain( 10.0 ),
mLevel( 0.5 )
{
}

Distortion3::~Distortion3( void )
{
}

void Distortion3::reset( void )
{
}

// ディストーション（全波整流＋対称ハードクリッピング）
void Distortion3::apply( Track* track )
{
	double* wave = track->getAdjWave();

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = wave[i];

		if( s < 0.0 ) {
			s *= -1.0; /* 音データの全波整流（絶対値） */
		}
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