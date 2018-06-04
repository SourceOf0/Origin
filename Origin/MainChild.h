#ifndef INCLUDED_SEQUENCE_MAIN_CHILD_H
#define INCLUDED_SEQUENCE_MAIN_CHILD_H

#include <windows.h>

#define BOOK_CORNAR_HIT_SIZE 32

namespace Sequence {

class MainParent;

class MainChild {
public:
	virtual ~MainChild( void ) {} // �������Ȃ�
	
	// ���g�Ȃ��i�h���N���X�Œ�`����ĂȂ��ƃG���[�j
	virtual void update( MainParent* parent ) = 0; 
	virtual void draw( HDC& hdc, MainParent* parent ) = 0;
};

} // namespace Sequence

#endif // INCLUDED_SEQUENCE_MAIN_CHILD_H