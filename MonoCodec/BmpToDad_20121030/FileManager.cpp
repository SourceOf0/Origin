#include <iostream>
#include <fstream>
using namespace std;

#include "FileManager.h"
#include "MonoData.h"
#include "NumData.h"

FileManager::FileManager( void )
{
	mData = 0;
}


FileManager::~FileManager( void )
{
	if( mData != 0 ) {
		delete mData;
		mData = 0;
	}
}

void FileManager::loadFile( char* pass, int ver )
{
	cout << "-- LOAD -- " << endl << endl;

	unsigned int i = 0;
	unsigned int data = 0;
	int width, height;

	mVersion = ver;

	ifstream fin( pass, ios::in | ios::binary );
	
	fin.seekg( 2, ios_base::beg ); // bfType
	fin.seekg( 4, ios_base::cur ); // bfSize
	fin.seekg( 2, ios_base::cur ); // bfReserved1
	fin.seekg( 2, ios_base::cur ); // bfReserved2
	fin.seekg( 4, ios_base::cur ); // bfOffBits

	fin.seekg( 4, ios_base::cur ); // biSize

	fin.read( ( char* )&width, sizeof( int ) );
	cout << "W : " << width << endl;

	fin.read( ( char* )&height, sizeof( int ) );
	cout << "H : " << height << endl;

	fin.seekg( 2, ios_base::cur ); // biPlanes
	fin.seekg( 2, ios_base::cur ); // biBitCount
	fin.seekg( 4, ios_base::cur ); // biCopmression
	fin.seekg( 4, ios_base::cur ); // biSizeImage
	fin.seekg( 4, ios_base::cur ); // biXPixPerMeter
	fin.seekg( 4, ios_base::cur ); // biYPixPerMeter
	fin.seekg( 4, ios_base::cur ); // biClrUsed
	fin.seekg( 4, ios_base::cur ); // biCirImportant
	fin.seekg( 4, ios_base::cur ); // ??

	switch( ver ) {
		case 0:
			mData = new MonoData( width, height );
			break;
		case 1:
			mData = new NumData( width, height );
			break;
	}

	while( !fin.eof() ){  //ファイルの最後まで続ける
		fin.read( ( char * )&data, sizeof( unsigned int ) );
		mData->setData( data, i );
		++i;
	}
	
	fin.close();  //ファイルを閉じる

	mData->setEnd();
	mData->printCount();
}

void FileManager::writeFile( char* pass )
{
	cout << "-- WRITE -- " << endl;

    ofstream fout;
    fout.open( pass, ios::out|ios::binary|ios::trunc );
    //  ファイルを開く
    //  ios::out は書き込み専用（省略可）
    //  ios::binary はバイナリ形式で出力（省略するとアスキー形式で出力）
    //  ios::truncはファイルを新規作成（省略可）
    //  ios::addにすると追記になる

	if( !fout ) {
		cout << pass << endl;
		cout << "が開けません";
		return;
	}

	/* sizeof( int ) = 4, sizeof( unsigned int ) = 4 */
    fout.write(( char* ) &mData->mWidth, sizeof( int ) );
    fout.write(( char* ) &mData->mHeight, sizeof( int ) );
    fout.write(( char* ) &mData->mArrLeng, sizeof( unsigned int ) );
    fout.write(( char* ) &mVersion, sizeof( char ) );
	fout.write(( char* ) &mData->colorNum, sizeof( char ) );
	char temp = 0;
    fout.write(( char* ) &temp, sizeof( char ) );
    fout.write(( char* ) &temp, sizeof( char ) );

	unsigned int writePixel;
	unsigned int arrLeng = mData->mArrLeng;
    for( unsigned int i = 0; i < arrLeng; ++i ){
		writePixel = mData->mPixelData[i];
        fout.write(( char * ) &writePixel, sizeof( unsigned int ) );
    }

    fout.close();  //ファイルを閉じる
}
