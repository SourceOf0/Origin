#ifndef INCLUDED_NUM_DATA_H
#define INCLUDED_NUM_DATA_H

#include "DataBase.h"

class NumData : public DataBase
{
public:
	NumData( int width, int height );
	~NumData( void );

	void setData( unsigned int data, unsigned int index );
	void setEnd( void );

private :
	typedef struct _COLOR_NODE {
		ColorID color;
		unsigned int count;
		_COLOR_NODE* next;
	} ColorNode;

	typedef struct _COLOR_LIST {
		_COLOR_NODE* first;
		_COLOR_LIST* nextList;
	} ColorList;

	ColorList* mFirstList;
	ColorList* mNowList;
	ColorNode* mNowNode;
	int mNodeNum;
	int mListNum;
};

#endif // INCLUDED_NUM_DATA_H