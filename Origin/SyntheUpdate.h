
void Synthesizer::update( Sequence::RoomParent* parent )
{
	if( !checkHit() ) {
		if( Main::HandManager::inst()->getX() < 50 || Main::HandManager::inst()->getY() < 100 || ( Main::HandManager::inst()->getX() > static_cast< int >( mBackBmp1->mWidth ) - 50 ) || ( Main::HandManager::inst()->getY() > static_cast< int >( mBackBmp1->mHeight ) - 50 ) ) {
			if( Main::HandManager::isClick ) {
				parent->moveTo( parent->SEQ_ROOM1 );
			} else {
				Main::HandManager::inst()->setState( Main::HandManager::HAND_BACK );
			}
		}
	}

	for( int i = 0 ; i < EFFECT_SELECT_NUM; ++i ) {
		mEffectDial[ i ].update();
		if( !mEffectDial[ i ].isChangeSign() ) continue;
		Main::SoundManager::inst()->getTrack( i / 3 )->addEffect( i % 3, getEffectID( mEffectDial[ i ].getSign() ) );
	}
	for( int i = 0 ; i < TRACK_NUM; ++i ) {
		mWaveDial[ i ].update();
	}

	updatePad( parent->mIsConnectSocket );
}

BOOL Synthesizer::checkHit( void )
{
	Main::SoundManager* soundManager = Main::SoundManager::inst();
	Main::HandManager* handManager = Main::HandManager::inst();

	handManager->setState( handManager->HAND_NORMAL );

	if( handManager->getX() > 550 ) {
		BOOL isKeyHit = FALSE;
		for( int i = 0 ; i < KEY_NUM; ++i ) {
			if( mKeyButton[ i ].checkHit() ) isKeyHit = TRUE;
		}
		if( isKeyHit ) return TRUE;
	
		if( checkHitPad() )	return TRUE;
		return FALSE;
	}


	for( int i = 0 ; i < EFFECT_FADER_NUM; ++i ) {
		if( !mEffectFader[ i ].checkHit() ) continue;
		if( !mEffectFader[ i ].isHold() ) return TRUE;
		if( i % 2 == 0 ) {
			soundManager->getTrack( i / 6 )->getEffect( ( i % 6 ) / 2 )->setNum1( mEffectFader[ i ].getVal() );
		} else {
			soundManager->getTrack( i / 6 )->getEffect( ( i % 6 ) / 2 )->setNum2( mEffectFader[ i ].getVal() );
		}
		return TRUE;
	}

	for( int i = 0 ; i < EFFECT_SELECT_NUM; ++i ) {
		if( mEffectDial[ i ].checkHit() ) return TRUE;
	}

	for( int i = 0 ; i < TRACK_NUM; ++i ) {
		if( mWaveDial[ i ].checkHit() ) return TRUE;
	}

	for( int i = 0 ; i < VOLUME_FADER_NUM; ++i ) {
		if( !mVolumeFader[ i ].checkHit() ) continue;
		if( !mVolumeFader[ i ].isHold() ) return TRUE;
		if( i == 0 ) {
			soundManager->setVol( mVolumeFader[ 0 ].getVal() );
		} else if( i == 1 ) {
			soundManager->setPan( mVolumeFader[ 1 ].getVal() );
		} else if( i % 2 == 0 ) {
			soundManager->getTrack( i / 2 - 1 )->setVol( mVolumeFader[ i ].getVal() );
		} else {
			soundManager->getTrack( i / 2 - 1 )->setPan( mVolumeFader[ i ].getVal() );
		}
		return TRUE;
	}

	for( int i = 0 ; i < TRACK_NUM; ++i ) {
		if( !mAutoPanButton[ i ].checkHit() ) continue;
		if( !mAutoPanButton[ i ].isSwitch() ) return TRUE;
		if( mAutoPanButton[ i ].isOn() ) {
			soundManager->getTrack( i )->setAutoPan( TRUE );
			soundManager->getTrack( i )->setPan( mVolumeFader[ i * 2 + 3 ].getVal() );
		} else {
			soundManager->getTrack( i )->setAutoPan( FALSE );
			soundManager->getTrack( i )->setPan( mVolumeFader[ i * 2 + 3 ].getVal() );
		}
		return TRUE;
	}

	int waveButtonIndex = -1;
	for( int i = 0 ; i < TRACK_NUM; ++i ) {
		if( !mTrackButton[ i ].checkHit() ) continue;
		if( !mTrackButton[ i ].isSwitch() ) continue;
		waveButtonIndex = i;
	}
	if( waveButtonIndex != -1 ) {
		for( int i = 0 ; i < TRACK_NUM; ++i ) {
			if( i == waveButtonIndex ) {
				for( int j = 0; j < NOTE_SET_MAX_NUM; ++j ) {
					mNoteLamp[ i ][ j ].setPartsID( PARTS_LAMP_NOTE_1 );
				}
				continue;
			}
			mTrackButton[ i ].setOff();
			for( int j = 0; j < NOTE_SET_MAX_NUM; ++j ) {
				mNoteLamp[ i ][ j ].setPartsID( PARTS_LAMP_NOTE_2 );
			}
		}
		return TRUE;
	}

	for( int i = 0 ; i < EFFECT_EQ_NUM; ++i ) {
		if( !mEQLever[ i ].checkHit() ) continue;
		if( !mEQLever[ i ].isChangeVal() ) return TRUE;
		switch( mEQLever[ i ].getVal() ) {
			case 4:
				soundManager->getTrack( i / 3 )->setEQKind( i % 3, EQ_HIGH_SHELVING );
				break;
			case 3:
				soundManager->getTrack( i / 3 )->setEQKind( i % 3, EQ_PEAKING );
				break;
			case 2:
				soundManager->getTrack( i / 3 )->setEQKind( i % 3, EQ_LOW_SHELVING );
				break;
			case 1:
				soundManager->getTrack( i / 3 )->setEQKind( i % 3, EQ_NONE );
				break;
		}
		return TRUE;
	}

	for( int i = 0 ; i < EQ_FADER_NUM; ++i ) {
		if( !mEQFader[ i ].checkHit() ) continue;
		if( !mEQFader[ i ].isHold() ) return TRUE;
		double setFc = 0;
		double setG = 0;
		if( i % 2 == 0 ) {
			setFc = mEQFader[ i ].getVal() * 1400 + 100;
			setG = ( mEQFader[ i + 1 ].getVal() - 0.5 ) * 2;
		} else {
			setFc = mEQFader[ i - 1 ].getVal() * 1400 + 100;
			setG = ( mEQFader[ i ].getVal() - 0.5 ) * 2;
		}
		soundManager->getTrack( i / 6 )->setEQState( ( i % 6 ) / 2, setFc, setG );
		return TRUE;
	}

	return FALSE;
}

void Synthesizer::playTrack( Sequence::RoomParent* parent )
{
	BOOL isPlay = FALSE;

	if( !parent->mIsConnectSocket ) {
		for( int i = 0; i < TRACK_NUM; ++i ) {
			for( int j = 0; j < NOTE_SET_MAX_NUM; ++j ) {
				setNoteRatio( -1.0, i, j );
			}
		}
	}

	if( mPlayButton[ 0 ].isOn() ) {
		isPlay = TRUE;
		++mPlayCount;
	}
	if( mPlayButton[ 1 ].isOn() ) {
		isPlay = TRUE;
	}
	if( mPlayButton[ 2 ].isOn() ) {
		for( int i = 0 ; i < KEY_NUM; ++i ) {
			if( !mKeyButton[ i ].isOn() ) continue;
			setNoteRatio( getCodeRatio( i ), getSelectTrack(), mPlayTime );
			break;
		}
	}

	if( isPlay ) {
		if( mPlayCount >= mTempo ) {
			mPlayCount = 0;
			mPlayTime = ( mPlayTime + 1 ) % NOTE_SET_MAX_NUM;
		}
		for( int i = 0 ; i < TRACK_NUM; ++i ) {
//			mPlayWaveID[ i ] = ( WaveID )( mWaveDial[ i ].getSign() - PARTS_SIGN_CURVE );
			mPlayWaveID[ i ] = getWaveID( mWaveDial[ i ].getSign() );
			Main::SoundManager::inst()->getTrack( i )->setF( getFixCodeHz( mNoteRatio[ i ][ mPlayTime ] ) );
		}
	} else {
		for( int i = 0 ; i < TRACK_NUM; ++i ) {
//			mPlayWaveID[ i ] = ( WaveID )( mWaveDial[ i ].getSign() - PARTS_SIGN_CURVE );
			mPlayWaveID[ i ] = getWaveID( mWaveDial[ i ].getSign() );
			Main::SoundManager::inst()->getTrack( i )->setF( 0.0 );
			if( i != getSelectTrack() ) continue;
			for( int j = 0 ; j < KEY_NUM; ++j ) {
				if( !mKeyButton[ j ].isOn() ) continue;
				Main::SoundManager::inst()->getTrack( i )->setF( getHz( j ) );
				break;
			}
		}
	}

	for( int i = 0; i < TRACK_NUM; ++i ) {
		Main::SoundManager::inst()->getTrack( i )->setWave( mPlayWaveID[ i ] );
	}

	if( !mIsInit ) {
		mIsInit = TRUE;
		initSoundState();
		Main::SoundManager::inst()->play();
		updateWave();
		return;
	}
	if( Main::SceneManager::isAddWave ) updateWave();
}

void Synthesizer::updateWave( void )
{
	Main::SoundManager* soundManager = Main::SoundManager::inst();
	double* waveLog1 = soundManager->getTrack( 0 )->getPlayData();
	double* waveLog2 = soundManager->getTrack( 1 )->getPlayData();
	double* waveLog3 = soundManager->getTrack( 2 )->getPlayData();

	int maxHeight = 10;
	int disY = 50;
	int setY = maxHeight + 30;

	mWaveBmp->setWhite();

	HPEN hPen = CreatePen( PS_SOLID, 1, RGB( 0, 0, 0 ) );
	HBRUSH hBrush = CreateSolidBrush( RGB( 255, 255, 255 ) );

	SelectObject( mWaveBmp->mHdcBmp, hBrush );
	SelectObject( mWaveBmp->mHdcBmp, hPen );
	
	MoveToEx( mWaveBmp->mHdcBmp, 0, static_cast< int >( waveLog1[ 0 ] * maxHeight + setY ), NULL );
	for( int i = 1; i < 356; ++i ) {
		double setNum = waveLog1[ i * 3 ];
		setNum += waveLog1[ i * 3 + 1 ];
		setNum += waveLog1[ i * 3 + 2 ];
		setNum /= 3.0;
		LineTo( mWaveBmp->mHdcBmp, i, static_cast< int >( setNum * maxHeight + setY ) );
	}

	setY += disY;
	MoveToEx( mWaveBmp->mHdcBmp, 0, static_cast< int >( waveLog2[ 0 ] * maxHeight + setY ), NULL );
	for( int i = 1; i < 356; ++i ) {
		double setNum = waveLog2[ i * 3 ];
		setNum += waveLog2[ i * 3 + 1 ];
		setNum += waveLog2[ i * 3 + 2 ];
		setNum /= 3.0;
		LineTo( mWaveBmp->mHdcBmp, i, static_cast< int >( setNum * maxHeight + setY ) );
	}

	setY += disY;
	MoveToEx( mWaveBmp->mHdcBmp, 0, static_cast< int >( waveLog3[ 0 ] * maxHeight + setY ), NULL );
	for( int i = 1; i < 356; ++i ) {
		double setNum = waveLog3[ i * 3 ];
		setNum += waveLog3[ i * 3 + 1 ];
		setNum += waveLog3[ i * 3 + 2 ];
		setNum /= 3.0;
		LineTo( mWaveBmp->mHdcBmp, i, static_cast< int >( setNum * maxHeight + setY ) );
	}

	DeleteObject( hPen );
	DeleteObject( hBrush );
}

void Synthesizer::initSoundState( void )
{
	Main::SoundManager* soundManager = Main::SoundManager::inst();
	soundManager->getTrack( 0 )->setWave( WAVE_NONE );
	soundManager->getTrack( 1 )->setWave( WAVE_NONE );
	soundManager->getTrack( 2 )->setWave( WAVE_NONE );

	for( int i = 0 ; i < EFFECT_SELECT_NUM; ++i ) {
		soundManager->getTrack( i / 3 )->addEffect( i % 3, getEffectID( mEffectDial[ i ].getSign() ) );
	}

	for( int i = 0 ; i < VOLUME_FADER_NUM; ++i ) {
		if( i == 0 ) {
			soundManager->setVol( mVolumeFader[ 0 ].getVal() );
		} else if( i == 1 ) {
			soundManager->setPan( mVolumeFader[ 1 ].getVal() );
		} else if( i % 2 == 0 ) {
			soundManager->getTrack( i / 2 - 1 )->setVol( mVolumeFader[ i ].getVal() );
		} else {
			soundManager->getTrack( i / 2 - 1 )->setPan( mVolumeFader[ i ].getVal() );
		}
	}

	for( int i = 0 ; i < TRACK_NUM; ++i ) {
		soundManager->getTrack( i )->setAutoPan( mAutoPanButton[ i ].isOn() );
		soundManager->getTrack( i )->setF( 0.0 );
	}

	for( int i = 0 ; i < EFFECT_EQ_NUM; ++i ) {
		double setFc = mEQFader[ i * 2 ].getVal() * 1400 + 100;
		double setG = ( mEQFader[ i * 2 + 1 ].getVal() - 0.5 ) * 2;
		switch( mEQLever[ i ].getVal() ) {
			case 1:
				soundManager->getTrack( i / 3 )->setEQKind( i % 3, EQ_NONE );
				break;
			case 2:
				soundManager->getTrack( i / 3 )->setEQKind( i % 3, EQ_LOW_SHELVING );
				break;
			case 3:
				soundManager->getTrack( i / 3 )->setEQKind( i % 3, EQ_PEAKING );
				break;
			case 4:
				soundManager->getTrack( i / 3 )->setEQKind( i % 3, EQ_HIGH_SHELVING );
				break;
		}
		soundManager->getTrack( i / 3 )->setEQState( i % 3, setFc, setG );
	}

	mTempo = static_cast< int >( ( 1 - mPadFader[ 0 ].getVal() ) * 15 + 1 );

	for( int i = 0; i < TRACK_NUM; ++i ) {
		for( int j = 0; j < NOTE_SET_MAX_NUM; ++j ) {
			int noteIndex = static_cast< int >( mNoteRatio[ i ][ j ] );
			double nodeRatio = mNoteRatio[ i ][ j ] - noteIndex;
			ViewObj *target = &mNoteLamp[ i ][ j ];
			if( noteIndex < 0 ) {
				target->setView( FALSE );
			} else {
				int setX = 0;
				int setY = 0;
				target->setView( TRUE );
				target->setPartsID( ( mTrackButton[ i ].isOn() )? PARTS_LAMP_NOTE_1 : PARTS_LAMP_NOTE_2 );
				if( ( noteIndex + 1 ) < NOTE_HEIGHT_NUM ) {
					setX = static_cast< int >( mNotePosX[ noteIndex ][ j ] + ( mNotePosX[ noteIndex + 1 ][ j ] - mNotePosX[ noteIndex ][ j ] ) * nodeRatio + 0.5 );
					setY = static_cast< int >( mNotePosY[ noteIndex ][ j ] + ( mNotePosY[ noteIndex + 1 ][ j ] - mNotePosY[ noteIndex ][ j ] ) * nodeRatio + 0.5 );
				} else if( noteIndex < NOTE_HEIGHT_NUM ) {
					setX = mNotePosX[ noteIndex ][ j ];
					setY = mNotePosY[ noteIndex ][ j ];
				} else {
					setX = mNotePosX[ NOTE_HEIGHT_NUM - 1 ][ j ];
					setY = mNotePosY[ NOTE_HEIGHT_NUM - 1 ][ j ];
				}
				target->setPos( setX, setY );
			}
		}
	}
}
