#include "RoomParent.h"
#include "RoomChild.h"
#include "Synthesizer.h"

#include "ImageFactory.h"
#include "SceneManager.h"
#include "SoundManager.h"

#include "LayerData.h"
#include "DCBitmap.h"

#include "Track.h"
#include "EffectBase.h"

namespace Sequence {
namespace Room {

BOOL Synthesizer::mIsInit = FALSE;

Synthesizer::Synthesizer( HDC& hdc, Sequence::RoomParent* parent )
{
	Main::ImageFactory* imageFactory = Main::ImageFactory::inst();
	int windowWidth = Main::SceneManager::windowWidth;
	int windowHeight = Main::SceneManager::windowHeight;

	mBackBmp = ( Image::LayerData* )( imageFactory->load( hdc, "resource\\synthe.dad" ) );
	mBackBmp->mUseAlpha = FALSE;

	mPartsBmp = ( Image::LayerData* )( imageFactory->load( hdc, "resource\\synthe_parts.dad" ) );
	mPartsBmp->mUseAlpha = TRUE;

	mWaveBmp = new Image::DCBitmap( hdc, 355, 176, 0xFF );
	mWaveBmp->mX = 580;
	mWaveBmp->mY = 158;

	sizeInit();
	posInit();
}

Synthesizer::~Synthesizer()
{
	delete mBackBmp;
	mBackBmp = 0;

	delete mPartsBmp;
	mPartsBmp = 0;

	delete mWaveBmp;
	mWaveBmp = 0;
}

#include "SynthePartsInit.h"
#include "SyntheUpdate.h"

void Synthesizer::draw( HDC& hdc, Sequence::RoomParent* parent )
{
	mBackBmp->drawWindow();
	
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
	viewParts( mScaleDial );
	viewSign( mScaleSign );

	mWaveBmp->drawWindowAnd();
}

void Synthesizer::viewParts( PartsData& target )
{
	PartsSize size = mPartsSize[ target.partsID ];
	mPartsBmp->drawWindow( target.x, target.y, size.startX, size.startY, size.width, size.height );
}
void Synthesizer::viewSign( PartsData& target )
{
	PartsSize size = mPartsSize[ target.partsID ];
	if( target.x < target.defX - 4 ) {
		int fixX = target.defX - 4 - target.x;
		mPartsBmp->drawWindow( target.x + fixX - size.width / 2, target.y - size.height / 2, size.startX + fixX, size.startY, size.width - fixX, size.height );
	} else if( target.x > target.defX + 5 ) {
		int fixX = target.x - target.defX - 5;
		mPartsBmp->drawWindow( target.x - size.width / 2, target.y - size.height / 2, size.startX, size.startY, size.width - fixX, size.height );
	} else {
		mPartsBmp->drawWindow( target.x - size.width / 2, target.y - size.height / 2, size.startX, size.startY, size.width, size.height );
	}
}

} // namespace Room
} // namespace Sequence