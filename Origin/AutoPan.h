#ifndef INCLUDED_SOUND_AUTO_PAN_H
#define INCLUDED_SOUND_AUTO_PAN_H

namespace Sound {

class Track;

class AutoPan
{
public:
	AutoPan( void );
	~AutoPan( void );

	void reset( void );
	double applyL( double target, int time );
	double applyR( double target, int time );

	bool mIsUse;

private:
	double mDepth;
	double mRate;
};

} // namespace Sound

#endif // INCLUDED_SOUND_AUTO_PAN_H