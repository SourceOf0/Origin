#include "Equalizer.h"
#include "Track.h"

#include <memory.h>

namespace Sound {

Equalizer::Equalizer( void ) :
EffectBase( 0 )
{
	reset();
}


Equalizer::~Equalizer( void )
{
}

void Equalizer::reset( void )
{
	EQData* newData = &mEQData[ 0 ];

	newData->isSetEnd = FALSE;
	newData->fc = 500.0;
	newData->g = -1.0;
	newData->kind = EQ_NONE;

	newData = &mEQData[ 1 ];
	newData->isSetEnd = FALSE;
	newData->fc = 1000.0;
	newData->g = 1.0;
	newData->kind = EQ_NONE;

	newData = &mEQData[ 2 ];
	newData->isSetEnd = FALSE;
	newData->fc = 1500.0;
	newData->g = -1.0;
	newData->kind = EQ_NONE;

	for( int n = 0; n < EQDATA_MAX_NUM; ++n ) {
		for( int i = 0; i < 2; ++i ) {
			for( int j = 0; j < 2; ++j ) {
				for( int k = 0; k < 2; ++k ) {
					mEQData[ n ].prevData[ i ][ j ][ k ] = 0.0;
				}
			}
		}
	}
}

void Equalizer::setKind( int index, EQID kind )
{
	EQData* target = &mEQData[ index ];
	target->kind = kind;
	target->isSetEnd = FALSE;
}
void Equalizer::setState( int index, double fc, double g )
{
	EQData* target = &mEQData[ index ];
	target->fc = fc;
	target->g = g;
	target->isSetEnd = FALSE;
}

// イコライザー
void Equalizer::apply( Track* track )
{
	double* waveData = track->getWaveData();
	double orgData[ WAVE_DATA_LENGTH ];
	double useData[ EQDATA_MAX_NUM ][ 2 ][ 2 ][ 2 ];
	BOOL isEnd = TRUE;
	int J = 2;
	int I = 2;

	for( int i = 0; i < EQDATA_MAX_NUM; ++i ) {
		if( mEQData[ i ].kind == EQ_NONE ) continue;
		isEnd = FALSE;
		if( mEQData[ i ].isSetEnd ) continue; 
		mEQData[ i ].isSetEnd = TRUE;

		/* IIRフィルタの設計 */
		switch( mEQData[ i ].kind ) {
			case EQ_LOW_SHELVING:
				setLowShelving( &mEQData[ i ] );
				break;
			case EQ_PEAKING:
				setPeaking( &mEQData[ i ] );
				break;
			case EQ_HIGH_SHELVING:
				setHighShelving( &mEQData[ i ] );
				break;
		}
	}
	if( isEnd ) return;

	for( int n = 0; n < EQDATA_MAX_NUM; ++n ) {
		for( int i = 0; i < 2; ++i ) {
			for( int j = 0; j < 2; ++j ) {
				for( int k = 0; k < 2; ++k ) {
					useData[ n ][ i ][ j ][ k ] = mEQData[ n ].prevData[ i ][ j ][ k ];
				}
			}
		}
	}

	memcpy( orgData, waveData, WAVE_DATA_LENGTH * sizeof( double ) );

	for( int i = 0; i < EQDATA_MAX_NUM; ++i ) {
		if( mEQData[ i ].kind == EQ_NONE ) continue;
		double* a = mEQData[ i ].a;
		double* b = mEQData[ i ].b;
		for( int n = 0; n < WAVE_DATA_LENGTH; ++n ) {
			waveData[ n ] = 0;
		}
		for( int n = 0; n < WAVE_DATA_LENGTH; ++n ) {
			if( n == WAVE_DATA_LENGTH - 2 ) {
				mEQData[ i ].prevData[ 0 ][ 0 ][ 0 ] = orgData[ n - 0 ];
				mEQData[ i ].prevData[ 0 ][ 0 ][ 1 ] = orgData[ n - 1 ];
			} else if( n == WAVE_DATA_LENGTH - 1 ) {
				mEQData[ i ].prevData[ 0 ][ 1 ][ 0 ] = orgData[ n - 0 ];
				mEQData[ i ].prevData[ 0 ][ 1 ][ 1 ] = orgData[ n - 1 ];
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
				mEQData[ i ].prevData[ 1 ][ 0 ][ 0 ] = waveData[ n - 0 ];
				mEQData[ i ].prevData[ 1 ][ 0 ][ 1 ] = waveData[ n - 1 ];
			} else if( n == WAVE_DATA_LENGTH - 1 ) {
				mEQData[ i ].prevData[ 1 ][ 1 ][ 0 ] = waveData[ n - 0 ];
				mEQData[ i ].prevData[ 1 ][ 1 ][ 1 ] = waveData[ n - 1 ];
			}
		}
		memcpy( orgData, waveData, WAVE_DATA_LENGTH * sizeof( double ) );
	}
}

void Equalizer::setLowShelving( EQData* target )
{
	double Q = 1.0 / customSqrt( 2.0 );
	double fc = customTan( M_PI * ( target->fc / SAMPLES_PER_SEC ) ) / ( 2.0 * M_PI );
	double g = target->g;
	double* a = target->a;
	double* b = target->b;

	a[ 0 ] = 1.0 + 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc;
	a[ 1 ] = (8.0 * M_PI * M_PI * fc * fc - 2.0) / a[ 0 ];
	a[ 2 ] = (1.0 - 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc) / a[ 0 ];
	b[ 0 ] = (1.0 + customSqrt(1.0 + g) * 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc * (1.0 + g)) / a[ 0 ];
	b[ 1 ] = (8.0 * M_PI * M_PI * fc * fc * (1.0 + g) - 2.0) / a[ 0 ];
	b[ 2 ] = (1.0 - customSqrt(1.0 + g) * 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc * (1.0 + g)) / a[ 0 ];

	a[ 0 ] = 1.0;
}

void Equalizer::setHighShelving( EQData* target )
{
	double Q = 1.0 / customSqrt( 2.0 );
	double fc = customTan( M_PI * ( target->fc / SAMPLES_PER_SEC ) ) / ( 2.0 * M_PI );
	double g = target->g;
	double* a = target->a;
	double* b = target->b;

	a[ 0 ] = 1.0 + 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc;
	a[ 1 ] = (8.0 * M_PI * M_PI * fc * fc - 2.0) / a[ 0 ];
	a[ 2 ] = (1.0 - 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc) / a[ 0 ];
	b[ 0 ] = ((1.0 + g) + customSqrt(1.0 + g) * 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc) / a[ 0 ];
	b[ 1 ] = (8.0 * M_PI * M_PI * fc * fc - 2.0 * (1.0 + g)) / a[ 0 ];
	b[ 2 ] = ((1.0 + g) - customSqrt(1.0 + g) * 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc) / a[ 0 ];

	a[ 0 ] = 1.0;
}

void Equalizer::setPeaking( EQData* target )
{
	double Q = 1.0 / customSqrt( 2.0 );
	double fc = customTan( M_PI * ( target->fc / SAMPLES_PER_SEC ) ) / ( 2.0 * M_PI );
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