#include "SoundManager.h"

#include "EffectBase.h"
#include "SoundBase.h"
#include "Track.h"
#include "Wave.h"

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

SoundManager::SoundManager( HWND& hwnd ) :
mWasReset( TRUE ),
mIsPlay( FALSE ),
mSetBufferIndex( 0 ),
mSetBufferNum( 0 ),
test( 0 )
{
	WAVEFORMATEX wfe;

	mTrack1 = new Sound::Track();
	mTrack2 = new Sound::Track();
	mTrack3 = new Sound::Track();

	mTrack1->setWave( WAVE_SAWTOOTH );
	mTrack1->addEffect( EFFECT_CHORUS );
	mTrack1->addEffect( EFFECT_VIBRATO );
	mTrack1->addEffect( EFFECT_LOW_PASS_FILTER );
	mTrack1->addEffect( EFFECT_EQUALIZER );

	mTrack2->setWave( WAVE_SAWTOOTH );
	mTrack2->addEffect( EFFECT_CHORUS );
	mTrack2->addEffect( EFFECT_VIBRATO );
	mTrack2->addEffect( EFFECT_LOW_PASS_FILTER );
	mTrack2->addEffect( EFFECT_EQUALIZER );

	mTrack3->setWave( WAVE_SAWTOOTH );
	mTrack3->addEffect( EFFECT_CHORUS );
	mTrack3->addEffect( EFFECT_VIBRATO );
	mTrack3->addEffect( EFFECT_LOW_PASS_FILTER );
	mTrack3->addEffect( EFFECT_EQUALIZER );

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
	waveOutSetVolume( mHWaveOut, (DWORD)( 0x05FF05FF ) );
//	waveOutSetVolume( mHWaveOut, (DWORD)( 0x2FFF2FFF ) );
	setSound( 0 );
}


SoundManager::~SoundManager( void )
{
	mIsPlay = FALSE;

	waveOutReset( mHWaveOut );
	for( int i = 0; i < 2; ++i ) {
		waveOutUnprepareHeader( mHWaveOut, &mWaveHeader[ i ], sizeof(WAVEHDR) );
	}
	waveOutClose( mHWaveOut );
	for( int i = 0; i < 2; ++i ) {
		delete[] mLpWave[ i ];
	}

	delete mTrack1;
	mTrack1 = 0;

	delete mTrack2;
	mTrack2 = 0;

	delete mTrack3;
	mTrack3 = 0;
}

int SoundManager::play( void )
{
	mIsPlay = TRUE;
	mWasReset = FALSE;
	mTrack1->setF( 400 );
	mTrack2->setF( 300 );
	mTrack3->setF( 200 );
	
	++test;
	switch( test ) {
		case 3:
			test = 0;
		case 0:
			mTrack1->setWave( WAVE_SAWTOOTH );
			mTrack2->setWave( WAVE_SAWTOOTH );
			mTrack3->setWave( WAVE_SAWTOOTH );
			break;
		case 1:
			mTrack1->setWave( WAVE_SQUARE );
			mTrack2->setWave( WAVE_SQUARE );
			mTrack3->setWave( WAVE_SQUARE );
			break;
		case 2:
			mTrack1->setWave( WAVE_TRIANGLE );
			mTrack2->setWave( WAVE_TRIANGLE );
			mTrack3->setWave( WAVE_TRIANGLE );
			break;
	}
	return 0;
}

int SoundManager::stop( void )
{
//	mIsPlay = FALSE;
//	mTrack1->setF( 400 );
//	mTrack2->setF( 300 );
	mTrack1->setWave( WAVE_NONE );
	mTrack2->setWave( WAVE_NONE );
	mTrack3->setWave( WAVE_NONE );
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

Sound::Track* SoundManager::getTrack( int index )
{
	switch( index ) {
		case 1:
			return mTrack1;
			break;
		case 2:
			return mTrack2;
			break;
		case 3:
			return mTrack3;
			break;
	}
	return NULL;
}

int SoundManager::makeWave( void )
{
	if( !mIsPlay ) {
		if( mWasReset ) return 0;
		mWasReset = TRUE;
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
	mTrack2->update();
	mTrack3->update();

//	mTrack1->getEffect(0)->mSetNum1 += 0.0001;
//	mTrack2->getEffect(0)->mSetNum1 += 0.0001;

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = 0;
		s += mTrack1->getPlayDataR( i );
		s += mTrack2->getPlayDataR( i );
		s += mTrack3->getPlayDataR( i );
		s = clipping( s / 3 );
		short data = static_cast<short>( s + 0.5 ) - 32768; /* 四捨五入とオフセットの調節 */
		// 右
		mLpWave[ mSetBufferIndex ][ i*4 ] = static_cast<char>(data & 0 << 8);
		mLpWave[ mSetBufferIndex ][ i*4+1 ] = static_cast<char>(data >> 8);
		
		s = 0;
		s += mTrack1->getPlayDataL( i );
		s += mTrack2->getPlayDataL( i );
		s += mTrack3->getPlayDataL( i );
		s = clipping( s / 3 );
		data = static_cast<short>( s + 0.5 ) - 32768; /* 四捨五入とオフセットの調節 */
		// 左
		mLpWave[ mSetBufferIndex ][ i*4+2 ] = static_cast<char>(data & 0 << 8);
		mLpWave[ mSetBufferIndex ][ i*4+3 ] = static_cast<char>(data >> 8);
	}
	waveOutWrite( mHWaveOut, &mWaveHeader[ mSetBufferIndex ], sizeof(WAVEHDR) );

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
