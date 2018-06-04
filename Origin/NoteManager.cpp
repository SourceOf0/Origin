#include "NoteManager.h"

#include "LayerData.h"

namespace Main {

NoteManager* NoteManager::mInst = 0;

NoteManager* NoteManager::inst( void )
{
	return mInst;
}
void NoteManager::create( void )
{
	if( mInst == 0 ) {
		mInst = new NoteManager();
	}
}
void NoteManager::destroy( void )
{
	if( mInst != 0 ) {
		delete mInst;
		mInst = 0;
	}
}

NoteManager::NoteManager( void ) :
mNowPageNum( 1 ),
mTargetPageNum( 1 ),
mNowPageState( 1 << NOTE_ROOM_1 ),
mTargetPageState( 1 << NOTE_ROOM_1 )
{
	for( int i = 0; i < NOTE_NONE; ++i ) {
		mNowNote[ i ] = NOTE_NONE;
		mTargetNote[ i ] = NOTE_NONE;
	}
	mNowNote[ 0 ] = NOTE_ROOM_1;
	mTargetNote[ 0 ] = NOTE_ROOM_1;
}

NoteManager::~NoteManager( void )
{
}

int NoteManager::getTrashCount( void )
{
	int ret = 0;

	if( ( mNowPageState & ( 1 << NOTE_ROOM_2 ) ) != 0 ) ++ret;
	if( ( mNowPageState & ( 1 << NOTE_ROOM_3 ) ) != 0 ) ++ret;
	if( ( mNowPageState & ( 1 << NOTE_BOOK1_3 ) ) != 0 ) ++ret;
	if( ( mNowPageState & ( 1 << NOTE_BOOK2_1 ) ) != 0 ) ++ret;
	if( ( mNowPageState & ( 1 << NOTE_BOOK2_2 ) ) != 0 ) ++ret;
	if( ( mNowPageState & ( 1 << NOTE_BOOK4_3 ) ) != 0 ) ++ret;
	if( ( mNowPageState & ( 1 << NOTE_BOOK6_1 ) ) != 0 ) ++ret;
	if( ( mNowPageState & ( 1 << NOTE_BOOK7_1 ) ) != 0 ) ++ret;

	return ret;
}

int NoteManager::getNowPageNum( void )
{
	return mNowPageNum;
}

PageKind NoteManager::getNowPage( int index )
{
	return mNowNote[ index ];
}

BOOL NoteManager::canWrite( void )
{
	return ( mNowPageNum < mTargetPageNum );
}
int NoteManager::write( void )
{
	if( mNowPageNum >= NOTE_NONE ) return -1;
	PageKind page = mTargetNote[ mNowPageNum ];
	if( page == NOTE_NONE ) return -1;
	mNowPageState |= ( 1 << page );
	mNowNote[ mNowPageNum++ ] = page;

	if( mNowPageNum != NOTE_END ) return mNowPageNum - 1;

	mNowNote[ NOTE_END ] = NOTE_END;
	mNowPageState |= ( 1 << NOTE_END );
	mNowNote[ NOTE_TITLE ] = NOTE_TITLE;
	mNowPageState |= ( 1 << NOTE_TITLE );
	mNowPageNum = NOTE_NONE;

	return NOTE_END - 1;
}
void NoteManager::setNextPage( PageKind page )
{
	if( mTargetPageNum >= NOTE_NONE ) return;
	if( ( mTargetPageState & ( 1 << page ) ) != 0 ) return;
	mTargetPageState |= ( 1 << page );
	mTargetNote[ mTargetPageNum++ ] = page;
}
BOOL NoteManager::wasSetTargetPage( PageKind page )
{
	return ( ( mTargetPageState & ( 1 << page ) ) != 0 );
}


} // namespace Main
