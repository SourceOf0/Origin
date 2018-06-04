#ifndef INCLUDED_SOUND_EFFECT_BASE_H
#define INCLUDED_SOUND_EFFECT_BASE_H

namespace Sound {

class Track;

class EffectBase {
	public:
		virtual ~EffectBase( void ) {} // �������Ȃ�

		// ���g�Ȃ��i�h���N���X�Œ�`����ĂȂ��ƃG���[�j
		virtual void reset( void ) = 0;
		virtual void apply( Track* track ) = 0;
};

} // namespace Sound

#endif // INCLUDED_SOUND_EFFECT_BASE_H