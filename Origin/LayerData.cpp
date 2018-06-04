#include "LayerData.h"
#include "PixelBitmap.h"
#include "DCBitmap.h"

namespace Image {

LayerData::LayerData( HDC& hdc, unsigned int width, unsigned int height ) : 
mUseAlpha( TRUE ),
mDepth( 0.0 )
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
	int i = 1;
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
			++i;
		} else {
			mViewTone->drawWindow( x, y, startX, startY, width, height );
		}
	}
	
	for( ; i < COLOR_KIND_NUM; ++ i ) {
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
			value = ( mUseAlpha )? 0.6 : 0.7;
			break;
		case CLR_GREEN_BLUE:
			value = ( mUseAlpha )? 1.0 : 0.65;
			break;
		case CLR_BLUE_RED:
			value = ( mUseAlpha )? 0.7 : 0.6;
			break;
		case CLR_GREEN:
			value = ( mUseAlpha )? 0.65 : 0.55;
			break;
		case CLR_RED:
			value = ( mUseAlpha )? 0.6 : 0.5;
			break;
		case CLR_BLUE:
			value = ( mUseAlpha )? 0.55 : 0.45;
			break;
		case CLR_BLACK:
			value = 0.3;
			break;
	}
	if( value < 0.0 ) {
		return ( ToneID )( TONE_NONE - 1 );
	}
	value += mDepth;
	if( value > 1.0 ) value = 1.0;
	if( value < 0.0 ) value = 0.0;
	return ( ToneID )( static_cast< int >( ( 1.0 - value ) * ( TONE_NONE - 1 ) ) );
}


} // namespace Image