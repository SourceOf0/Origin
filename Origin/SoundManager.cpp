#include "SoundManager.h"

#include "SoundBase.h"
#include "Track.h"
#include "Wave.h"

#include "Distortion1.h"
#include "Distortion2.h"
#include "Distortion3.h"
#include "Compressor.h"
#include "Tremolo.h"
#include "Delay.h"

#define _USE_MATH_DEFINES
#include <math.h>

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

	mIsPlay = FALSE;
	mSetBufferIndex = 0;
	mSetBufferNum = 0;

	test = 0;

	mTrack1 = new Sound::Track();
	mTrack2 = new Sound::Track();

	mTrack1->setWave( WAVE_SAWTOOTH );
	mTrack1->addEffect( new Sound::Delay() );
	
	mTrack2->setWave( WAVE_SQUARE );

	wfe.wFormatTag = WAVE_FORMAT_PCM;
	wfe.nChannels = CHANNEL;	//ステレオ
	wfe.wBitsPerSample = BITS_PER_SAMPLE;	//量子化ビット数
	wfe.nBlockAlign = BLOCK_ALIGN;
	wfe.nSamplesPerSec = SAMPLES_PER_SEC;	//標本化周波数
	wfe.nAvgBytesPerSec = BYTES_PER_SEC;

	waveOutOpen( &mHWaveOut, WAVE_MAPPER, &wfe, (DWORD)hwnd, 0, CALLBACK_WINDOW );

	for( int k = 0; k < 2; ++k ) {
		mLpWave[k] = (LPBYTE)new char[ BUFFER_SIZE ];
		for( int i = 0; i < BUFFER_SIZE; ++i ) {		//波形データ初期化
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
//	waveOutSetVolume( mHWaveOut, (DWORD)( 0xFFFFFFFF ) );
//	waveOutSetVolume( mHWaveOut, (DWORD)( 0x1FFF1FFF ) );
	waveOutSetVolume( mHWaveOut, (DWORD)( 0x2FFF2FFF ) );
	setSound( 0 );
}


SoundManager::~SoundManager( void )
{
	mIsPlay = FALSE;

	waveOutReset( mHWaveOut );
	for( int i = 0; i < 2; ++i ) {
		waveOutUnprepareHeader( mHWaveOut, &mWaveHeader[i], sizeof(WAVEHDR) );
	}
	waveOutClose( mHWaveOut );
	for( int i = 0; i < 2; ++i ) {
		delete[] mLpWave[i];
	}

	delete mTrack1;
	mTrack1 = 0;

	delete mTrack2;
	mTrack2 = 0;
}

int SoundManager::play( void )
{
	mIsPlay = TRUE;
	mTrack1->setF( 300 );
	mTrack2->setF( 100 );
	
	++test;
	switch( test ) {
		case 3:
			test = 0;
		case 0:
			mTrack1->setWave( WAVE_SAWTOOTH );
			break;
		case 1:
			mTrack1->setWave( WAVE_SQUARE );
			break;
		case 2:
			mTrack1->setWave( WAVE_TRIANGLE );
			break;
	}
	return 0;
}

int SoundManager::stop( void )
{
//	mIsPlay = FALSE;
//	mTrack1->setF( 400 );
//	mTrack2->setF( 200 );
	mTrack1->setWave( WAVE_NONE );
	return 0;
}

int SoundManager::setBuffer()
{
	if( mSetBufferNum > 0) --mSetBufferNum;
	return 0;
}

int SoundManager::setSound( int index )
{
//	mPlayingIndex = index;
	return 0;
}

int SoundManager::makeWave( void )
{
	if( !mIsPlay ) {
		waveOutReset( mHWaveOut );
		mSetBufferNum = 0;
		mSetBufferIndex = 0;
		mTrack1->reset();
		mTrack2->reset();
		return 0;
	}
	if( mSetBufferNum >= 2 ) return 0;
	++mSetBufferNum;

	mTrack1->update();
//	mTrack2->update();

	double* wave1 = mTrack1->getPlayWave();
	double* wave2 = mTrack2->getPlayWave();

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = clipping( ( wave1[i] + wave2[i] ) / 2 );
		short data = static_cast<short>( s + 0.5 ) - 32768; /* 四捨五入とオフセットの調節 */
		// 右
		mLpWave[mSetBufferIndex][i*4] = static_cast<char>(data & 0 << 8);
		mLpWave[mSetBufferIndex][i*4+1] = static_cast<char>(data >> 8);
		// 左
		mLpWave[mSetBufferIndex][i*4+2] = static_cast<char>(data & 0 << 8);
		mLpWave[mSetBufferIndex][i*4+3] = static_cast<char>(data >> 8);
	}
	waveOutWrite( mHWaveOut, &mWaveHeader[mSetBufferIndex], sizeof(WAVEHDR) );

	mSetBufferIndex = ( mSetBufferIndex + 1 ) % 2;

	return 0;
}

double SoundManager::clipping( double s )
{
	s = ( s + 1.0 ) / 2.0 * 65536.0;
			
	if( s > 65535.0 ) {
		s = 65535.0; /* クリッピング */
	} else if (s < 0.0) {
		s = 0.0; /* クリッピング */
	}

	return s;
}


} // namespace Main
