#ifndef INCLUDED_SEQUENCE_MAIN_CHILD_H
#define INCLUDED_SEQUENCE_MAIN_CHILD_H

#include <windows.h>

namespace Sequence {

class MainParent;

class MainChild {
public:
	virtual ~MainChild( void ) {} // 何もしない
	virtual void update( HDC& hdc, MainParent* parent ) = 0; // 中身なし（派生クラスで定義されてないとエラー）
};

} // namespace Sequence

#endif // INCLUDED_SEQUENCE_MAIN_CHILD_H