#include "Equalizer.h"
#include "Track.h"

#include <memory.h>

#define _USE_MATH_DEFINES
#include <Math.h>

namespace Sound {

Equalizer::Equalizer( void )
{
	EQData* newData;

	newData = new EQData();
	newData->isSetEnd = false;
	newData->fc = 500;
	newData->g = -1;
	newData->kind = 1;
	mEQData[ 0 ] = newData;

	newData = new EQData();
	newData->isSetEnd = false;
	newData->fc = 1000;
	newData->g = 1;
	newData->kind = 2;
	mEQData[ 1 ] = newData;

	newData = new EQData();
	newData->isSetEnd = false;
	newData->fc = 2000;
	newData->g = -1;
	newData->kind = 3;
	mEQData[ 2 ] = newData;

	for( int n = 0; n < EQDATA_MAX_NUM; ++n ) {
//		mEQData[ i ] = new EQData();
//		mEQData[ i ]->fc = 1000;
//		mEQData[ i ]->g = 1;
//		mEQData[ i ]->kind = 0;
		for( int i = 0; i < 2; ++i ) {
			for( int j = 0; j < 2; ++j ) {
				for( int k = 0; k < 2; ++k ) {
					mEQData[ n ]->prevData[ i ][ j ][ k ] = 0.0;
				}
			}
		}
	}
}


Equalizer::~Equalizer( void )
{
	for( int i = 0; i < EQDATA_MAX_NUM; ++i ) {
		delete mEQData[ i ];
		mEQData[ i ] = 0;
	}
}

void Equalizer::reset( void )
{
}

// イコライザー
void Equalizer::apply( Track* track )
{
	double* waveData = track->getWaveData();
	double orgData[ WAVE_DATA_LENGTH ];
	double useData[ EQDATA_MAX_NUM ][ 2 ][ 2 ][ 2 ];
	bool isEnd = true;
	int J = 2;
	int I = 2;

	for( int i = 0; i < EQDATA_MAX_NUM; ++i ) {
		if( mEQData[ i ]->kind == 0 ) continue;
		isEnd = false;
		if( mEQData[ i ]->isSetEnd ) continue; 
		mEQData[ i ]->isSetEnd = true;

		/* IIRフィルタの設計 */
		switch( mEQData[ i ]->kind ) {
			case 1:
				setLowShelving( mEQData[ i ] );
				break;
			case 2:
				setPeaking( mEQData[ i ] );
				break;
			case 3:
				setHighShelving( mEQData[ i ] );
				break;
		}
	}
	if( isEnd ) return;

	for( int n = 0; n < EQDATA_MAX_NUM; ++n ) {
		for( int i = 0; i < 2; ++i ) {
			for( int j = 0; j < 2; ++j ) {
				for( int k = 0; k < 2; ++k ) {
					useData[ n ][ i ][ j ][ k ] = mEQData[ n ]->prevData[ i ][ j ][ k ];
				}
			}
		}
	}

	memcpy( orgData, waveData, WAVE_DATA_LENGTH * sizeof( double ) );

	for( int i = 0; i < EQDATA_MAX_NUM; ++i ) {
		if( mEQData[ i ]->kind == 0 ) continue;
		double* a = mEQData[ i ]->a;
		double* b = mEQData[ i ]->b;
		for( int n = 0; n < WAVE_DATA_LENGTH; ++n ) {
			waveData[ n ] = 0;
		}
		for( int n = 0; n < WAVE_DATA_LENGTH; ++n ) {
			if( n == WAVE_DATA_LENGTH - 2 ) {
				mEQData[ i ]->prevData[ 0 ][ 0 ][ 0 ] = orgData[ n - 0 ];
				mEQData[ i ]->prevData[ 0 ][ 0 ][ 1 ] = orgData[ n - 1 ];
			} else if( n == WAVE_DATA_LENGTH - 1 ) {
				mEQData[ i ]->prevData[ 0 ][ 1 ][ 0 ] = orgData[ n - 0 ];
				mEQData[ i ]->prevData[ 0 ][ 1 ][ 1 ] = orgData[ n - 1 ];
			}
			for( int m = 0; m <= J; ++m ) {
				if( n - m >= 0 ) {
					waveData[ n ] += b[ m ] * orgData[ n - m ];
				} else {
					waveData[ n ] += b[ m ] * useData[ i ][ 0 ][ n ][ m - 1 ];
				}
			}
			for( int m = 1; m <= I; ++m ) {
				if( n - m >= 0 ) {
					waveData[ n ] += -a[ m ] * waveData[ n - m ];
				} else {
					waveData[ n ] += -a[ m ] * useData[ i ][ 1 ][ n ][ m - 1 ];
				}
			}
			if( n == WAVE_DATA_LENGTH - 2 ) {
				mEQData[ i ]->prevData[ 1 ][ 0 ][ 0 ] = waveData[ n - 0 ];
				mEQData[ i ]->prevData[ 1 ][ 0 ][ 1 ] = waveData[ n - 1 ];
			} else if( n == WAVE_DATA_LENGTH - 1 ) {
				mEQData[ i ]->prevData[ 1 ][ 1 ][ 0 ] = waveData[ n - 0 ];
				mEQData[ i ]->prevData[ 1 ][ 1 ][ 1 ] = waveData[ n - 1 ];
			}
		}
		memcpy( orgData, waveData, WAVE_DATA_LENGTH * sizeof( double ) );
	}
}

void Equalizer::setLowShelving( EQData* target )
{
	double Q = 1.0 / sqrt( 2.0 );
	double fc = tan( M_PI * ( target->fc / SAMPLES_PER_SEC ) ) / ( 2.0 * M_PI );
	double g = target->g;
	double* a = target->a;
	double* b = target->b;

	a[ 0 ] = 1.0 + 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc;
	a[ 1 ] = (8.0 * M_PI * M_PI * fc * fc - 2.0) / a[ 0 ];
	a[ 2 ] = (1.0 - 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc) / a[ 0 ];
	b[ 0 ] = (1.0 + sqrt(1.0 + g) * 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc * (1.0 + g)) / a[ 0 ];
	b[ 1 ] = (8.0 * M_PI * M_PI * fc * fc * (1.0 + g) - 2.0) / a[ 0 ];
	b[ 2 ] = (1.0 - sqrt(1.0 + g) * 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc * (1.0 + g)) / a[ 0 ];

	a[ 0 ] = 1.0;
}

void Equalizer::setHighShelving( EQData* target )
{
	double Q = 1.0 / sqrt( 2.0 );
	double fc = tan( M_PI * ( target->fc / SAMPLES_PER_SEC ) ) / ( 2.0 * M_PI );
	double g = target->g;
	double* a = target->a;
	double* b = target->b;

	a[ 0 ] = 1.0 + 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc;
	a[ 1 ] = (8.0 * M_PI * M_PI * fc * fc - 2.0) / a[ 0 ];
	a[ 2 ] = (1.0 - 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc) / a[ 0 ];
	b[ 0 ] = ((1.0 + g) + sqrt(1.0 + g) * 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc) / a[ 0 ];
	b[ 1 ] = (8.0 * M_PI * M_PI * fc * fc - 2.0 * (1.0 + g)) / a[ 0 ];
	b[ 2 ] = ((1.0 + g) - sqrt(1.0 + g) * 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc) / a[ 0 ];

	a[ 0 ] = 1.0;
}

void Equalizer::setPeaking( EQData* target )
{
	double Q = 1.0 / sqrt( 2.0 );
	double fc = tan( M_PI * ( target->fc / SAMPLES_PER_SEC ) ) / ( 2.0 * M_PI );
	double g = target->g;
	double* a = target->a;
	double* b = target->b;

	a[ 0 ] = 1.0 + 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc;
	a[ 1 ] = (8.0 * M_PI * M_PI * fc * fc - 2.0) / a[ 0 ];
	a[ 2 ] = (1.0 - 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc) / a[ 0 ];
	b[ 0 ] = (1.0 + 2.0 * M_PI * fc / Q * (1.0 + g) + 4.0 * M_PI * M_PI * fc * fc) / a[ 0 ];
	b[ 1 ] = (8.0 * M_PI * M_PI * fc * fc - 2.0) / a[ 0 ];
	b[ 2 ] = (1.0 - 2.0 * M_PI * fc / Q * (1.0 + g) + 4.0 * M_PI * M_PI * fc * fc) / a[ 0 ];

	a[ 0 ] = 1.0;
}



} // namespace Sound