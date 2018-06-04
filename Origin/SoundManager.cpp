#include "SoundManager.h"

#define SRATE	8000	//標本化周波数(1秒間のサンプル数)
#define F		400		//周波数(1秒間の波形数)

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
	wfe.nChannels = 2;	//ステレオ
	wfe.wBitsPerSample = 8;	//量子化ビット数
	wfe.nBlockAlign = wfe.nChannels * wfe.wBitsPerSample / 8;
	wfe.nSamplesPerSec = SRATE;	//標本化周波数
	wfe.nAvgBytesPerSec = wfe.nSamplesPerSec * wfe.nBlockAlign;

	waveOutOpen( &mHWaveOut, WAVE_MAPPER, &wfe, (DWORD)hwnd, 0, CALLBACK_WINDOW );

	len = SRATE / F;	//波長
	mLpWave = (LPBYTE)calloc( wfe.nAvgBytesPerSec, 2 );	//2秒分
	for( i = 0; i < SRATE * 2; ++i ) {		//波形データ作成
		if( i % len < len / 2 ) {
			mLpWave[2*i  ] = 128 + 2;		//左
			mLpWave[2*i+1] = 128 + 1;		//右
		} else {
			mLpWave[2*i  ] = 128 - 2;		//左
			mLpWave[2*i+1] = 128 - 1;		//右
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
	// 再生中であればバッファを追加
	waveOutWrite( mHWaveOut, &mWaveHeader, sizeof(WAVEHDR) );
	return 0;
}

} // namespace Main
