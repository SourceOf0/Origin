#include "SoundManager.h"

#define SRATE	8000	//�W�{�����g��(1�b�Ԃ̃T���v����)
#define F		400		//���g��(1�b�Ԃ̔g�`��)

namespace Main {

SoundManager* SoundManager::mInst = 0;

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
	int i, len;

	wfe.wFormatTag = WAVE_FORMAT_PCM;
	wfe.nChannels = 2;	//�X�e���I
	wfe.wBitsPerSample = 8;	//�ʎq���r�b�g��
	wfe.nBlockAlign = wfe.nChannels * wfe.wBitsPerSample / 8;
	wfe.nSamplesPerSec = SRATE;	//�W�{�����g��
	wfe.nAvgBytesPerSec = wfe.nSamplesPerSec * wfe.nBlockAlign;

	waveOutOpen( &mHWaveOut, WAVE_MAPPER, &wfe, (DWORD)hwnd, 0, CALLBACK_WINDOW );

	len = SRATE / F;	//�g��
	mLpWave = (LPBYTE)calloc( wfe.nAvgBytesPerSec, 2 );	//2�b��
	for( i = 0; i < SRATE * 2; ++i ) {		//�g�`�f�[�^�쐬
		if( i % len < len / 2 ) {
			mLpWave[2*i  ] = 128 + 2;		//��
			mLpWave[2*i+1] = 128 + 1;		//�E
		} else {
			mLpWave[2*i  ] = 128 - 2;		//��
			mLpWave[2*i+1] = 128 - 1;		//�E
		}
		mWaveHeader.lpData = (LPSTR)mLpWave;
		mWaveHeader.dwBufferLength = wfe.nAvgBytesPerSec * 2;
		mWaveHeader.dwLoops = 1;
		mWaveHeader.dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
		mWaveHeader.reserved = 0;
		mWaveHeader.lpNext = 0;

		waveOutPrepareHeader( mHWaveOut, &mWaveHeader, sizeof(WAVEHDR) );
	}
	isReset = TRUE;
}


SoundManager::~SoundManager( void )
{
	waveOutReset( mHWaveOut );
	waveOutUnprepareHeader( mHWaveOut, &mWaveHeader, sizeof(WAVEHDR) );
	waveOutClose( mHWaveOut );
	free( mLpWave );
}

int SoundManager::play( void )
{
	if( !isReset ) return 0;
	waveOutWrite( mHWaveOut, &mWaveHeader, sizeof(WAVEHDR) );
	isReset = FALSE;
	return 0;
}

int SoundManager::stop( void )
{
	if( isReset ) return 0;
	waveOutReset( mHWaveOut );
	isReset = TRUE;
	return 0;
}

int SoundManager::setBuffer( void )
{
	if( isReset ) return 0;
	// �Đ����ł���΃o�b�t�@��ǉ�
	waveOutWrite( mHWaveOut, &mWaveHeader, sizeof(WAVEHDR) );
	return 0;
}

} // namespace Main
