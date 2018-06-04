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

namespace Sound {

Track::Track( void ) :
mPlayTime( 0 ),
mWaveID( WAVE_SAWTOOTH ),
mUseLog( 0 )
{
	mWave = new Wave();

	mWaveData = new double[ WAVE_DATA_LENGTH ];
	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		mWaveData[i] = 0;
	}

	mPlayData = new double[ WAVE_DATA_LENGTH ];
	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		mPlayData[i] = 0;
	}

	for( int i = 0; i < LOG_MAX_INDEX_NUM; ++i ) {
		for( int j = 0; j < LOG_MAX_DATA_NUM; ++j ) {
			mWaveLog[ i ][ j ] = new double[ WAVE_DATA_LENGTH ];
		}
	}

	for( int i = 0; i < EFFECT_MAX_NUM; ++i ) {
		mEffectList[ i ] = 0;
	}
}

Track::~Track( void )
{
	delete mWave;
	mWave = 0;

	delete[] mWaveData;
	mWaveData = 0;

	delete[] mPlayData;
	mPlayData = 0;

	for( int i = 0; i < LOG_MAX_INDEX_NUM; ++i ) {
		for( int j = 0; j < LOG_MAX_DATA_NUM; ++j ) {
			delete[] mWaveLog[ i ][ j ];
			mWaveLog[ i ][ j ] = 0;
		}
	}

	for( int i = 0; i < EFFECT_MAX_NUM; ++i ) {
		delete mEffectList[ i ];
		mEffectList[ i ] = 0;
	}
}

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
}

int Track::update( void )
{
	mWave->setData( this, mWaveID );

	for( int i = 0; i < EFFECT_MAX_NUM; ++i ) {
		if( mEffectList[ i ] != 0 ) mEffectList[ i ]->apply( this );
	}

	memcpy( mPlayData, mWaveData, WAVE_DATA_LENGTH * sizeof( double ) );
	
	mPlayTime = ( mPlayTime + WAVE_DATA_LENGTH ) % ( SAMPLES_PER_SEC * 10 );

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

double* Track::getPlayData( void )
{
	return mPlayData;
}

int Track::addEffect( EffectID id )
{
	int setIndex = 0;
	char useLogIndex = 0;
	char count = 0;
	Sound::EffectBase* newEffect;

	for( setIndex = 0; setIndex < EFFECT_MAX_NUM; ++setIndex ) {
		if( mEffectList[ setIndex ] == 0 ) break;
	}
	if( setIndex == EFFECT_MAX_NUM ) return 1;

	while( ( ( mUseLog >> count ) & 1 ) == 1 ) {
		++count;
		if( count == LOG_MAX_INDEX_NUM ) {
			count = -1;
		}
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
			if( count == -1 ) return 1;
			mUseLog |= 1 << count;
			newEffect = new Sound::Delay( mWaveLog[ count ] );
			break;
		case EFFECT_CHORUS:
			if( count == -1 ) return 1;
			mUseLog |= 1 << count;
			newEffect = new Sound::Chorus( mWaveLog[ count ] );
			break;
		case EFFECT_VIBRATO:
			if( count == -1 ) return 1;
			mUseLog |= 1 << count;
			newEffect = new Sound::Vibrato( mWaveLog[ count ] );
			break;
		case EFFECT_LOW_PASS_FILTER:
			if( count == -1 ) return 1;
			mUseLog |= 1 << count;
			newEffect = new Sound::LowPassFilter( mWaveLog[ count ] );
			break;
		case EFFECT_HIGH_PASS_FILTER:
			if( count == -1 ) return 1;
			mUseLog |= 1 << count;
			newEffect = new Sound::HighPassFilter( mWaveLog[ count ] );
			break;
		case EFFECT_BAND_PASS_FILTER:
			if( count == -1 ) return 1;
			mUseLog |= 1 << count;
			newEffect = new Sound::BandPassFilter( mWaveLog[ count ] );
			break;
		case EFFECT_BAND_ELIMINATE_FILTER:
			if( count == -1 ) return 1;
			mUseLog |= 1 << count;
			newEffect = new Sound::BandEliminateFilter( mWaveLog[ count ] );
			break;
		case EFFECT_EQUALIZER:
			newEffect = new Sound::Equalizer();
			break;
		default:
			return 1;
			break;
	}
	mEffectList[ setIndex ] = newEffect;

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