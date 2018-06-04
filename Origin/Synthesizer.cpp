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

	mX = ( windowWidth - mBackBmp1->mWidth ) / 2;
	mY = ( windowHeight - mBackBmp1->mHeight ) / 2;

	mPartsBmp = ( Image::LayerData* )( imageFactory->load( hdc, "resource\\synthe_parts.dad" ) );
	mPartsBmp->mUseAlpha = TRUE;

	mWaveBmp = new Image::DCBitmap( hdc, 355, 176, 0xFF );
	mWaveBmp->mX = 580 + mX;
	mWaveBmp->mY = 158 + mY;

	mPadBmp = imageFactory->loadDC( hdc, "resource\\synthe_pad.dad" );
	mPadBmp->mX = 581 + mX;
	mPadBmp->mY = 416 + mY;

	for( int i = 0; i < TRACK_NUM; ++i ) {
		mPlayWaveID[ i ] = WAVE_NONE;
	}

	sizeInit();
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
		viewParts( mEffectFader[ i ] );
	}
	for( int i = 0 ; i < EQ_FADER_NUM; ++i ) {
		viewParts( mEQFader[ i ] );
	}
	for( int i = 0 ; i < EFFECT_SELECT_NUM; ++i ) {
		viewSign( mEffectSign[ i ] );
	}
	for( int i = 0 ; i < TRACK_NUM; ++i ) {
		viewParts( mWaveDial[ i ] );
		viewSign( mWaveSign[ i ] );
	}
	for( int i = 0 ; i < VOLUME_FADER_NUM; ++i ) {
		viewParts( mVolumeFader[ i ] );
	}
	for( int i = 0 ; i < TRACK_NUM; ++i ) {
		viewParts( mAutoPanButton[ i ] );
		viewParts( mTrackButton[ i ] );
	}
	for( int i = 0 ; i < EFFECT_EQ_NUM; ++i ) {
		viewParts( mEQLever[ i ] );
	}
	for( int i = 0 ; i < EFFECT_SELECT_NUM; ++i ) {
		if( mEffectDial[ i ].defX == 100 ) continue;
		viewParts( mEffectDial[ i ] );
	}
	for( int i = 0 ; i < KEY_NUM; ++i ) {
		viewParts( mKeyButton[ i ] );
	}
	for( int i = 0 ; i < PLAY_BUTTON_NUM; ++i ) {
		viewParts( mPlayButton[ i ] );
		viewParts( mPlaySign[ i ] );
	}

	if( mScaleDial.defX != 100 ) {
		viewParts( mScaleDial );
	}
	viewSign( mScaleSign );
	
	int selectTrack = getSelectTrack();
	for( int i = 0; i < TRACK_NUM; ++i ) {
		if( selectTrack == i ) continue;
		for( int j = 0 ; j < NOTE_SET_MAX_NUM; ++j ) {
			if( mNoteLamp[ i ][ j ].defX == 100 ) continue;
			viewParts( mNoteLamp[ i ][ j ] );
		}
	}
	if( parent->mIsConnectSocket ) {
		for( int j = 0 ; j < NOTE_SET_MAX_NUM; ++j ) {
			if( mNoteLamp[ selectTrack ][ j ].defX == 100 ) continue;
			viewParts( mNoteLamp[ selectTrack ][ j ] );
		}
		for( int i = 0 ; i < NOTE_SET_MAX_NUM; ++i ) {
			if( mTimeLampX[ i ].defX == 100 ) continue;
			viewParts( mTimeLampX[ i ] );
		}
	}
	for( int i = 0; i < PAD_FADER_NUM; ++i ) {
		viewParts( mPadFader[ i ] );
	}

	if( parent->mIsConnectSocket ) mWaveBmp->drawWindowAnd();
	mPadBmp->drawWindowAnd();
}

void Synthesizer::viewParts( PartsData& target, BOOL isTransparent )
{
	PartsSize size = mPartsSize[ target.partsID ];
	mPartsBmp->drawWindow( mX + target.x, mY + target.y, size.startX, size.startY, size.width, size.height, isTransparent );
}
void Synthesizer::viewSign( PartsData& target )
{
	PartsSize size = mPartsSize[ target.partsID ];
	if( target.x < target.defX - 4 ) {
		int fixX = target.defX - 4 - target.x;
		mPartsBmp->drawWindow( mX + target.x + fixX - size.width / 2, mY + target.y - size.height / 2, size.startX + fixX, size.startY, size.width - fixX, size.height );
	} else if( target.x > target.defX + 5 ) {
		int fixX = target.x - target.defX - 5;
		mPartsBmp->drawWindow( mX + target.x - size.width / 2, mY + target.y - size.height / 2, size.startX, size.startY, size.width - fixX, size.height );
	} else {
		mPartsBmp->drawWindow( mX + target.x - size.width / 2, mY + target.y - size.height / 2, size.startX, size.startY, size.width, size.height );
	}
}

} // namespace Room
} // namespace Sequence