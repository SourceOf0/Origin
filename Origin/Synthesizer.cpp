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
	int windowWidth = Main::SceneManager::windowWidth;
	int windowHeight = Main::SceneManager::windowHeight;

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


} // namespace Room
} // namespace Sequence