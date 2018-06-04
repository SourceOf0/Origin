#include "Wave.h"
#include "SoundBase.h"
#include "Track.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace Sound {

Wave::Wave( void ) :
mA( 0.0 ),
mF( 0.0 ),
mTargetF( 0.0 ),
mRatio( 0.5 )
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
	mTargetF = f;
}
double Wave::getF( void )
{
	return mTargetF;
}
void Wave::setVol( double vol )
{
	mA = vol;
}

void Wave::setData( Track* track, WaveID id )
{
	switch( id ) {
		case WAVE_CURVE:
			setCurve( track );
			break;
		case WAVE_SAWTOOTH:
			setSawtooth( track );
			break;
		case WAVE_SQUARE:
			setSquare( track );
			break;
		case WAVE_TRIANGLE:
			setTriangle( track );
			break;
		case WAVE_NONE:
			setSilent( track );
	}
}

// ����
void Wave::setSilent( Track* track )
{
	double* waveData = track->getWaveData();
	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		waveData[i] = 0.0;
	}
}

// �T�C���g
void Wave::setCurve( Track* track )
{
	double* waveData = track->getWaveData();
	double time = track->getPlayTime();
	double s1 = 0.0;
	double s2 = 0.0;
	double setF = 0.0;

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		if( mF == mTargetF ) {
			waveData[ i ] = mA * sin( 2.0 * M_PI * mF * time / SAMPLES_PER_SEC );
			time += 1.0;
			continue;
		}
		s1 = mA * sin( 2.0 * M_PI * mF * time / SAMPLES_PER_SEC );
		s2 = mA * sin( 2.0 * M_PI * mTargetF * time / SAMPLES_PER_SEC );
		waveData[ i ] = ( s1 + s2 ) / 2.0;
		setF = ( mTargetF - mF ) * mRatio;
		if( setF * setF < 0.000001  ) {
			mF = mTargetF;
		} else {
			mF += setF;
		}
		time += 1.0;
	}
}

// �T�C���g�̃m�R�M���g
void Wave::setSawtooth( Track* track )
{
	double* waveData = track->getWaveData();
	double time = track->getPlayTime();
	double setF = 0.0;

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		if( mF == mTargetF ) {
			double s = 0;
			for( int j = 1; j <= 18; ++j ) {		/* �{���̏d�ˍ��킹 */
				s += mA / j * sin( 2.0 * M_PI * mF * j * time / SAMPLES_PER_SEC );
			}
			waveData[ i ] = s;
			time += 1.0;
			continue;
		}
		double s1 = 0.0;
		double s2 = 0.0;
		for( int j = 1; j <= 18; ++j ) {		/* �{���̏d�ˍ��킹 */
			s1 += mA / j * sin( 2.0 * M_PI * mF * j * time / SAMPLES_PER_SEC );
			s2 += mA / j * sin( 2.0 * M_PI * mTargetF * j * time / SAMPLES_PER_SEC );
		}
		waveData[ i ] = ( s1 + s2 ) / 2.0;
		setF = ( mTargetF - mF ) * mRatio;
		if( setF * setF < 0.000001  ) {
			mF = mTargetF;
		} else {
			mF += setF;
		}
		time += 1.0;
	}
}

// �T�C���g�̒Z�`�g
void Wave::setSquare( Track* track )
{
	double* waveData = track->getWaveData();
	double time = track->getPlayTime();
	double setF = 0.0;

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		if( mF == mTargetF ) {
			double s = 0;
			/* ����̔{���̂ݏd�ˍ��킹�� */
			for( int j = 1; j <= 30; j += 2 ) {
				s += mA / j * sin( 2.0 * M_PI * mF * j * time / SAMPLES_PER_SEC );
			}
			waveData[ i ] = s;
			time += 1.0;
			continue;
		}
		double s1 = 0.0;
		double s2 = 0.0;
		/* ����̔{���̂ݏd�ˍ��킹�� */
		for( int j = 1; j <= 30; j += 2 ) {
			s1 += mA / j * sin( 2.0 * M_PI * mF * j * time / SAMPLES_PER_SEC );
			s2 += mA / j * sin( 2.0 * M_PI * mTargetF * j * time / SAMPLES_PER_SEC );
		}
		waveData[ i ] = ( s1 + s2 ) / 2.0;
		setF = ( mTargetF - mF ) * mRatio;
		if( setF * setF < 0.000001  ) {
			mF = mTargetF;
		} else {
			mF += setF;
		}
		time += 1.0;
	}
}

// �T�C���g�̎O�p�g
void Wave::setTriangle( Track* track )
{
	double* waveData = track->getWaveData();
	double time = track->getPlayTime();
	double setF = 0.0;

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		if( mF == mTargetF ) {
			double s = 0;
			/* ����̔{���̂ݏd�ˍ��킹�� */
			for( int j = 1; j <= 16; j += 2 ) {
				if( j % 4 == 1 ) {
					s += mA / ( j * j ) * sin( 2.0 * M_PI * mF * j * time / SAMPLES_PER_SEC );
				} else if( j % 4 == 3 ){
					s -= mA / ( j * j ) * sin( 2.0 * M_PI * mF * j * time / SAMPLES_PER_SEC );
				}
			}
			waveData[ i ] = s;
			time += 1.0;
			continue;
		}
		double s1 = 0.0;
		double s2 = 0.0;
		/* ����̔{���̂ݏd�ˍ��킹�� */
		for( int j = 1; j <= 16; j += 2 ) {
			if( j % 4 == 1 ) {
				s1 += mA / ( j * j ) * sin( 2.0 * M_PI * mF * j * time / SAMPLES_PER_SEC );
				s1 += mA / ( j * j ) * sin( 2.0 * M_PI * mTargetF * j * time / SAMPLES_PER_SEC );
			} else if( j % 4 == 3 ){
				s1 -= mA / ( j * j ) * sin( 2.0 * M_PI * mF * j * time / SAMPLES_PER_SEC );
				s1 -= mA / ( j * j ) * sin( 2.0 * M_PI * mTargetF * j * time / SAMPLES_PER_SEC );
			}
		}
		waveData[ i ] = ( s1 + s2 ) / 2.0;
		setF = ( mTargetF - mF ) * mRatio;
		if( setF * setF < 0.000001  ) {
			mF = mTargetF;
		} else {
			mF += setF;
		}
		time += 1.0;
	}
}

} // namespace Sound