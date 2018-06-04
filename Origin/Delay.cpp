#include "Delay.h"
#include "SoundBase.h"
#include "Track.h"

#define _USE_MATH_DEFINES
#include <Math.h>

namespace Sound {

Delay::Delay( double** setWaveLog ) :
mA( 0.7 ),
mDelayTime( SAMPLES_PER_SEC * 0.1 ),
mRepeat( 2 ),
mLogIndex( 0 )
{
	mWaveLog = setWaveLog;

	mSetNum1 = 0;

	for( int i = 0; i < LOG_MAX_NUM; ++i ) {
		for( int j = 0; j < WAVE_DATA_LENGTH; ++j ) {
			mWaveLog[i][j] = 0;
		}
	}
}


Delay::~Delay( void )
{
}

void Delay::reset( void )
{
	for( int i = 0; i < LOG_MAX_NUM; ++i ) {
		for( int j = 0; j < WAVE_DATA_LENGTH; ++j ) {
			mWaveLog[i][j] = 0;
		}
	}
}

// ディレイ
void Delay::apply( Track* track )
{
	double* waveData = track->getWaveData();
	double delayTime = 0;

	switch( mLogIndex % 3 ) {
		case 0:
			delayTime = ( mSetNum1 - 0.00001 * mSetNum1 ) * SAMPLES_PER_SEC;
			break;
		case 1:
			delayTime = mSetNum1 * SAMPLES_PER_SEC;
			break;
		case 2:
			delayTime = ( mSetNum1 + 0.00001 * mSetNum1 ) * SAMPLES_PER_SEC;
			break;
	}

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = waveData[i];
		mWaveLog[ mLogIndex ][ i ] = s;
		
		for( int j = 1; j <= mRepeat; ++j ) {
//			int m = static_cast<int>( static_cast<double>(i) - static_cast<double>(j) * mDelayTime );
			int m = static_cast<int>( static_cast<double>(i) - static_cast<double>(j) * delayTime );

			/* 過去の音データをミックスする */
			s += pow( mA, static_cast<double>(j) ) * getPrevData(m);
		}

		waveData[i] = s;
	}

	mLogIndex = ( mLogIndex + 1 ) % LOG_MAX_NUM;
}

double Delay::getPrevData( int prevIndex )
{
	int dataIndex = ( ( prevIndex < 0 )? -prevIndex : prevIndex ) % WAVE_DATA_LENGTH;
	int blockIndex = mLogIndex + static_cast<int>( prevIndex / WAVE_DATA_LENGTH );
	if( blockIndex < 0 ) blockIndex = LOG_MAX_NUM + blockIndex;
	if( blockIndex == mLogIndex ) return 0;
	return mWaveLog[ blockIndex ][ dataIndex ];
}


} // namespace Sound