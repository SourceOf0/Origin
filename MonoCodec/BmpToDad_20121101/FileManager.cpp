#include <iostream>
#include <fstream>
using namespace std;

#include "FileManager.h"
#include "MonoData.h"
#include "NumData.h"

FileManager::FileManager( void ) :
mSetData( 0 ),
mData1( 0 ),
mData2( 0 )
{
}


FileManager::~FileManager( void )
{
	if( mData1 != 0 ) {
		delete mData1;
		mData1 = 0;
	}
	if( mData2 != 0 ) {
		delete mData2;
		mData2 = 0;
	}
}

void FileManager::loadFile( char* pass )
{
	cout << "-- LOAD -- " << endl << endl;

	unsigned int i = 0;
	unsigned int data = 0;
	int width, height;

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

	mData1 = new MonoData( width, height );
	mData2 = new NumData( width, height );

	while( !fin.eof() ){  //ファイルの最後まで続ける
		fin.read( ( char * )&data, sizeof( unsigned int ) );
		mData1->setData( data, i );
		mData2->setData( data, i );
		++i;
	}
	
	fin.close();  //ファイルを閉じる

	mData1->setEnd();
	mData2->setEnd();

	if( mData1->mArrLeng <= mData2->mArrLeng ) {
		mVersion = 0;
		mSetData = mData1;
	} else {
		mVersion = 1;
		mSetData = mData2;
	}

	mSetData->printCount();
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
    fout.write(( char* ) &mSetData->mWidth, sizeof( int ) );
    fout.write(( char* ) &mSetData->mHeight, sizeof( int ) );
    fout.write(( char* ) &mSetData->mArrLeng, sizeof( unsigned int ) );
    fout.write(( char* ) &mVersion, sizeof( char ) );
	fout.write(( char* ) &mSetData->colorNum, sizeof( char ) );
	char temp = 0;
    fout.write(( char* ) &temp, sizeof( char ) );
    fout.write(( char* ) &temp, sizeof( char ) );

	unsigned int writePixel;
	unsigned int arrLeng = mSetData->mArrLeng;
    for( unsigned int i = 0; i < arrLeng; ++i ){
		writePixel = mSetData->mPixelData[i];
        fout.write(( char * ) &writePixel, sizeof( unsigned int ) );
    }

    fout.close();  //ファイルを閉じる
}
