#include <memory.h>

#include "BandPassFilter.h"
#include "Track.h"

namespace Sound {

BandPassFilter::BandPassFilter( void ) : 
mFe1( 500.0 ),
mFe2( 2000.0 ),
mDelta( 1000.0 ),
mB( 0 ),
mJ( 0 ),
mX( 0 ),
mY( 0 )
{
	init( mWaveLog );

	mL = WAVE_DATA_LENGTH / 10; /* �t���[���̒��� */
	mY = new double[ mL ];

	setState();
}

BandPassFilter::~BandPassFilter( void )
{
	delete[] mB;
	mB = 0;

	delete[] mX;
	mX = 0;
	
	delete[] mY;
	mY = 0;
}

void BandPassFilter::reset( void )
{
	init( mWaveLog );
}

// High-Pass�i���ʉ߁j�t�B���^
void BandPassFilter::apply( Track* track )
{
	double* waveData = track->getWaveData();
	int numberOfFrame = WAVE_DATA_LENGTH / mL; /* �t���[���̐� */

	setState();

	memcpy( mWaveLog[ mLogIndex ], waveData, WAVE_DATA_LENGTH * sizeof( double ) );

	for ( int frame = 0; frame < numberOfFrame; ++frame ) {
		int offset = mL * frame;

		/* ���O�̃t���[���̌㔼��J�T���v������������ */
		for( int n = 0; n < mL + mJ; ++n ) {
			mX[ n ] = getPrevData( mWaveLog, offset - mJ + n );
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

void BandPassFilter::setState( void )
{
	if( mFe1 == mSetNum1 && mDelta == mSetNum2 ) return;

	mFe1 = mSetNum1;
	mFe2 = mSetNum1 + 0.3;
	mDelta = mSetNum2;

	double fe1 = ( mFe1 * 1000.0 + 200.0 ) / SAMPLES_PER_SEC; /* �G�b�W���g�� */
	double fe2 = ( mFe2 * 1000 + 200.0 ) / SAMPLES_PER_SEC; /* �G�b�W���g�� */
	double delta = ( 1000.0 - mDelta * 1000.0 + 100.0 ) / SAMPLES_PER_SEC; /* �J�ڑш敝 */
	int setJ = static_cast< int >( 3.1 / delta + 0.5 ) - 1; /* �x����̐� */
	if( setJ % 2 == 1 ) ++setJ; /* J+1����ɂȂ�悤�ɒ������� */

	double* w = new double[ setJ + 1 ];

	if( setJ != mJ ) {
		mJ = setJ;
		if( mB != 0 ) {
			delete mB;
		}
		mB = new double[ setJ + 1 ];
		if( mX != 0 ) {
			delete mX;
		}
		mX = new double[ mL + setJ ];
	}

	getHanningWindow( w, setJ + 1 ); /* �n�j���O�� */

	setBPF( fe1, fe2, w ); /* FIR�t�B���^�̐݌v */

	delete w;
	w = 0;
}

/* Finite Impulse Response�i�L���C���p���X�����j �t�B���^ */
/* Band-Pass�i�ш�ʉ߁j�t�B���^ �@������̑ш��ʉ߂����� */
void BandPassFilter::setBPF( double fe1, double fe2, double* w )
{
	int offset = mJ / 2;
	for( int m = 0; m <= mJ; ++m ) {
		int fixM = m - offset;
		mB[ m ] = 2.0 * fe2 * sinc( 2.0 * M_PI * fe2 * fixM ) - 2.0 * fe1 * sinc( 2.0 * M_PI * fe1 * fixM ) * w[ m ];
	}
}


} // namespace Sound