#include "ImageFactory.h"
#include "ToneFactory.h"

#include "AnimeData.h"
#include "LayerData.h"
#include "DCBitmap.h"
#include "PixelBitmap.h"

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

using namespace Image;

namespace Main {

ImageFactory* ImageFactory::mInst = 0;

ImageFactory* ImageFactory::inst( void )
{
	return mInst;
}
void ImageFactory::create( HDC& hdc )
{
	if( mInst == 0 ) {
		mInst = new ImageFactory( hdc );
		ToneFactory::create( hdc );
	}
}
void ImageFactory::destroy( void )
{
	if( mInst != 0 ) {
		ToneFactory::destroy();
		delete mInst;
		mInst = 0;
	}
}

ImageFactory::ImageFactory( HDC& hdc )
{
	for( int i = 0; i < COLOR_KIND_NUM; ++i ) {
		mLayerData[ i ] = new PixelBitmap( 0, 0 );
	}
}
ImageFactory::~ImageFactory()
{
	for( int i = 0; i < COLOR_KIND_NUM; ++i ) {
		delete mLayerData[ i ];
		mLayerData[ i ] = 0;
	}
}


ColorID ImageFactory::getColor( unsigned char color )
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

unsigned int ImageFactory::setBlack( PixelBitmap* target, unsigned int count, unsigned int index )
{
	for( unsigned int i = count - 1; i != 0xFFFFFFFF; --i ) {
		target->setBlack( index );
		++index;
	}
	return count;
}

unsigned int ImageFactory::setWhite( PixelBitmap* target, unsigned int count, unsigned int index )
{
	for( unsigned int i = count - 1; i != 0xFFFFFFFF; --i ) {
		target->setWhite( index );
		++index;
	}
	return count;
}

unsigned int ImageFactory::setTone( PixelBitmap* target, unsigned int count, unsigned int index )
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


BitmapBase* ImageFactory::loadAnime( HDC& hdc, int animeNum, const int fileIDs[], BOOL isDC )
{
	AnimeData* ret = new AnimeData();
	BitmapBase** setData = new BitmapBase*[ animeNum ];
	unsigned int bmpWidth, bmpHeight;

	HRSRC hResource = FindResource( NULL, MAKEINTRESOURCE(fileIDs[0]), "DAD");
	if( !hResource ) {
		MessageBox( NULL, TEXT( "1 ファイル読み込めないんですけど。" ), TEXT( "Origin" ), MB_OK );
		return NULL;
	}
	HGLOBAL hLoadedResource = LoadResource( NULL, hResource );
	if( !hLoadedResource ) {
		MessageBox( NULL, TEXT( "2 ファイル読み込めないんですけど。" ), TEXT( "Origin" ), MB_OK );
		return NULL;
	}

	char* pLockedResource = (char*)LockResource(hLoadedResource);
	if( !pLockedResource ) {
		MessageBox( NULL, TEXT( "3 ファイル読み込めないんですけど。" ), TEXT( "Origin" ), MB_OK );
		return NULL;
	}
	DWORD dwResourceSize = SizeofResource( NULL, hResource );
	if( 0 == dwResourceSize ) {
		MessageBox( NULL, TEXT( "4 ファイル読み込めないんですけど。" ), TEXT( "Origin" ), MB_OK );
		return NULL;
	}

	std::string result;
	result.assign( pLockedResource, dwResourceSize );
	std::istringstream fin( result, std::istringstream::binary );
	//ifstream fin( fileName[ 0 ], ios::in | ios::binary );
	if( !fin ) {
		MessageBox( NULL, TEXT( "ファイル読み込めないんですけど。" ), TEXT( "Origin" ), MB_OK );
		return NULL;
	}
	fin.read( ( char* )&bmpWidth, sizeof( int ) );
	fin.read( ( char* )&bmpHeight, sizeof( int ) );

	if( isDC ) {
		for( int i = 0; i < animeNum; ++i ) {
			setData[ i ] = loadDC( hdc, fileIDs[ i ] );
		}
	} else {
		for( int i = 0; i < animeNum; ++i ) {
			setData[ i ] = load( hdc, fileIDs[ i ] );
		}
	}
	ret->setData( setData, animeNum );

	return ret;
}

DCBitmap* ImageFactory::loadDC( HDC& hdc, const int fileID )
{
	unsigned int setData, bmpWidth, bmpHeight, bmpSize, dataLeng, bitDataLeng;
	unsigned char ver, useColor;
	DCBitmap* ret;

	HRSRC hResource = FindResource( NULL, MAKEINTRESOURCE(fileID), "DAD");
	if( !hResource ) {
		MessageBox( NULL, TEXT( "1 ファイル読み込めないんですけど。" ), TEXT( "Origin" ), MB_OK );
		return NULL;
	}
	HGLOBAL hLoadedResource = LoadResource( NULL, hResource );
	if( !hLoadedResource ) {
		MessageBox( NULL, TEXT( "2 ファイル読み込めないんですけど。" ), TEXT( "Origin" ), MB_OK );
		return NULL;
	}

	char* pLockedResource = (char*)LockResource(hLoadedResource);
	if( !pLockedResource ) {
		MessageBox( NULL, TEXT( "3 ファイル読み込めないんですけど。" ), TEXT( "Origin" ), MB_OK );
		return NULL;
	}
	DWORD dwResourceSize = SizeofResource( NULL, hResource );
	if( 0 == dwResourceSize ) {
		MessageBox( NULL, TEXT( "4 ファイル読み込めないんですけど。" ), TEXT( "Origin" ), MB_OK );
		return NULL;
	}

	std::string result;
	result.assign( pLockedResource, dwResourceSize );
	std::istringstream fin( result, std::istringstream::binary );
	//ifstream fin( fileName, ios::in | ios::binary );

	if( !fin ) {
		MessageBox( NULL, TEXT( "ファイル読み込めないんですけど。" ), TEXT( "Origin" ), MB_OK );
		return NULL;
	}

	fin.read( ( char* )&bmpWidth, sizeof( int ) );
	fin.read( ( char* )&bmpHeight, sizeof( int ) );
	fin.read( ( char* )&dataLeng, sizeof( int ) );
	fin.read( ( char* )&ver, sizeof( char ) );
	fin.read( ( char* )&useColor, sizeof( char ) );
	fin.seekg( 2, ios_base::cur );

	bmpSize = bmpWidth * bmpHeight;
	bitDataLeng = ( bmpSize % 32 == 0) ? bmpSize / 32 : (int)( bmpSize / 32 ) + 1;

	PixelBitmap* pixelData = mLayerData[ 0 ];
	pixelData->reset( bmpWidth, bmpHeight );

	if( ver == 0 ) {
		for( unsigned int i = 0; i < bitDataLeng; ++i ) {
			fin.read( ( char * )&setData, sizeof( char ) );
			pixelData->setData( i*4, setData );
			fin.read( ( char * )&setData, sizeof( char ) );
			pixelData->setData( i*4 + 1, setData );
			fin.read( ( char * )&setData, sizeof( char ) );
			pixelData->setData( i*4 + 2, setData );
			fin.read( ( char * )&setData, sizeof( char ) );
			pixelData->setData( i*4 + 3, setData );
		}
		ret = new Image::DCBitmap( hdc, pixelData );
	} else if( ver == 1 ) {
		for( int i = 0; i < COLOR_KIND_NUM; ++i ) {
			mLayerData[ i ]->reset( bmpWidth, bmpHeight );
		}
		unsigned int index = 0;
		for( unsigned int i = 0; i < dataLeng; ++i ) {
			fin.read( ( char * )&setData, sizeof( unsigned int ) );
			unsigned int count = setData & 0x0FFFFFFF;
			unsigned char targetColor = setData >> 28;
			for( int k = 0; k < COLOR_KIND_NUM; ++k ) {
				if( ( ( useColor >> k ) & 1 ) == 0 ) continue;
				if( targetColor == k ) {
					setBlack( mLayerData[ k ], count, index );
				} else {
					setWhite( mLayerData[ k ], count, index );
				}
			}
			index += count;
			
			targetColor = ( ColorID )( targetColor << 1 );
		}

		LayerData* layerData = new Image::LayerData( hdc, bmpWidth, bmpHeight );
		for( int i = 0; i < COLOR_KIND_NUM; ++i ) {
			if( ( useColor & 1 ) == 0 ) {
				useColor >>= 1;
				continue;
			}
			useColor >>= 1;
			layerData->mLayer[ i ] = new DCBitmap( hdc, mLayerData[ i ] );
		}
		ret = new DCBitmap( hdc, bmpWidth, bmpHeight );
		layerData->drawDCBitmap( ret, 0, 0, bmpWidth, 0 );
		delete layerData;
		layerData = 0;
	}

	//fin.close();  //ファイルを閉じる

	return ret;
}

BitmapBase* ImageFactory::load( HDC& hdc, const int fileID )
{
	unsigned int setData, bmpWidth, bmpHeight, dataLeng;
	unsigned char ver, useColor;
	BitmapBase* ret = 0;

	HRSRC hResource = FindResource( NULL, MAKEINTRESOURCE(fileID), "DAD");
	if( !hResource ) {
		MessageBox( NULL, TEXT( "1 ファイル読み込めないんですけど。" ), TEXT( "Origin" ), MB_OK );
		return NULL;
	}
	HGLOBAL hLoadedResource = LoadResource( NULL, hResource );
	if( !hLoadedResource ) {
		MessageBox( NULL, TEXT( "2 ファイル読み込めないんですけど。" ), TEXT( "Origin" ), MB_OK );
		return NULL;
	}

	char* pLockedResource = (char*)LockResource(hLoadedResource);
	if( !pLockedResource ) {
		MessageBox( NULL, TEXT( "3 ファイル読み込めないんですけど。" ), TEXT( "Origin" ), MB_OK );
		return NULL;
	}
	DWORD dwResourceSize = SizeofResource( NULL, hResource );
	if( 0 == dwResourceSize ) {
		MessageBox( NULL, TEXT( "4 ファイル読み込めないんですけど。" ), TEXT( "Origin" ), MB_OK );
		return NULL;
	}

	std::string result;
	result.assign( pLockedResource, dwResourceSize );
	std::istringstream fin( result, std::istringstream::binary );
	//ifstream fin( fileName, ios::in | ios::binary );

	if( !fin ) {
		MessageBox( NULL, TEXT( "ファイル読み込めないんですけど。" ), TEXT( "Origin" ), MB_OK );
		return NULL;
	}

	fin.read( ( char* )&bmpWidth, sizeof( int ) );
	fin.read( ( char* )&bmpHeight, sizeof( int ) );
	fin.read( ( char* )&dataLeng, sizeof( int ) );
	fin.read( ( char* )&ver, sizeof( char ) );
	fin.read( ( char* )&useColor, sizeof( char ) );
	fin.seekg( 2, ios_base::cur );

	if( ver == 0 ) {
		PixelBitmap* pixelData = mLayerData[ 0 ];
		pixelData->reset( bmpWidth, bmpHeight );
		unsigned int bmpSize = bmpWidth * bmpHeight;
		unsigned int bitDataLeng = ( bmpSize % 32 == 0) ? bmpSize / 32 : (int)( bmpSize / 32 ) + 1;

		for( unsigned int i = 0; i < bitDataLeng; ++i ) {
			fin.read( ( char * )&setData, sizeof( char ) );
			pixelData->setData( i*4, setData );
			fin.read( ( char * )&setData, sizeof( char ) );
			pixelData->setData( i*4 + 1, setData );
			fin.read( ( char * )&setData, sizeof( char ) );
			pixelData->setData( i*4 + 2, setData );
			fin.read( ( char * )&setData, sizeof( char ) );
			pixelData->setData( i*4 + 3, setData );
		}
		ret = new Image::DCBitmap( hdc, pixelData );

	} else if( ver == 1 ) {
		for( int i = 0; i < COLOR_KIND_NUM; ++i ) {
			mLayerData[ i ]->reset( bmpWidth, bmpHeight );
		}
		unsigned int index = 0;
		for( unsigned int i = 0; i < dataLeng; ++i ) {
			fin.read( ( char * )&setData, sizeof( unsigned int ) );
			unsigned int count = setData & 0x0FFFFFFF;
			unsigned char targetColor = setData >> 28;
			for( int k = 0; k < COLOR_KIND_NUM; ++k ) {
				if( ( ( useColor >> k ) & 1 ) == 0 ) continue;
				if( targetColor == k ) {
					setBlack( mLayerData[ k ], count, index );
				} else {
					setWhite( mLayerData[ k ], count, index );
				}
			}
			index += count;
	
			targetColor = ( ColorID )( targetColor << 1 );
		}

		LayerData* layerData = new LayerData( hdc, bmpWidth, bmpHeight );
		for( int i = 0; i < COLOR_KIND_NUM; ++i ) {
			if( ( useColor & 1 ) == 0 ) {
				useColor >>= 1;
				continue;
			}
			useColor >>= 1;
			layerData->mLayer[ i ] = new DCBitmap( hdc, mLayerData[ i ] );
		}
		ret = layerData;
	}

	return ret;
}


} // namespace Main
