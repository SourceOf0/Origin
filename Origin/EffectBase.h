#ifndef INCLUDED_SOUND_EFFECT_BASE_H
#define INCLUDED_SOUND_EFFECT_BASE_H

namespace Sound {

class Track;

class EffectBase {
	public:
		virtual ~EffectBase( void ) {} // 何もしない

		// 中身なし（派生クラスで定義されてないとエラー）
		virtual void reset( void ) = 0;
		virtual void apply( Track* track ) = 0;
};

} // namespace Sound

#endif // INCLUDED_SOUND_EFFECT_BASE_H