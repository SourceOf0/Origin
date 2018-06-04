#include "SceneManager.h"
#include "PixelBitmap.h"

namespace Image {

PixelBitmap::PixelBitmap( int width, int height, unsigned char setColor ) : 
mWidth( width ),
mHeight( height ),
mWidthIndex( width / 32 ),
mHeightIndex( height / 32 ),
mX( 0 ),
mY( 0 )
{
	unsigned int bmpSize = width * height;
	unsigned int bitDataLeng = ( bmpSize % 32 == 0) ? bmpSize / 32 : (int)( bmpSize / 32 ) + 1;
	mDataLeng = bitDataLeng * 4;

	for( unsigned int i = 0; i < mDataLeng; ++i ) {
		mPixelData[ i ] = setColor;
	}
}

PixelBitmap::~PixelBitmap( void )
{
}

void PixelBitmap::reset( int width, int height, unsigned char setColor )
{
	unsigned int bmpSize = width * height;
	unsigned int bitDataLeng = ( bmpSize % 32 == 0) ? bmpSize / 32 : (int)( bmpSize / 32 ) + 1;
	mDataLeng = bitDataLeng * 4;

	mWidth = width;
	mHeight = height;
	mWidthIndex = width / 32;
	mHeightIndex = height / 32;

	for( unsigned int i = 0; i < mDataLeng; ++i ) {
		mPixelData[ i ] = setColor;
	}
}

char PixelBitmap::getBit( int x, int y )
{
	if( x < 0 || y < 0 ) return 1;
	unsigned int index = ( y * mWidth + x ) / 8;
	int sift = 7 - ( y * mWidth + x ) % 8;
	if( index >= mDataLeng ) return -1;
	return ( ( mPixelData[ index ] & ( 1 << sift ) ) > 0 ) ? 1 : 0;

}

int PixelBitmap::setData( unsigned int index, unsigned char data )
{
	if( index >= mDataLeng ) {
		return 1;
	}
	mPixelData[ index ] = data;
	return 0;
}
int PixelBitmap::setBlack( int x, int y )
{
	return 0;
	if( x < 0 || y < 0 ) return 1;
	unsigned int index = ( y * mWidth + x ) / 8;
	int sift = 7 - ( y * mWidth + x ) % 8;
	if( index >= mDataLeng ) return 1;
	mPixelData[ index ] &= ~( 1 << sift );
	return 0;
}
int PixelBitmap::setBlack( unsigned int index )
{
	unsigned int dataIndex = index / 8;
	int sift = 7 - index % 8;
	if( dataIndex >= mDataLeng ) return 1;
	mPixelData[ dataIndex ] &= ~( 1 << sift );
	return 0;
}
int PixelBitmap::setWhite( int x, int y )
{
	if( x < 0 || y < 0 ) return 1;
	unsigned int index = ( y * mWidth + x ) / 8;
	int sift = 7 - ( y * mWidth + x ) % 8;
	if( index >= mDataLeng ) return 1;
	mPixelData[ index ] |= 1 << sift;
	return 0;
}
int PixelBitmap::setWhite( unsigned int index )
{
	unsigned int dataIndex = index / 8;
	int sift = 7 - index % 8;
	if( dataIndex >= mDataLeng ) return 1;
	mPixelData[ dataIndex ] |= 1 << sift;
	return 0;
}
int PixelBitmap::setRev( int x, int y )
{
	if( x < 0 || y < 0 ) return 1;
	unsigned int index = ( y * mWidth + x ) / 8;
	int sift = 7 - ( y * mWidth + x ) % 8;
	if( index >= mDataLeng ) return 1;
	mPixelData[index] ^= ( 1 << sift );
	return 0;
}

/*
int PixelBitmap::drawWindow( void )
{
	Main::SceneManager* sceneManager = Main::SceneManager::inst();
	int width = sceneManager->mWindowWidth;
	int height = sceneManager->mWindowHeight;
	LPDWORD windowPixelData = sceneManager->mWindowPixel;

	if(mX >= width) return 0;

	int fixWidth = width / 32;
	int maxIndex = width * height / 32;
	int k = fixWidth * (int)( mY + 0.5 ) + (int)( mX + 0.5 ) / 32;
	if( k >= maxIndex ) return 0;

	unsigned int setData = 0;
	int dataLeng = mDataLeng / 4;
	int sift = (int)( mX + 0.5 ) % 32;
	int siftRev = 32 - sift;
	int addWidth = fixWidth - mWidthIndex;
	int cutWidth = width - (int)( mX );
	if( cutWidth > mWidth ) {
		cutWidth = 0;
	} else {
		cutWidth = cutWidth / 32;
	}

	if( sift == 0 ) {
		for( int i = 0; i < dataLeng; ++i ) {
			if( i % mWidthIndex == 0 && i != 0) k += addWidth;
			if( k >= maxIndex ) break;
			if( cutWidth != 0 && i % (int)( mWidth / 32 ) >= cutWidth ) {
				++k;
				continue;
			}
			if( k < 0 ) continue;
			setData = mPixelData[ i*4 ];
			setData |= mPixelData[ i*4 + 1 ] << 8;
			setData |= mPixelData[ i*4 + 2 ] << 16;
			setData |= mPixelData[ i*4 + 3 ] << 24;
			windowPixelData[ k++ ] = setData;
		}
		return 0;
	}

	setData = windowPixelData[ k ];
	unsigned char setData1 = setData & 0x000000FF;;
	unsigned char setData2 = setData >> 8 & 0x0000FFFF;
	unsigned char setData3 = setData >> 16 & 0x00FFFFFF;
	unsigned char setData4 = setData >> 24;
	unsigned int nowData = 0xFFFFFFFF;
	unsigned int oldData = ( setData4 | setData3 << 8 | setData2 << 16 | setData1 << 24 ) << siftRev;

	for( int i = 0; i < dataLeng; ++i ) {
		if( cutWidth != 0 && i % ( mWidth / 32 ) > cutWidth ) {
			++k;
			continue;
		}
		if( i % mWidthIndex == 0 ) {
			if( k >= maxIndex ) break;
			nowData = windowPixelData[ k ];
			setData1 = nowData & 0x000000FF;
			setData2 = nowData >> 8 & 0x0000FFFF;
			setData3 = nowData >> 16 & 0x00FFFFFF;
			setData4 = nowData >> 24;
			setData = ( setData4 | setData3 << 8 | setData2 << 16 | setData1 << 24 ) >> sift | oldData;
			setData1 = setData & 0x000000FF;
			setData2 = setData >> 8 & 0x0000FFFF;
			setData3 = setData >> 16 & 0x00FFFFFF;
			setData4 = setData >> 24;
			if( cutWidth == 0 ) windowPixelData[ k ] = setData4 | setData3 << 8 | setData2 << 16 | setData1 << 24;
			if( i != 0 ) k += addWidth;
			if( k >= maxIndex ) break;
			nowData = windowPixelData[ k ];
			setData1 = nowData & 0x000000FF;
			setData2 = nowData >> 8 & 0x0000FFFF;
			setData3 = nowData >> 16 & 0x00FFFFFF;
			setData4 = nowData >> 24;
			oldData = ( setData4 | setData3 << 8 | setData2 << 16 | setData1 << 24 ) << siftRev;
		}
		nowData = mPixelData[ i*4 ] << 24;
		nowData |= mPixelData[ i*4 + 1 ] << 16;
		nowData |= mPixelData[ i*4 + 2 ] << 8;
		nowData |= mPixelData[ i*4 + 3 ];
		setData = nowData >> sift | oldData;
		if( setData != 0xFFFFFFFF ) {
			setData = setData;
		}
		setData1 = setData & 0x000000FF;
		setData2 = setData >> 8 & 0x0000FFFF;
		setData3 = setData >> 16 & 0x00FFFFFF;
		setData4 = setData >> 24;
		windowPixelData[ k++ ] = setData4 | setData3 << 8 | setData2 << 16 | setData1 << 24;
		oldData = nowData << siftRev;
	}
	if( k >= maxIndex ) return 0;
	if( cutWidth != 0 ) return 0;
	nowData = windowPixelData[ k ];
	setData1 = nowData & 0x000000FF;
	setData2 = nowData >> 8 & 0x0000FFFF;
	setData3 = nowData >> 16 & 0x00FFFFFF;
	setData4 = nowData >> 24;
	setData = ( setData4 | setData3 << 8 | setData2 << 16 | setData1 << 24 ) >> sift | oldData;
	setData1 = setData & 0x000000FF;
	setData2 = setData >> 8 & 0x0000FFFF;
	setData3 = setData >> 16 & 0x00FFFFFF;
	setData4 = setData >> 24;
	windowPixelData[ k ] = setData4 | setData3 << 8 | setData2 << 16 | setData1 << 24;
	return 0;
}
*/

} // namespace Image

