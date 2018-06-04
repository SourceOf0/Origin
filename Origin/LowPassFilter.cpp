#include <memory.h>

#include "LowPassFilter.h"
#include "Track.h"

#define _USE_MATH_DEFINES
#include <Math.h>

namespace Sound {

LowPassFilter::LowPassFilter( double** setWaveLog ) : 
mFe( 3000.0 ),
mDelta( 1000.0 ),
mB( 0 ),
mJ( 0 ),
mX( 0 ),
mY( 0 )
{
	init( setWaveLog, 0, 0, 0 );

	double fe = mFe / SAMPLES_PER_SEC; /* エッジ周波数 */
	double delta = mDelta / SAMPLES_PER_SEC; /* 遷移帯域幅 */
	mJ = (int)( 3.1 / delta + 0.5 ) - 1; /* 遅延器の数 */
	if( mJ % 2 == 1 ) ++mJ; /* J+1が奇数になるように調整する */

	double* w = new double[ mJ + 1 ];
	mB = new double[ mJ + 1 ];

	mL = WAVE_DATA_LENGTH / 10; /* フレームの長さ */
	mX = new double[ mL + mJ ];
	mY = new double[ mL ];

	getHanningWindow( w, mJ + 1 ); /* ハニング窓 */

	setLPF( fe, w ); /* FIRフィルタの設計 */

	delete w;
	w = 0;
}

LowPassFilter::~LowPassFilter( void )
{
	delete[] mB;
	mB = 0;

	delete[] mX;
	mX = 0;
	
	delete[] mY;
	mY = 0;
}

void LowPassFilter::reset( void )
{
	init( mWaveLog, 0, 0, 0 );
}

// Low-Pass（低域通過）フィルタ
void LowPassFilter::apply( Track* track )
{
	double* waveData = track->getWaveData();
	int numberOfFrame = WAVE_DATA_LENGTH / mL; /* フレームの数 */

	memcpy( mWaveLog[ mLogIndex ], waveData, WAVE_DATA_LENGTH * sizeof( double ) );

	for ( int frame = 0; frame < numberOfFrame; ++frame ) {
		int offset = mL * frame;

		/* 直前のフレームの後半のJサンプルをつけ加える */
		for( int n = 0; n < mL + mJ; ++n ) {
			mX[ n ] = getPrevData( offset - mJ + n );
		}

		/* フィルタリング */
		for( int n = 0; n < mL; ++n ) {
			mY[ n ] = 0.0;
			for( int m = 0; m <= mJ; ++m ) {
				mY[ n ] += mB[ m ] * mX[ mJ + n - m ];
			}
		}

		/* フィルタリング結果の連結 */
		for( int n = 0; n < mL; ++n ) {
			waveData[ offset + n ] = mY[ n ];
		}
	}

	mLogIndex = ( mLogIndex + 1 ) % LOG_MAX_DATA_NUM;
}

/* Finite Impulse Response（有限インパルス応答） フィルタ */
/* Low-Pass（低域通過）フィルタ */
void LowPassFilter::setLPF( double fe, double* w )
{
	int offset = mJ / 2;
	for( int m = 0; m <= mJ; ++m ) {
		mB[ m ] = 2.0 * fe * sinc( 2.0 * M_PI * fe * ( m - offset ) ) * w[ m ];
	}
}


} // namespace Sound