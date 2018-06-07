#include "RoomParent.h"
#include "RoomChild.h"
#include "Synthesizer.h"

#include "ImageFactory.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "HandManager.h"

#include "LayerData.h"
#include "DCBitmap.h"

#include "Track.h"
#include "EffectBase.h"

namespace Sequence {
namespace Room {

BOOL Synthesizer::mIsInit = FALSE;

Synthesizer::Synthesizer( HDC& hdc, Sequence::RoomParent* parent ) :
mPlayTime( 0 ),
mPlayCount( 0 ),
mTempo( 10 )
{
	Main::ImageFactory* imageFactory = Main::ImageFactory::inst();

	mBackBmp1 = ( Image::LayerData* )( imageFactory->load( hdc, "resource\\synthe.dad" ) );
	mBackBmp1->mUseAlpha = FALSE;

	mBackBmp2 = ( Image::LayerData* )( imageFactory->load( hdc, "resource\\synthe_2.dad" ) );
	mBackBmp2->mUseAlpha = FALSE;

	mPartsBmp = ( Image::LayerData* )( imageFactory->load( hdc, "resource\\synthe_parts.dad" ) );
	mPartsBmp->mUseAlpha = TRUE;

	mWaveBmp = new Image::DCBitmap( hdc, 355, 176 );
	mWaveBmp->mX = 580;
	mWaveBmp->mY = 158;
	mWaveBmp->setWhite();

	mPadBmp = imageFactory->loadDC( hdc, "resource\\synthe_pad.dad" );
	mPadBmp->mX = 581;
	mPadBmp->mY = 416;

	for( int i = 0; i < TRACK_NUM; ++i ) {
		mPlayWaveID[ i ] = WAVE_NONE;
	}

	posInit();
	padInit();
}

Synthesizer::~Synthesizer()
{
	delete mBackBmp1;
	mBackBmp1 = 0;

	delete mBackBmp2;
	mBackBmp2 = 0;

	delete mPartsBmp;
	mPartsBmp = 0;

	delete mWaveBmp;
	mWaveBmp = 0;

	delete mPadBmp;
	mPadBmp = 0;
}

#include "SynthePartsInit.h"
#include "SyntheUpdate.h"
#include "SynthePad.h"

void Synthesizer::draw( HDC& hdc, Sequence::RoomParent* parent, double depth, int fadeCount )
{
	mPartsBmp->mDepth = depth;
	mBackBmp1->mDepth = depth;
	mBackBmp2->mDepth = depth;

	if( fadeCount == 0 ) {
		mBackBmp1->drawWindow();
	} else if( fadeCount == TONE_NONE * 2 ) {
		mBackBmp2->drawWindow();
	} else if( fadeCount < TONE_NONE ) {
		mBackBmp2->drawWindow();
		mFadeBmp->copyWindow();
		Image::BitmapBase::mTone[ fadeCount - 1 ]->drawImageOr( mFadeBmp->mHdcBmp, 0, 0 );
		mBackBmp1->drawWindow();
		mFadeBmp->drawWindowAnd();
	} else {
		mBackBmp1->drawWindow();
		mFadeBmp->copyWindow();
		Image::BitmapBase::mTone[ TONE_NONE * 2 - fadeCount - 1 ]->drawImageOr( mFadeBmp->mHdcBmp, 0, 0 );
		mBackBmp2->drawWindow();
		mFadeBmp->drawWindowAnd();
	}
	
	for( int i = 0 ; i < EFFECT_FADER_NUM; ++i ) {
		mEffectFader[ i ].draw( mPartsBmp );
	}
	for( int i = 0 ; i < EQ_FADER_NUM; ++i ) {
		mEQFader[ i ].draw( mPartsBmp );
	}
	for( int i = 0 ; i < TRACK_NUM; ++i ) {
		mWaveDial[ i ].draw( mPartsBmp );
		mAutoPanButton[ i ].draw( mPartsBmp );
		mTrackButton[ i ].draw( mPartsBmp );
	}
	for( int i = 0 ; i < VOLUME_FADER_NUM; ++i ) {
		mVolumeFader[ i ].draw( mPartsBmp );
	}
	for( int i = 0 ; i < EFFECT_EQ_NUM; ++i ) {
		mEQLever[ i ].draw( mPartsBmp );
	}
	for( int i = 0 ; i < EFFECT_SELECT_NUM; ++i ) {
		mEffectDial[ i ].draw( mPartsBmp );
	}
	for( int i = 0 ; i < KEY_NUM; ++i ) {
		mKeyButton[ i ].draw( mPartsBmp );
	}
	for( int i = 0 ; i < PLAY_BUTTON_NUM; ++i ) {
		mPlayButton[ i ].draw( mPartsBmp );
	}

	mScaleDial.draw( mPartsBmp );
	
	if( parent->mIsConnectSocket ) {
		int selectTrack = getSelectTrack();
		for( int i = 0; i < TRACK_NUM; ++i ) {
			if( selectTrack == i ) continue;
			for( int j = 0 ; j < NOTE_SET_MAX_NUM; ++j ) {
				mNoteLamp[ i ][ j ].draw( mPartsBmp );
			}
		}
		for( int j = 0 ; j < NOTE_SET_MAX_NUM; ++j ) {
			mNoteLamp[ selectTrack ][ j ].draw( mPartsBmp );
			mTimeLamp[ j ].draw( mPartsBmp );
		}
	}
	for( int i = 0; i < PAD_FADER_NUM; ++i ) {
		mPadFader[ i ].draw( mPartsBmp );
	}

	if( parent->mIsConnectSocket ) mWaveBmp->drawWindowAnd();
	mPadBmp->drawWindowAnd();
}

EffectID Synthesizer::getEffectID( PartsID id )
{
	switch( id ) {
		case PARTS_SIGN_NOISE_GATE:
			return EFFECT_NOISE_GATE;
		case PARTS_SIGN_DISTORTION1:
			return EFFECT_DISTORTION1;
		case PARTS_SIGN_DISTORTION2:
			return EFFECT_DISTORTION2;
		case PARTS_SIGN_DISTORTION3:
			return EFFECT_DISTORTION3;
		case PARTS_SIGN_COMPRESSOR:
			return EFFECT_COMPRESSOR;
		case PARTS_SIGN_TREMOLO:
			return EFFECT_TREMOLO;
		case PARTS_SIGN_DELAY:
			return EFFECT_DELAY;
		case PARTS_SIGN_CHORUS:
			return EFFECT_CHORUS;
		case PARTS_SIGN_VIBRATO:
			return EFFECT_VIBRATO;
		case PARTS_SIGN_LOW_PASS_FILTER:
			return EFFECT_LOW_PASS_FILTER;
		case PARTS_SIGN_HIGH_PASS_FILTER:
			return EFFECT_HIGH_PASS_FILTER;
		case PARTS_SIGN_BAND_PASS_FILTER:
			return EFFECT_BAND_PASS_FILTER;
		case PARTS_SIGN_BAND_ELIMINATE_FILTER:
			return EFFECT_BAND_ELIMINATE_FILTER;
	}
	return EFFECT_NONE;
}

WaveID Synthesizer::getWaveID( PartsID id )
{
	switch( id ) {
		case PARTS_SIGN_CURVE:
			return WAVE_CURVE;
		case PARTS_SIGN_SAWTOOTH:
			return WAVE_SAWTOOTH;
		case PARTS_SIGN_SQUARE:
			return WAVE_SQUARE;
		case PARTS_SIGN_TRIANGLE:
			return WAVE_TRIANGLE;
	}
	return WAVE_NONE;
}

int Synthesizer::getSelectTrack( void )
{
	for( int i = 0; i < TRACK_NUM; ++i ) {
		if( mTrackButton[ i ].isOn() ) return i;
	}
	return -1;
}

double Synthesizer::getCodeRatio( int seed )
{
	int scale = mScaleDial.getSign() - PARTS_SIGN_SCALE_C;
	int scaleHalf = scale / 2;
	double ret = 0.0;

	if( seed < scaleHalf || seed > ( scaleHalf + 12 ) ) return -1.0;

	switch( seed - scaleHalf ) {
		case 0:
			ret = 0.0;
			break;
		case 1:
			ret = 0.5;
			break;
		case 2:
			ret = 1.0;
			break;
		case 3:
			ret = ( scale % 2 == 0 )? 1.5 : 2.0;
			break;
		case 4:
			ret = ( scale % 2 == 0 )? 2.0 : 2.5;
			break;
		case 5:
			ret = 3.0;
			break;
		case 6:
			ret = 3.5;
			break;
		case 7:
			ret = 4.0;
			break;
		case 8:
			ret = ( scale % 2 == 0 )? 4.5 : 5.0;
			break;
		case 9:
			ret = ( scale % 2 == 0 )? 5.0 : 5.5;
			break;
		case 10:
			ret = ( scale % 2 == 0 )? 5.5 : 6.0;
			break;
		case 11:
			ret = ( scale % 2 == 0 )? 6.0 : 6.5;
			break;
		case 12:
			ret = 7.0;
			break;
	}

	return ( 7.0 - ret );
}

double Synthesizer::getFixCodeHz( double seed )
{
	if( seed < 0.0 ) return 0.0;

	seed = NOTE_HEIGHT_NUM - 1 - seed;
	int noteIndex = static_cast< int >( seed );
	double noteRatio = seed - noteIndex;
	double ret = 0;

	if( noteIndex >= NOTE_HEIGHT_NUM ) {
		noteIndex = NOTE_HEIGHT_NUM - 1;
	}

	ret = getCodeHz( noteIndex );
	if( ( noteIndex + 1 ) < NOTE_HEIGHT_NUM ) {
		ret += ( getCodeHz( noteIndex + 1 ) - ret ) * noteRatio;
	}

	return ret;
}

double Synthesizer::getCodeHz( int seed )
{
	int scale = mScaleDial.getSign() - PARTS_SIGN_SCALE_C;
	int hzIndex = 0;

	switch( seed ) {
		case 0:
			hzIndex = 0;
			break;
		case 1:
			hzIndex = 2;
			break;
		case 2:
			hzIndex = ( ( scale ) % 2 == 0 )? 4 : 3;
			break;
		case 3:
			hzIndex = 5;
			break;
		case 4:
			hzIndex = 7;
			break;
		case 5:
			hzIndex = ( ( scale ) % 2 == 0 )? 9 : 8;
			break;
		case 6:
			hzIndex = ( ( scale ) % 2 == 0 )? 11 : 10;
			break;
		case 7:
			hzIndex = 12;
			break;
	}

	return getHz( hzIndex + static_cast< int >( scale / 2 ) );
}

#include <Math.h>
double Synthesizer::getHz( double seed )
{
	if( seed < 0 ) return 0.0;
	return pow( 2.0, ( seed - 9 ) / 12.0 ) * 440.0;
}


} // namespace Room
} // namespace Sequence