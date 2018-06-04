#include "SoundManager.h"

#include "EffectBase.h"
#include "SoundBase.h"
#include "Track.h"
#include "Wave.h"

#define MAX_SYSTEM_VOL 0x5F

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
mMainVol( 0.0 ),
mMainVolL( 0.5 ),
mMainVolR( 0.5 ),
mSysVol( 0 )
{
	WAVEFORMATEX wfe;

	Sound::EffectBase::initTable();

	mTrack1 = new Sound::Track();
	mTrack2 = new Sound::Track();
	mTrack3 = new Sound::Track();

	mTrack1->setWave( WAVE_SAWTOOTH );
	mTrack2->setWave( WAVE_SAWTOOTH );
	mTrack3->setWave( WAVE_SAWTOOTH );

	wfe.wFormatTag = WAVE_FORMAT_PCM;
	wfe.nChannels = CHANNEL;	//ステレオ
	wfe.wBitsPerSample = BITS_PER_SAMPLE;	//量子化ビット数
	wfe.nBlockAlign = BLOCK_ALIGN;
	wfe.nSamplesPerSec = SAMPLES_PER_SEC;	//標本化周波数
	wfe.nAvgBytesPerSec = BYTES_PER_SEC;
	wfe.cbSize = 0;

	waveOutOpen( &mHWaveOut, WAVE_MAPPER, &wfe, ( DWORD )hwnd, 0, CALLBACK_WINDOW );

	for( int k = 0; k < 2; ++k ) {
		for( int i = 0; i < BUFFER_SIZE; ++i ) {		//波形データ初期化
			mLpWave[k][i] = 0;
		}
		mWaveHeader[k].lpData = ( LPSTR )mLpWave[k];
		mWaveHeader[k].dwBufferLength = BUFFER_SIZE;
		mWaveHeader[k].dwBytesRecorded = 0;
		mWaveHeader[k].dwLoops = 1;
		mWaveHeader[k].dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
		mWaveHeader[k].reserved = 0;
		mWaveHeader[k].lpNext = 0;

		waveOutPrepareHeader( mHWaveOut, &mWaveHeader[ k ], sizeof(WAVEHDR) );
	}
	setSysVol();
}


SoundManager::~SoundManager( void )
{
	mIsPlay = FALSE;

	waveOutReset( mHWaveOut );
	for( int i = 0; i < 2; ++i ) {
		waveOutUnprepareHeader( mHWaveOut, &mWaveHeader[ i ], sizeof(WAVEHDR) );
	}
	waveOutClose( mHWaveOut );

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
	return 0;
}

int SoundManager::stop( void )
{
	mIsPlay = FALSE;
	return 0;
}

int SoundManager::setBuffer()
{
	if( mSetBufferNum > 0) --mSetBufferNum;
	return 0;
}

void SoundManager::setVol( double vol )
{
	mMainVol = vol;
}
void SoundManager::setPan( double vol )
{
	mMainVolL = vol;
	mMainVolR = 1.0 - vol;
}

Sound::Track* SoundManager::getTrack( int index )
{
	switch( index ) {
		case 0:
			return mTrack1;
			break;
		case 1:
			return mTrack2;
			break;
		case 2:
			return mTrack3;
			break;
	}
	return NULL;
}

int SoundManager::makeWave( void )
{
	if( !mIsPlay ) {
		if( mSysVol == 0 ) {
			waveOutUnprepareHeader( mHWaveOut, &mWaveHeader[ 0 ], sizeof(WAVEHDR) );
			waveOutUnprepareHeader( mHWaveOut, &mWaveHeader[ 1 ], sizeof(WAVEHDR) );
			return 0;
		} else {
			--mSysVol;
			setSysVol();
		}
	} else if( mSysVol < MAX_SYSTEM_VOL ) {
		++mSysVol;
		setSysVol();
	}

	if( mSetBufferNum >= 2 ) return 0;
	++mSetBufferNum;

	waveOutUnprepareHeader( mHWaveOut, &mWaveHeader[ mSetBufferIndex ], sizeof(WAVEHDR) );
	waveOutPrepareHeader( mHWaveOut, &mWaveHeader[ mSetBufferIndex ], sizeof(WAVEHDR) );

	mTrack1->update();
	mTrack2->update();
	mTrack3->update();

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		double s = 0;
		s += mTrack1->getPlayDataR( i );
		s += mTrack2->getPlayDataR( i );
		s += mTrack3->getPlayDataR( i );
		s = clipping( s / 3.0 * mMainVol * mMainVolR );
		// 右   /* 四捨五入とオフセットの調節 */
		mLpWave[ mSetBufferIndex ][ i * 2 ] = static_cast< short >( s + 0.5 ) - 32768;
		
		s = 0;
		s += mTrack1->getPlayDataL( i );
		s += mTrack2->getPlayDataL( i );
		s += mTrack3->getPlayDataL( i );
		s = clipping( s / 3.0 * mMainVol * mMainVolL );
		// 左   /* 四捨五入とオフセットの調節 */
		mLpWave[ mSetBufferIndex ][ i * 2 + 1 ] = static_cast< short >( s + 0.5 ) - 32768;
	}
	waveOutWrite( mHWaveOut, &mWaveHeader[ mSetBufferIndex ], sizeof( WAVEHDR ) );

	mSetBufferIndex = ( mSetBufferIndex + 1 ) % 2;

	return 1;
}

double SoundManager::clipping( double s )
{
	s = ( s + 1.0 ) / 2.0 * 65536.0;
	
	if( s > 65535.0 ) {
		s = 65535.0; /* クリッピング */
	} else if( s < 0.0 ) {
		s = 0.0; /* クリッピング */
	}

	return s;
}

void SoundManager::setSysVol( void )
{
	unsigned vol = 0;
	vol = 0xFF | mSysVol << 8;
	waveOutSetVolume( mHWaveOut, ( DWORD )( vol | vol << 16 ) );
}


} // namespace Main
