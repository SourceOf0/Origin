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
	unsigned int bitDataLeng = ( bmpSize % 32 == 0 ) ? bmpSize / 32 : static_cast< int >( bmpSize / 32 ) + 1;
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
	unsigned int bitDataLeng = ( bmpSize % 32 == 0 ) ? bmpSize / 32 : static_cast< int >( bmpSize / 32 ) + 1;
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

} // namespace Image

