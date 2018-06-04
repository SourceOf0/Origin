#ifndef INCLUDED_MONO_DATA_H
#define INCLUDED_MONO_DATA_H

#include "DataBase.h"

class MonoData : public DataBase
{
public:
	MonoData( int width, int height );
	~MonoData( void );

	void setData( unsigned int data, unsigned int index );
	void setEnd( void ) {}

private :
	void setPixel( unsigned int i );

	unsigned int mFixWidth;
	unsigned int mWidthCount;
};

#endif // INCLUDED_MONO_DATA_H