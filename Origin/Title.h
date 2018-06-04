#ifndef INCLUDED_SEQUENCE_TITLE_H
#define INCLUDED_SEQUENCE_TITLE_H

#include "MainChild.h"

namespace Sequence {

class MainParent;

class Title : public MainChild {
public:
	Title( HDC& hdc, MainParent* parent );
	~Title( void );
	void update( MainParent* parent );
	void draw( HDC& hdc, MainParent* parent );

private:
};

} //namespace Sequence

#endif // INCLUDED_SEQUENCE_TITLE_H
