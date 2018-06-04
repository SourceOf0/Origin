#include "Track.h"
#include "SoundBase.h"
#include "Wave.h"
#include "EffectBase.h"

#include "Distortion1.h"
#include "Distortion2.h"
#include "Distortion3.h"
#include "Compressor.h"
#include "Tremolo.h"
#include "Delay.h"
#include "Chorus.h"

namespace Sound {

Track::Track( void ) :
mPlayTime( 0 ),
mWaveID( WAVE_SAWTOOTH )
{
	mWave = new Wave();

	mWaveData = new double[ WAVE_DATA_LENGTH ];
	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		mWaveData[i] = 0;
	}

	for( int i = 0; i < LOG_MAX_NUM; ++i ) {
		mWaveLog[i] = new double[ WAVE_DATA_LENGTH ];
		for( int j = 0; j < WAVE_DATA_LENGTH; ++j ) {
			mWaveLog[i][j] = 0;
		}
	}

	for( int i = 0; i < EFFECT_MAX_NUM; ++i ) {
		mEffectList[i] = 0;
	}
}

Track::~Track( void )
{
	delete mWave;
	mWave = 0;

	delete[] mWaveData;
	mWaveData = 0;

	for( int i = 0; i < LOG_MAX_NUM; ++i ) {
		delete[] mWaveLog[i];
		mWaveLog[i] = 0;
	}

	for( int i = 0; i < EFFECT_MAX_NUM; ++i ) {
		delete mEffectList[i];
		mEffectList[i] = 0;
	}
}

void Track::reset( void )
{
	mWave->reset();
	mPlayTime = 0;
	
	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		mWaveData[i] = 0;
	}

	for( int i = 0; i < LOG_MAX_NUM; ++i ) {
		for( int j = 0; j < WAVE_DATA_LENGTH; ++j ) {
			mWaveLog[i][j] = 0;
		}
	}

	for( int i = 0; i < EFFECT_MAX_NUM; ++i ) {
		if( mEffectList[i] != 0 ) mEffectList[i]->reset();
	}
}

int Track::update( void )
{
	mWave->setData( this , mWaveID );

	for( int i = 0; i < EFFECT_MAX_NUM; ++i ) {
		if( mEffectList[i] != 0 ) mEffectList[i]->apply( this );
	}

	mPlayTime += WAVE_DATA_LENGTH;
	if( mPlayTime >= SAMPLES_PER_SEC ) mPlayTime -= SAMPLES_PER_SEC; 

	return 0;
}

void Track::setF( double f )
{
	mWave->setF( f );
}

int Track::getPlayTime( void )
{
	return mPlayTime;
}

double* Track::getWaveData( void )
{
	return mWaveData;
}

int Track::addEffect( EffectID id )
{
	int setIndex = 0;
	Sound::EffectBase* newEffect;

	for( setIndex = 0; setIndex < EFFECT_MAX_NUM; ++setIndex ) {
		if( mEffectList[setIndex] == 0 ) break;
	}
	if( setIndex == EFFECT_MAX_NUM ) return 1;

	switch( id ) {
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
			newEffect = new Sound::Delay( mWaveLog );
			break;
		case EFFECT_CHORUS:
			newEffect = new Sound::Chorus( mWaveLog );
			break;
		default:
			return 1;
			break;
	}
	mEffectList[setIndex] = newEffect;

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