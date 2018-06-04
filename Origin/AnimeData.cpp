#include "AnimeData.h"
#include "LayerData.h"
#include "DCBitmap.h"

namespace Image {

AnimeData::AnimeData( void ) :
mAnimeNum( 0 )
{
	init( 0, 0 );

	mAnimeData = 0;
}

AnimeData::~AnimeData( void )
{
	for( int i = 0; i < mAnimeNum; ++i ) {
		delete mAnimeData[ i ];
		mAnimeData[ i ] = 0;
	}

	delete[] mAnimeData;
	mAnimeData = 0;
}

void AnimeData::setData( BitmapBase** setData, int setAnimeNum )
{
	mAnimeData = setData;
	mAnimeNum = setAnimeNum;

	init( setData[ 0 ]->mWidth, setData[ 0 ]->mHeight );
}

void AnimeData::drawWindow( void )
{
	for( int i = 0; i < mAnimeNum; ++i ) {
		mAnimeData[ i ]->drawWindow( static_cast< int >( mX - i * 10 ), static_cast< int >( mY ) );
	}
}

void AnimeData::drawWindow( int x, int y )
{
	for( int i = 0; i < mAnimeNum; ++i ) {
		mAnimeData[ i ]->drawWindow( x, y );
	}
}


} // namespace Image