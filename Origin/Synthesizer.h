#ifndef INCLUDED_SEQUENCE_ROOM_SYNTHESIZER_H
#define INCLUDED_SEQUENCE_ROOM_SYNTHESIZER_H

#include "RoomChild.h"
#include "SoundBase.h"

#include "Dial.h"
#include "FaderH.h"
#include "FaderV.h"
#include "Lever.h"
#include "TimeLamp.h"
#include "KeyButton.h"
#include "AutoPanButton.h"
#include "TrackButton.h"
#include "PlayButton.h"
#include "ViewObj.h"

#define EFFECT_FADER_NUM 18
#define EQ_FADER_NUM 18
#define EFFECT_SELECT_NUM 9
#define EFFECT_EQ_NUM 9
#define TRACK_NUM 3
#define VOLUME_FADER_NUM 8
#define KEY_NUM 24
#define PAD_FADER_NUM 2
#define PLAY_BUTTON_NUM 3

#define NOTE_SET_MAX_NUM 16
#define NOTE_HEIGHT_NUM 8

namespace Image {
	class LayerData;
	class DCBitmap;
}

namespace Sequence {

class RoomParent;

namespace Room {

class Synthesizer : public RoomChild {
public:
	Synthesizer( HDC& hdc, Sequence::RoomParent* parent );
	~Synthesizer( void );
	void update( Sequence::RoomParent* parent );
	void draw( HDC& hdc, Sequence::RoomParent* parent, double depth, int fadeCount );
	void playTrack( Sequence::RoomParent* parent );

private:
	void posInit( void );
	void setEffectFaderPos( void );
	void setEQFaderPos( void );
	void setEffectDialPos( void );
	void setWaveDialPos( void );
	void setVolumeFaderPos( void );
	void setAutoPanButtonPos( void );
	void setTrackButtonPos( void );
	void setEQLeverPos( void );
	void setKeyButtonPos( void );
	void setPlayButtonPos( void );
	void setScaleDialPos( void );
	void setPadFaderPos( void );
	void setNoteLampPos( void );
	void setTimeLampPos( void );
	
	void padInit( void );

	EffectID getEffectID( PartsID id );
	WaveID getWaveID( PartsID id );

	double getCodeRatio( int seed ); /* 0 <= seed <= 23 */
	double getFixCodeHz( double seed ); /* 0.0 <= seed <= NOTE_HEIGHT_NUM(8.0) */
	double getCodeHz( int seed ); /* 0 <= seed <= NOTE_HEIGHT_NUM(8) */
	double getHz( double seed ); /* 0.0 <= seed <= 23.0 */
	int getSelectTrack( void );

	BOOL checkHit( void );
	BOOL checkHitPad( void );
	void updateWave( void );
	void initSoundState( void );
	void updatePad( BOOL isConnectSocket );
	void setNoteRatio( double setRatio, int trackIndex, int time );

	static BOOL mIsInit;

	Image::LayerData* mBackBmp1;
	Image::LayerData* mBackBmp2;
	Image::LayerData* mPartsBmp;
	Image::DCBitmap* mWaveBmp;
	Image::DCBitmap* mPadBmp;

	FaderV mEffectFader[ EFFECT_FADER_NUM ];
	FaderV mEQFader[ EQ_FADER_NUM ];
	Dial mEffectDial[ EFFECT_SELECT_NUM ];
	Dial mWaveDial[ TRACK_NUM ];

	FaderH mVolumeFader[ VOLUME_FADER_NUM ];
	AutoPanButton mAutoPanButton[ TRACK_NUM ];
	TrackButton mTrackButton[ TRACK_NUM ];
	Lever mEQLever[ EFFECT_EQ_NUM ];
	KeyButton mKeyButton[ KEY_NUM ];
	PlayButton mPlayButton[ PLAY_BUTTON_NUM ];
	Dial mScaleDial;
	FaderH mPadFader[ PAD_FADER_NUM ];
	ViewObj mNoteLamp[ TRACK_NUM ][ NOTE_SET_MAX_NUM ];
	TimeLamp mTimeLamp[ NOTE_SET_MAX_NUM ];

	WaveID mPlayWaveID[ TRACK_NUM ];

	int mNotePosX[ NOTE_HEIGHT_NUM ][ NOTE_SET_MAX_NUM ];
	int mNotePosY[ NOTE_HEIGHT_NUM ][ NOTE_SET_MAX_NUM ];
	double mNoteRatio[ TRACK_NUM ][ NOTE_SET_MAX_NUM ]; /* 0.0 < val < 7.0 */
	int mPlayTime;
	int mPlayCount;
	int mTempo;
};

} //namespace Room
} //namespace Sequence

#endif // INCLUDED_SEQUENCE_ROOM_SYNTHESIZER_H
