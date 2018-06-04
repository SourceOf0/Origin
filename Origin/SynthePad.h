
void Synthesizer::padInit( void )
{
	for( int i = 0; i < TRACK_NUM; ++i ) {
		for( int j = 0; j < NOTE_SET_MAX_NUM; ++j ) {
			mNoteRatio[ i ][ j ] = -1.0;
		}
	}
}

BOOL Synthesizer::checkHitPad( void )
{
	Main::SoundManager* soundManager = Main::SoundManager::inst();
	Main::HandManager* handManager = Main::HandManager::inst();
	int hitX1 = 581;
	int hitY1 = 417;
	int disX = 22;
	int disY = 21;
	int hitX2 = hitX1 + NOTE_SET_MAX_NUM * disX;
	int hitY2 = hitY1 + NOTE_HEIGHT_NUM * disY;

	if( mScaleDial.checkHit() ) return TRUE;

	int playButtonIndex = -1;
	for( int i = 0 ; i < PLAY_BUTTON_NUM; ++i ) {
		if( !mPlayButton[ i ].checkHit() ) continue;
		if( !mPlayButton[ i ].isSwitch() ) continue;
		mPlayCount = 0;
		playButtonIndex = i;
	}
	if( playButtonIndex != -1 ) {
		for( int i = 0 ; i < PLAY_BUTTON_NUM; ++i ) {
			if( i == playButtonIndex ) continue;
			mPlayButton[ i ].setOff();
		}
		return TRUE;
	}

	for( int i = 0 ; i < PAD_FADER_NUM; ++i ) {
		if( !mPadFader[ i ].checkHit() ) continue;
		if( !mPadFader[ i ].isHold() ) return TRUE;
		if( i == 0 ) {
			mTempo = static_cast< int >( ( 1 - mPadFader[ 0 ].getVal() ) * 15 + 1 );
		} else if( i == 1 ) {
			setNoteRatio( mPadFader[ 1 ].getVal() * ( NOTE_HEIGHT_NUM - 1 ), getSelectTrack(), mPlayTime );
		}
		return TRUE;
	}

	for( int i = 0; i < NOTE_SET_MAX_NUM; ++i ) {
		if( !mTimeLamp[ i ].checkHit() ) continue;
		if( !mTimeLamp[ i ].isSwitch() ) return TRUE;
		mPlayTime = i;
		mPlayCount = 0;
		return TRUE;
	}

	int mouseX = handManager->getX();
	int mouseY = handManager->getY();
	if( mouseX > hitX1 && mouseX < hitX2 && mouseY > hitY1 && mouseY < hitY2 ) {
		if( Main::HandManager::isClick ) {
			int targetX = ( mouseX - hitX1 ) / disX;
			int targetY = ( mouseY - hitY1 ) / disY;
			int trackIndex = getSelectTrack();
			if( mNoteRatio[ trackIndex ][ targetX ] == targetY ) {
				setNoteRatio( -1.0, trackIndex, targetX );
			} else {
				setNoteRatio( targetY, trackIndex, targetX );
			}
			handManager->setState( handManager->HAND_PUSH_AFTER );
		} else {
			handManager->setState( handManager->HAND_PUSH_BEFORE );
		}
		return TRUE;
	}

	return FALSE;
}

void Synthesizer::updatePad( BOOL isConnectSocket )
{
	mScaleDial.update();

	if( !isConnectSocket ) {
		for( int i = 0; i < TRACK_NUM; ++i ) {
			for( int j = 0; j < NOTE_SET_MAX_NUM; ++j ) {
				setNoteRatio( -1.0, i, j );
			}
		}
	}

	for( int i = 0; i < NOTE_SET_MAX_NUM; ++i ) {
		( mPlayTime == i )? mTimeLamp[ i ].setOn() : mTimeLamp[ i ].setOff();
	}
}

void Synthesizer::setNoteRatio( double setRatio, int trackIndex, int time )
{
	if( mNoteRatio[ trackIndex ][ time ] == setRatio ) return;
	mNoteRatio[ trackIndex ][ time ] = setRatio;

	int noteIndex = static_cast< int >( setRatio );
	double nodeRatio = setRatio - noteIndex;
	ViewObj *target = &mNoteLamp[ trackIndex ][ time ];

	if( noteIndex < 0 ) {
		target->setView( FALSE );
		return;
	}
	int setX = 0;
	int setY = 0;
	target->setView( TRUE );
	if( ( noteIndex + 1 ) < NOTE_HEIGHT_NUM ) {
		setX = static_cast< int >( mNotePosX[ noteIndex ][ time ] + ( mNotePosX[ noteIndex + 1 ][ time ] - mNotePosX[ noteIndex ][ time ] ) * nodeRatio + 0.5 );
		setY = static_cast< int >( mNotePosY[ noteIndex ][ time ] + ( mNotePosY[ noteIndex + 1 ][ time ] - mNotePosY[ noteIndex ][ time ] ) * nodeRatio + 0.5 );
	} else if( noteIndex < NOTE_HEIGHT_NUM ) {
		setX = mNotePosX[ noteIndex ][ time ];
		setY = mNotePosY[ noteIndex ][ time ];
	} else {
		setX = mNotePosX[ NOTE_HEIGHT_NUM - 1 ][ time ];
		setY = mNotePosY[ NOTE_HEIGHT_NUM - 1 ][ time ];
	}
	target->setPos( setX, setY );
}
