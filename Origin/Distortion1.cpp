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

// �f�B�X�g�[�V�����i�Ώ̃n�[�h�N���b�s���O�j
void Distortion1::apply( Track* track )
{
	double* wave = track->getAdjWave();

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = wave[i];

		s = s * mGain; /* ���f�[�^�̑��� */
		if( s > 1.0 ) {
			s = 1.0; /* �N���b�s���O */
		} else if( s < -1.0 ) {
			s = -1.0; /* �N���b�s���O */
		}
		s *= mLevel; /* ���̑傫���𒲐߂��� */
		
		wave[i] = s;
	}
}


} // namespace Sound