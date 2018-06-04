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
		case WAVE_NONE:
			setSilent( track );
	}
}

// –³‰¹
void Wave::setSilent( Track* track )
{
	double* waveData = track->getWaveData();
	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		waveData[i] = 0;
	}
}

// ƒTƒCƒ“”g‚ÌƒmƒRƒMƒŠ”g
void Wave::setSawtooth( Track* track )
{
	double* waveData = track->getWaveData();
	double time = track->getPlayTime();

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = 0;
		for( int j = 1; j <= 18; ++j ) {		/* ”{‰¹‚Ìd‚Ë‡‚í‚¹ */
			s += mA / j * sin( 2.0 * M_PI * mF * j * time / SAMPLES_PER_SEC );
//			s += mA / j * cos( 2.0 * M_PI * mF * j * time / SAMPLES_PER_SEC + M_PI / 2 );
//			s += mA / j * cos( 2.0 * M_PI * mF * j * time / SAMPLES_PER_SEC );
		}
		waveData[i] = s;

		time += 1.0;
	}
}

// ƒTƒCƒ“”g‚Ì’ZŒ`”g
void Wave::setSquare( Track* track )
{
	double* waveData = track->getWaveData();
	double time = track->getPlayTime();

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = 0;
		/* Šï”ŽŸ‚Ì”{‰¹‚Ì‚Ýd‚Ë‡‚í‚¹‚é */
		for( int j = 1; j <= 30; j += 2 ) {
			s += mA / j * sin( 2.0 * M_PI * mF * j * time / SAMPLES_PER_SEC );
		}
		waveData[i] = s;

		time += 1.0;
	}
}

// ƒTƒCƒ“”g‚ÌŽOŠp”g
void Wave::setTriangle( Track* track )
{
	double* waveData = track->getWaveData();
	double time = track->getPlayTime();

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = 0;
		/* Šï”ŽŸ‚Ì”{‰¹‚Ì‚Ýd‚Ë‡‚í‚¹‚é */
		for( int j = 1; j <= 16; j += 2 ) {
			if( j % 4 == 1 ) {
				s += mA / ( j * j ) * sin( 2.0 * M_PI * mF * j * time / SAMPLES_PER_SEC );
			} else if( j % 4 == 3 ){
				s -= mA / ( j * j ) * sin( 2.0 * M_PI * mF * j * time / SAMPLES_PER_SEC );
			}
		}
		waveData[i] = s;

		time += 1.0;
	}
}

} // namespace Sound