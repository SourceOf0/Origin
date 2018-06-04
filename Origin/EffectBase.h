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

	void setNum1( double val );
	void setNum2( double val );
	double getNum1( void );
	double getNum2( void );

protected:
	void init( double** setWaveLog );

	double sinc( double x );
	void getHanningWindow( double* w, int N );

	double getPrevData( int prevIndex );

	double mSetNum1;
	double mSetNum2;

	int mLogIndex;
	double** mWaveLog;
};

} // namespace Sound

#endif // INCLUDED_SOUND_EFFECT_BASE_H