#include "Track.h"
#include "SoundBase.h"
#include "Wave.h"
#include "EffectBase.h"

namespace Sound {

Track::Track( void ) :
mPlayTime( 0 ),
mWaveID( WAVE_SAWTOOTH ),
mLogIndex( 0 )
{
	mWave = new Wave();

	mAdjWave = new double[ WAVE_DATA_LENGTH ];
	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		mAdjWave[i] = 0;
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
	delete[] mAdjWave;
	mAdjWave = 0;

	delete mWave;
	mWave = 0;

	for( int i = 0; i < EFFECT_MAX_NUM; ++i ) {
		delete mEffectList[i];
		mEffectList[i] = 0;
	}

	for( int i = 0; i < LOG_MAX_NUM; ++i ) {
		delete[] mWaveLog[i];
		mWaveLog[i] = 0;
	}
}

void Track::reset( void )
{
	mWave->reset();
	mPlayTime = 0;
	
	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		mAdjWave[i] = 0;
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

double Track::getPlayTime( void )
{
	return mPlayTime;
}

double Track::getPrevData( int prevIndex )
{
	int dataIndex = ( ( prevIndex < 0 )? -prevIndex : prevIndex ) % WAVE_DATA_LENGTH;
	int blockIndex = mLogIndex + static_cast<int>( prevIndex / WAVE_DATA_LENGTH );
	if( blockIndex < 0 ) blockIndex = LOG_MAX_NUM + blockIndex;
	return mWaveLog[ blockIndex ][ dataIndex ];
}

double* Track::getAdjWave( void )
{
	return mAdjWave;
}

double* Track::getPlayWave( void )
{
	double* ret = mAdjWave;
	mAdjWave = mWaveLog[ mLogIndex ];
	mWaveLog[ mLogIndex ] = ret;
	mLogIndex = ( mLogIndex + 1 ) % LOG_MAX_NUM;
	for( int i = 0; i < WAVE_DATA_LENGTH; ++i ) {
		mAdjWave[i] = 0;
	}
	return ret;
}

int Track::addEffect( EffectBase* newEffect )
{
	if( newEffect == 0 ) return 1;

	for( int i = 0; i < EFFECT_MAX_NUM; ++i ) {
		if( mEffectList[i] != 0 ) continue;
		mEffectList[i] = newEffect;
		return 0;
	}

	return 1;
}

int Track::setWave( WaveID id )
{
	mWaveID = id;
	return 0;
}


} // namespace Sound