#ifndef INCLUDED_SEQUENCE_BOOK3_H
#define INCLUDED_SEQUENCE_BOOK3_H

#include "MainChild.h"

namespace Image {
	class DCBitmap;
}

namespace Sequence {

class MainParent;

class Book3 : public MainChild {
public:
	Book3( HDC& hdc, MainParent* parent );
	~Book3( void );
	void update( MainParent* parent );
	void draw( HDC& hdc, MainParent* parent );

private:
	enum ImageID {
		IMAGE_00,
		IMAGE_01,
		IMAGE_02,
		IMAGE_10,
		IMAGE_11,
		IMAGE_12,
		IMAGE_20,
		IMAGE_21,
		IMAGE_22,
		IMAGE_30,
		IMAGE_31,
		IMAGE_32,
		IMAGE_40,
		IMAGE_41,
		IMAGE_42,

		IMAGE_NONE
	};

	typedef struct _ANIME_STATE {
		int x;
		int y;
		int count;
		int state;
		ImageID image;
		_ANIME_STATE* next;
		_ANIME_STATE* prev;
	} AnimeState;

	void newAnimeState( int setX, int setY );
	BOOL setAnimeState( AnimeState* target, int setX, int setY );
	void nextAnimeState( AnimeState* target, ImageID image );
	AnimeState* deleteAnimeState( AnimeState* target );

	BOOL motion00( AnimeState* target, BOOL wasHit, BOOL isClick, BOOL isMouseDown,int mouseX, int mouseY );
	BOOL motion01( AnimeState* target, int mouseX, int mouseY );
	void motion02( AnimeState* target, int mouseX, int mouseY );
	BOOL motion10( AnimeState* target, BOOL wasHit, BOOL isClick, BOOL isMouseDown, int mouseX, int mouseY );
	BOOL motion11( AnimeState* target, int mouseX, int mouseY );
	void motion12( AnimeState* target, int mouseX, int mouseY );
	BOOL motion20( AnimeState* target, BOOL wasHit, BOOL isClick, BOOL isMouseDown, int mouseX, int mouseY );
	BOOL motion21( AnimeState* target, int mouseX, int mouseY );
	void motion22( AnimeState* target, int mouseX, int mouseY );
	BOOL motion30( AnimeState* target, BOOL wasHit, BOOL isClick, BOOL isMouseDown, int mouseX, int mouseY );
	BOOL motion31( AnimeState* target, int mouseX, int mouseY );
	void motion32( AnimeState* target, int mouseX, int mouseY );
	BOOL motion40( AnimeState* target, BOOL wasHit, BOOL isClick, BOOL isMouseDown, int mouseX, int mouseY );
	BOOL motion41( AnimeState* target, int mouseX, int mouseY );
	BOOL motion42( AnimeState* target, int mouseX, int mouseY );

	Image::DCBitmap* mImageArr[ IMAGE_NONE ];
	AnimeState mFirstNode;
	AnimeState mLastNode;

};

} //namespace Sequence

#endif // INCLUDED_SEQUENCE_BOOK3_H
