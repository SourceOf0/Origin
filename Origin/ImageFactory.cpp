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

Common::PixelBitmap* ImageFactory::load( const char* outfile )
{
	unsigned char setData;
	int i = 0;
	int bmpWidth, bmpHeight, pixelDataLeng;

	ifstream fin( outfile, ios::in | ios::binary );

    if(!fin) return NULL;

	fin.read( ( char* )&bmpWidth, sizeof( int ) );
	fin.read( ( char* )&bmpHeight, sizeof( int ) );
	fin.read( ( char* )&pixelDataLeng, sizeof( int ) );
	fin.seekg( 4, ios_base::cur ); // reserved
	
	Common::PixelBitmap* ret = new Common::PixelBitmap( bmpWidth, bmpHeight, pixelDataLeng * 4 );

	for( i = 0; i < pixelDataLeng; ++i ) {
		fin.read( ( char * )&setData, sizeof( char ) );
		ret->setData( i*4, setData );
		fin.read( ( char * )&setData, sizeof( char ) );
		ret->setData( i*4 + 1, setData );
		fin.read( ( char * )&setData, sizeof( char ) );
		ret->setData( i*4 + 2, setData );
		fin.read( ( char * )&setData, sizeof( char ) );
		ret->setData( i*4 + 3, setData );
	}
	fin.close();  //ƒtƒ@ƒCƒ‹‚ð•Â‚¶‚é

	return ret;
}


} // namespace Main
