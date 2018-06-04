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

	double mSetNum1;
	double mSetNum2;
	double mSetNum3;

protected:
	void init( double** setWaveLog, double set1, double set2, double set3 );

	double sinc( double x );
	void getHanningWindow( double* w, int N );

	double getPrevData( int prevIndex );

	int mLogIndex;
	double** mWaveLog;
};

} // namespace Sound

#endif // INCLUDED_SOUND_EFFECT_BASE_H