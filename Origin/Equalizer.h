#ifndef INCLUDED_SOUND_EQUALIZER_H
#define INCLUDED_SOUND_EQUALIZER_H

#include <windows.h>
#include "SoundBase.h"
#include "EffectBase.h"

#define EQDATA_MAX_NUM 3

namespace Sound {

class Track;

class Equalizer : public EffectBase
{
public:
	Equalizer( void );
	~Equalizer( void );

	void reset( void );
	void apply( Track* track );

	void setKind( int index, EQID kind );
	void setState( int index, double fc, double g );

private:
	typedef struct _EQ_DATA {
		BOOL isSetEnd;
		EQID kind;
		double fc;
		double g;
		double a[ 3 ];
		double b[ 3 ];
		double prevData[ 2 ][ 2 ][ 2 ];
	} EQData;

	void setLowShelving( EQData* target );
	void setHighShelving( EQData* target );
	void setPeaking( EQData* target );

	EQData mEQData[ EQDATA_MAX_NUM ];
};

} // namespace Sound

#endif // INCLUDED_SOUND_EQUALIZER_H