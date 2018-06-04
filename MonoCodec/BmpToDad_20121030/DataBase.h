#ifndef INCLUDED_DATA_BASE_H
#define INCLUDED_DATA_BASE_H

typedef enum _COLOR_ID {
	CLR_BLACK,
	CLR_WHITE,
	CLR_RED,
	CLR_RED_GREEN,
	CLR_GREEN,
	CLR_GREEN_BLUE,
	CLR_BLUE,
	CLR_BLUE_RED,
	
	CLR_OTHER
} ColorID;

class DataBase
{
public:
	virtual ~DataBase( void ) {}

	virtual void setData( unsigned int data, unsigned int index ) = 0;
	virtual void setEnd( void ) = 0;

	void init( int width, int height );
	void printCount( void );
	ColorID checkColor( unsigned int data );

	unsigned int* mPixelData;
	unsigned int mArrLeng;

	unsigned char colorNum;
	int mWidth;
	int mHeight;

protected :
	unsigned int mBmpSize;
	unsigned int oCount;

	unsigned int wCount;
	unsigned int kCount;

	unsigned int rCount;
	unsigned int rgCount;
	unsigned int gCount;
	unsigned int gbCount;
	unsigned int bCount;
	unsigned int brCount;
};

#endif // INCLUDED_DATA_BASE_H