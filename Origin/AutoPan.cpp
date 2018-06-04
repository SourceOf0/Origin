#include "AutoPan.h"
#include "SoundBase.h"

#define _USE_MATH_DEFINES
#include <Math.h>

namespace Sound {

AutoPan::AutoPan( void ) :
mDepth( 1.0 ),
mRate( 1.0 ),
mIsUse( FALSE )
{
}


AutoPan::~AutoPan( void )
{
}

void AutoPan::reset( void )
{
	mDepth = 1.0;
	mRate = 1.0;
	mIsUse = FALSE;
}

void AutoPan::setRate( double rate )
{
	mRate = rate;
}

// オートパンL
double AutoPan::applyL( double target, double time )
{
	if( !mIsUse ) return target;
	return target * ( 1.0 + mDepth * sin( 2.0 * M_PI * mRate * time / SAMPLES_PER_SEC ) );
}

// オートパンR
double AutoPan::applyR( double target, double time )
{
	if( !mIsUse ) return target;
	return target * ( 1.0 + mDepth * sin( 2.0 * M_PI * mRate * time / SAMPLES_PER_SEC + M_PI ) );
}


} // namespace Sound