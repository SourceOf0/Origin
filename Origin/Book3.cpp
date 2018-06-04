#include "MainParent.h"
#include "MainChild.h"
#include "Book3.h"

#include "ImageFactory.h"
#include "SceneManager.h"
#include "HandManager.h"

#include "DCBitmap.h"

#define ANIME_SPEED 4
#define USE_IMAGE_SIZE 256
#define USE_IMAGE_SIZE_HALF 128
#define SET_MAX_DISTANCE 50

namespace Sequence {

Book3::Book3( HDC& hdc, MainParent* parent )
{
	Main::ImageFactory* imageFactory = Main::ImageFactory::inst();
	int windowWidth = Main::SceneManager::windowWidth;
	int windowHeight = Main::SceneManager::windowHeight;
	int i = -1;

	mImageArr[ ++i ] = imageFactory->loadDC( hdc, "resource\\book3_00.dad" );
	mImageArr[ ++i ] = imageFactory->loadDC( hdc, "resource\\book3_01.dad" );
	mImageArr[ ++i ] = imageFactory->loadDC( hdc, "resource\\book3_02.dad" );
	mImageArr[ ++i ] = imageFactory->loadDC( hdc, "resource\\book3_10.dad" );
	mImageArr[ ++i ] = imageFactory->loadDC( hdc, "resource\\book3_11.dad" );
	mImageArr[ ++i ] = imageFactory->loadDC( hdc, "resource\\book3_12.dad" );
	mImageArr[ ++i ] = imageFactory->loadDC( hdc, "resource\\book3_20.dad" );
	mImageArr[ ++i ] = imageFactory->loadDC( hdc, "resource\\book3_21.dad" );
	mImageArr[ ++i ] = imageFactory->loadDC( hdc, "resource\\book3_22.dad" );
	mImageArr[ ++i ] = imageFactory->loadDC( hdc, "resource\\book3_30.dad" );
	mImageArr[ ++i ] = imageFactory->loadDC( hdc, "resource\\book3_31.dad" );
	mImageArr[ ++i ] = imageFactory->loadDC( hdc, "resource\\book3_32.dad" );
	mImageArr[ ++i ] = imageFactory->loadDC( hdc, "resource\\book3_40.dad" );
	mImageArr[ ++i ] = imageFactory->loadDC( hdc, "resource\\book3_41.dad" );
	mImageArr[ ++i ] = imageFactory->loadDC( hdc, "resource\\book3_42.dad" );

	mFirstNode.x = 0;
	mFirstNode.y = 0;
	mFirstNode.count = 0;
	mFirstNode.state = 0;
	mFirstNode.image = IMAGE_NONE;
	mFirstNode.next = &mLastNode;
	mFirstNode.prev = 0;

	mLastNode.x = 0;
	mLastNode.y = 0;
	mLastNode.count = 0;
	mLastNode.state = 0;
	mLastNode.image = IMAGE_NONE;
	mLastNode.next = 0;
	mLastNode.prev = &mFirstNode;

	newAnimeState( ( windowWidth - USE_IMAGE_SIZE ) / 2, ( windowHeight - USE_IMAGE_SIZE ) / 2 );
}

Book3::~Book3()
{
	for( int i = 0; i < IMAGE_NONE; ++i ) {
		delete mImageArr[ i ];
		mImageArr[ i ] = 0;
	}

	AnimeState* target = mFirstNode.next;
	AnimeState* next = 0;
	while( target != &mLastNode ) {
		next = target->next;
		delete target;
		target = next;
	}
}

void Book3::update( MainParent* parent )
{
	int mouseX = Main::HandManager::inst()->getX();
	int mouseY = Main::HandManager::inst()->getY();
	BOOL isClick = Main::SceneManager::isClick;
	BOOL isMouseDown = Main::SceneManager::isMouseDown;
	BOOL wasHit = FALSE;

	Main::HandManager::inst()->setState( Main::HandManager::HAND_NORMAL );
	AnimeState* target = mFirstNode.next;
	while( target != &mLastNode ) {
		switch( target->image ) {
			case IMAGE_00:
				wasHit |= motion00( target, wasHit, isClick, isMouseDown, mouseX, mouseY );
				break;
			case IMAGE_01:
				if( !motion01( target, mouseX, mouseY ) ) target = deleteAnimeState( target );
				break;
			case IMAGE_02:
				motion02( target, mouseX, mouseY );
				break;
			case IMAGE_10:
				wasHit |= motion10( target, wasHit, isClick, isMouseDown, mouseX, mouseY );
				break;
			case IMAGE_11:
				if( !motion11( target, mouseX, mouseY ) ) target = deleteAnimeState( target );
				break;
			case IMAGE_12:
				motion12( target, mouseX, mouseY );
				break;
			case IMAGE_20:
				wasHit |= motion20( target, wasHit, isClick, isMouseDown, mouseX, mouseY );
				break;
			case IMAGE_21:
				if( !motion21( target, mouseX, mouseY ) ) target = deleteAnimeState( target );
				break;
			case IMAGE_22:
				motion22( target, mouseX, mouseY );
				break;
			case IMAGE_30:
				wasHit |= motion30( target, wasHit, isClick, isMouseDown, mouseX, mouseY );
				break;
			case IMAGE_31:
				if( !motion31( target, mouseX, mouseY ) ) target = deleteAnimeState( target );
				break;
			case IMAGE_32:
				motion32( target, mouseX, mouseY );
				break;
			case IMAGE_40:
				wasHit |= motion40( target, wasHit, isClick, isMouseDown, mouseX, mouseY );
				break;
			case IMAGE_41:
				if( !motion41( target, mouseX, mouseY ) ) target = deleteAnimeState( target );
				break;
			case IMAGE_42:
				if( !motion42( target, mouseX, mouseY ) ) target = deleteAnimeState( target );
				break;
		}
		target = target->next;
	}

	if( mouseX > Main::SceneManager::windowWidth - 64 && mouseY > Main::SceneManager::windowHeight - 64 ) {
		if( Main::SceneManager::isClick ) {
			Main::HandManager::inst()->setState( Main::HandManager::HAND_NORMAL );
			parent->moveTo( parent->SEQ_ROOM );
		} else {
			Main::HandManager::inst()->setState( Main::HandManager::HAND_CLOSE );
		}
	}
}

void Book3::draw( HDC& hdc, MainParent* parent )
{
	AnimeState* target = mFirstNode.next;
	while( target != &mLastNode ) {
		mImageArr[ target->image ]->drawWindowOr( target->x, target->y, static_cast< int >( target->count / ANIME_SPEED ) * USE_IMAGE_SIZE, 0, USE_IMAGE_SIZE, USE_IMAGE_SIZE );
		target = target->next;
	}
}

void Book3::newAnimeState( int setX, int setY )
{
	if( setX < SET_MAX_DISTANCE - USE_IMAGE_SIZE_HALF || setX > Main::SceneManager::windowWidth - SET_MAX_DISTANCE - USE_IMAGE_SIZE_HALF ) {
		return;
	}
	if( setY < SET_MAX_DISTANCE - USE_IMAGE_SIZE_HALF || setY > Main::SceneManager::windowHeight - SET_MAX_DISTANCE - USE_IMAGE_SIZE_HALF ) {
		return;
	}
	
	AnimeState* newAnime = new AnimeState();
	AnimeState* temp = mLastNode.prev;

	mLastNode.prev = newAnime;
	temp->next = newAnime;
	newAnime->x = setX;
	newAnime->y = setY;
	newAnime->count = 0;
	newAnime->state = 0;
	newAnime->image = IMAGE_00;
	newAnime->next = &mLastNode;
	newAnime->prev = temp;
}
BOOL Book3::setAnimeState( AnimeState* target, int setX, int setY )
{
	if( setX < SET_MAX_DISTANCE - USE_IMAGE_SIZE_HALF || setX > Main::SceneManager::windowWidth - SET_MAX_DISTANCE - USE_IMAGE_SIZE_HALF ) {
		return FALSE;
	}
	if( setY < SET_MAX_DISTANCE - USE_IMAGE_SIZE_HALF || setY > Main::SceneManager::windowHeight - SET_MAX_DISTANCE - USE_IMAGE_SIZE_HALF ) {
		return FALSE;
	}

	target->x = setX;
	target->y = setY;
	target->count = 0;
	target->state = 0;
	target->image = IMAGE_00;
	return TRUE;
}
void Book3::nextAnimeState( AnimeState* target, ImageID image )
{
	target->count = 0;
	target->state = 0;
	target->image = image;
}
Book3::AnimeState* Book3::deleteAnimeState( AnimeState* target )
{
	AnimeState* next = target->next;
	AnimeState* prev = target->prev;

	delete target;
	target = 0;

	next->prev = prev;
	prev->next = next;
	return prev;
}

#include "Book3Objs.h"

} // namespace Sequence