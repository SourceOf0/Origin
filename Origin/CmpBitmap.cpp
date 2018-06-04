#include "CmpBitmap.h"
#include "PixelBitmap.h"
#include "DCBitmap.h"

namespace Image {

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

	mPixelBitmap = new Image::PixelBitmap( width, height );

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

	if( mPixelBitmap != 0 ) {
		delete mPixelBitmap;
		mPixelBitmap = 0;
	}
}

int CmpBitmap::setData( unsigned char color, unsigned int count )
{
	ColorID setColor = CLR_OTHER;
	ColorData* setData = new ColorData();

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
	mUseColor |= setColor;
	setData->color = setColor;
	setData->count = count;

	mColorData[ mSetDataNum++ ] = setData;

	return 0;
}

int CmpBitmap::drawData( HDC& hdc )
{
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
				for( unsigned int k = targetData->count - 1; k != 0xFFFFFFFF; --k ) {
					mPixelBitmap->setBlack( index );
					++index;
				}
			} else {
				for( unsigned int k = targetData->count - 1; k != 0xFFFFFFFF; --k ) {
					mPixelBitmap->setWhite( index );
					++index;
				}
			}
		}
		mLayer[ setLayerIndex++ ] = new DCBitmap( hdc, mPixelBitmap );
		targetColor = ( ColorID )( targetColor << 1 );
	}

	for( unsigned int i = 0; i < mSetDataNum; ++i ) {
		delete mColorData[ i ];
		mColorData[ i ] = 0;
	}

	delete mPixelBitmap;
	mPixelBitmap = 0;

	return 0;
}

int CmpBitmap::drawData( PixelBitmap* target )
{
	ColorData* targetData = 0; 
	unsigned int index = 0;

	for( unsigned int j = 0; j < mSetDataNum; ++j ) {
		targetData = mColorData[ j ];
		if( targetData->color == CLR_WHITE ) {
			for( unsigned int k = targetData->count - 1; k != 0xFFFFFFFF; --k ) {
				target->setWhite( index );
				++index;
			}
		} else if( targetData->color != CLR_BLACK ) {
			for( unsigned int k = targetData->count - 1; k != 0xFFFFFFFF; --k ) {
				if( index % 3 != 0 ) {
					target->setWhite( index );
				} else {
					target->setBlack( index );
				}
				++index;
			}
		} else {
			for( unsigned int k = targetData->count - 1; k != 0xFFFFFFFF; --k ) {
				target->setBlack( index );
				++index;
			}
		}
	}
	return 0;
}

void CmpBitmap::drawWindow( void )
{
	mLayer[ 1 ]->drawWindowOr( (int)( mX + 0.5 ), (int)( mY + 0.5 ) );
	mLayer[ 0 ]->drawWindowAnd( (int)( mX + 0.5 ), (int)( mY + 0.5 ) );
/*	for( int i = 2; i < mColorNum; ++ i ) {
		mLayer[ i ]->drawWindowAnd( mX + 0.5, mY + 0.5 );
	}*/
}

void CmpBitmap::drawWindow( int x, int y )
{
	mLayer[ 1 ]->drawWindowOr( x, y );
	mLayer[ 0 ]->drawWindowAnd( x, y );
/*	for( int i = 2; i < mColorNum; ++ i ) {
		mLayer[ i ]->drawWindowAnd( x, y );
	}*/
}

} // namespace Image