#ifndef INCLUDED_SEQUENCE_MAIN_CHILD_H
#define INCLUDED_SEQUENCE_MAIN_CHILD_H

#include <windows.h>

namespace Sequence {

class MainParent;

class MainChild {
public:
	virtual ~MainChild( void ) {} // �������Ȃ�
	virtual void update( HDC& hdc, MainParent* parent ) = 0; // ���g�Ȃ��i�h���N���X�Œ�`����ĂȂ��ƃG���[�j
};

} // namespace Sequence

#endif // INCLUDED_SEQUENCE_MAIN_CHILD_H