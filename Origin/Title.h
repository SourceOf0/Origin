#ifndef INCLUDED_SEQUENCE_TITLE_H
#define INCLUDED_SEQUENCE_TITLE_H

#include "MainChild.h"

namespace Common {
	class PixelBitmap;
	class DCBitmap;
}

namespace Sequence {
class MainParent;

class Title : public MainChild {
	public:
		Title( HDC& hdc );
		~Title( void );
		void update( HDC& hdc, MainParent* parent );
private:
	Common::PixelBitmap* testBmp;
	Common::DCBitmap* testBmp2;
	int testX;
	int testY;
};

} //namespace Sequence

#endif
