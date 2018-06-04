#include "ImageFactory.h"

#include "DCBitmap.h"
#include "PixelBitmap.h"
#include "CmpBitmap.h"

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

Image::DCBitmap* ImageFactory::loadDC( HDC& hdc, const char* fileName )
{
	unsigned int setData;
	int bmpWidth, bmpHeight, bmpSize, dataLeng, bitDataLeng;
	unsigned char ver, colorNum;
	Image::PixelBitmap* pixelData;
	Image::DCBitmap* ret;

	ifstream fin( fileName, ios::in | ios::binary );

    if( !fin ) return NULL;

	fin.read( ( char* )&bmpWidth, sizeof( int ) );
	fin.read( ( char* )&bmpHeight, sizeof( int ) );
	fin.read( ( char* )&dataLeng, sizeof( int ) );
	fin.read( ( char* )&ver, sizeof( char ) );
	fin.read( ( char* )&colorNum, sizeof( char ) );
	fin.seekg( 2, ios_base::cur );

	bmpSize = bmpWidth * bmpHeight;
	bitDataLeng = ( bmpSize % 32 == 0) ? bmpSize / 32 : (int)( bmpSize / 32 ) + 1;
	pixelData = new Image::PixelBitmap( bmpWidth, bmpHeight, bitDataLeng * 4 );

	if( ver == 0 ) {
		for( int i = 0; i < bitDataLeng; ++i ) {
			fin.read( ( char * )&setData, sizeof( char ) );
			pixelData->setData( i*4, setData );
			fin.read( ( char * )&setData, sizeof( char ) );
			pixelData->setData( i*4 + 1, setData );
			fin.read( ( char * )&setData, sizeof( char ) );
			pixelData->setData( i*4 + 2, setData );
			fin.read( ( char * )&setData, sizeof( char ) );
			pixelData->setData( i*4 + 3, setData );
		}
	} else if( ver == 1 ) {
		Image::CmpBitmap* loadData = new Image::CmpBitmap( bmpWidth, bmpHeight, colorNum );
		
		for( int i = 0; i < dataLeng; ++i ) {
			fin.read( ( char * )&setData, sizeof( unsigned int ) );
			loadData->setData( (ColorID)( setData >> 28 ), setData & 0x0FFFFFFF );
		}
		loadData->drawData( pixelData );

		delete loadData;
		loadData = 0;
	}

	fin.close();  //ファイルを閉じる

	ret = new Image::DCBitmap( hdc, pixelData );

	delete pixelData;
	pixelData = 0;

	return ret;
}

Image::CmpBitmap* ImageFactory::loadCmp( HDC& hdc, const char* fileName )
{
	unsigned int setData;
	int bmpWidth, bmpHeight, bmpSize, dataLeng, bitDataLeng;
	unsigned char ver, colorNum;
	Image::CmpBitmap* ret;

	ifstream fin( fileName, ios::in | ios::binary );

    if( !fin ) return NULL;

	fin.read( ( char* )&bmpWidth, sizeof( int ) );
	fin.read( ( char* )&bmpHeight, sizeof( int ) );
	fin.read( ( char* )&dataLeng, sizeof( int ) );
	fin.read( ( char* )&ver, sizeof( char ) );
	fin.read( ( char* )&colorNum, sizeof( char ) );
	fin.seekg( 2, ios_base::cur );

	bmpSize = bmpWidth * bmpHeight;
	bitDataLeng = ( bmpSize % 32 == 0) ? bmpSize / 32 : (int)( bmpSize / 32 ) + 1;
	ret = new Image::CmpBitmap( bmpWidth, bmpHeight, colorNum );

	if( ver == 1 ) {
		for( int i = 0; i < dataLeng; ++i ) {
			fin.read( ( char * )&setData, sizeof( unsigned int ) );
			ret->setData( (ColorID)( setData >> 28 ), setData & 0x0FFFFFFF );
		}
		ret->drawData( hdc );
	}

	fin.close();  //ファイルを閉じる

	return ret;
}

} // namespace Main
