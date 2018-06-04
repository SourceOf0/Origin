#include "CmpBitmap.h"
#include "PixelBitmap.h"
#include "DCBitmap.h"

namespace Image {

CmpBitmap::CmpBitmap( unsigned int width, unsigned int height, char colorNum ) :
mX( 0 ),
mY( 0 ),
mWidth( width ),
mHeight( height ),
mColorNum( colorNum ),
mUseColor( 0 ),
mFirstNode( 0 ),
mNowNode( 0 )
{
	mFirstNode = new ColorNode();
	mFirstNode->color = CLR_OTHER;
	mFirstNode->count = 0;
	mFirstNode->next = 0;
	mNowNode = mFirstNode;

	unsigned int bmpSize = width * height;
	unsigned int bitDataLeng = ( bmpSize % 32 == 0) ? bmpSize / 32 : (int)( bmpSize / 32 ) + 1;
	mPixelBitmap = new Image::PixelBitmap( width, height, bitDataLeng * 4 );

	mLayer = new DCBitmap*[ colorNum ];
	for( int i = 0; i < colorNum; ++i ) {
		mLayer[ i ] = 0;
	}
}

CmpBitmap::~CmpBitmap( void )
{
	for( int i = 0; i < mColorNum; ++i ) {
		if( mLayer[ i ] != 0 ) {
			delete mLayer[ i ];
			mLayer[ i ] = 0;
		}
	}

	delete[] mLayer;
	mLayer = 0;
}

int CmpBitmap::setData( unsigned char color, unsigned int count )
{
	ColorID setColor = CLR_OTHER;

	mNowNode->next = new ColorNode();
	mNowNode = mNowNode->next;

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
	mNowNode->color = setColor;
	mNowNode->count = count;

	return 0;
}

int CmpBitmap::drawData( HDC& hdc )
{
	ColorID targetColor = CLR_BLACK;
	unsigned int index = 0;
	int setIndex = 0;

	for( int i = 0; i < mColorNum; ++i ) {
		while( ( mUseColor & targetColor ) == 0 ) {
			targetColor = ( ColorID )( targetColor << 1 );
			continue;
		}
		index = 0;
		mNowNode = mFirstNode->next;
		while( mNowNode != 0 ) {
			if( mNowNode->color == targetColor ) {
				for( unsigned int j = mNowNode->count - 1; j != 0xFFFFFFFF; --j ) {
					mPixelBitmap->setBlack( index );
					++index;
				}
			} else {
				for( unsigned int j = mNowNode->count - 1; j != 0xFFFFFFFF; --j ) {
					mPixelBitmap->setWhite( index );
					++index;
				}
			}
			mNowNode = mNowNode->next;
		}
		mLayer[ setIndex++ ] = new DCBitmap( hdc, mPixelBitmap );
		targetColor = ( ColorID )( targetColor << 1 );
	}

	ColorNode* target = mFirstNode;

	while( target != 0 ) {
		mNowNode = target->next;
		delete target;
		target = mNowNode;
	}

	delete mPixelBitmap;
	mPixelBitmap = 0;

	return 0;
}

int CmpBitmap::drawData( PixelBitmap* target )
{
	unsigned int index = 0;

	mNowNode = mFirstNode->next;

	while( mNowNode != 0 ) {
		if( mNowNode->color == CLR_WHITE ) {
			for( unsigned int j = mNowNode->count - 1; j != 0xFFFFFFFF; --j ) {
				target->setWhite( index );
				++index;
			}
		} else if( mNowNode->color != CLR_BLACK ) {
			for( unsigned int j = mNowNode->count - 1; j != 0xFFFFFFFF; --j ) {
				if( index % 3 != 0 ) {
					target->setWhite( index );
				} else {
					target->setBlack( index );
				}
				++index;
			}
		} else {
			for( unsigned int j = mNowNode->count - 1; j != 0xFFFFFFFF; --j ) {
				target->setBlack( index );
				++index;
			}
		}
		mNowNode = mNowNode->next;
	}
	return 0;
}

int CmpBitmap::drawWindow( void )
{
	mLayer[ 1 ]->drawWindowOr( (int)( mX + 0.5 ), (int)( mY + 0.5 ) );
	mLayer[ 0 ]->drawWindowAnd( (int)( mX + 0.5 ), (int)( mY + 0.5 ) );
/*	for( int i = 2; i < mColorNum; ++ i ) {
		mLayer[ i ]->drawWindowAnd( mX + 0.5, mY + 0.5 );
	}*/
	return 0;
}


} // namespace Image