#include <iostream>
using namespace std;

#include "NumData.h"

NumData::NumData( int width, int height )
{
	init( width, height );

	mNowNode = 0;

	mFirstList = new ColorList();
	mFirstList->first = 0;
	mFirstList->nextList = 0;

	mNowList = mFirstList;

	mNodeNum = 0;
	mListNum = 0;
}

NumData::~NumData( void )
{
	if( mPixelData != 0 ) {
		delete mPixelData;
		mPixelData = 0;
	}

	ColorList* list = mFirstList;
	ColorList* nextList = mFirstList->nextList;
	ColorNode* node = 0;
	ColorNode* next = 0;
	while( list != 0 ) {
		nextList = list->nextList;
		node = list->first;
		while( node != 0 ) {
			next = node->next;
			delete node;
			node = next;
		}
		delete list;
		list = nextList;
	}
}

void NumData::setData( unsigned int data, unsigned int index )
{
	if( index >= mWidth * mHeight ) return;

	ColorID color = checkColor( data );

	if( index % mWidth == 0 ) {
		mNowNode = new ColorNode();
		mNowNode->color = color;
		mNowNode->count = 0;
		mNowNode->next = 0;
		++mNodeNum;

		ColorList* temp = mNowList;
		mNowList = new ColorList();
		mNowList->nextList = temp;
		mNowList->first = mNowNode;
		++mListNum;
	} else if( color != mNowNode->color ) {
		mNowNode->next = new ColorNode();
		mNowNode = mNowNode->next;
		mNowNode->color = color;
		mNowNode->count = 0;
		++mNodeNum;
	}
	++mNowNode->count;
}

void NumData::setEnd( void )
{
	ColorID color = CLR_OTHER;
	unsigned int count = 0;
	unsigned int fixArrLeng = 0;

	mArrLeng = mNodeNum;
	mNowNode = mNowList->first;

	mPixelData = new unsigned int[ mArrLeng ];
	for ( unsigned int i = 0; i < mArrLeng; ++i ) {
		if( ( mNowNode->count & 0xF0000000 ) != 0 ) {
			return;
		}
		if( color == mNowNode->color ) {
			count += mNowNode->count;
		} else {
			mPixelData[ fixArrLeng ] = count | ( color << ( 28 ) );
			count = mNowNode->count;
			color = mNowNode->color;
			++fixArrLeng;
		}
		mNowNode = mNowNode->next;
		if( mNowNode == 0 ) {
			--mListNum;
			mNowList = mNowList->nextList;
			mNowNode = mNowList->first;
		}
	}
	mPixelData[ fixArrLeng ] = count | ( color << ( 28 ) );
	++fixArrLeng;
	mArrLeng = fixArrLeng;
}