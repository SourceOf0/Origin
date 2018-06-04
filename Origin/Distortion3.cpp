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

// �f�B�X�g�[�V�����i�S�g�����{�Ώ̃n�[�h�N���b�s���O�j
void Distortion3::apply( Track* track )
{
	double* waveData = track->getWaveData();

	double gain = mSetNum1 * 15.0;	/* ������ */
	double level = mSetNum2;

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = waveData[ i ];

		if( s < 0.0 ) {
			s *= -1.0; /* ���f�[�^�̑S�g�����i��Βl�j */
		}
		s = s * gain; /* ���f�[�^�̑��� */
		if( s > 1.0 ) {
			s = 1.0; /* �N���b�s���O */
		} else if( s < -1.0 ) {
			s = -1.0; /* �N���b�s���O */
		}
		s *= level; /* ���̑傫���𒲐߂��� */
		
		waveData[ i ] = s;
	}
}


} // namespace Sound