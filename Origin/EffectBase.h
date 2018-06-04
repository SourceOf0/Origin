#ifndef INCLUDED_SOUND_EFFECT_BASE_H
#define INCLUDED_SOUND_EFFECT_BASE_H

#include "SoundBase.h"

#define M_PI 3.14159265358979323846
#define SIN_COS_TABLE_NUM 4500

#define customSin(x) (customCos(x-M_PI/2))
#define customTan(x) (customSin(x) / customCos(x))

namespace Sound {

class Track;

class EffectBase {
public:
	virtual ~EffectBase( void ) {} // 何もしない
	
	// 中身なし（派生クラスで定義されてないとエラー）
	virtual void reset( void ) = 0;
	virtual void apply( Track* track ) = 0;
	static void initTable( void );

	static double customPow( double x, double y );
	static double customSqrt( double x );
	static double customAtan( double x );
	static double customCos( double x );
	static double sinc( double x );

	void setNum1( double val );
	void setNum2( double val );
	double getNum1( void );
	double getNum2( void );

protected:
	void init( double waveLog[ LOG_MAX_DATA_NUM ][ WAVE_DATA_LENGTH ] );

	void getHanningWindow( double* w, int N );

	double getPrevData( double waveLog[ LOG_MAX_DATA_NUM ][ WAVE_DATA_LENGTH ], int prevIndex );

	double mSetNum1;
	double mSetNum2;

	int mLogIndex;

private:
	static double mSinCosTable[ SIN_COS_TABLE_NUM ];

};

} // namespace Sound

#endif // INCLUDED_SOUND_EFFECT_BASE_H