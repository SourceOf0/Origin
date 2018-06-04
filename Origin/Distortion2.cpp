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

// �f�B�X�g�[�V�����i�Ώ̃\�t�g�N���b�s���O�j
void Distortion2::apply( Track* track )
{
	double* waveData = track->getWaveData();

	double gain = mSetNum1 * 15.0;	/* ������ */
	double level = mSetNum2;

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = waveData[i];

		s = s * gain; /* ���f�[�^�̑��� */
		if( s >= 0.0 ) {
			s = atan( s ) / ( M_PI / 2.0 ); /* �N���b�s���O */
		} else if ( s < -0.0 ) {
			s = atan( s ) / ( M_PI / 2.0 ) * 1; /* �N���b�s���O */
		}
		s *= level; /* ���̑傫���𒲐߂��� */
		
		waveData[i] = s;
	}
}

} // namespace Sound