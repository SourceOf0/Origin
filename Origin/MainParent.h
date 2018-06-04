#ifndef INCLUDED_SEQUENCE_MAIN_PARENT_H
#define INCLUDED_SEQUENCE_MAIN_PARENT_H

#include <windows.h>

namespace Sequence {
	
class MainChild;

class MainParent {
public:
	enum SeqID {
		SEQ_TITLE,
	
		SEQ_NONE
	};
	MainParent( HDC& hdc );
	~MainParent( void );
	void update( void );
	void draw( HDC& hdc );
	void moveTo( SeqID );
private:
	MainChild* mChild;

	SeqID mNext;
};

} //namespace Sequence

#endif // INCLUDED_SEQUENCE_MAIN_PARENT_H
