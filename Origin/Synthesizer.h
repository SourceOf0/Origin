#ifndef INCLUDED_SEQUENCE_ROOM_SYNTHESIZER_H
#define INCLUDED_SEQUENCE_ROOM_SYNTHESIZER_H

#include "RoomChild.h"
#include "SoundBase.h"

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
	void draw( HDC& hdc, Sequence::RoomParent* parent );
	void playTrack( void );

private:
	enum PartsID {
		PARTS_BUTTON_AUTOPAN_ON,
		PARTS_BUTTON_AUTOPAN_OFF,
		PARTS_BUTTON_TRACK_ON,
		PARTS_BUTTON_TRACK_OFF,
		PARTS_BUTTON_PLAY_ON,
		PARTS_BUTTON_PLAY_OFF,
		PARTS_BUTTON_KEY_ON,
		PARTS_BUTTON_KEY_OFF,
		PARTS_FADER_H,
		PARTS_FADER_V,
		PARTS_LEVER_1,
		PARTS_LEVER_2,
		PARTS_LEVER_3,
		PARTS_LEVER_4,
		PARTS_DIAL_1,
		PARTS_DIAL_2,
		PARTS_LAMP_TIME,
		PARTS_LAMP_NOTE_1,
		PARTS_LAMP_NOTE_2,

		PARTS_SIGN_PLAY,
		PARTS_SIGN_PAUSE,
		PARTS_SIGN_REC,

		PARTS_SIGN_CURVE,
		PARTS_SIGN_SAWTOOTH,
		PARTS_SIGN_SQUARE,
		PARTS_SIGN_TRIANGLE,

		PARTS_SIGN_NOISE_GATE,
		PARTS_SIGN_DISTORTION1,
		PARTS_SIGN_DISTORTION2,
		PARTS_SIGN_DISTORTION3,
		PARTS_SIGN_COMPRESSOR,
		PARTS_SIGN_TREMOLO,
		PARTS_SIGN_DELAY,
		PARTS_SIGN_CHORUS,
		PARTS_SIGN_VIBRATO,
		PARTS_SIGN_LOW_PASS_FILTER,
		PARTS_SIGN_HIGH_PASS_FILTER,
		PARTS_SIGN_BAND_PASS_FILTER,
		PARTS_SIGN_BAND_ELIMINATE_FILTER,
//		PARTS_SIGN_EQUALIZER,

		PARTS_SIGN_SCALE_C,
		PARTS_SIGN_SCALE_CM,
		PARTS_SIGN_SCALE_D,
		PARTS_SIGN_SCALE_DM,
		PARTS_SIGN_SCALE_E,
		PARTS_SIGN_SCALE_EM,
		PARTS_SIGN_SCALE_F,
		PARTS_SIGN_SCALE_FM,
		PARTS_SIGN_SCALE_G,
		PARTS_SIGN_SCALE_GM,
		PARTS_SIGN_SCALE_A,
		PARTS_SIGN_SCALE_AM,
		PARTS_SIGN_SCALE_B,
		PARTS_SIGN_SCALE_BM,

		PARTS_NONE
	};

	typedef struct _PARTS_SIZE {
		int startX;
		int startY;
		int width;
		int height;
	} PartsSize;

	typedef struct _PARTS_DATA {
		PartsID partsID;
		int x;
		int y;
		int defX;
		int defY;
		int hitX1;
		int hitY1;
		int hitX2;
		int hitY2;
	} PartsData;

	void posInit( void );
	void setEffectFaderPos( void );
	void setEQFaderPos( void );
	void setEffectSignPos( void );
	void setEffectDialPos( void );
	void setWaveSignPos( void );
	void setWaveDialPos( void );
	void setVolumeFaderPos( void );
	void setAutoPanButtonPos( void );
	void setTrackButtonPos( void );
	void setEQLeverPos( void );
	void setKeyButtonPos( void );
	void setPlayButtonPos( void );
	void setScaleSignPos( void );
	void setScaleDialPos( void );
	void setPadFaderPos( void );
	void setNoteLampPos( void );
	void setTimeLampPos( void );
	void setPos( PartsData& target, PartsID id, int x, int y );
	void fixHitRange( PartsData& target, int fixX1, int fixY1, int fixX2, int fixY2 );

	void sizeInit( void );
	void setSize( PartsID id, int startX, int startY, int width, int height );
	
	void padInit( void );

	BOOL checkHit( PartsData& target, int x, int y );
	double getCodeRatio( int seed ); /* 0 <= seed <= 23 */
	double getFixCodeHz( double seed ); /* 0.0 <= seed <= NOTE_HEIGHT_NUM(8.0) */
	double getCodeHz( int seed ); /* 0 <= seed <= NOTE_HEIGHT_NUM(8) */
	double getHz( double seed ); /* 0.0 <= seed <= 23.0 */
	int getSelectTrack( void );
	double getFaderH( PartsData& target );
	double getFaderV( PartsData& target );
	void updateDial( int index, PartsData& target, PartsData& targetSign );
	void updateWave( void );
	void updateSoundState( void );
	BOOL updatePad( BOOL isHit, BOOL isClick, int mouseX, int mouseY );

	void viewParts( PartsData& target, BOOL isTransparent = FALSE );
	void viewSign( PartsData& target );

	static BOOL mIsInit;

	Image::LayerData* mBackBmp;
	Image::LayerData* mPartsBmp;
	Image::DCBitmap* mWaveBmp;
	Image::DCBitmap* mPadBmp;

	PartsSize mPartsSize[ PARTS_NONE ];

	PartsData mEffectFader[ EFFECT_FADER_NUM ];
	PartsData mEQFader[ EQ_FADER_NUM ];
	PartsData mEffectSign[ EFFECT_SELECT_NUM ];
	PartsData mEffectDial[ EFFECT_SELECT_NUM ];
	PartsData mWaveSign[ TRACK_NUM ];
	PartsData mWaveDial[ TRACK_NUM ];
	PartsData mVolumeFader[ VOLUME_FADER_NUM ];
	PartsData mAutoPanButton[ TRACK_NUM ];
	PartsData mTrackButton[ TRACK_NUM ];
	PartsData mEQLever[ EFFECT_EQ_NUM ];
	PartsData mKeyButton[ KEY_NUM ];
	PartsData mPlayButton[ PLAY_BUTTON_NUM ];
	PartsData mPlaySign[ PLAY_BUTTON_NUM ];
	PartsData mScaleSign;
	PartsData mScaleDial;
	PartsData mPadFader[ PAD_FADER_NUM ];
	PartsData mNoteLamp[ TRACK_NUM ][ NOTE_SET_MAX_NUM ];
	PartsData mTimeLampX[ NOTE_SET_MAX_NUM ];

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
