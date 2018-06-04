#include "PartsBase.h"

namespace Sequence {

namespace Room {


void PartsBase::init( PartsID id, int x, int y )
{
	mPartsID = id;
	mX = x;
	mY = y;
	mHitX1 = x;
	mHitY1 = y;

	setPartsSize( id );
	
	mHitX2 = x + mWidth;
	mHitY2 = y + mHeight;
}

BOOL PartsBase::isHit( int mouseX, int mouseY )
{
	return ( mouseX >= mHitX1 && mouseX <= mHitX2 && mouseY >= mHitY1 && mouseY <= mHitY2 );
}

void PartsBase::setPartsSize( PartsID id )
{
	int scaleSignAdd = 13;

	mPartsID = id;
	switch( id ) {
		case PARTS_BUTTON_AUTOPAN_ON:
			setSize( 0, 0, 41, 28 );
			break;
		case PARTS_BUTTON_AUTOPAN_OFF:
			setSize( 0, 28, 41, 39 );
			break;
		case PARTS_BUTTON_TRACK_ON:
			setSize( 41, 0, 102, 28 );
			break;
		case PARTS_BUTTON_TRACK_OFF:
			setSize( 41, 28, 102, 39 );
			break;
		case PARTS_BUTTON_PLAY_ON:
			setSize( 143, 29, 39, 38 );
			break;
		case PARTS_BUTTON_PLAY_OFF:
			setSize( 182, 29, 39, 44 );
			break;
		case PARTS_BUTTON_KEY_ON:
			setSize( 81, 67, 24, 31 );
			break;
		case PARTS_BUTTON_KEY_OFF:
			setSize( 57, 67, 24, 36 );
			break;

		case PARTS_FADER_H:
			setSize( 197, 73, 11, 31 );
			break;
		case PARTS_FADER_V:
			setSize( 177, 73, 20, 19 );
			break;

		case PARTS_LEVER_1:
			setSize( 143, 0, 20, 29 );
			break;
		case PARTS_LEVER_2:
			setSize( 163, 0, 18, 29 );
			break;
		case PARTS_LEVER_3:
			setSize( 181, 0, 18, 29 );
			break;
		case PARTS_LEVER_4:
			setSize( 199, 0, 20, 29 );
			break;

		case PARTS_DIAL_1:
			setSize( 0, 67, 57, 20 );
			break;
		case PARTS_DIAL_2:
			setSize( 0, 87, 57, 20 );
			break;

		case PARTS_LAMP_TIME:
			setSize( 208, 103, 16, 16 );
			break;
		case PARTS_LAMP_NOTE_1:
			setSize( 208, 73, 16, 15 );
			break;
		case PARTS_LAMP_NOTE_2:
			setSize( 208, 88, 16, 15 );
			break;

		case PARTS_SIGN_PLAY:
			setSize( 0, 107, 17, 20 );
			break;
		case PARTS_SIGN_PAUSE:
			setSize( 17, 107, 15, 20 );
			break;
		case PARTS_SIGN_REC:
			setSize( 32, 107, 21, 21 );
			break;

		case PARTS_SIGN_CURVE:
			setSize( 163, 67, 14, 13 );
			break;
		case PARTS_SIGN_SAWTOOTH:
			setSize( 151, 67, 12, 13 );
			break;
		case PARTS_SIGN_SQUARE:
			setSize( 142, 67, 9, 13 );
			break;
		case PARTS_SIGN_TRIANGLE:
			setSize( 133, 67, 9, 13 );
			break;

		case PARTS_SIGN_NOISE_GATE:
			setSize( 105, 79, 14, 12 );
			break;
		case PARTS_SIGN_DISTORTION1:
			setSize( 80, 98, 12, 16 );
			break;
		case PARTS_SIGN_DISTORTION2:
			setSize( 92, 98, 12, 12 );
			break;
		case PARTS_SIGN_DISTORTION3:
			setSize( 93, 112, 13, 15 );
			break;
		case PARTS_SIGN_COMPRESSOR:
			setSize( 119, 67, 14, 12 );
			break;
		case PARTS_SIGN_TREMOLO:
			setSize( 119, 80, 14, 13 );
			break;
		case PARTS_SIGN_DELAY:
			setSize( 133, 81, 17, 10 );
			break;
		case PARTS_SIGN_CHORUS:
			setSize( 105, 67, 14, 12 );
			break;
		case PARTS_SIGN_VIBRATO:
			setSize( 80, 115, 13, 13 );
			break;
		case PARTS_SIGN_LOW_PASS_FILTER:
			setSize( 57, 116, 11, 12 );
			break;
		case PARTS_SIGN_HIGH_PASS_FILTER:
			setSize( 57, 103, 11, 12 );
			break;
		case PARTS_SIGN_BAND_PASS_FILTER:
			setSize( 69, 103, 11, 12);
			break;
		case PARTS_SIGN_BAND_ELIMINATE_FILTER:
			setSize( 69, 116, 11, 12 );
			break;
//		case PARTS_SIGN_EQUALIZER:

		case PARTS_SIGN_SCALE_C:
			setSize( 105 + scaleSignAdd * 6, 104, 13, 12 );
			break;
		case PARTS_SIGN_SCALE_CM:
			setSize( 105 + scaleSignAdd * 6, 92, 13, 12 );
			break;
		case PARTS_SIGN_SCALE_D:
			setSize( 105 + scaleSignAdd * 5, 104, 13, 12 );
			break;
		case PARTS_SIGN_SCALE_DM:
			setSize( 105 + scaleSignAdd * 5, 92, 13, 12 );
			break;
		case PARTS_SIGN_SCALE_E:
			setSize( 105 + scaleSignAdd * 4, 104, 13, 12 );
			break;
		case PARTS_SIGN_SCALE_EM:
			setSize( 105 + scaleSignAdd * 4, 92, 13, 12 );
			break;
		case PARTS_SIGN_SCALE_F:
			setSize( 105 + scaleSignAdd * 3, 104, 13, 12 );
			break;
		case PARTS_SIGN_SCALE_FM:
			setSize( 105 + scaleSignAdd * 3, 92, 13, 12 );
			break;
		case PARTS_SIGN_SCALE_G:
			setSize( 105 + scaleSignAdd * 2, 104, 13, 12 );
			break;
		case PARTS_SIGN_SCALE_GM:
			setSize( 105 + scaleSignAdd * 2, 92, 13, 12 );
			break;
		case PARTS_SIGN_SCALE_A:
			setSize( 105 + scaleSignAdd * 1, 104, 13, 12 );
			break;
		case PARTS_SIGN_SCALE_AM:
			setSize( 105 + scaleSignAdd * 1, 92, 13, 12 );
			break;
		case PARTS_SIGN_SCALE_B:
			setSize( 105 + scaleSignAdd * 0, 104, 13, 12 );
			break;
		case PARTS_SIGN_SCALE_BM:
			setSize( 105 + scaleSignAdd * 0, 92, 13, 12 );
			break;

		case PARTS_NONE:
			setSize( 0, 0, 0, 0 );
			break;
	}
}

void PartsBase::setSize( int cutStartX, int cutStartY, int width, int height )
{
	mCutStartX = cutStartX;
	mCutStartY = cutStartY;
	mWidth = width;
	mHeight = height;
}


} // namespace Room
} // namespace Sequence
