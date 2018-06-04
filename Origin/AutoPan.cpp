#include "AutoPan.h"
#include "SoundBase.h"

#define _USE_MATH_DEFINES
#include <Math.h>

namespace Sound {

AutoPan::AutoPan( void ) :
mDepth( 1.0 ),
mRate( 0.2 ),
mIsUse( false )
{
}


AutoPan::~AutoPan( void )
{
}

void AutoPan::reset( void )
{
}

// オートパンL
double AutoPan::applyL( double target, int time )
{
	if( !mIsUse ) return target;
	return target * ( 1.0 + mDepth * sin( 2.0 * M_PI * mRate * time / SAMPLES_PER_SEC ) );
}

// オートパンR
double AutoPan::applyR( double target, int time )
{
	if( !mIsUse ) return target;
	return target * ( 1.0 + mDepth * sin( 2.0 * M_PI * mRate * time / SAMPLES_PER_SEC + M_PI ) );
}


} // namespace Sound