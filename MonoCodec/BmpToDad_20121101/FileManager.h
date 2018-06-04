#ifndef INCLUDED_FILE_MANAGER_H
#define INCLUDED_FILE_MANAGER_H

class DataBase;

class FileManager
{
public:
	FileManager( void );
	~FileManager( void );

	void loadFile( char* pass );
	void writeFile( char* pass );

private:
	DataBase* mData1;
	DataBase* mData2;
	DataBase* mSetData;
	unsigned char mVersion;
};

#endif // INCLUDED_FILE_MANAGER_H

