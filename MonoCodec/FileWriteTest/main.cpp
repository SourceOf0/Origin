#include <iostream>
#include <fstream>
using namespace std;

unsigned int* lpdwPixel;
unsigned int arrLeng;
int width = 0;
int height = 0;

void setPixel(unsigned int i)
{
	unsigned int fixIndex = i / 32;
	unsigned int setBitPos = 32 - (i % 32 + 1);
	unsigned int mask = 0xFFFFFFFF;
	int type = setBitPos / 8;
	if( fixIndex >= arrLeng ) {
		return;
	}

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
	
	lpdwPixel[ fixIndex ] &= mask ^ ( 1 << setBitPos );
}

void setBitmapPixel()
{
	char outfile[] = "frame.bmp";  //�ǂݍ��ރt�@�C���̎w��
	unsigned int d, i, wCount, bmpSize, fixWidth;
	d = 0;
	i = 0;
	wCount = 1;
	fixWidth = 0;

	ifstream fin( outfile, ios::in | ios::binary );
	
	fin.seekg(2, ios_base::beg); // bfType
	fin.seekg(4, ios_base::cur); // bfSize
	fin.seekg(2, ios_base::cur); // bfReserved1
	fin.seekg(2, ios_base::cur); // bfReserved2
	fin.seekg(4, ios_base::cur); // bfOffBits

	fin.seekg(4, ios_base::cur); // biSize

//	fin.seekg(4, ios_base::cur); // biWidth
	fin.read( (char *)&width, sizeof( int ) );
	cout << "W : " << width << endl;

//	fin.seekg(4, ios_base::cur); // biHeight
	fin.read( (char *)&height, sizeof( int ) );
	cout << "H : " << height << endl;

	fin.seekg(2, ios_base::cur); // biPlanes
	fin.seekg(2, ios_base::cur); // biBitCount
	fin.seekg(4, ios_base::cur); // biCopmression
	fin.seekg(4, ios_base::cur); // biSizeImage
	fin.seekg(4, ios_base::cur); // biXPixPerMeter
	fin.seekg(4, ios_base::cur); // biYPixPerMeter
	fin.seekg(4, ios_base::cur); // biClrUsed
	fin.seekg(4, ios_base::cur); // biCirImportant
	fin.seekg(4, ios_base::cur); // ??

	bmpSize = width * height;
	fixWidth = width;
	arrLeng = ( bmpSize % 32 == 0) ? bmpSize / 32 : (int)(bmpSize / 32) + 1;
	lpdwPixel = new unsigned int[ arrLeng ];
	for (i = 0;i < arrLeng;i++) {
		lpdwPixel[i] = 0xFFFFFFFF;
	}
	i = 0;

	while(!fin.eof()){  //�t�@�C���̍Ō�܂ő�����
		fin.read( ( char * )&d, sizeof( unsigned int ) );
		switch( d ) {
			case 0xFFFFFF00:
				break;
			case 0x00000000:
				setPixel( bmpSize - fixWidth + ( i % width ) );
				break;
		}
		++i;
		if( i % width == 0 ) {
			++wCount;
			fixWidth = width * wCount;
		}
	}
	
	fin.close();  //�t�@�C�������
}

void writeFile()
{
    ofstream fout;
    fout.open("frame.dad", ios::out|ios::binary|ios::trunc);
    //  �t�@�C�����J��
    //  ios::out �͏������ݐ�p�i�ȗ��j
    //  ios::binary �̓o�C�i���`���ŏo�́i�ȗ�����ƃA�X�L�[�`���ŏo�́j
    //  ios::trunc�̓t�@�C����V�K�쐬�i�ȗ��j
    //  ios::add�ɂ���ƒǋL�ɂȂ�

    if (!fout) {
        cout << "�t�@�C�� file.txt ���J���܂���";
        return;
    }

	unsigned int temp = 0;

	/* sizeof( int ) = 4, sizeof( unsigned int ) = 4 */
    fout.write(( char * ) &width, sizeof( int ) );
    fout.write(( char * ) &height, sizeof( int ) );
    fout.write(( char * ) &arrLeng, sizeof( unsigned int ) );
    fout.write(( char * ) &temp, sizeof( unsigned int ) ); // �\��

	unsigned int kCount = 0;
	unsigned int wCount = 0;
	unsigned int writePixel;
    for(int i = 0; i < arrLeng; i++){
		writePixel = lpdwPixel[i];
		if(writePixel == 0) ++kCount;
		if(writePixel == 0xFFFFFFFF) ++wCount;
        fout.write(( char * ) &writePixel, sizeof( unsigned int ) );
        //������ł͂Ȃ��f�[�^����������
    }

    fout.close();  //�t�@�C�������

    cout << endl;
    cout << "A : " << arrLeng << endl;
    cout << "K : " << kCount << endl;
    cout << "W : " << wCount << endl;
    cout << "END" << endl;
	
	delete [] lpdwPixel;
}


int main()
{
	setBitmapPixel();
	writeFile();

	while(1) {}

	return 0;
}
