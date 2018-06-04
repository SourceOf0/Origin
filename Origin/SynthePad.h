
void Synthesizer::padInit( void )
{
	for( int i = 0; i < TRACK_NUM; ++i ) {
		for( int j = 0; j < NOTE_SET_MAX_NUM; ++j ) {
			mNoteRatio[ i ][ j ] = -1.0;
		}
	}
}

BOOL Synthesizer::updatePad( BOOL isHit, BOOL isClick, int mouseX, int mouseY )
{
	Main::SoundManager* soundManager = Main::SoundManager::inst();
	BOOL isPlay = FALSE;
	int hitX1 = 581;
	int hitY1 = 417;
	int disX = 22;
	int disY = 21;
	int hitX2 = hitX1 + NOTE_SET_MAX_NUM * disX;
	int hitY2 = hitY1 + NOTE_HEIGHT_NUM * disY;

	if( checkHit( mScaleDial, mouseX , mouseY ) ) {
		isHit = TRUE;
		if( isClick ) {
			if( mouseX < mScaleDial.x + 30 ) {
				mScaleSign.defY = mScaleSign.defY + 1;
				if( mScaleSign.defY <= PARTS_SIGN_SCALE_BM ) {
					if( mScaleDial.defX == 100 ) mScaleDial.defX = 0;
				} else {
					mScaleSign.defY = PARTS_SIGN_SCALE_BM;
				}
			} else {
				mScaleSign.defY = mScaleSign.defY - 1;
				if( mScaleSign.defY >= PARTS_SIGN_SCALE_C ) {
					if( mScaleDial.defX == 100 ) mScaleDial.defX = 0;
				} else {
					mScaleSign.defY = PARTS_SIGN_SCALE_C;
				}
			}
			mHandState = Main::HandManager::HAND_PUSH_AFTER;
		} else {
			mHandState = Main::HandManager::HAND_PUSH_BEFORE;
		}
	}
	updateDial( -1, mScaleDial, mScaleSign );

	for( int i = 0 ; i < PAD_FADER_NUM; ++i ) {
		PartsData& target = mPadFader[ i ];
		if( checkHit( target, mouseX , mouseY ) ) {
			if( !isHit ) {
				int setX = mouseX - 5;
				if( setX < target.defX ) setX = target.defX;
				if( setX > target.hitX2 - 10 ) setX = target.hitX2 - 10;
				target.x = setX;
				isHit = TRUE;
				Main::HandManager::inst()->lockY();
				Main::HandManager::inst()->setRangeX( target.defX + 5, target.hitX2 - 5 );
				mHandState = Main::HandManager::HAND_HOLD_AFTER;
				if( i != 1 ) continue;
				mNoteRatio[ getSelectTrack() ][ mPlayTime ] = getFaderH( target ) * ( NOTE_HEIGHT_NUM - 1 );
			} else {
				mHandState = Main::HandManager::HAND_HOLD_BEFORE;
			}
		}
		if( i != 0 ) continue;
		mTempo = static_cast< int >( ( 1 - getFaderH( target ) ) * 80 + 4 );
	}

	for( int i = 0; i < NOTE_SET_MAX_NUM; ++i ) {
		if( checkHit( mTimeLampX[ i ], mouseX , mouseY ) ) {
			if( !isHit ) {
				isHit = TRUE;
				if( isClick ) {
					mPlayTime = i;
					mPlayCount = 0;
					mHandState = Main::HandManager::HAND_PUSH_AFTER;
				} else {
					mHandState = Main::HandManager::HAND_PUSH_BEFORE;
				}
			} else if( mHandState != Main::HandManager::HAND_PUSH_AFTER ) {
				mHandState = Main::HandManager::HAND_PUSH_BEFORE;
			}
		}
	}
	for( int i = 0; i < NOTE_SET_MAX_NUM; ++i ) {
		mTimeLampX[ i ].defX = ( mPlayTime == i )? 0 : 100;
	}

	if( mouseX > hitX1 && mouseX < hitX2 && mouseY > hitY1 && mouseY < hitY2 ) {
		isHit = TRUE;
		if( isClick ) {
			int targetX = ( mouseX - hitX1 ) / disX;
			int targetY = ( mouseY - hitY1 ) / disY;
			int trackIndex = getSelectTrack();
			if( mNoteRatio[ trackIndex ][ targetX ] == targetY ) {
				mNoteRatio[ trackIndex ][ targetX ] = -1.0;
			} else {
				mNoteRatio[ trackIndex ][ targetX ] = targetY;
			}
			mHandState = Main::HandManager::HAND_PUSH_AFTER;
		} else {
			mHandState = Main::HandManager::HAND_PUSH_BEFORE;
		}
	}

	if( mPlayButton[ 0 ].partsID == PARTS_BUTTON_PLAY_ON ) {
		isPlay = TRUE;
		++mPlayCount;
	}
	if( mPlayButton[ 1 ].partsID == PARTS_BUTTON_PLAY_ON ) {
		isPlay = TRUE;
		mPlayCount = 0;
	}
	if( mPlayButton[ 2 ].partsID == PARTS_BUTTON_PLAY_ON ) {
		isPlay = TRUE;
		mPlayCount = 0;
		for( int i = 0 ; i < KEY_NUM; ++i ) {
			if( mKeyButton[ i ].partsID == PARTS_BUTTON_KEY_OFF ) continue;
			mNoteRatio[ getSelectTrack() ][ mPlayTime ] = getCodeRatio( i );
			break;
		}
	}

	for( int i = 0; i < TRACK_NUM; ++i ) {
		for( int j = 0; j < NOTE_SET_MAX_NUM; ++j ) {
			int noteIndex = static_cast< int >( mNoteRatio[ i ][ j ] );
			double nodeRatio = mNoteRatio[ i ][ j ] - noteIndex;
			PartsData& target = mNoteLamp[ i ][ j ];
			if( noteIndex < 0 ) {
				target.defX = 100;
			} else {
				target.defX = 0;
				target.partsID = ( getSelectTrack() == i )? PARTS_LAMP_NOTE_1 : PARTS_LAMP_NOTE_2;
				if( ( noteIndex + 1 ) < NOTE_HEIGHT_NUM ) {
					target.x = static_cast< int >( mNotePosX[ noteIndex ][ j ] + ( mNotePosX[ noteIndex + 1 ][ j ] - mNotePosX[ noteIndex ][ j ] ) * nodeRatio + 0.5 );
					target.y = static_cast< int >( mNotePosY[ noteIndex ][ j ] + ( mNotePosY[ noteIndex + 1 ][ j ] - mNotePosY[ noteIndex ][ j ] ) * nodeRatio + 0.5 );
				} else if( noteIndex < NOTE_HEIGHT_NUM ) {
					target.x = mNotePosX[ noteIndex ][ j ];
					target.y = mNotePosY[ noteIndex ][ j ];
				} else {
					target.x = mNotePosX[ NOTE_HEIGHT_NUM - 1 ][ j ];
					target.y = mNotePosY[ NOTE_HEIGHT_NUM - 1 ][ j ];
				}
			}
		}
	}

	if( isPlay ) {
		if( mPlayCount >= mTempo ) {
			mPlayCount = 0;
			mPlayTime = ( mPlayTime + 1 ) % NOTE_SET_MAX_NUM;
		}
		for( int i = 0 ; i < TRACK_NUM; ++i ) {
			mPlayWaveID[ i ] = ( WaveID )( mWaveSign[ i ].partsID - PARTS_SIGN_CURVE );
			soundManager->getTrack( i )->setF( getFixCodeHz( mNoteRatio[ i ][ mPlayTime ] ) );
		}
	}

	return isHit;
}

double Synthesizer::getCodeRatio( int seed )
{
	int scale = mScaleSign.partsID - PARTS_SIGN_SCALE_C;
	int scaleHalf = scale / 2;
	double ret = 0.0;

	if( seed < scaleHalf || seed > ( scaleHalf + 12 ) ) return -1.0;

	switch( seed - scaleHalf ) {
		case 0:
			ret = 0.0;
			break;
		case 1:
			ret = 0.5;
			break;
		case 2:
			ret = 1.0;
			break;
		case 3:
			ret = ( scale % 2 == 0 )? 1.5 : 2.0;
			break;
		case 4:
			ret = ( scale % 2 == 0 )? 2.0 : 2.5;
			break;
		case 5:
			ret = 3.0;
			break;
		case 6:
			ret = 3.5;
			break;
		case 7:
			ret = 4.0;
			break;
		case 8:
			ret = ( scale % 2 == 0 )? 4.5 : 5.0;
			break;
		case 9:
			ret = ( scale % 2 == 0 )? 5.0 : 5.5;
			break;
		case 10:
			ret = ( scale % 2 == 0 )? 5.5 : 6.0;
			break;
		case 11:
			ret = ( scale % 2 == 0 )? 6.0 : 6.5;
			break;
		case 12:
			ret = 7.0;
			break;
	}

	return ( 7.0 - ret );
}

double Synthesizer::getFixCodeHz( double seed )
{
	if( seed < 0.0 ) return 0.0;

	seed = NOTE_HEIGHT_NUM - 1 - seed;
	int noteIndex = static_cast< int >( seed );
	double noteRatio = seed - noteIndex;
	double ret = 0;

	if( noteIndex >= NOTE_HEIGHT_NUM ) {
		noteIndex = NOTE_HEIGHT_NUM - 1;
	}

	ret = getCodeHz( noteIndex );
	if( ( noteIndex + 1 ) < NOTE_HEIGHT_NUM ) {
		ret += ( getCodeHz( noteIndex + 1 ) - ret ) * noteRatio;
	}

	return ret;
}

double Synthesizer::getCodeHz( int seed )
{
	int scale = mScaleSign.partsID - PARTS_SIGN_SCALE_C;
	int hzIndex = 0;

	switch( seed ) {
		case 0:
			hzIndex = 0;
			break;
		case 1:
			hzIndex = 2;
			break;
		case 2:
			hzIndex = ( ( scale ) % 2 == 0 )? 4 : 3;
			break;
		case 3:
			hzIndex = 5;
			break;
		case 4:
			hzIndex = 7;
			break;
		case 5:
			hzIndex = ( ( scale ) % 2 == 0 )? 9 : 8;
			break;
		case 6:
			hzIndex = ( ( scale ) % 2 == 0 )? 11 : 10;
			break;
		case 7:
			hzIndex = 12;
			break;
	}

	return getHz( hzIndex + static_cast< int >( scale / 2 ) );
}

#include <Math.h>
double Synthesizer::getHz( double seed )
{
	if( seed < 0 ) return 0.0;
	return pow( 2.0, ( seed - 9 ) / 12.0 ) * 440.0;
}
