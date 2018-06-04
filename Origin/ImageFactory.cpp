#include "ImageFactory.h"
#include "PixelBitmap.h"

#include <iostream>
#include <fstream>
using namespace std;

namespace Main {

ImageFactory* ImageFactory::mInst = 0;

ImageFactory* ImageFactory::inst( void )
{
	return mInst;
}
void ImageFactory::create( void )
{
	if( mInst == 0 ) {
		mInst = new ImageFactory();
	}
}
void ImageFactory::destroy( void )
{
	if( mInst != 0 ) {
		delete mInst;
		mInst = 0;
	}
}

ImageFactory::ImageFactory()
{
}
ImageFactory::~ImageFactory()
{
}

Image::PixelBitmap* ImageFactory::load( const char* fileName )
{
	unsigned int setData;
	int bmpWidth, bmpHeight, bmpSize, dataLeng, bitDataLeng;
	unsigned char ver, color;
	Image::PixelBitmap* ret;

	ifstream fin( fileName, ios::in | ios::binary );

    if( !fin ) return NULL;

	fin.read( ( char* )&bmpWidth, sizeof( int ) );
	fin.read( ( char* )&bmpHeight, sizeof( int ) );
	fin.read( ( char* )&dataLeng, sizeof( int ) );
	fin.read( ( char* )&ver, sizeof( char ) );
	fin.read( ( char* )&color, sizeof( char ) );
	fin.seekg( 2, ios_base::cur );

	bmpSize = bmpWidth * bmpHeight;
	bitDataLeng = ( bmpSize % 32 == 0) ? bmpSize / 32 : (int)( bmpSize / 32 ) + 1;
	ret = new Image::PixelBitmap( bmpWidth, bmpHeight, bitDataLeng * 4 );

	if( ver == 0 ) {
		for( int i = 0; i < bitDataLeng; ++i ) {
			fin.read( ( char * )&setData, sizeof( char ) );
			ret->setData( i*4, setData );
			fin.read( ( char * )&setData, sizeof( char ) );
			ret->setData( i*4 + 1, setData );
			fin.read( ( char * )&setData, sizeof( char ) );
			ret->setData( i*4 + 2, setData );
			fin.read( ( char * )&setData, sizeof( char ) );
			ret->setData( i*4 + 3, setData );
		}
	} else if( ver == 1 ) {
		unsigned int count = 0;
		unsigned int index = 0;
		int width = ret->mWidth;
		int height = ret->mHeight;
		char color = 0;
		for( int i = 0; i < dataLeng; ++i ) {
			fin.read( ( char * )&setData, sizeof( unsigned int ) );
			count = setData & 0x0FFFFFFF;
			color = setData >> 28;
			if( color == 1 ) {
				for( unsigned int j = 0; j < count; ++j ) {
					ret->setWhite( index );
					++index;
				}
			} else {
				index += count;
			}
		}
	}

	fin.close();  //ƒtƒ@ƒCƒ‹‚ð•Â‚¶‚é

	return ret;
}


} // namespace Main
