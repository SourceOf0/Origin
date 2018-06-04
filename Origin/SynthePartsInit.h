
void Synthesizer::posInit( void )
{
	setEffectFaderPos();
	setEQFaderPos();
	setEffectDialPos();
	setWaveDialPos();
	setVolumeFaderPos();
	setAutoPanButtonPos();
	setTrackButtonPos();
	setEQLeverPos();
	setKeyButtonPos();
	setPlayButtonPos();
	setScaleDialPos();
	setPadFaderPos();
	setNoteLampPos();
	setTimeLampPos();
}

void Synthesizer::setEffectFaderPos( void )
{
	int index = -1;
	int baseX = 95;
	int baseY = 225;
	int disX1 = 25;
	int disX2 = 37;
	int disY1 = 180;
	int disX = 0;
	int disY = 0;

	mEffectFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );
	disX += disX1;
	mEffectFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );
	disX += disX2;
	mEffectFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );
	disX += disX1;
	mEffectFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );
	disX += disX2 - 1;
	mEffectFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );
	disX += disX1;
	mEffectFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );

	disX = 3;
	disY += disY1;
	mEffectFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );
	disX += disX1;
	mEffectFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );
	disX += disX2;
	mEffectFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );
	disX += disX1;
	mEffectFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );
	disX += disX2 - 1;
	mEffectFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );
	disX += disX1;
	mEffectFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );

	disX = 3;
	disY += disY1;
	mEffectFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );
	disX += disX1;
	mEffectFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );
	disX += disX2;
	mEffectFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );
	disX += disX1;
	mEffectFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );
	disX += disX2 - 1;
	mEffectFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );
	disX += disX1;
	mEffectFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );
}
void Synthesizer::setEQFaderPos( void )
{
	int index = -1;
	int baseX = 282;
	int baseY = 226;
	int disX1 = 25;
	int disX2 = 37;
	int disY1 = 178;
	int disX = 0;
	int disY = 0;

	mEQFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );
	disX += disX1;
	mEQFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );
	disX += disX2;
	mEQFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );
	disX += disX1;
	mEQFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );
	disX += disX2 - 2;
	mEQFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );
	disX += disX1;
	mEQFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );

	disX = 3;
	disY += disY1;
	mEQFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );
	disX += disX1;
	mEQFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );
	disX += disX2;
	mEQFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );
	disX += disX1;
	mEQFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );
	disX += disX2 - 2;
	mEQFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );
	disX += disX1;
	mEQFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );

	disX = 4;
	disY += disY1 + 2;
	mEQFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );
	disX += disX1;
	mEQFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );
	disX += disX2;
	mEQFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );
	disX += disX1;
	mEQFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );
	disX += disX2 - 2;
	mEQFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );
	disX += disX1;
	mEQFader[ ++index ].setData( baseX + disX, baseY + disY, 5, 0, -5, 73 );
}

void Synthesizer::setEffectDialPos( void )
{
	int index = -1;
	int baseX = 88;
	int baseY = 197;
	int disX1 = 62;
	int disY1 = 178;
	int disX = 0;
	int disY = 0;

	mEffectDial[ ++index ].setData( PARTS_SIGN_NOISE_GATE, ( PartsID )( PARTS_SIGN_SCALE_C - 1 ), baseX + disX, baseY + disY );
	disX += disX1;
	mEffectDial[ ++index ].setData( PARTS_SIGN_NOISE_GATE, ( PartsID )( PARTS_SIGN_SCALE_C - 1 ), baseX + disX, baseY + disY );
	disX += disX1 - 1;
	mEffectDial[ ++index ].setData( PARTS_SIGN_NOISE_GATE, ( PartsID )( PARTS_SIGN_SCALE_C - 1 ), baseX + disX, baseY + disY );

	disX = 3;
	disY += disY1;
	mEffectDial[ ++index ].setData( PARTS_SIGN_NOISE_GATE, ( PartsID )( PARTS_SIGN_SCALE_C - 1 ), baseX + disX, baseY + disY );
	disX += disX1;
	mEffectDial[ ++index ].setData( PARTS_SIGN_NOISE_GATE, ( PartsID )( PARTS_SIGN_SCALE_C - 1 ), baseX + disX, baseY + disY );
	disX += disX1 - 1;
	mEffectDial[ ++index ].setData( PARTS_SIGN_NOISE_GATE, ( PartsID )( PARTS_SIGN_SCALE_C - 1 ), baseX + disX, baseY + disY );

	disX = 4;
	disY += disY1 + 3;
	mEffectDial[ ++index ].setData( PARTS_SIGN_NOISE_GATE, ( PartsID )( PARTS_SIGN_SCALE_C - 1 ), baseX + disX, baseY + disY );
	disX += disX1;
	mEffectDial[ ++index ].setData( PARTS_SIGN_NOISE_GATE, ( PartsID )( PARTS_SIGN_SCALE_C - 1 ), baseX + disX, baseY + disY );
	disX += disX1 - 1;
	mEffectDial[ ++index ].setData( PARTS_SIGN_NOISE_GATE, ( PartsID )( PARTS_SIGN_SCALE_C - 1 ), baseX + disX, baseY + disY );
}

void Synthesizer::setWaveDialPos( void )
{
	int index = -1;
	int baseX = 483;
	int baseY = 296;
	int disY1 = 150;
	int disY2 = 143;
	int disX = 0;
	int disY = 0;

	mWaveDial[ ++index ].setData( PARTS_SIGN_SAWTOOTH, PARTS_SIGN_CURVE, baseX + disX, baseY + disY );
	disX = 3;
	disY += disY1;
	mWaveDial[ ++index ].setData( PARTS_SIGN_SAWTOOTH, PARTS_SIGN_CURVE, baseX + disX, baseY + disY );
	disX = 5;
	disY += disY2;
	mWaveDial[ ++index ].setData( PARTS_SIGN_SAWTOOTH, PARTS_SIGN_CURVE, baseX + disX, baseY + disY );
}

void Synthesizer::setVolumeFaderPos( void )
{
	int index = -1;
	int baseX = 475;
	int baseY = 183;
	int disY1 = 31;
	int disY2 = 110;
	int disY3 = 114;
	int disX = 0;
	int disY = 0;

	mVolumeFader[ ++index ].setData( baseX + disX, baseY + disY, 0, 10, 63, -10 );
	disY += disY1;
	mVolumeFader[ ++index ].setData( baseX + disX, baseY + disY, 0, 10, 63, -10 );
	
	disY += disY2;
	mVolumeFader[ ++index ].setData( baseX + disX, baseY + disY, 0, 10, 63, -10 );
	disY += disY1;
	mVolumeFader[ ++index ].setData( baseX + disX, baseY + disY, 0, 10, 63, -10 );

	disX = 2;
	disY += disY3 + 5;
	mVolumeFader[ ++index ].setData( baseX + disX, baseY + disY, 0, 10, 63, -10 );
	disY += disY1;
	mVolumeFader[ ++index ].setData( baseX + disX, baseY + disY, 0, 10, 63, -10 );

	disX = 4;
	disY += disY3 - 2;
	mVolumeFader[ ++index ].setData( baseX + disX, baseY + disY, 0, 10, 63, -10 );
	disY += disY1;
	mVolumeFader[ ++index ].setData( baseX + disX, baseY + disY, 0, 10, 63, -10 );

	for( int i = 0; i < VOLUME_FADER_NUM; ++i ) {
		mVolumeFader[ i ].setVal( 0.5 );
	}
}

void Synthesizer::setAutoPanButtonPos( void )
{
	int index = -1;
	int baseX = 290;
	int baseY = 163;
	int disY1 = 178;
	int disY2 = 182;
	int disX = 0;
	int disY = 0;

	mAutoPanButton[ ++index ].setData( baseX + disX, baseY + disY );
	disY += disY1;
	mAutoPanButton[ ++index ].setData( baseX + disX, baseY + disY );
	disY += disY2;
	mAutoPanButton[ ++index ].setData( baseX + disX, baseY + disY );
}

void Synthesizer::setTrackButtonPos( void )
{
	int index = -1;
	int baseX = 350;
	int baseY = 163;
	int disY1 = 178;
	int disY2 = 182;
	int disX = 0;
	int disY = 0;

	mTrackButton[ ++index ].setData( baseX + disX, baseY + disY, TRUE );
	disX = 0;
	disY += disY1;
	mTrackButton[ ++index ].setData( baseX + disX, baseY + disY );
	disX = 0;
	disY += disY2;
	mTrackButton[ ++index ].setData( baseX + disX, baseY + disY );
}

void Synthesizer::setEQLeverPos( void )
{
	int index = -1;
	int baseX = 285;
	int baseY = 198;
	int disX1 = 60;
	int disY1 = 177;
	int disY2 = 182;
	int disX = 0;
	int disY = 0;

	mEQLever[ ++index ].setData( baseX + disX, baseY + disY, 1 );
	disX += disX1;
	mEQLever[ ++index ].setData( baseX + disX, baseY + disY, 1 );
	disX += disX1;
	mEQLever[ ++index ].setData( baseX + disX, baseY + disY, 1 );

	disX = 0;
	disY += disY1;
	mEQLever[ ++index ].setData( baseX + disX, baseY + disY, 1 );
	disX += disX1;
	mEQLever[ ++index ].setData( baseX + disX, baseY + disY, 1 );
	disX += disX1;
	mEQLever[ ++index ].setData( baseX + disX, baseY + disY, 1 );
	
	disX = 0;
	disY += disY2;
	mEQLever[ ++index ].setData( baseX + disX, baseY + disY, 1 );
	disX += disX1;
	mEQLever[ ++index ].setData( baseX + disX, baseY + disY, 1 );
	disX += disX1;
	mEQLever[ ++index ].setData( baseX + disX, baseY + disY, 1 );
}

void Synthesizer::setKeyButtonPos( void )
{
	int index = -1;
	int baseX = 565;
	int baseY = 630;
	int disX1 = 14;
	int disY1 = 35;
	int disX = 0;
	int disY = 0;

	for( int i = 0; i < KEY_NUM; ++i ) {
		switch( i % 12 ) {
			case 1:
			case 3:
			case 6:
			case 8:
			case 10:
				disY = 0;
				break;
			default:
				disY = disY1;
				break;
		}
		if( i == 5 || i == 12 || i == 17 ) {
			disX += disX1;
		}
		mKeyButton[ ++index ].setData( baseX + disX, baseY + disY );
		disX += disX1;
	}
}

void Synthesizer::setPlayButtonPos( void )
{
	int index = -1;
	int baseX = 800;
	int baseY = 355;
	int disX1 = 50;
	int disX2 = 12;
	int disY1 = 5;
	int disX = 0;
	int disY = 0;

	mPlayButton[ ++index ].setData( PARTS_SIGN_PLAY, baseX + disX, baseY + disY, baseX + disX + disX2, baseY + disY1 + 1 );
	disX += disX2;
	
	disY = 0;
	disX += disX1 - disX2;
	mPlayButton[ ++index ].setData( PARTS_SIGN_PAUSE, baseX + disX, baseY + disY, baseX + disX + disX2 + 1, baseY + disY1 );
	disX += disX2 + 1;
	
	disY = 0;
	disX += disX1 - disX2 - 1;
	mPlayButton[ ++index ].setData( PARTS_SIGN_REC, baseX + disX, baseY + disY, baseX + disX + disX2 - 2, baseY + disY1 );
	disX += disX2 - 2;
}

void Synthesizer::setScaleDialPos( void )
{
	int baseX = 584;
	int baseY = 382;
	mScaleDial.setData( PARTS_SIGN_SCALE_C, PARTS_SIGN_SCALE_BM, baseX, baseY );
}

void Synthesizer::setPadFaderPos( void )
{
	int index = -1;
	int baseX = 659;
	int baseY = 348;
	int disY1 = 30;
	int disX = 0;
	int disY = 0;

	mPadFader[ ++index ].setData( baseX + disX, baseY + disY, 0, 10, 113, -10 );
	disY += disY1;
	mPadFader[ ++index ].setData( baseX + disX, baseY + disY, 0, 10, 113, -10 );
}

void Synthesizer::setNoteLampPos( void )
{
	int index = -1;
	int baseX = 583;
	int baseY = 418;
	int disX1 = 22;
	int disY1 = 21;
	int disX = 0;
	int disY = 0;

	mNotePosX[ 0 ][ ++index ] = baseX + disX;
	disX += disX1;
	mNotePosX[ 0 ][ ++index ] = baseX + disX;
	disX += disX1 + 1;
	mNotePosX[ 0 ][ ++index ] = baseX + disX;
	disX += disX1 + 1;
	mNotePosX[ 0 ][ ++index ] = baseX + disX;
	disX += disX1;
	mNotePosX[ 0 ][ ++index ] = baseX + disX;

	disX += disX1;
	mNotePosX[ 0 ][ ++index ] = baseX + disX;
	disX += disX1;
	mNotePosX[ 0 ][ ++index ] = baseX + disX;
	disX += disX1 - 1;
	mNotePosX[ 0 ][ ++index ] = baseX + disX;
	disX += disX1 - 1;
	mNotePosX[ 0 ][ ++index ] = baseX + disX;
	disX += disX1;
	mNotePosX[ 0 ][ ++index ] = baseX + disX;

	disX += disX1 - 1;
	mNotePosX[ 0 ][ ++index ] = baseX + disX;
	disX += disX1;
	mNotePosX[ 0 ][ ++index ] = baseX + disX;
	disX += disX1;
	mNotePosX[ 0 ][ ++index ] = baseX + disX;
	disX += disX1;
	mNotePosX[ 0 ][ ++index ] = baseX + disX;
	disX += disX1;
	mNotePosX[ 0 ][ ++index ] = baseX + disX;
	
	disX += disX1 + 1;
	mNotePosX[ 0 ][ ++index ] = baseX + disX;


	index = -1;
	mNotePosY[ ++index ][ 0 ] = baseY + disY;
	disY += disY1;
	mNotePosY[ ++index ][ 0 ] = baseY + disY;
	disY += disY1;
	mNotePosY[ ++index ][ 0 ] = baseY + disY;
	disY += disY1;
	mNotePosY[ ++index ][ 0 ] = baseY + disY;
	disY += disY1;
	mNotePosY[ ++index ][ 0 ] = baseY + disY;
	disY += disY1;
	mNotePosY[ ++index ][ 0 ] = baseY + disY;
	disY += disY1 + 1;
	mNotePosY[ ++index ][ 0 ] = baseY + disY;
	disY += disY1 + 2;
	mNotePosY[ ++index ][ 0 ] = baseY + disY;

	for( int i = 0; i < NOTE_HEIGHT_NUM; ++i ) {
		for( int j = 0; j < NOTE_SET_MAX_NUM; ++j ) {
			if( i < 3 ) {
				mNotePosX[ i ][ j ] = mNotePosX[ 0 ][ j ];
			} else {
				mNotePosX[ i ][ j ] = mNotePosX[ 0 ][ j ] + 1;
			}
			if( i != 6 ) {
				if( j < 5 ) {
					mNotePosY[ i ][ j ] = mNotePosY[ i ][ 0 ];
				} else if( j < 12 ) {
					mNotePosY[ i ][ j ] = mNotePosY[ i ][ 0 ] - 1;
				} else {
					mNotePosY[ i ][ j ] = mNotePosY[ i ][ 0 ] - 2;
				}
			} else {
				if( j < 5 ) {
					mNotePosY[ i ][ j ] = mNotePosY[ i ][ 0 ] + 1;
				} else if( j < 12 ) {
					mNotePosY[ i ][ j ] = mNotePosY[ i ][ 0 ];
				} else {
					mNotePosY[ i ][ j ] = mNotePosY[ i ][ 0 ] - 1;
				}
			}
		}
	}

	for( int i = 0; i < TRACK_NUM; ++i ) {
		for( int j = 0; j < NOTE_SET_MAX_NUM; ++j ) {
			mNoteLamp[ i ][ j ].setData( PARTS_LAMP_NOTE_1, mNotePosX[ 0 ][ j ], mNotePosY[ 0 ][ j ], FALSE );
		}
	}
}

void Synthesizer::setTimeLampPos( void )
{
	int index = -1;
	int baseX = 587;
	int baseY = 599;
	int disX1 = 21;
	int disX = 0;

	mTimeLamp[ ++index ].setData( baseX + disX, baseY, TRUE );
	disX += disX1;
	mTimeLamp[ ++index ].setData( baseX + disX, baseY );
	disX += disX1 + 1;
	mTimeLamp[ ++index ].setData( baseX + disX, baseY );
	disX += disX1;
	mTimeLamp[ ++index ].setData( baseX + disX, baseY );
	disX += disX1 + 2;
	mTimeLamp[ ++index ].setData( baseX + disX, baseY );

	disX += disX1;
	mTimeLamp[ ++index ].setData( baseX + disX, baseY );
	disX += disX1 + 1;
	mTimeLamp[ ++index ].setData( baseX + disX, baseY );
	disX += disX1 + 2;
	mTimeLamp[ ++index ].setData( baseX + disX, baseY );
	disX += disX1 + 2;
	mTimeLamp[ ++index ].setData( baseX + disX, baseY );
	disX += disX1;
	mTimeLamp[ ++index ].setData( baseX + disX, baseY );

	disX += disX1 + 1;
	mTimeLamp[ ++index ].setData( baseX + disX, baseY );
	disX += disX1;
	mTimeLamp[ ++index ].setData( baseX + disX, baseY );
	disX += disX1 + 2;
	mTimeLamp[ ++index ].setData( baseX + disX, baseY );
	disX += disX1;
	mTimeLamp[ ++index ].setData( baseX + disX, baseY );
	disX += disX1 + 1;
	mTimeLamp[ ++index ].setData( baseX + disX, baseY );

	disX += disX1;
	mTimeLamp[ ++index ].setData( baseX + disX, baseY );
}

