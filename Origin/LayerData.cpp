#include "LayerData.h"
#include "PixelBitmap.h"
#include "DCBitmap.h"

namespace Image {

LayerData::LayerData( HDC& hdc, unsigned int width, unsigned int height ) : 
mUseAlpha( TRUE )
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
	drawWindow( static_cast< int >( mX ), static_cast< int >( mY ) );
}

void LayerData::drawWindow( int x, int y )
{
	drawWindow( x, y, 0, 0, mWidth, mHeight );
}

void LayerData::drawWindow( int x, int y, int startX, int startY, int width, int height, BOOL isTransparent )
{
	if( !isTransparent ) {
		mViewTone->setWhite( x, y, width, height );
		if( mUseAlpha ) {
			if( mLayer[ 1 ] != 0 ) {
				mLayer[ 1 ]->drawImage( mViewTone->mHdcBmp, 0, 0, startX, startY, width, height );
			}
			if( mLayer[ 3 ] != 0 ) {
				mLayer[ 3 ]->drawImageAnd( mViewTone->mHdcBmp, 0, 0, startX, startY, width, height );
			}
			mViewTone->drawWindowOr( x, y, 0, 0, width, height );
		} else {
			mViewTone->drawWindow( x, y, startX, startY, width, height );
		}
	}
	
	for( int i = 2; i < COLOR_KIND_NUM; ++ i ) {
		if( mLayer[ i ] == 0 ) continue;
		mViewTone->setBlack( x, y, width, height );
		mLayer[ i ]->drawImage( mViewTone->mHdcBmp, 0, 0, startX, startY, width, height );
		mTone[ getToneID( i ) ]->drawImageOr( mViewTone->mHdcBmp, 0, 0, x, y, width, height );
		mViewTone->drawWindowAnd( x, y, 0, 0, width, height );
	}
	mLayer[ 0 ]->drawWindowAnd( x, y, startX, startY, width, height );
}

void LayerData::drawDCBitmap( DCBitmap* target, int x, int y, int width, int index )
{
	mLayer[ 0 ]->drawBlock( target->mHdcBmp, x, y, width, index );
}

ToneID LayerData::getToneID( int index )
{
	double value = 0;

	switch( 1 << index ) {
		case CLR_WHITE:
			value = ( mUseAlpha )? -1 : 1.0;
			break;
		case CLR_RED_GREEN:
			value = ( mUseAlpha )? 0.7 : 0.9;
			break;
		case CLR_GREEN_BLUE:
			value = ( mUseAlpha )? 1.0 : 0.8;
			break;
		case CLR_BLUE_RED:
			value = ( mUseAlpha )? 0.9 : 0.7;
			break;
		case CLR_GREEN:
			value = ( mUseAlpha )? 0.8 : 0.5;
			break;
		case CLR_RED:
			value = ( mUseAlpha )? 0.7 : 0.3;
			break;
		case CLR_BLUE:
			value = ( mUseAlpha )? 0.5 : 0.2;
			break;
		case CLR_BLACK:
			value = 0.0;
			break;
	}
	if( value < 0 ) {
		return TONE_015;
	}
	return ( ToneID )( static_cast< int >( ( 1.0 - value ) * ( TONE_NONE - 1 ) ) );
}


} // namespace Image