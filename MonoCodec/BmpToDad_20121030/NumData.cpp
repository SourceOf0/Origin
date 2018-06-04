#include <iostream>
using namespace std;

#include "NumData.h"

NumData::NumData( int width, int height )
{
	init( width, height );

	mFirstNode = new ColorNode();
	mFirstNode->color = CLR_OTHER;
	mFirstNode->count = 0;
	mFirstNode->next = 0;

	mNowNode = mFirstNode;
	mNodeNum = 0;
}

NumData::~NumData( void )
{
	if( mPixelData != 0 ) {
		delete mPixelData;
		mPixelData = 0;
	}

	ColorNode* target = mFirstNode;
	ColorNode* next = 0;
	while( target != 0 ) {
		next = target->next;
		delete target;
		target = next;
	}
}

void NumData::setData( unsigned int data, unsigned int index )
{
	ColorID color = checkColor( data );
	if( color != mNowNode->color ) {
		if( index != 0 ) {
			mNowNode->next = new ColorNode();
			mNowNode = mNowNode->next;
		}
		mNowNode->color = color;
		++mNodeNum;
	}
	++mNowNode->count;
}

void NumData::setEnd( void )
{
	mArrLeng = mNodeNum;
	mNowNode = mFirstNode;
	mPixelData = new unsigned int[ mArrLeng ];
	for ( unsigned int i = 0; i < mArrLeng; ++i ) {
		if( ( mNowNode->count & 0xF0000000 ) != 0 ) {
			return;
		}
		mPixelData[i] = mNowNode->count | ( mNowNode->color << ( 28 ) );
		mNowNode = mNowNode->next;
	}
}