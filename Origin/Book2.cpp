#include "MainParent.h"
#include "MainChild.h"
#include "Book2.h"

#include "ImageFactory.h"
#include "SceneManager.h"
#include "HandManager.h"
#include "NoteManager.h"

#include "DCBitmap.h"

#define POINT_MASK_ANIME_NUM 11
#define POINT_MASK_FRAME_COUNT 2
#define POINT_TRACK_DIS 20
#define CHANGE_COUNT_MAX 200
#define FILTER_FRAME_COUNT 2

namespace Sequence {

Book2::Book2( HDC& hdc, MainParent* parent )
{
	Main::ImageFactory* imageFactory = Main::ImageFactory::inst();
	int windowWidth = Main::SceneManager::windowWidth;
	int windowHeight = Main::SceneManager::windowHeight;

	for( int i = 0; i < POINT_TRACK_NUM; ++i ) {
		mPointTrack[i].x = -1;
		mPointTrack[i].y = -1;
		mPointTrack[i].count = 0;
	}

	mBackBmp1 = imageFactory->loadDC( hdc, "resource\\pic02.dad" );
	mBackBmp1->mX = static_cast< double >( windowWidth - mBackBmp1->mWidth ) / 2;
	mBackBmp1->mY = static_cast< double >( windowHeight - mBackBmp1->mHeight ) / 2 - 10;

	mBackBmp2 = imageFactory->loadDC( hdc, "resource\\pic01.dad" );
	mBackBmp2->mX = static_cast< double >( windowWidth - mBackBmp2->mWidth ) / 2;
	mBackBmp2->mY = static_cast< double >( windowHeight - mBackBmp2->mHeight ) / 2 - 10;

	mBackBmp3 = imageFactory->loadDC( hdc, "resource\\pic03.dad" );
	mBackBmp3->mX = static_cast< double >( windowWidth - mBackBmp3->mWidth ) / 2;
	mBackBmp3->mY = static_cast< double >( windowHeight - mBackBmp3->mHeight ) / 2 - 10;

	mBackBmp4 = imageFactory->loadDC( hdc, "resource\\pic05.dad" );
	mBackBmp4->mX = static_cast< double >( windowWidth - mBackBmp4->mWidth ) / 2;
	mBackBmp4->mY = static_cast< double >( windowHeight - mBackBmp4->mHeight ) / 2 - 10;

	mBackBmp5 = imageFactory->loadDC( hdc, "resource\\pic04.dad" );
	mBackBmp5->mX = static_cast< double >( windowWidth - mBackBmp5->mWidth ) / 2;
	mBackBmp5->mY = static_cast< double >( windowHeight - mBackBmp5->mHeight ) / 2 - 10;

	mFrontBmp = imageFactory->loadDC( hdc, "resource\\frame.dad" );
	mFrontBmp->mX = static_cast< double >( windowWidth - mFrontBmp->mWidth ) / 2;
	mFrontBmp->mY = static_cast< double >( windowHeight - mFrontBmp->mHeight ) / 2;

	mMaskBmp = new Image::DCBitmap( hdc, windowWidth, windowHeight );

	mMaskBlockBmp = imageFactory->loadDC( hdc, "resource\\smallFilter.dad" );

	mPointBmp = imageFactory->loadDC( hdc, "resource\\pointMask.dad" );

	mCount = FILTER_FRAME_COUNT;
	mChangeCount = CHANGE_COUNT_MAX;
	mBackIndex = 1;
	mOldMousePos.x = -1;
	mOldMousePos.y = -1;
}

Book2::~Book2()
{
	delete mBackBmp1;
	mBackBmp1 = 0;

	delete mBackBmp2;
	mBackBmp2 = 0;

	delete mBackBmp3;
	mBackBmp3 = 0;

	delete mBackBmp4;
	mBackBmp4 = 0;

	delete mBackBmp5;
	mBackBmp5 = 0;

	delete mFrontBmp;
	mFrontBmp = 0;

	delete mMaskBmp;
	mMaskBmp = 0;

	delete mMaskBlockBmp;
	mMaskBlockBmp = 0;

	delete mPointBmp;
	mPointBmp = 0;
}

void Book2::update( MainParent* parent )
{
	int windowWidth = Main::SceneManager::windowWidth;
	int windowHeight = Main::SceneManager::windowHeight;
	
	if( mCount < 0 ) {
		( rand() * 1.0 / RAND_MAX > 0.05 ) ? mCount = FILTER_FRAME_COUNT : mCount = FILTER_FRAME_COUNT * 5 ;
	}
	--mCount;
	int blockWidth = mMaskBlockBmp->mWidth / 5;
	for( int y = 0; y < windowHeight; y += blockWidth ) {
		for( int x = 0; x < windowWidth; x += blockWidth ) {
			mMaskBlockBmp->drawBlock( mMaskBmp->mHdcBmp, x, y, blockWidth, static_cast< int >( mCount / FILTER_FRAME_COUNT ) );
		}
	}

	if( Main::HandManager::isMouseDown ) {
		Main::HandManager::inst()->setState( Main::HandManager::HAND_PUSH_AFTER );
		setPointMask();
		mChangeCount = CHANGE_COUNT_MAX;
		Main::NoteManager::inst()->setNextPage( NOTE_BOOK2_1 );
	} else {
		Main::HandManager::inst()->setState( Main::HandManager::HAND_PUSH_BEFORE );
		mOldMousePos.x = -1;
		mOldMousePos.y = -1;
	}

	if( Main::HandManager::inst()->getX() > windowWidth - BOOK_CORNAR_HIT_SIZE && Main::HandManager::inst()->getY() > windowHeight - BOOK_CORNAR_HIT_SIZE ) {
		if( Main::HandManager::isClick ) {
			Main::HandManager::inst()->setState( Main::HandManager::HAND_NORMAL );
			parent->moveTo( parent->SEQ_ROOM );
		} else {
			Main::HandManager::inst()->setState( Main::HandManager::HAND_CLOSE );
		}
	}
}

void Book2::draw( HDC& hdc, MainParent* parent )
{
	int setCount = POINT_MASK_ANIME_NUM * POINT_MASK_FRAME_COUNT;
	int pointWidth = mPointBmp->mWidth / POINT_MASK_ANIME_NUM;
	for( int i = 0; i < POINT_TRACK_NUM; ++i ) {
		if( mPointTrack[i].count <= 0 ) continue;
		if( mPointTrack[i].count >= setCount ) {
			mPointBmp->drawBlockOr( mMaskBmp->mHdcBmp, mPointTrack[i].x - pointWidth / 2, mPointTrack[i].y - pointWidth / 2, pointWidth, POINT_MASK_ANIME_NUM - 1 - (int)( ( mPointTrack[i].count - setCount ) / POINT_MASK_FRAME_COUNT ) );
		} else {
			mPointBmp->drawBlockOr( mMaskBmp->mHdcBmp, mPointTrack[i].x - pointWidth / 2, mPointTrack[i].y - pointWidth / 2, pointWidth, (int)( mPointTrack[i].count / POINT_MASK_FRAME_COUNT ) );
		}
		--mPointTrack[i].count;
	}

	--mChangeCount;
	if( mChangeCount <= 0 ) {
		mChangeCount = CHANGE_COUNT_MAX;
		mCount = FILTER_FRAME_COUNT * 5;
		++mBackIndex;
	}
	switch( mBackIndex ) {
		case 6:
			mBackIndex = 1;
			if( Main::NoteManager::inst()->wasSetTargetPage( NOTE_BOOK2_2 ) ) {
				Main::NoteManager::inst()->setNextPage( NOTE_BOOK2_3 );
			}
		case 1:
			mBackBmp1->drawWindow();
			if( Main::NoteManager::inst()->wasSetTargetPage( NOTE_BOOK2_1 ) ) {
				Main::NoteManager::inst()->setNextPage( NOTE_BOOK2_2 );
			}
			break;
		case 2:
			mBackBmp2->drawWindow();
			break;
		case 3:
			mBackBmp3->drawWindow();
			break;
		case 4:
			mBackBmp4->drawWindow();
			break;
		case 5:
			mBackBmp5->drawWindow();
			break;
	}
	mMaskBmp->drawWindowAnd();
	mFrontBmp->drawWindowAnd();
}

int Book2::setPointMask( void )
{
	int mouseX = Main::HandManager::inst()->getX();
	int mouseY = Main::HandManager::inst()->getY();

	int setCount = POINT_MASK_ANIME_NUM * POINT_MASK_FRAME_COUNT;
	if( ( mOldMousePos.x < mouseX - POINT_TRACK_DIS || mOldMousePos.x > mouseX + POINT_TRACK_DIS )
		|| ( mOldMousePos.y < mouseY - POINT_TRACK_DIS || mOldMousePos.y > mouseY + POINT_TRACK_DIS ) ) { 
		for( int i = 0; i < POINT_TRACK_NUM; ++i ) {
			if( mPointTrack[i].count > 0 ) continue;
			mPointTrack[i].x = mouseX;
			mPointTrack[i].y = mouseY;
			mPointTrack[i].count = setCount * 2;
			break;
		}
		mOldMousePos.x = mouseX;
		mOldMousePos.y = mouseY;
	}

	return 0;
}

} // namespace Sequence