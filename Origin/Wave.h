#ifndef INCLUDED_SOUND_SAWTOOTH_WAVE_H
#define INCLUDED_SOUND_SAWTOOTH_WAVE_H

#include "SoundBase.h"

namespace Sound {

class Track;

class Wave {

public:
	Wave( void );
	~Wave( void );
	void reset( void );

	void setF( double f );
	double getF( void );
	void setVol( double vol );
	void setData( Track* track, WaveID id );

private:
	void setCurve( Track* track );
	void setSawtooth( Track* track );
	void setSquare( Track* track );
	void setTriangle( Track* track );
	void setSilent( Track* track );

	double mA;
	double mRatio;
	double mF;
	double mTargetF;
};

} //namespace Sound

#endif // INCLUDED_SOUND_SAWTOOTH_WAVE_H
