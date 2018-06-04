#ifndef INCLUDED_SOUND_AUTO_PAN_H
#define INCLUDED_SOUND_AUTO_PAN_H

#include <windows.h>

namespace Sound {

class Track;

class AutoPan
{
public:
	AutoPan( void );
	~AutoPan( void );

	void reset( void );
	void setRate( double rate );
	double applyL( double target, double time );
	double applyR( double target, double time );

	BOOL mIsUse;

private:
	double mDepth;
	double mRate;
};

} // namespace Sound

#endif // INCLUDED_SOUND_AUTO_PAN_H