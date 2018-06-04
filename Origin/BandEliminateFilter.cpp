#include <memory.h>

#include "BandEliminateFilter.h"
#include "Track.h"

#define _USE_MATH_DEFINES
#include <Math.h>

namespace Sound {

BandEliminateFilter::BandEliminateFilter( double** setWaveLog ) : 
mFe1( 1000.0 ),
mFe2( 5000.0 ),
mDelta( 1000.0 ),
mB( 0 ),
mJ( 0 ),
mX( 0 ),
mY( 0 )
{
	init( setWaveLog, 0, 0, 0 );

	double fe1 = mFe1 / SAMPLES_PER_SEC; /* �G�b�W���g�� */
	double fe2 = mFe2 / SAMPLES_PER_SEC; /* �G�b�W���g�� */
	double delta = mDelta / SAMPLES_PER_SEC; /* �J�ڑш敝 */
	mJ = (int)( 3.1 / delta + 0.5 ) - 1; /* �x����̐� */
	if( mJ % 2 == 1 ) ++mJ; /* J+1����ɂȂ�悤�ɒ������� */

	double* w = new double[ mJ + 1 ];
	mB = new double[ mJ + 1 ];

	mL = WAVE_DATA_LENGTH / 10; /* �t���[���̒��� */
	mX = new double[ mL + mJ ];
	mY = new double[ mL ];

	getHanningWindow( w, mJ + 1 ); /* �n�j���O�� */

	setBEF( fe1, fe2, w ); /* FIR�t�B���^�̐݌v */

	delete w;
	w = 0;
}

BandEliminateFilter::~BandEliminateFilter( void )
{
	delete[] mB;
	mB = 0;

	delete[] mX;
	mX = 0;
	
	delete[] mY;
	mY = 0;
}

void BandEliminateFilter::reset( void )
{
	init( mWaveLog, 0, 0, 0 );
}

// High-Pass�i���ʉ߁j�t�B���^
void BandEliminateFilter::apply( Track* track )
{
	double* waveData = track->getWaveData();
	int numberOfFrame = WAVE_DATA_LENGTH / mL; /* �t���[���̐� */

	memcpy( mWaveLog[ mLogIndex ], waveData, WAVE_DATA_LENGTH * sizeof( double ) );

	for ( int frame = 0; frame < numberOfFrame; ++frame ) {
		int offset = mL * frame;

		/* ���O�̃t���[���̌㔼��J�T���v������������ */
		for( int n = 0; n < mL + mJ; ++n ) {
			mX[ n ] = getPrevData( offset - mJ + n );
		}

		/* �t�B���^�����O */
		for( int n = 0; n < mL; ++n ) {
			mY[ n ] = 0.0;
			for( int m = 0; m <= mJ; ++m ) {
				mY[ n ] += mB[ m ] * mX[ mJ + n - m ];
			}
		}

		/* �t�B���^�����O���ʂ̘A�� */
		for( int n = 0; n < mL; ++n ) {
			waveData[ offset + n ] = mY[ n ];
		}
	}

	mLogIndex = ( mLogIndex + 1 ) % LOG_MAX_DATA_NUM;
}

/* Finite Impulse Response�i�L���C���p���X�����j �t�B���^ */
/* Band-Eliminate�i�ш�j�~�j�t�B���^ �@������̑ш��j�~���� */
void BandEliminateFilter::setBEF( double fe1, double fe2, double* w )
{
	int offset = mJ / 2;
	for( int m = 0; m <= mJ; ++m ) {
		int fixM = m - offset;
		mB[ m ] = sinc( M_PI * fixM ) - 2.0 * fe2 * sinc( 2.0 * M_PI * fe2 * fixM ) + 2.0 * fe1 * sinc( 2.0 * M_PI * fe1 * fixM ) * w[ m ];
	}
}


} // namespace Sound