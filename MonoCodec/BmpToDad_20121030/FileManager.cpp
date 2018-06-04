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

	while( !fin.eof() ){  //�t�@�C���̍Ō�܂ő�����
		fin.read( ( char * )&data, sizeof( unsigned int ) );
		mData->setData( data, i );
		++i;
	}
	
	fin.close();  //�t�@�C�������

	mData->setEnd();
	mData->printCount();
}

void FileManager::writeFile( char* pass )
{
	cout << "-- WRITE -- " << endl;

    ofstream fout;
    fout.open( pass, ios::out|ios::binary|ios::trunc );
    //  �t�@�C�����J��
    //  ios::out �͏������ݐ�p�i�ȗ��j
    //  ios::binary �̓o�C�i���`���ŏo�́i�ȗ�����ƃA�X�L�[�`���ŏo�́j
    //  ios::trunc�̓t�@�C����V�K�쐬�i�ȗ��j
    //  ios::add�ɂ���ƒǋL�ɂȂ�

	if( !fout ) {
		cout << pass << endl;
		cout << "���J���܂���";
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

    fout.close();  //�t�@�C�������
}
