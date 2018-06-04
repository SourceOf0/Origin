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

// �f�B�X�g�[�V�����i�Ώ̃n�[�h�N���b�s���O�j
void Distortion1::apply( Track* track )
{
	double* waveData = track->getWaveData();

	double gain = mSetNum1 * 15.0;	/* ������ */
	double level = mSetNum2;

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = waveData[i];

		s = s * gain; /* ���f�[�^�̑��� */
		if( s > 1.0 ) {
			s = 1.0; /* �N���b�s���O */
		} else if( s < -1.0 ) {
			s = -1.0; /* �N���b�s���O */
		}
		s *= level; /* ���̑傫���𒲐߂��� */
		
		waveData[i] = s;
	}
}


} // namespace Sound