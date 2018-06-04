#include <iostream>
using namespace std;

#include "DataBase.h"

void DataBase::init( int width, int height )
{
	mWidth = width;
	mHeight = height;
	mBmpSize = width * height;
	
	colorNum = 0;
	oCount = 0;

	wCount = 0;
	kCount = 0;
	
	rCount = 0;
	rgCount = 0;
	gCount = 0;
	gbCount = 0;
	bCount = 0;
	brCount = 0;
}

ColorID DataBase::checkColor( unsigned int data )
{
	ColorID ret = CLR_OTHER;

	switch( data ) {
		case 0x00FFFFFF :
			ret = CLR_WHITE;
			if( wCount == 0 ) ++colorNum;
			++wCount;
			break;
		case 0x00000000 :
			ret = CLR_BLACK;
			if( kCount == 0 ) ++colorNum;
			++kCount;
			break;
		case 0x00FF0000 :
			ret = CLR_RED;
			if( rCount == 0 ) ++colorNum;
			++rCount;
			break;
		case 0x00FFFF00 :
			ret = CLR_RED_GREEN;
			if( rgCount == 0 ) ++colorNum;
			++rgCount;
			break;
		case 0x0000FF00 :
			ret = CLR_GREEN;
			if( gCount == 0 ) ++colorNum;
			++gCount;
			break;
		case 0x0000FFFF :
			ret = CLR_GREEN_BLUE;
			if( gbCount == 0 ) ++colorNum;
			++gbCount;
			break;
		case 0x000000FF :
			ret = CLR_BLUE;
			if( bCount == 0 ) ++colorNum;
			++bCount;
			break;
		case 0x00FF00FF :
			ret = CLR_BLUE_RED;
			if( brCount == 0 ) ++colorNum;
			++brCount;
			break;
		default:
			++colorNum;
			++oCount;
			break;
	}
	return ret;
}

void DataBase::printCount( void )
{
	cout << endl;
	cout << "ColorNum : " << (int)(colorNum) << endl;
	cout << "O  : " << oCount << endl;
	cout << "K  : " << kCount << endl;
	cout << "W  : " << wCount << endl;
	cout << "R  : " << rCount << endl;
	cout << "RG : " << rgCount << endl;
	cout << "G  : " << gCount << endl;
	cout << "GB : " << gbCount << endl;
	cout << "B  : " << bCount << endl;
	cout << "RB : " << brCount << endl;
	cout << endl;
}

