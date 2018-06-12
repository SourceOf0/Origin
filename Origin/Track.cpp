#define _USE_MATH_DEFINES
#include <math.h>
#include <memory.h>

#include "Track.h"
#include "SoundBase.h"
#include "Wave.h"
#include "EffectBase.h"

#include "NoiseGate.h"
#include "Distortion1.h"
#include "Distortion2.h"
#include "Distortion3.h"
#include "Compressor.h"
#include "Tremolo.h"

#include "Delay.h"
#include "Chorus.h"
#include "Vibrato.h"

#include "LowPassFilter.h"
#include "HighPassFilter.h"
#include "BandPassFilter.h"
#include "BandEliminateFilter.h"

#include "Equalizer.h"
#include "AutoPan.h"

namespace Sound {

Track::Track( void ) :
mPlayTime( 0 ),
mWaveID( WAVE_SAWTOOTH ),
mVolL( 1.0 ),
mVolR( 1.0 ),
mIsUpdate( FALSE )
{
	mWave = new Wave();

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		mWaveData[ i ] = 0;
	}

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		mPlayData[ i ] = 0;
	}

	for( int i = 0; i < EFFECT_MAX_NUM; ++i ) {
		mEffectList[ i ] = 0;
	}

	mAutoPan = new AutoPan();
	mEQ = new Equalizer();
}

Track::~Track( void )
{
	delete mWave;
	mWave = 0;

	for( int i = 0; i < EFFECT_MAX_NUM; ++i ) {
		delete mEffectList[ i ];
		mEffectList[ i ] = 0;
	}

	delete mAutoPan;
	mAutoPan = 0;

	delete mEQ;
	mEQ = 0;
}

// 未使用
void Track::reset( void )
{
	mWave->reset();
	mPlayTime = 0;
	
	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		mWaveData[ i ] = 0;
	}

	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		mPlayData[ i ] = 0;
	}

	for( int i = 0; i < EFFECT_MAX_NUM; ++i ) {
		if( mEffectList[ i ] != 0 ) mEffectList[ i ]->reset();
	}

	mAutoPan->reset();
	mEQ->reset();
}

int Track::update( void )
{
	mIsUpdate = TRUE;
	
	mWave->amend( this );
	
	for( int i = 0; i < EFFECT_MAX_NUM; ++i ) {
		if( mEffectList[ i ] != 0 ) mEffectList[ i ]->apply( this );
	}
	mEQ->apply( this );

	// 再生時間をバッファサイズの10秒分で丸め込む
	mPlayTime = fmod( mPlayTime + WAVE_DATA_LENGTH, SAMPLES_PER_SEC * 10 );

	memcpy( mPlayData, mWaveData, WAVE_DATA_LENGTH * sizeof( double ) );

	mIsUpdate = FALSE;
	return 0;
}

void Track::setData( void )
{
	mWave->setData( this, mWaveID );
}

void Track::setF( double f )
{
	if( f > 3000 ) return;
	mWave->setF( f );
}

void Track::setVol( double vol )
{
	if( vol < -0.0 || vol > 1.0 ) return;
	mWave->setVol( vol );
}
void Track::setPan( double vol )
{
	if( vol < -0.0 || vol > 1.0 ) return;
	if( mAutoPan->mIsUse ) {
		mAutoPan->setRate( vol * 1.5 + 0.3 );
		mVolL = 0.5;
		mVolR = 0.5;
	} else {
		mAutoPan->setRate( 0.5 );
		mVolL = vol;
		mVolR = 1.0 - vol;
	}
}
void Track::setEQKind( int index, EQID kind )
{
	mEQ->setKind( index, kind );
}
void Track::setEQState( int index, double fc, double g )
{
	if( g < -1.0 || g > 1.0 ) return;
	if( fc < -0.0 || fc > 3000 ) return;
	mEQ->setState( index, fc, g );
}

void Track::setAutoPan( BOOL isUse )
{
	mAutoPan->mIsUse = isUse;
	mAutoPan->setRate( 0.5 );
	mVolL = 0.5;
	mVolR = 0.5;
}

double Track::getPlayTime( void )
{
	return mPlayTime;
}

double* Track::getWaveData( void )
{
	return mWaveData;
}

double* Track::getPlayData( void )
{
	return mPlayData;
}
double Track::getPlayDataL( int index )
{
	return mAutoPan->applyL( mPlayData[ index ] * mVolL, mPlayTime );
}
double Track::getPlayDataR( int index )
{
	return mAutoPan->applyR( mPlayData[ index ] * mVolR, mPlayTime );
}

int Track::addEffect( int index, EffectID id )
{
	while( mIsUpdate ) {
		Sleep( 1 );
	}

	double setNum1 = 0;
	double setNum2 = 0;
	Sound::EffectBase* newEffect = 0;
	if( mEffectList[ index ] != 0 ) {
		setNum1 = mEffectList[ index ]->getNum1();
		setNum2 = mEffectList[ index ]->getNum2();
		delete mEffectList[ index ];
		mEffectList[ index ] = 0;
	}

	switch( id ) {
		case EFFECT_NOISE_GATE:
			newEffect = new Sound::NoiseGate();
			break;
		case EFFECT_DISTORTION1:
			newEffect = new Sound::Distortion1();
			break;
		case EFFECT_DISTORTION2:
			newEffect = new Sound::Distortion2();
			break;
		case EFFECT_DISTORTION3:
			newEffect = new Sound::Distortion3();
			break;
		case EFFECT_COMPRESSOR:
			newEffect = new Sound::Compressor();
			break;
		case EFFECT_TREMOLO:
			newEffect = new Sound::Tremolo();
			break;
		case EFFECT_DELAY:
			newEffect = new Sound::Delay();
			break;
		case EFFECT_CHORUS:
			newEffect = new Sound::Chorus();
			break;
		case EFFECT_VIBRATO:
			newEffect = new Sound::Vibrato();
			break;
		case EFFECT_LOW_PASS_FILTER:
			newEffect = new Sound::LowPassFilter();
			break;
		case EFFECT_HIGH_PASS_FILTER:
			newEffect = new Sound::HighPassFilter();
			break;
		case EFFECT_BAND_PASS_FILTER:
			newEffect = new Sound::BandPassFilter();
			break;
		case EFFECT_BAND_ELIMINATE_FILTER:
			newEffect = new Sound::BandEliminateFilter();
			break;
		case EFFECT_EQUALIZER:
			newEffect = new Sound::Equalizer();
			break;
		default:
			return 1;
			break;
	}
	newEffect->setNum1( setNum1 );
	newEffect->setNum2( setNum2 );
	mEffectList[ index ] = newEffect;

	return 0;
}

EffectBase* Track::getEffect( int index )
{
	if( index < 0 && index >= EFFECT_MAX_NUM ) return 0;
	return mEffectList[ index ];
}

int Track::setWave( WaveID id )
{
	mWaveID = id;
	return 0;
}


} // namespace Sound