#include <iostream>
using namespace std;

#include "FileManager.h"

#define FOLDER_PASS_ROOT "C:\\Users\\Tanaka\\Desktop\\DotAnimeData\\"
#define FILE_NAME_IN_BMP "BmpData\\test"
#define FILE_NAME_OUT_DAD "DadData\\test"

int main()
{
	FileManager* fileManager = new FileManager();
	
	int i = 0;
	int rootCharNum = 0;
	int inCharNum = 0;
	int outCharNum = 0;
	int bmpCharNum = 0;
	int dadCharNum = 0;

	char* fileBmp = ".bmp";
	char* fileDad = ".dad";
	char* rootPass = FOLDER_PASS_ROOT;
	char* inFileName = FILE_NAME_IN_BMP;
	char* outFileName = FILE_NAME_OUT_DAD;

	char* inPass;
	char* outPass;

	while( rootPass[rootCharNum] != '\0' ) ++rootCharNum;
	while( inFileName[inCharNum] != '\0' ) ++inCharNum;
	while( outFileName[outCharNum] != '\0' ) ++outCharNum;
	while( fileBmp[bmpCharNum] != '\0' ) ++bmpCharNum;
	while( fileDad[dadCharNum] != '\0' ) ++dadCharNum;

	inPass = new char[rootCharNum + inCharNum + bmpCharNum + 1];
	outPass = new char[rootCharNum + outCharNum + dadCharNum + 1];

	for( i = 0; i < rootCharNum; ++i ) {
		inPass[i] = rootPass[i];
		outPass[i] = rootPass[i];
	}

	for( i = 0; i < inCharNum; ++i ) {
		inPass[i + rootCharNum] = inFileName[i];
	}
	for( i = 0; i < bmpCharNum; ++i ) {
		inPass[i + rootCharNum + inCharNum] = fileBmp[i];
	}
	inPass[rootCharNum + inCharNum + bmpCharNum] = '\0';

	for( i = 0; i < outCharNum; ++i ) {
		outPass[i + rootCharNum] = outFileName[i];
	}
	for( i = 0; i < dadCharNum; ++i ) {
		outPass[i + rootCharNum + outCharNum] = fileDad[i];
	}
	outPass[rootCharNum + outCharNum + dadCharNum] = '\0';
	
	fileManager->loadFile( inPass, 1 );
	fileManager->writeFile( outPass );

    cout << endl;
    cout << "END" << endl;

	delete fileManager;
	fileManager = 0;

	delete[] inPass;
	inPass = 0;

	delete[] outPass;
	outPass = 0;

	while(1) {}

	return 0;
}
