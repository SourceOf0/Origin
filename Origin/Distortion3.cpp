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

// �f�B�X�g�[�V�����i�S�g�����{�Ώ̃n�[�h�N���b�s���O�j
void Distortion3::apply( Track* track )
{
	double* wave = track->getAdjWave();

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = wave[i];

		if( s < 0.0 ) {
			s *= -1.0; /* ���f�[�^�̑S�g�����i��Βl�j */
		}
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