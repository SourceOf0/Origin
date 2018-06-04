#ifndef INCLUDED_IMAGE_ANIME_DATA_H
#define INCLUDED_IMAGE_ANIME_DATA_H

#include <windows.h>
#include "BitmapBase.h"

namespace Image {

class BitmapBase;

class AnimeData : public BitmapBase
{
public:
	AnimeData( void );
	~AnimeData( void );

	void setData( BitmapBase** setData, int setAnimeNum );

	void drawWindow( void );
	void drawWindow( int x, int y );

	int mAnimeNum;

private :
	BitmapBase** mAnimeData;
};

} // namespace Image

#endif // INCLUDED_IMAGE_ANIME_DATA_H