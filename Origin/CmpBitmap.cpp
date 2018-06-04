#include "CmpBitmap.h"
#include "PixelBitmap.h"
#include "DCBitmap.h"

namespace Image {

DCBitmap** CmpBitmap::mTone = 0;

CmpBitmap::CmpBitmap( unsigned int width, unsigned int height, char colorNum, unsigned int dataNum ) :
mColorNum( colorNum ),
mMaxDataNum( dataNum ),
mSetDataNum( 0 )
{
	init( width, height );

	mColorData = new ColorData*[ dataNum ];
	for( unsigned int i = 0; i < dataNum; ++i ) {
		mColorData[ i ] = 0;
	}

	mLayer = new DCBitmap*[ colorNum ];
	for( int i = 0; i < colorNum; ++i ) {
		mLayer[ i ] = 0;
	}
}

CmpBitmap::~CmpBitmap( void )
{
	for( int i = 0; i < mColorNum; ++i ) {
		delete mLayer[ i ];
		mLayer[ i ] = 0;
	}

	delete[] mLayer;
	mLayer = 0;

	for( unsigned int i = 0; i < mSetDataNum; ++i ) {
		if( mColorData[ i ] != 0 ) {
			delete mColorData[ i ];
			mColorData[ i ] = 0;
		}
	}

	delete[] mColorData;
	mColorData = 0;
}

ColorID CmpBitmap::getColor( unsigned char color )
{
	ColorID setColor = CLR_OTHER;

	switch( color ) {
		case 0:
			setColor = CLR_BLACK;
			break;
		case 1:
			setColor = CLR_WHITE;
			break;
		case 2:
			setColor = CLR_RED;
			break;
		case 3:
			setColor = CLR_RED_GREEN;
			break;
		case 4:
			setColor = CLR_GREEN;
			break;
		case 5:
			setColor = CLR_GREEN_BLUE;
			break;
		case 6:
			setColor = CLR_BLUE;
			break;
		case 7:
			setColor = CLR_BLUE_RED;
			break;
		case 8:
			setColor = CLR_OTHER;
			break;
	}

	return setColor;
}

unsigned int CmpBitmap::setBlack( PixelBitmap* target, unsigned int count, unsigned int index )
{
	for( unsigned int i = count - 1; i != 0xFFFFFFFF; --i ) {
		target->setBlack( index );
		++index;
	}
	return count;
}

unsigned int CmpBitmap::setWhite( PixelBitmap* target, unsigned int count, unsigned int index )
{
	for( unsigned int i = count - 1; i != 0xFFFFFFFF; --i ) {
		target->setWhite( index );
		++index;
	}
	return count;
}

unsigned int CmpBitmap::setTone( PixelBitmap* target, unsigned int count, unsigned int index )
{
	for( unsigned int i = count - 1; i != 0xFFFFFFFF; --i ) {
		if( index % 3 != 0 ) {
			target->setWhite( index );
		} else {
			target->setBlack( index );
		}
		++index;
	}
	return count;
}

void CmpBitmap::setData( unsigned char color, unsigned int count )
{
	ColorData* setData = new ColorData();
	ColorID setColor = getColor( color );

	mUseColor |= setColor;
	setData->color = setColor;
	setData->count = count;

	mColorData[ mSetDataNum++ ] = setData;
}

DCBitmap* CmpBitmap::getDCBitmap( HDC& hdc )
{
	PixelBitmap* target = new Image::PixelBitmap( mWidth, mHeight );
	DCBitmap* ret = 0;
	ColorData* targetData = 0; 
	unsigned int index = 0;

	for( unsigned int j = 0; j < mSetDataNum; ++j ) {
		targetData = mColorData[ j ];
		if( targetData->color == CLR_BLACK ) {
			index += setBlack( target, targetData->count, index );
		} else {
			index += setWhite( target, targetData->count, index );
		}
	}

	for( unsigned int i = 0; i < mSetDataNum; ++i ) {
		delete mColorData[ i ];
		mColorData[ i ] = 0;
	}

	ret = new DCBitmap( hdc, target );

	delete target;
	target = 0;

	return ret;
}

void CmpBitmap::drawData( HDC& hdc )
{
	PixelBitmap* target = new Image::PixelBitmap( mWidth, mHeight );
	ColorID targetColor = CLR_BLACK;
	ColorData* targetData = 0; 
	unsigned int index = 0;
	int setLayerIndex = 0;

	for( int i = 0; i < mColorNum; ++i ) {
		while( ( mUseColor & targetColor ) == 0 ) {
			targetColor = ( ColorID )( targetColor << 1 );
			continue;
		}
		index = 0;
		for( unsigned int j = 0; j < mSetDataNum; ++j ) {
			targetData = mColorData[ j ];
			if( targetData->color == targetColor ) {
				index += setBlack( target, targetData->count, index );
			} else {
				index += setWhite( target, targetData->count, index );
			}
		}
		mLayer[ setLayerIndex++ ] = new DCBitmap( hdc, target );

		switch( targetColor ) {
			case CLR_RED:
				mTone[ TONE_001 ]->drawBlockOr( mLayer[ i ]->mHdcBmp, 0, 0, mWidth, 0 );
				break;
			case CLR_RED_GREEN:
				mTone[ TONE_001 ]->drawBlockOr( mLayer[ i ]->mHdcBmp, 0, 0, mWidth, 0 );
				break;
			case CLR_GREEN:
				mTone[ TONE_003 ]->drawBlockOr( mLayer[ i ]->mHdcBmp, 0, 0, mWidth, 0 );
				break;
			case CLR_GREEN_BLUE:
				mTone[ TONE_008 ]->drawBlockOr( mLayer[ i ]->mHdcBmp, 0, 0, mWidth, 0 );
				break;
			case CLR_BLUE:
				mTone[ TONE_013 ]->drawBlockOr( mLayer[ i ]->mHdcBmp, 0, 0, mWidth, 0 );
				break;
			case CLR_BLUE_RED:
				mTone[ TONE_015 ]->drawBlockOr( mLayer[ i ]->mHdcBmp, 0, 0, mWidth, 0 );
				break;
		}

		targetColor = ( ColorID )( targetColor << 1 );
	}

	for( unsigned int i = 0; i < mSetDataNum; ++i ) {
		delete mColorData[ i ];
		mColorData[ i ] = 0;
	}

	delete target;
	target = 0;
}

void CmpBitmap::drawWindow( void )
{
	mLayer[ 1 ]->drawWindowOr( static_cast< int >( mX + 0.5 ), static_cast< int >( mY + 0.5 ) );
	for( int i = 2; i < mColorNum; ++ i ) {
		mLayer[ i ]->drawWindowAnd( static_cast< int >( mX + 0.5 ), static_cast< int >( mY + 0.5 ) );
	}
	mLayer[ 0 ]->drawWindowAnd( static_cast< int >( mX + 0.5 ), static_cast< int >( mY + 0.5 ) );
}

void CmpBitmap::drawWindow( int x, int y )
{
	mLayer[ 1 ]->drawWindowOr( x, y );
/*	for( int i = 2; i < mColorNum; ++ i ) {
		mLayer[ i ]->drawWindowAnd( x, y );
	}*/
	mLayer[ 0 ]->drawWindowAnd( x, y );
}

} // namespace Image