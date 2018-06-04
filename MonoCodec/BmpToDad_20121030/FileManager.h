#ifndef INCLUDED_FILE_MANAGER_H
#define INCLUDED_FILE_MANAGER_H

class DataBase;

class FileManager
{
public:
	FileManager( void );
	~FileManager( void );

	void loadFile( char* pass, int ver );
	void writeFile( char* pass );

private:
	DataBase* mData;
	unsigned char mVersion;
};

#endif // INCLUDED_FILE_MANAGER_H

