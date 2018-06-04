#include "EffectBase.h"
#include "SoundBase.h"

#define _USE_MATH_DEFINES
#include <Math.h>

namespace Sound {

void EffectBase::init( double** setWaveLog )
{
	mLogIndex = 0;
	mSetNum1 = 0;
	mSetNum2 = 0;

	mWaveLog = setWaveLog;
	if( mWaveLog == 0 ) return;
	for( int i = 0; i < LOG_MAX_DATA_NUM; ++i ) {
		for( int j = 0; j < WAVE_DATA_LENGTH; ++j ) {
			mWaveLog[ i ][ j ] = 0;
		}
	}
}

double EffectBase::getPrevData( int prevIndex )
{
	int dataIndex = 0;
	int blockIndex = 0;

	if( prevIndex < 0 ) {
		dataIndex = WAVE_DATA_LENGTH + prevIndex % WAVE_DATA_LENGTH;
		blockIndex = mLogIndex + static_cast<int>( prevIndex / WAVE_DATA_LENGTH ) - 1;
		if( blockIndex < 0 ) blockIndex = LOG_MAX_DATA_NUM + blockIndex;
	} else if( prevIndex < WAVE_DATA_LENGTH ) {
 		dataIndex = prevIndex % WAVE_DATA_LENGTH;
		blockIndex = mLogIndex;
	} else {
		return 0;
	}

	return mWaveLog[ blockIndex ][ dataIndex ];
}

void EffectBase::setNum1( double val )
{
	if( val < -0.0 ) val = 0.0;
	if( val > 1.0 ) val = 1.0;
	mSetNum1 = val;
}
void EffectBase::setNum2( double val )
{
	if( val < -0.0 ) val = 0.0;
	if( val > 1.0 ) val = 1.0;
	mSetNum2 = val;
}
double EffectBase::getNum1( void )
{
	return mSetNum1;
}
double EffectBase::getNum2( void )
{
	return mSetNum2;
}

double EffectBase::sinc( double x )
{
	return ( x == 0.0 )? 1.0 : ( sin( x ) / x );
}

void EffectBase::getHanningWindow( double* w, int N )
{
	if( N % 2 == 0 ) {
		/* NÇ™ãÙêîÇÃÇ∆Ç´ */
		for( int n = 0; n < N; ++n ) {
			w[ n ] = 0.5 - 0.5 * cos( 2.0 * M_PI * n / N );
		}
	} else {
		/* NÇ™äÔêîÇÃÇ∆Ç´ */
		for( int n = 0; n < N; ++n ) {
			w[ n ] = 0.5 - 0.5 * cos( 2.0 * M_PI * ( n + 0.5 ) / N );
		}
	}
}


} // namespace Sound