#include "SoundManager.h"

#include <math.h>

namespace Main {

SoundManager* SoundManager::mInst = 0;
const double SoundManager::M_PI = 3.14159265;

SoundManager* SoundManager::inst( void )
{
	return mInst;
}
void SoundManager::create( HWND& hwnd )
{
	if( mInst == 0) {
		mInst = new SoundManager( hwnd );
	}
}
void SoundManager::destroy( void )
{
	if( mInst != 0) {
		delete mInst;
		mInst = 0;
	}
}

SoundManager::SoundManager( HWND& hwnd )
{
	WAVEFORMATEX wfe;

	mIsPlay = FALSE;
	mA = 0;
	mAddA = 0.00001;
	mSetWaveLeng = 0;
	mIsPlay = FALSE;
	mSetBufferIndex = 0;
	mSetBufferNum = 0;
	mF = 200;

	wfe.wFormatTag = WAVE_FORMAT_PCM;
	wfe.nChannels = 2;	//�X�e���I
	wfe.wBitsPerSample = 16;	//�ʎq���r�b�g��
	wfe.nBlockAlign = wfe.nChannels * wfe.wBitsPerSample / 8;
	wfe.nSamplesPerSec = 44100;	//�W�{�����g��
	wfe.nAvgBytesPerSec = wfe.nSamplesPerSec * wfe.nBlockAlign;

	waveOutOpen( &mHWaveOut, WAVE_MAPPER, &wfe, (DWORD)hwnd, 0, CALLBACK_WINDOW );

//	BUFFER_SIZE = wfe.nAvgBytesPerSec / 8;
	BUFFER_SIZE = wfe.nAvgBytesPerSec / 15;

	for( int k = 0; k < 2; ++k ) {
//		mLpWave[k] = (LPBYTE)calloc( wfe.nAvgBytesPerSec, 1 );
		mLpWave[k] = (LPBYTE)new char[ BUFFER_SIZE ];
		for( int i = 0; i < BUFFER_SIZE; ++i ) {		//�g�`�f�[�^�쐬
/*			if( i % 20 < 10 ) {
				mLpWave[k][2*i  ] = 128 + 2;		//��
				mLpWave[k][2*i+1] = 128 + 1;		//�E
			} else {
				mLpWave[k][2*i  ] = 128 - 2;		//��
				mLpWave[k][2*i+1] = 128 - 1;		//�E
			}*/
			mLpWave[k][i] = 0;
		}
		mWaveHeader[k].lpData = (LPSTR)mLpWave[k];
		mWaveHeader[k].dwBufferLength = BUFFER_SIZE;
		mWaveHeader[k].dwLoops = 1;
		mWaveHeader[k].dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
		mWaveHeader[k].reserved = 0;
		mWaveHeader[k].lpNext = 0;

		waveOutPrepareHeader( mHWaveOut, &mWaveHeader[k], sizeof(WAVEHDR) );
	}
	mPlayingIndex = 1;
	setSound( 0 );
}


SoundManager::~SoundManager( void )
{
	waveOutReset( mHWaveOut );
	for( int i = 0; i < 2; ++i ) {
		waveOutUnprepareHeader( mHWaveOut, &mWaveHeader[i], sizeof(WAVEHDR) );
	}
	waveOutClose( mHWaveOut );
	for( int i = 0; i < 2; ++i ) {
//		free( mLpWave[i] );
		delete[] mLpWave[i];
	}
}

int SoundManager::play( void )
{
	mIsPlay = TRUE;
	mF = 200;
	return 0;
}

int SoundManager::stop( void )
{
//	mIsPlay = FALSE;
	mF = 300;
	return 0;
}

int SoundManager::setBuffer()
{
	if( mSetBufferNum > 0) --mSetBufferNum;
	return 0;
}

int SoundManager::setSound( int index )
{
	if( index == mPlayingIndex ) return 1;
	switch( index ) {
		case 0:
//			setSound000();
			break;
		case 1:
//			setSound001();
			break;
		default:
			return 1;
			break;
	}
	mPlayingIndex = index;
	return 0;
}

int SoundManager::makeWave( void )
{
	if( !mIsPlay ) {
		waveOutReset( mHWaveOut );
		mSetBufferNum = 0;
		mSetWaveLeng = 0;
		mA = 0;
		mAddA = 0.00001;
		mSetBufferIndex = 0;
		return 0;
	}
	if( mSetBufferNum >= 2 ) return 0;
	++mSetBufferNum;

	double A = mA; /* �U�� */
//	double f0 = 261.63; /* ��{���g�� */
	double f0 = mF;
	int fs = 44100; /* �W�{�����g�� */
//	int length = SRATE; /* ���f�[�^�̒��� */
	int length = BUFFER_SIZE / 4; /* ���f�[�^�̒��� */
	int i;
	short data = 0;
	double s = 0;

	for (i = 0; i < length; i++)
	{
		s = sound01( A, f0, fs, mSetWaveLeng );
//		s = effect03( s );
		s = clipping( s );
		data = static_cast<short>(s + 0.5) - 32768; /* �l�̌ܓ��ƃI�t�Z�b�g�̒��� */
		// �E
		mLpWave[mSetBufferIndex][i*4] = static_cast<char>(data & 0 << 8);
		mLpWave[mSetBufferIndex][i*4+1] = static_cast<char>(data >> 8);

		s = sound01( A, f0, fs, mSetWaveLeng );
		s = effect03( s );
		s = clipping( s );
		data = static_cast<short>(s + 0.5) - 32768; /* �l�̌ܓ��ƃI�t�Z�b�g�̒��� */
		// ��
		mLpWave[mSetBufferIndex][i*4+2] = static_cast<char>(data & 0 << 8);
		mLpWave[mSetBufferIndex][i*4+3] = static_cast<char>(data >> 8);

		A += mAddA;
		if(A < 0 || A > 0.3) mAddA *= -1;
		mSetWaveLeng += 1;
	}
	waveOutWrite( mHWaveOut, &mWaveHeader[mSetBufferIndex], sizeof(WAVEHDR) );

	mA = A;
	mSetBufferIndex = ( mSetBufferIndex + 1 ) % 2;

	return 0;
}

double SoundManager::clipping( double s )
{
	s = (s + 1.0) / 2.0 * 65536.0;
			
	if (s > 65535.0)
	{
		s = 65535.0; /* �N���b�s���O */
	}
	else if (s < 0.0)
	{
		s = 0.0; /* �N���b�s���O */
	}

	return s;
}

// �T�C���g�̃m�R�M���g 
double SoundManager::sound01( double A, double f0, double fs, double t )
{
	double s = 0;
	int i;
	for (i = 1; i <= 15; i++) /* 15�{���܂ł̏d�ˍ��킹 */
	{
		s += A / i * sin(2.0 * M_PI * f0 * i * t / fs);
//		s += A / i * cos(2.0 * M_PI * f0 * i * t / fs + M_PI / 2);
	}
	return s;
}


// �f�B�X�g�[�V�����i�Ώ̃n�[�h�N���b�s���O�j
double SoundManager::effect01( double s )
{
	double gain = 100.0; /* ������ */
	double level = 0.5; /* ���x�� */

	s = s * gain; /* ���f�[�^�̑��� */
    
	if (s > 1.0)
	{
		s = 1.0; /* �N���b�s���O */
	}
		else if (s < -1.0)
	{
		s = -1.0; /* �N���b�s���O */
	}

	s *= level; /* ���̑傫���𒲐߂��� */

	return s;
}

// �f�B�X�g�[�V�����i��Ώ̃\�t�g�N���b�s���O�j
double SoundManager::effect02( double s )
{
	double gain = 10.0; /* ������ */
	double level = 0.5; /* ���x�� */

	s = s * gain; /* ���f�[�^�̑��� */

	if (s >= 0.0)
	{
		s = atan(s) / (M_PI / 2.0); /* �N���b�s���O */
	}
	else if (s < -0.0)
	{
		s = atan(s) / (M_PI / 2.0) * 0.1; /* �N���b�s���O */
	}
	
	s *= level; /* ���̑傫���𒲐߂��� */

	return s;
}

// �f�B�X�g�[�V�����i�S�g�����{�Ώ̃n�[�h�N���b�s���O�j
double SoundManager::effect03( double s )
{
	double gain = 10.0; /* ������ */
	double level = 0.5; /* ���x�� */

	if (s < 0.0)
	{
		s *= -1.0; /* ���f�[�^�̑S�g�����i��Βl�j */
	}
    
	s = s * gain; /* ���f�[�^�̑��� */

	if (s > 1.0)
	{
		s = 1.0; /* �N���b�s���O */
	}
	else if (s < -1.0)
	{
		s = -1.0; /* �N���b�s���O */
	}

	s *= level; /* ���̑傫���𒲐߂��� */

	return s;
}


} // namespace Main
