#include <iostream>
using namespace std;

#include "MonoData.h"

MonoData::MonoData( int width, int height ) :
mFixWidth( 0 ),
mWidthCount( 0 )
{
	init( width, height );

	mArrLeng = ( mBmpSize % 32 == 0) ? mBmpSize / 32 : (int)( mBmpSize / 32 ) + 1;
	mPixelData = new unsigned int[ mArrLeng ];
	for ( unsigned int i = 0; i < mArrLeng; ++i ) {
		mPixelData[i] = 0xFFFFFFFF;
	}
}

MonoData::~MonoData( void )
{
	if( mPixelData != 0 ) {
		delete mPixelData;
		mPixelData = 0;
	}
}

void MonoData::setData( unsigned int data, unsigned int index )
{
	ColorID color = checkColor( data );

	if( index % mWidth == 0 ) {
		++mWidthCount;
		mFixWidth = mWidth * mWidthCount;
	}

	if( color == CLR_BLACK ) {
		setPixel( mBmpSize - mFixWidth + ( index % mWidth ) );
	}
}

void MonoData::setPixel( unsigned int i )
{
	unsigned int fixIndex = i / 32;
	unsigned int setBitPos = 32 - (i % 32 + 1);
	unsigned int mask = 0xFFFFFFFF;
	int type = setBitPos / 8;

	if( fixIndex >= mArrLeng ) return;

	switch( type ) {
		case 0:
			setBitPos -= 8;
			break;
		case 1:
			setBitPos -= 24;
			break;
		case 2:
			setBitPos += 24;
			break;
		case 3:
			setBitPos += 8;
			break;
	}
	
	mPixelData[ fixIndex ] &= mask ^ ( 1 << setBitPos );
}

