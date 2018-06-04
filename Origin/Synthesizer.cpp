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

	mBackBmp = ( Image::LayerData* )( imageFactory->load( hdc, "resource\\synthe.dad" ) );
	mBackBmp->mUseAlpha = FALSE;

	mX = ( windowWidth - mBackBmp->mWidth ) / 2;
	mY = ( windowHeight - mBackBmp->mHeight ) / 2;

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
	delete mBackBmp;
	mBackBmp = 0;

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

void Synthesizer::draw( HDC& hdc, Sequence::RoomParent* parent )
{
	mBackBmp->drawWindow( mX, mY );
	
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
	
	for( int i = 0 ; i < TRACK_NUM; ++i ) {
		for( int j = 0 ; j < NOTE_SET_MAX_NUM; ++j ) {
			if( mNoteLamp[ i ][ j ].defX == 100 ) continue;
			viewParts( mNoteLamp[ i ][ j ] );
		}
	}
	for( int i = 0 ; i < NOTE_SET_MAX_NUM; ++i ) {
		if( mTimeLampX[ i ].defX == 100 ) continue;
		viewParts( mTimeLampX[ i ] );
	}
	for( int i = 0; i < PAD_FADER_NUM; ++i ) {
		viewParts( mPadFader[ i ] );
	}

	mWaveBmp->drawWindowAnd();
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