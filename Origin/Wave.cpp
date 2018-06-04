#include "Wave.h"
#include "SoundBase.h"
#include "Track.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace Sound {

Wave::Wave( void ) :
mA( 0.3 ),
mF( 300 )
{
}

Wave::~Wave( void )
{
}

void Wave::reset( void )
{
}

void Wave::setF( double f )
{
	mF = f;
}


void Wave::setData( Track* track, WaveID id )
{
	switch( id ) {
		case WAVE_SAWTOOTH:
			setSawtooth( track );
			break;
		case WAVE_SQUARE:
			setSquare( track );
			break;
		case WAVE_TRIANGLE:
			setTriangle( track );
			break;
	}
}

// �T�C���g�̃m�R�M���g
void Wave::setSawtooth( Track* track )
{
	double* wave = track->getAdjWave();
	double time = track->getPlayTime();

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = 0;
		for( int j = 1; j <= 15; ++j ) {		/* 15�{���܂ł̏d�ˍ��킹 */
			s += mA / j * sin( 2.0 * M_PI * mF * j * time / SAMPLES_PER_SEC );
//			s += mA / j * cos( 2.0 * M_PI * mF * j * time / SAMPLES_PER_SEC + M_PI / 2 );
		}
		wave[i] = s;

		time += 1;
		if( time > SAMPLES_PER_SEC ) time -= SAMPLES_PER_SEC;
	}
}

// �T�C���g�̒Z�`�g
void Wave::setSquare( Track* track )
{
	double* wave = track->getAdjWave();
	double time = track->getPlayTime();

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = 0;
		/* 15�{���܂ł̊���̔{���̂ݏd�ˍ��킹�� */
		for( int j = 1; j <= 16; j += 2 ) {
			s += mA / j * sin( 2.0 * M_PI * mF * j * time / SAMPLES_PER_SEC );
		}
		wave[i] = s;

		time += 1;
		if( time > SAMPLES_PER_SEC ) time -= SAMPLES_PER_SEC;
	}
}

// �T�C���g�̎O�p�g
void Wave::setTriangle( Track* track )
{
	double* wave = track->getAdjWave();
	double time = track->getPlayTime();

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = 0;
		/* ����̔{���̂ݏd�ˍ��킹�� */
		for( int j = 1; j <= 18; j += 2 ) {
			if( j % 6 == 1 ) {
				s += mA / ( j * j ) * sin( 2.0 * M_PI * mF * j * time / SAMPLES_PER_SEC );
			} else {
				s -= mA / ( j * j ) * sin( 2.0 * M_PI * mF * j * time / SAMPLES_PER_SEC );
			}
		}
		wave[i] = s;

		time += 1;
		if( time > SAMPLES_PER_SEC ) time -= SAMPLES_PER_SEC;
	}
}

} // namespace Sound