#include "EffectBase.h"
#include "SoundBase.h"

#include <Math.h>

namespace Sound {

double EffectBase::mSinCosTable[ SIN_COS_TABLE_NUM ];

EffectBase::EffectBase( double waveLog[ LOG_MAX_DATA_NUM ][ WAVE_DATA_LENGTH ] )
{
	init( waveLog );
}
void EffectBase::init( double waveLog[ LOG_MAX_DATA_NUM ][ WAVE_DATA_LENGTH ] )
{
	mLogIndex = 0;
	mSetNum1 = 0;
	mSetNum2 = 0;

	if( waveLog == 0 ) return;
	for( int i = 0; i < LOG_MAX_DATA_NUM; ++i ) {
		for( int j = 0; j < WAVE_DATA_LENGTH; ++j ) {
			waveLog[ i ][ j ] = 0;
		}
	}
}
void EffectBase::initTable( void )
{
	for( int i = 0; i < SIN_COS_TABLE_NUM; ++i ) {
		mSinCosTable[ i ] = cos( i * M_PI / 2 / SIN_COS_TABLE_NUM );
	}
}

double EffectBase::getPrevData( double waveLog[ LOG_MAX_DATA_NUM ][ WAVE_DATA_LENGTH ], int prevIndex )
{
	int dataIndex = 0;
	int blockIndex = 0;

	if( prevIndex < 0 ) {
		dataIndex = WAVE_DATA_LENGTH + prevIndex % WAVE_DATA_LENGTH;
		blockIndex = mLogIndex + static_cast<int>( prevIndex / WAVE_DATA_LENGTH ) - 1;
		if( blockIndex < -LOG_MAX_DATA_NUM ) return 0;
		if( blockIndex < 0 ) blockIndex = LOG_MAX_DATA_NUM + blockIndex;
	} else if( prevIndex < WAVE_DATA_LENGTH ) {
 		dataIndex = prevIndex % WAVE_DATA_LENGTH;
		blockIndex = mLogIndex;
	} else {
		return 0;
	}

	return waveLog[ blockIndex ][ dataIndex ];
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

double EffectBase::customPow( double x, double y )
{
	return pow( x, y );
}
double EffectBase::customSqrt( double x )
{
	return sqrt( x );
}
double EffectBase::customAtan( double x )
{
	return atan( x );
}
double EffectBase::customCos( double x )
{
	double sign = 1;
	int i;

	/*  cos( x ) = cos( -x )     */
	if( x < 0 ) x = -x;

	x /= M_PI;
	
	/*  cos( x ) = cos( x + 2 * PI ) */
	x = ( x - static_cast< int >( x / 2 ) * 2 );
	
	/*  cos( x ) = cos( x - PI )   */
	if( x > 1 ) x = 2 - x;

	/* -cos( x ) = cos( PI - x )   */
	if(x > 0.5 ) {
		x = 1 - x;
		sign = -1;
	}

	i = static_cast< int >( x * 2 * SIN_COS_TABLE_NUM );

	return ( sign * mSinCosTable[ i ] );
}
double EffectBase::sinc( double x )
{
	return ( x == 0.0 )? 1.0 : ( customSin( x ) / x );
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