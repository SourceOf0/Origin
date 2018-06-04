#include "MainParent.h"
#include "MainChild.h"
#include "Title.h"

#include "ImageFactory.h"

#include "PixelBitmap.h"
#include "DCBitmap.h"

namespace Sequence {

Title::Title( HDC& hdc )
{
	testBmp = Main::ImageFactory::inst()->load( "file.txt" );
	testBmp2 = new Common::DCBitmap( hdc, testBmp );
	testX = 5;
	testY = 0;
}

Title::~Title()
{
	delete testBmp;
	testBmp = 0;

	delete testBmp2;
	testBmp2 = 0;
}

void Title::update( HDC& hdc, MainParent* parent )
{
	testBmp->drawWindow();
//	testBmp->setWhite( testX, testY - 1 );
//	testBmp->setBlack( testX, testY );
	testBmp->setRev( testX, testY );
/*	if( testBmp->getBit( testX, testY ) == 0 ) {
		testBmp->setWhite( testX, testY );
	} else {
		testBmp->setBlack( testX, testY );
	}*/
	++testY;
//	testBmp->mX += 1;
	testBmp2->drawWindow();
	testBmp2->mY += 1;
}

} // namespace Sequence