#ifndef INCLUDED_MAIN_NOTE_MANAGER_H
#define INCLUDED_MAIN_NOTE_MANAGER_H

#include <windows.h>

enum PageKind {
	NOTE_ROOM_1,
	NOTE_ROOM_2,
	NOTE_ROOM_3,
	NOTE_BOOK1_1,
	NOTE_BOOK1_2,
	NOTE_BOOK1_3,
	NOTE_BOOK2_1,
	NOTE_BOOK2_2,
	NOTE_BOOK2_3,
	NOTE_BOOK3_1,
	NOTE_BOOK3_2,
	NOTE_BOOK3_3,
	NOTE_BOOK4_1,
	NOTE_BOOK4_2,
	NOTE_BOOK4_3,
	NOTE_BOOK5_1,
	NOTE_BOOK5_2,
	NOTE_BOOK5_3,
	NOTE_BOOK6_1,
	NOTE_BOOK6_2,
	NOTE_BOOK6_3,
	NOTE_BOOK7_1,
	NOTE_BOOK7_2,
	NOTE_BOOK7_3,
	NOTE_END,
	NOTE_TITLE,

	NOTE_NONE
};

namespace Main {

class NoteManager
{
public:
	static NoteManager* inst();
	static void create( void );
	static void destroy( void );

	int getTrashCount( void );
	int getNowPageNum( void );
	PageKind getNowPage( int index );

	BOOL canWrite( void );
	int write( void );
	void setNextPage( PageKind page );
	BOOL wasSetTargetPage( PageKind page );

private:
	NoteManager( void );
	NoteManager( NoteManager& );
	~NoteManager( void );

	static NoteManager* mInst;

	PageKind mNowNote[ NOTE_NONE ];
	unsigned int mNowPageState;
	int mNowPageNum;

	PageKind mTargetNote[ NOTE_NONE ];
	unsigned int mTargetPageState;
	int mTargetPageNum;
};

} // namespace Main

#endif // INCLUDED_MAIN_HAND_MANAGER_H
