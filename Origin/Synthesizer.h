#ifndef INCLUDED_SEQUENCE_ROOM_SYNTHESIZER_H
#define INCLUDED_SEQUENCE_ROOM_SYNTHESIZER_H

#include "RoomChild.h"

#define EFFECT_FADER_NUM 18
#define EQ_FADER_NUM 18
#define EFFECT_SELECT_NUM 9
#define EFFECT_EQ_NUM 9
#define TRACK_NUM 3
#define VOLUME_FADER_NUM 8
#define KEY_NUM 24
#define PLAY_BUTTON_NUM 3

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
		PARTS_RAMP_TIME,
		PARTS_RAMP_NOTE,

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
	void setPos( PartsData& target, PartsID id, int x, int y );
	void fixHitRange( PartsData& target, int fixX1, int fixY1, int fixX2, int fixY2 );

	void sizeInit( void );
	void setSize( PartsID id, int startX, int startY, int width, int height );
	
	BOOL checkHit( PartsData& target, int x, int y );
	double getHz( int index );
	int getSelectTrack( void );
	double getFaderH( PartsData& target );
	double getFaderV( PartsData& target );
	void updateDial( int index, PartsData& target, PartsData& targetSign );
	void updateWave( void );
	void updateSoundState( void );

	void viewParts( PartsData& target );
	void viewSign( PartsData& target );

	static BOOL mIsInit;

	Image::LayerData* mBackBmp;
	Image::LayerData* mPartsBmp;
	Image::DCBitmap* mWaveBmp;

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
};

} //namespace Room
} //namespace Sequence

#endif // INCLUDED_SEQUENCE_ROOM_SYNTHESIZER_H
