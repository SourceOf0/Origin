
void Synthesizer::update( Sequence::RoomParent* parent )
{
	Main::SoundManager* soundManager = Main::SoundManager::inst();
	BOOL isClick = Main::SceneManager::isClick;
	BOOL isHit = !Main::SceneManager::isMouseDown;
	POINT mousePos;
	GetCursorPos( &mousePos );
	int mouseX = mousePos.x;
	int mouseY = mousePos.y;
	BOOL isPlaySound = FALSE;

	for( int i = 0 ; i < EFFECT_FADER_NUM; ++i ) {
		if( !isHit && checkHit( mEffectFader[ i ], mouseX , mouseY ) ) {
			PartsData& target = mEffectFader[ i ];
			int setY = mouseY - 5;
			if( setY < target.defY ) setY = target.defY;
			if( setY > target.hitY2 - 10 ) setY = target.hitY2 - 10;
			target.y = setY;
			if( i % 2 == 0 ) {
				soundManager->getTrack( i / 6 )->getEffect( ( i % 6 ) / 2 )->setNum1( getFaderV( target ) );
			} else {
				soundManager->getTrack( i / 6 )->getEffect( ( i % 6 ) / 2 )->setNum2( getFaderV( target ) );
			}
			isHit = TRUE;
		}
	}

	for( int i = 0 ; i < EQ_FADER_NUM; ++i ) {
		if( !isHit && checkHit( mEQFader[ i ], mouseX , mouseY ) ) {
			PartsData& target = mEQFader[ i ];
			int setY = mouseY - 5;
			double setFc = 0;
			double setG = 0;
			if( setY < target.defY ) setY = target.defY;
			if( setY > target.hitY2 - 10 ) setY = target.hitY2 - 10;
			target.y = setY;
			if( i % 2 == 0 ) {
				setFc = getFaderV( mEQFader[ i ] ) * 1400 + 100;
				setG = ( getFaderV( mEQFader[ i + 1 ] ) - 0.5 ) * 2;
			} else {
				setFc = getFaderV( mEQFader[ i - 1 ] ) * 1400 + 100;
				setG = ( getFaderV( mEQFader[ i ] ) - 0.5 ) * 2;
			}
			switch( mEQLever[ i / 2 ].partsID ) {
				case PARTS_LEVER_1:
					soundManager->getTrack( i / 6 )->setEQState( ( i % 6 ) / 2, setFc, setG );
					break;
				case PARTS_LEVER_2:
					soundManager->getTrack( i / 6 )->setEQState( ( i % 6 ) / 2, setFc, setG );
					break;
				case PARTS_LEVER_3:
					soundManager->getTrack( i / 6 )->setEQState( ( i % 6 ) / 2, setFc, setG );
					break;
				case PARTS_LEVER_4:
					soundManager->getTrack( i / 6 )->setEQState( ( i % 6 ) / 2, setFc, setG );
					break;
			}
			isHit = TRUE;
		}
	}

	for( int i = 0 ; i < EFFECT_SELECT_NUM; ++i ) {
		PartsData& target = mEffectDial[ i ];
		PartsData& targetSign = mEffectSign[ i ];
		if( checkHit( target, mouseX , mouseY ) ) {
			isHit = TRUE;
			if( isClick ) {
				if( mouseX < target.x + 30 ) {
					targetSign.defY = targetSign.defY + 1;
					if( targetSign.defY <= PARTS_SIGN_BAND_ELIMINATE_FILTER ) {
						if( target.defX == 100 ) target.defX = 0;
					} else {
						targetSign.defY = PARTS_SIGN_BAND_ELIMINATE_FILTER;
					}
				} else {
					targetSign.defY = targetSign.defY - 1;
					if( targetSign.defY >= PARTS_SIGN_NOISE_GATE ) {
						if( target.defX == 100 ) target.defX = 0;
					} else {
						targetSign.defY = PARTS_SIGN_NOISE_GATE;
					}
				}
			}
		}
		updateDial( i, target, targetSign );
	}

	for( int i = 0 ; i < TRACK_NUM; ++i ) {
		PartsData& target = mWaveDial[ i ];
		PartsData& targetSign = mWaveSign[ i ];
		if( checkHit( target, mouseX , mouseY ) ) {
			isHit = TRUE;
			if( isClick ) {
				if( mouseX < target.x + 30 ) {
					targetSign.defY = targetSign.defY + 1;
					if( targetSign.defY <= PARTS_SIGN_TRIANGLE ) {
						if( target.defX == 100 ) target.defX = 0;
					} else {
						targetSign.defY = PARTS_SIGN_TRIANGLE;
					}
				} else {
					targetSign.defY = targetSign.defY - 1;
					if( targetSign.defY >= PARTS_SIGN_CURVE ) {
						if( target.defX == 100 ) target.defX = 0;
					} else {
						targetSign.defY = PARTS_SIGN_CURVE;
					}
				}
			}
		}
		updateDial( -1, target, targetSign );
	}

	for( int i = 0 ; i < VOLUME_FADER_NUM; ++i ) {
		if( !isHit && checkHit( mVolumeFader[ i ], mouseX , mouseY ) ) {
			PartsData& target = mVolumeFader[ i ];
			int setX = mouseX - 5;
			if( setX < target.defX ) setX = target.defX;
			if( setX > target.hitX2 - 10 ) setX = target.hitX2 - 10;
			target.x = setX;
			isHit = TRUE;
			if( i == 0 ) {
				soundManager->setVol( getFaderH( target ) );
			} else if( i == 1 ) {
				soundManager->setPan( getFaderH( target ) );
			} else if( i % 2 == 0 ) {
				soundManager->getTrack( i / 2 - 1 )->setVol( getFaderH( target ) );
			} else {
				soundManager->getTrack( i / 2 - 1 )->setPan( getFaderH( target ) );
			}
		}
	}

	for( int i = 0 ; i < TRACK_NUM; ++i ) {
		if( checkHit( mAutoPanButton[ i ], mouseX , mouseY ) ) {
			isHit = TRUE;
			if( isClick && checkHit( mAutoPanButton[ i ], mouseX , mouseY ) ) {
				if( mAutoPanButton[ i ].partsID == PARTS_BUTTON_AUTOPAN_OFF ) {
					mAutoPanButton[ i ].partsID = PARTS_BUTTON_AUTOPAN_ON;
					soundManager->getTrack( i )->setAutoPan( TRUE );
				} else {
					mAutoPanButton[ i ].partsID = PARTS_BUTTON_AUTOPAN_OFF;
					soundManager->getTrack( i )->setAutoPan( FALSE );
				}
				soundManager->getTrack( i )->setPan( getFaderH( mVolumeFader[ i * 2 + 3 ] ) );
			}
		}
	}

	int waveButtonIndex = -1;
	for( int i = 0 ; i < TRACK_NUM; ++i ) {
		if( checkHit( mTrackButton[ i ], mouseX , mouseY ) ) {
			isHit = TRUE;
			if( isClick && checkHit( mTrackButton[ i ], mouseX , mouseY ) ) {
				waveButtonIndex = i;
				mTrackButton[ i ].partsID = ( mTrackButton[ i ].partsID == PARTS_BUTTON_TRACK_OFF )? PARTS_BUTTON_TRACK_ON : PARTS_BUTTON_TRACK_OFF;
			}
		}
	}
	if( waveButtonIndex != -1 ) {
		for( int i = 0 ; i < TRACK_NUM; ++i ) {
			if( i == waveButtonIndex ) continue;
			mTrackButton[ i ].partsID = PARTS_BUTTON_TRACK_OFF;
		}
	}

	for( int i = 0 ; i < EFFECT_EQ_NUM; ++i ) {
		if( !isHit && checkHit( mEQLever[ i ], mouseX , mouseY ) ) {
			PartsData& target = mEQLever[ i ];
			int setX = mouseX - 12;
			if( setX < target.defX ) {
				target.partsID = PARTS_LEVER_4;
				soundManager->getTrack( i / 3 )->setEQKind( i % 3, EQ_HIGH_SHELVING );
				setX = target.defX;
			} else if( setX < target.defX + 12 ) {
				target.partsID = PARTS_LEVER_3;
				soundManager->getTrack( i / 3 )->setEQKind( i % 3, EQ_PEAKING );
				setX = target.defX + 12;
			} else if( setX < target.defX + 23 ) {
				target.partsID = PARTS_LEVER_2;
				soundManager->getTrack( i / 3 )->setEQKind( i % 3, EQ_LOW_SHELVING );
				setX = target.defX + 23;
			} else {
				target.partsID = PARTS_LEVER_1;
				soundManager->getTrack( i / 3 )->setEQKind( i % 3, EQ_NONE );
				setX = target.hitX2 - 20;
			}
			target.x = setX;
			isHit = TRUE;
		}
	}
	for( int i = 0 ; i < KEY_NUM; ++i ) {
		if( !isHit && checkHit( mKeyButton[ i ], mouseX , mouseY ) ) {
			if( mKeyButton[ i ].partsID == PARTS_BUTTON_KEY_OFF ) {
				int trackIndex = getSelectTrack();
				if( trackIndex >= 0 ) {
					soundManager->getTrack( trackIndex )->setF( getHz( i ) );
				}
			}
			isPlaySound = TRUE;
			mKeyButton[ i ].partsID = PARTS_BUTTON_KEY_ON;
			isHit = TRUE;
		} else {
			mKeyButton[ i ].partsID = PARTS_BUTTON_KEY_OFF;
		}
	}
	if( !isPlaySound ) {
		soundManager->getTrack( 0 )->setWave( WAVE_NONE );
		soundManager->getTrack( 1 )->setWave( WAVE_NONE );
		soundManager->getTrack( 2 )->setWave( WAVE_NONE );
	} else {
		soundManager->getTrack( 0 )->setWave( ( WaveID )( mWaveSign[ 0 ].partsID - PARTS_SIGN_CURVE ) );
		soundManager->getTrack( 1 )->setWave( ( WaveID )( mWaveSign[ 1 ].partsID - PARTS_SIGN_CURVE ) );
		soundManager->getTrack( 2 )->setWave( ( WaveID )( mWaveSign[ 2 ].partsID - PARTS_SIGN_CURVE ) );
	}

	int playButtonIndex = -1;
	for( int i = 0 ; i < PLAY_BUTTON_NUM; ++i ) {
		if( checkHit( mPlayButton[ i ], mouseX , mouseY ) ) {
			isHit = TRUE;
			PartsData& target = mPlayButton[ i ];
			if( isClick && checkHit( target, mouseX , mouseY ) ) {
				playButtonIndex = i;
				if( target.partsID == PARTS_BUTTON_PLAY_OFF ) {
					target.partsID = PARTS_BUTTON_PLAY_ON;
					mPlaySign[ i ].y = mPlaySign[ i ].defY + 3;
				} else {
					target.partsID = PARTS_BUTTON_PLAY_OFF;
					mPlaySign[ i ].y = mPlaySign[ i ].defY;
				}
			}
		}
	}
	if( playButtonIndex != -1 ) {
		for( int i = 0 ; i < PLAY_BUTTON_NUM; ++i ) {
			if( i == playButtonIndex ) continue;
			mPlayButton[ i ].partsID = PARTS_BUTTON_PLAY_OFF;
			mPlaySign[ i ].y = mPlaySign[ i ].defY;
		}
	}

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
		}
	}
	updateDial( -1, mScaleDial, mScaleSign );

	if( !mIsInit ) {
		mIsInit = TRUE;
		updateSoundState();
		Main::SoundManager::inst()->play();
	} else if( !Main::SceneManager::isAddWave ) {
		return;
	}
	updateWave();

	double test1 = 1.0 / 12;
	double test2 = getHz( 0 ) + test1;
	double test3 = getHz( 0 ) + test1 * 2;
	double test4 = getHz( 0 ) + test1 * 3;
}

BOOL Synthesizer::checkHit( PartsData& target, int x, int y )
{
	return ( x >= target.hitX1 && x <= target.hitX2 && y >= target.hitY1 && y <= target.hitY2 );
}

#include <Math.h>
double Synthesizer::getHz( int index )
{
	double ret = 0;
	switch( index % 12 ) {
		case 0:
			ret = pow( 2.0, -9 / 12.0 ) * 440;
//			ret = 261.6255653005986;
			break;
		case 1:
			ret = pow( 2.0, -8 / 12.0 ) * 440;
//			ret = 277.1826309768721;
			break;
		case 2:
			ret = pow( 2.0, -7 / 12.0 ) * 440;
//			ret = 293.6647679174076;
			break;
		case 3:
			ret = pow( 2.0, -6 / 12.0 ) * 440;
//			ret = 311.1269837220809;
			break;
		case 4:
			ret = pow( 2.0, -5 / 12.0 ) * 440;
//			ret = 329.6275569128699;
			break;
		case 5:
			ret = pow( 2.0, -4 / 12.0 ) * 440;
//			ret = 349.2282314330039;
			break;
		case 6:
			ret = pow( 2.0, -3 / 12.0 ) * 440;
//			ret = 369.9944227116344;
			break;
		case 7:
			ret = pow( 2.0, -2 / 12.0 ) * 440;
//			ret = 391.99543598174926;
			break;
		case 8:
			ret = pow( 2.0, -1 / 12.0 ) * 440;
//			ret = 415.3046975799451;
			break;
		case 9:
			ret = 440.0;
			break;
		case 10:
			ret = pow( 2.0, 1 / 12.0 ) * 440;
//			ret = 466.1637615180899;
			break;
		case 11:
			ret = pow( 2.0, 2 / 12.0 ) * 440;
//			ret = 493.8833012561241;
			break;
	}
	if( index >= 12 ) ret *= 2;
	return ret;
}

int Synthesizer::getSelectTrack( void )
{
	for( int i = 0 ; i < TRACK_NUM; ++i ) {
		if( mTrackButton[ i ].partsID == PARTS_BUTTON_TRACK_ON ) return i;
	}
	return -1;
}

double Synthesizer::getFaderH( PartsData& target )
{
	return ( static_cast< double >( target.x - target.defX ) / ( target.hitX2 - 10 - target.defX ) );
}
double Synthesizer::getFaderV( PartsData& target )
{
	return ( static_cast< double >( target.y - target.defY ) / ( target.hitY2 - 10 - target.defY ) );
}

void Synthesizer::updateDial( int index, PartsData& target, PartsData& targetSign )
{
	if( targetSign.defY < targetSign.partsID ) {
		targetSign.x += 4;
		if( targetSign.x > targetSign.defX + 18 ) {
			targetSign.x = targetSign.defX - 18;
			targetSign.partsID = ( PartsID )( targetSign.partsID - 1 );
			if( index >= 0 ) {
				Main::SoundManager::inst()->getTrack( index / 3 )->addEffect( index % 3, ( EffectID )( targetSign.partsID - PARTS_SIGN_NOISE_GATE ) );
			}
		}
	} else if( targetSign.defY > targetSign.partsID ) {
		targetSign.x -= 4;
		if( targetSign.x < targetSign.defX - 18 ) {
			targetSign.x = targetSign.defX + 18;
			targetSign.partsID = ( PartsID )( targetSign.partsID + 1 );
			if( index >= 0 ) {
				Main::SoundManager::inst()->getTrack( index / 3 )->addEffect( index % 3, ( EffectID )( targetSign.partsID - PARTS_SIGN_NOISE_GATE ) );
			}
		}
	} else if( targetSign.x != targetSign.defX ) {
		if( targetSign.x > targetSign.defX ) {
			targetSign.x -= 4;
			if( targetSign.x <= targetSign.defX ) {
				targetSign.x = targetSign.defX;
			}
		} else {
			targetSign.x += 4;
			if( targetSign.x >= targetSign.defX ) {
				targetSign.x = targetSign.defX;
			}
		}
	}
	if( target.defX >= 10 ) {
		if( targetSign.defY == targetSign.partsID ) {
			target.defX = 100;
		} else {
			target.defX = 0;
		}
	}
	if( target.defX == 100 ) return;
	++target.defX;
	target.partsID = ( target.defX / 5 == 0 )? PARTS_DIAL_1 : PARTS_DIAL_2;
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

void Synthesizer::updateSoundState( void )
{
	Main::SoundManager* soundManager = Main::SoundManager::inst();
	soundManager->getTrack( 0 )->setWave( WAVE_NONE );
	soundManager->getTrack( 1 )->setWave( WAVE_NONE );
	soundManager->getTrack( 2 )->setWave( WAVE_NONE );

	for( int i = 0 ; i < EFFECT_SELECT_NUM; ++i ) {
		soundManager->getTrack( i / 3 )->addEffect( i % 3, ( EffectID )( mEffectSign[ i ].partsID - PARTS_SIGN_NOISE_GATE ) );
	}

	for( int i = 0 ; i < VOLUME_FADER_NUM; ++i ) {
		PartsData& target = mVolumeFader[ i ];
		if( i == 0 ) {
			soundManager->setVol( getFaderH( target ) );
		} else if( i == 1 ) {
			soundManager->setPan( getFaderH( target ) );
		} else if( i % 2 == 0 ) {
			soundManager->getTrack( i / 2 - 1 )->setVol( getFaderH( target ) );
		} else {
			soundManager->getTrack( i / 2 - 1 )->setPan( getFaderH( target ) );
		}
	}

	for( int i = 0 ; i < TRACK_NUM; ++i ) {
		if( mAutoPanButton[ i ].partsID == PARTS_BUTTON_AUTOPAN_ON ) {
			soundManager->getTrack( i )->setAutoPan( TRUE );
		} else {
			soundManager->getTrack( i )->setAutoPan( FALSE );
		}
		soundManager->getTrack( i )->setF( 0 );
	}

	for( int i = 0 ; i < EFFECT_EQ_NUM; ++i ) {
		double setFc = getFaderV( mEQFader[ i * 2 ] ) * 1400 + 100;
		double setG = ( getFaderV( mEQFader[ i * 2 + 1 ] ) - 0.5 ) * 2;
		switch( mEQLever[ i ].partsID ) {
			case PARTS_LEVER_1:
				soundManager->getTrack( i / 3 )->setEQKind( i % 3, EQ_NONE );
				break;
			case PARTS_LEVER_2:
				soundManager->getTrack( i / 3 )->setEQKind( i % 3, EQ_LOW_SHELVING );
				break;
			case PARTS_LEVER_3:
				soundManager->getTrack( i / 3 )->setEQKind( i % 3, EQ_PEAKING );
				break;
			case PARTS_LEVER_4:
				soundManager->getTrack( i / 3 )->setEQKind( i % 3, EQ_HIGH_SHELVING );
				break;
		}
		soundManager->getTrack( i / 3 )->setEQState( i % 3, setFc, setG );
	}
}
