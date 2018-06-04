#include "LayerData.h"
#include "PixelBitmap.h"
#include "DCBitmap.h"

namespace Image {

LayerData::LayerData( HDC& hdc, unsigned int width, unsigned int height )
{
	init( width, height );

	for( int i = 0; i < COLOR_KIND_NUM; ++i ) {
		mLayer[ i ] = 0;
	}
	mViewTone = new DCBitmap( hdc, width, height );
}

LayerData::~LayerData( void )
{
	for( int i = 0; i < COLOR_KIND_NUM; ++i ) {
		if( mLayer[ i ] == 0 ) continue;
		delete mLayer[ i ];
		mLayer[ i ] = 0;
	}
	delete mViewTone;
	mViewTone = 0;
}

void LayerData::drawWindow( void )
{
	ToneID setTone = TONE_NONE;
	mLayer[ 1 ]->drawWindowOr( static_cast< int >( mX + 0.5 ), static_cast< int >( mY + 0.5 ) );

	for( int i = 2; i < COLOR_KIND_NUM; ++ i ) {
		if( mLayer[ i ] == 0 ) continue;
		mViewTone->setBlack();
		mLayer[ i ]->drawBlock( mViewTone->mHdcBmp, 0, 0, mWidth, 0 );
		switch( 1 << i ) {
			case CLR_RED:
			case CLR_RED_GREEN:
				setTone = TONE_001;
				break;
			case CLR_GREEN:
				setTone = TONE_003;
				break;
			case CLR_GREEN_BLUE:
				setTone = TONE_008;
				break;
			case CLR_BLUE:
				setTone = TONE_013;
				break;
			case CLR_BLUE_RED:
				setTone = TONE_015;
				break;
		}
		mTone[ setTone ]->drawBlockOr( mViewTone->mHdcBmp, 0, 0, mWidth, 0 );
		mViewTone->drawWindowAnd( static_cast< int >( mX + 0.5 ), static_cast< int >( mY + 0.5 ) );
	}

	mLayer[ 0 ]->drawWindowAnd( static_cast< int >( mX + 0.5 ), static_cast< int >( mY + 0.5 ) );
}

void LayerData::drawWindow( int x, int y )
{
	ToneID setTone = TONE_NONE;
	mLayer[ 1 ]->drawWindowOr( x, y );

	for( int i = 2; i < COLOR_KIND_NUM; ++ i ) {
		if( mLayer[ i ] == 0 ) continue;
		mViewTone->setBlack();
		mLayer[ i ]->drawBlock( mViewTone->mHdcBmp, 0, 0, mWidth, 0 );
		switch( 1 << i ) {
			case CLR_RED:
			case CLR_RED_GREEN:
				setTone = TONE_001;
				break;
			case CLR_GREEN:
				setTone = TONE_003;
				break;
			case CLR_GREEN_BLUE:
				setTone = TONE_008;
				break;
			case CLR_BLUE:
				setTone = TONE_013;
				break;
			case CLR_BLUE_RED:
				setTone = TONE_015;
				break;
		}
		mTone[ setTone ]->drawBlockOr( mViewTone->mHdcBmp, 0, 0, mWidth, 0 );
		mViewTone->drawWindowAnd( x, y );
	}

	mLayer[ 0 ]->drawWindowAnd( x, y );
}

void LayerData::drawDCBitmap( DCBitmap* target, int x, int y, int width, int index )
{
	ToneID setTone = TONE_NONE;
	mLayer[ 1 ]->drawBlockOr( target->mHdcBmp, x, y, width, index );

	for( int i = 2; i < COLOR_KIND_NUM; ++ i ) {
		if( mLayer[ i ] == 0 ) continue;
		mViewTone->setBlack();
		mLayer[ i ]->drawBlock( mViewTone->mHdcBmp, 0, 0, mWidth, 0 );
		switch( 1 << i ) {
			case CLR_RED:
			case CLR_RED_GREEN:
				setTone = TONE_001;
				break;
			case CLR_GREEN:
				setTone = TONE_003;
				break;
			case CLR_GREEN_BLUE:
				setTone = TONE_008;
				break;
			case CLR_BLUE:
				setTone = TONE_013;
				break;
			case CLR_BLUE_RED:
				setTone = TONE_015;
				break;
		}
		mTone[ setTone ]->drawBlockOr( mViewTone->mHdcBmp, 0, 0, mWidth, 0 );
		mViewTone->drawBlockAnd( target->mHdcBmp, x, y, width, index );
	}

//	mLayer[ 0 ]->drawBlockAnd( target->mHdcBmp, x, y, width, index );
}


} // namespace Image