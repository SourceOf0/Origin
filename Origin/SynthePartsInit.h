
void Synthesizer::posInit( void )
{
	setEffectFaderPos();
	setEQFaderPos();
	setEffectSignPos();
	setEffectDialPos();
	setWaveSignPos();
	setWaveDialPos();
	setVolumeFaderPos();
	setAutoPanButtonPos();
	setTrackButtonPos();
	setEQLeverPos();
	setKeyButtonPos();
	setPlayButtonPos();
	setScaleSignPos();
	setScaleDialPos();
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

	setPos( mEffectFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );
	disX += disX1;
	setPos( mEffectFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );
	disX += disX2;
	setPos( mEffectFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );
	disX += disX1;
	setPos( mEffectFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );
	disX += disX2 - 1;
	setPos( mEffectFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );
	disX += disX1;
	setPos( mEffectFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );

	disX = 3;
	disY += disY1;
	setPos( mEffectFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );
	disX += disX1;
	setPos( mEffectFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );
	disX += disX2;
	setPos( mEffectFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );
	disX += disX1;
	setPos( mEffectFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );
	disX += disX2 - 1;
	setPos( mEffectFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );
	disX += disX1;
	setPos( mEffectFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );

	disX = 3;
	disY += disY1;
	setPos( mEffectFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );
	disX += disX1;
	setPos( mEffectFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );
	disX += disX2;
	setPos( mEffectFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );
	disX += disX1;
	setPos( mEffectFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );
	disX += disX2 - 1;
	setPos( mEffectFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );
	disX += disX1;
	setPos( mEffectFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );

	for( int i = 0; i < EFFECT_FADER_NUM; ++i ) {
		fixHitRange( mEffectFader[ i ], 5, 0, -5, 73 );
	}
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

	setPos( mEQFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );
	disX += disX1;
	setPos( mEQFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );
	disX += disX2;
	setPos( mEQFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );
	disX += disX1;
	setPos( mEQFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );
	disX += disX2 - 2;
	setPos( mEQFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );
	disX += disX1;
	setPos( mEQFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );

	disX = 3;
	disY += disY1;
	setPos( mEQFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );
	disX += disX1;
	setPos( mEQFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );
	disX += disX2;
	setPos( mEQFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );
	disX += disX1;
	setPos( mEQFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );
	disX += disX2 - 2;
	setPos( mEQFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );
	disX += disX1;
	setPos( mEQFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );

	disX = 4;
	disY += disY1 + 2;
	setPos( mEQFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );
	disX += disX1;
	setPos( mEQFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );
	disX += disX2;
	setPos( mEQFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );
	disX += disX1;
	setPos( mEQFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );
	disX += disX2 - 2;
	setPos( mEQFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );
	disX += disX1;
	setPos( mEQFader[ ++index ], PARTS_FADER_V, baseX + disX, baseY + disY );

	for( int i = 0; i < EQ_FADER_NUM; ++i ) {
		fixHitRange( mEQFader[ i ], 5, 0, -5, 73 );
	}
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

	setPos( mEffectDial[ ++index ], PARTS_DIAL_1, baseX + disX, baseY + disY );
	disX += disX1;
	setPos( mEffectDial[ ++index ], PARTS_DIAL_1, baseX + disX, baseY + disY );
	disX += disX1 - 1;
	setPos( mEffectDial[ ++index ], PARTS_DIAL_1, baseX + disX, baseY + disY );

	disX = 3;
	disY += disY1;
	setPos( mEffectDial[ ++index ], PARTS_DIAL_1, baseX + disX, baseY + disY );
	disX += disX1;
	setPos( mEffectDial[ ++index ], PARTS_DIAL_1, baseX + disX, baseY + disY );
	disX += disX1 - 1;
	setPos( mEffectDial[ ++index ], PARTS_DIAL_1, baseX + disX, baseY + disY );

	disX = 4;
	disY += disY1 + 3;
	setPos( mEffectDial[ ++index ], PARTS_DIAL_1, baseX + disX, baseY + disY );
	disX += disX1;
	setPos( mEffectDial[ ++index ], PARTS_DIAL_1, baseX + disX, baseY + disY );
	disX += disX1 - 1;
	setPos( mEffectDial[ ++index ], PARTS_DIAL_1, baseX + disX, baseY + disY );
}

void Synthesizer::setEffectSignPos( void )
{
	int index = -1;
	int baseX = 117;
	int baseY = 179;
	int disX1 = 62;
	int disY1 = 178;
	int disX = 0;
	int disY = 0;

	setPos( mEffectSign[ ++index ], PARTS_SIGN_NOISE_GATE, baseX + disX, baseY + disY );
	disX += disX1;
	setPos( mEffectSign[ ++index ], PARTS_SIGN_NOISE_GATE, baseX + disX, baseY + disY );
	disX += disX1 - 1;
	setPos( mEffectSign[ ++index ], PARTS_SIGN_NOISE_GATE, baseX + disX, baseY + disY );

	disX = 3;
	disY += disY1;
	setPos( mEffectSign[ ++index ], PARTS_SIGN_NOISE_GATE, baseX + disX, baseY + disY );
	disX += disX1;
	setPos( mEffectSign[ ++index ], PARTS_SIGN_NOISE_GATE, baseX + disX, baseY + disY );
	disX += disX1 - 1;
	setPos( mEffectSign[ ++index ], PARTS_SIGN_NOISE_GATE, baseX + disX, baseY + disY );

	disX = 4;
	disY += disY1 + 3;
	setPos( mEffectSign[ ++index ], PARTS_SIGN_NOISE_GATE, baseX + disX, baseY + disY );
	disX += disX1;
	setPos( mEffectSign[ ++index ], PARTS_SIGN_NOISE_GATE, baseX + disX, baseY + disY );
	disX += disX1 - 1;
	setPos( mEffectSign[ ++index ], PARTS_SIGN_NOISE_GATE, baseX + disX, baseY + disY );

	for( int i = 0; i < EFFECT_SELECT_NUM; ++i ) {
		mEffectSign[ i ].defY = PARTS_SIGN_NOISE_GATE;
	}
}

void Synthesizer::setWaveSignPos( void )
{
	int index = -1;
	int baseX = 512;
	int baseY = 277;
	int disY1 = 150;
	int disY2 = 143;
	int disX = 0;
	int disY = 0;

	setPos( mWaveSign[ ++index ], PARTS_SIGN_CURVE, baseX + disX, baseY + disY );
	disX = 3;
	disY += disY1;
	setPos( mWaveSign[ ++index ], PARTS_SIGN_CURVE, baseX + disX, baseY + disY );
	disX = 5;
	disY += disY2;
	setPos( mWaveSign[ ++index ], PARTS_SIGN_CURVE, baseX + disX, baseY + disY );

	for( int i = 0; i < TRACK_NUM; ++i ) {
		mWaveSign[ i ].defY = PARTS_SIGN_CURVE;
	}
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

	setPos( mWaveDial[ ++index ], PARTS_DIAL_1, baseX + disX, baseY + disY );
	disX = 3;
	disY += disY1;
	setPos( mWaveDial[ ++index ], PARTS_DIAL_1, baseX + disX, baseY + disY );
	disX = 5;
	disY += disY2;
	setPos( mWaveDial[ ++index ], PARTS_DIAL_1, baseX + disX, baseY + disY );
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

	setPos( mVolumeFader[ ++index ], PARTS_FADER_H, baseX + disX, baseY + disY );
	disY += disY1;
	setPos( mVolumeFader[ ++index ], PARTS_FADER_H, baseX + disX, baseY + disY );
	
	disY += disY2;
	setPos( mVolumeFader[ ++index ], PARTS_FADER_H, baseX + disX, baseY + disY );
	disY += disY1;
	setPos( mVolumeFader[ ++index ], PARTS_FADER_H, baseX + disX, baseY + disY );

	disX = 2;
	disY += disY3 + 5;
	setPos( mVolumeFader[ ++index ], PARTS_FADER_H, baseX + disX, baseY + disY );
	disY += disY1;
	setPos( mVolumeFader[ ++index ], PARTS_FADER_H, baseX + disX, baseY + disY );

	disX = 4;
	disY += disY3 - 2;
	setPos( mVolumeFader[ ++index ], PARTS_FADER_H, baseX + disX, baseY + disY );
	disY += disY1;
	setPos( mVolumeFader[ ++index ], PARTS_FADER_H, baseX + disX, baseY + disY );

	for( int i = 0; i < VOLUME_FADER_NUM; ++i ) {
		PartsData& target = mVolumeFader[ i ];
		fixHitRange( target, 0, 10, 63, -10 );
		target.x = ( target.hitX2 - 10 - target.defX ) / 2 + target.defX;
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

	setPos( mAutoPanButton[ ++index ], PARTS_BUTTON_AUTOPAN_ON, baseX + disX, baseY + disY );
	disY += disY1;
	setPos( mAutoPanButton[ ++index ], PARTS_BUTTON_AUTOPAN_ON, baseX + disX, baseY + disY );
	disY += disY2;
	setPos( mAutoPanButton[ ++index ], PARTS_BUTTON_AUTOPAN_ON, baseX + disX, baseY + disY );

	for( int i = 0; i < TRACK_NUM; ++i ) {
		mAutoPanButton[ i ].partsID = PARTS_BUTTON_AUTOPAN_OFF;
	}
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

	setPos( mTrackButton[ ++index ], PARTS_BUTTON_TRACK_ON, baseX + disX, baseY + disY );
	disX = 0;
	disY += disY1;
	setPos( mTrackButton[ ++index ], PARTS_BUTTON_TRACK_ON, baseX + disX, baseY + disY );
	disX = 0;
	disY += disY2;
	setPos( mTrackButton[ ++index ], PARTS_BUTTON_TRACK_ON, baseX + disX, baseY + disY );

	for( int i = 1; i < TRACK_NUM; ++i ) {
		mTrackButton[ i ].partsID = PARTS_BUTTON_TRACK_OFF;
	}
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

	setPos( mEQLever[ ++index ], PARTS_LEVER_4, baseX + disX, baseY + disY );
	disX += disX1;
	setPos( mEQLever[ ++index ], PARTS_LEVER_4, baseX + disX, baseY + disY );
	disX += disX1;
	setPos( mEQLever[ ++index ], PARTS_LEVER_4, baseX + disX, baseY + disY );

	disX = 0;
	disY += disY1;
	setPos( mEQLever[ ++index ], PARTS_LEVER_4, baseX + disX, baseY + disY );
	disX += disX1;
	setPos( mEQLever[ ++index ], PARTS_LEVER_4, baseX + disX, baseY + disY );
	disX += disX1;
	setPos( mEQLever[ ++index ], PARTS_LEVER_4, baseX + disX, baseY + disY );
	
	disX = 0;
	disY += disY2;
	setPos( mEQLever[ ++index ], PARTS_LEVER_4, baseX + disX, baseY + disY );
	disX += disX1;
	setPos( mEQLever[ ++index ], PARTS_LEVER_4, baseX + disX, baseY + disY );
	disX += disX1;
	setPos( mEQLever[ ++index ], PARTS_LEVER_4, baseX + disX, baseY + disY );

	for( int i = 0; i < EFFECT_EQ_NUM; ++i ) {
		PartsData& target = mEQLever[ i ];
		fixHitRange( target, 0, 5, 32, -12 );
		target.partsID = PARTS_LEVER_1;
		target.x = target.hitX2 - 20;
	}
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
		setPos( mKeyButton[ ++index ], PARTS_BUTTON_KEY_ON, baseX + disX, baseY + disY );
		disX += disX1;
		mKeyButton[ i ].partsID = PARTS_BUTTON_KEY_OFF;
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

	setPos( mPlayButton[ ++index ], PARTS_BUTTON_PLAY_ON, baseX + disX, baseY + disY );
	disY = disY1 + 1;
	disX += disX2;
	setPos( mPlaySign[ index ], PARTS_SIGN_PLAY, baseX + disX, baseY + disY );
	
	disY = 0;
	disX += disX1 - disX2;
	setPos( mPlayButton[ ++index ], PARTS_BUTTON_PLAY_ON, baseX + disX, baseY + disY );
	disY = disY1;
	disX += disX2 + 1;
	setPos( mPlaySign[ index ], PARTS_SIGN_PAUSE, baseX + disX, baseY + disY );
	
	disY = 0;
	disX += disX1 - disX2 - 1;
	setPos( mPlayButton[ ++index ], PARTS_BUTTON_PLAY_ON, baseX + disX, baseY + disY );
	disY = disY1;
	disX += disX2 - 2;
	setPos( mPlaySign[ index ], PARTS_SIGN_REC, baseX + disX, baseY + disY );

	for( int i = 0; i < PLAY_BUTTON_NUM; ++i ) {
		mPlayButton[ i ].partsID = PARTS_BUTTON_PLAY_OFF;
	}
}

void Synthesizer::setScaleSignPos( void )
{
	int baseX = 612;
	int baseY = 363;
	setPos( mScaleSign, PARTS_SIGN_SCALE_C, baseX, baseY);
	mScaleSign.defY = PARTS_SIGN_SCALE_C;
}

void Synthesizer::setScaleDialPos( void )
{
	int baseX = 584;
	int baseY = 382;
	setPos( mScaleDial, PARTS_DIAL_1, baseX, baseY);
}

void Synthesizer::setPos( PartsData& target, PartsID id, int x, int y )
{
	PartsSize& setSize = mPartsSize[ id ];
	target.partsID = id;
	target.x = x;
	target.y = y;
	target.defX = x;
	target.defY = y;
	target.hitX1 = x;
	target.hitY1 = y;
	target.hitX2 = x + setSize.width;
	target.hitY2 = y + setSize.height;
}

void Synthesizer::fixHitRange( PartsData& target, int fixX1, int fixY1, int fixX2, int fixY2 )
{
	target.hitX1 += fixX1;
	target.hitY1 += fixY1;
	target.hitX2 += fixX2;
	target.hitY2 += fixY2;
}

void Synthesizer::sizeInit( void )
{
	// トラック
	setSize( PARTS_BUTTON_TRACK_ON, 41, 0, 102, 28 );
	setSize( PARTS_BUTTON_TRACK_OFF, 41, 28, 102, 39 );

	// オートパン
	setSize( PARTS_BUTTON_AUTOPAN_ON, 0, 0, 41, 28 );
	setSize( PARTS_BUTTON_AUTOPAN_OFF, 0, 28, 41, 39 );

	// レバー
	setSize( PARTS_LEVER_1, 143, 0, 20, 29 );
	setSize( PARTS_LEVER_2, 163, 0, 18, 29 );
	setSize( PARTS_LEVER_3, 181, 0, 18, 29 );
	setSize( PARTS_LEVER_4, 199, 0, 20, 29 );

	// プレイボタン
	setSize( PARTS_BUTTON_PLAY_ON, 143, 29, 39, 38 );
	setSize( PARTS_BUTTON_PLAY_OFF, 182, 29, 39, 44 );

	// ダイヤル
	setSize( PARTS_DIAL_1, 0, 67, 57, 20 );
	setSize( PARTS_DIAL_2, 0, 87, 57, 20 );

	// 鍵盤
	setSize( PARTS_BUTTON_KEY_ON, 81, 67, 24, 31 );
	setSize( PARTS_BUTTON_KEY_OFF, 57, 67, 24, 36 );

	// ランプ
	setSize( PARTS_RAMP_TIME, 208, 73, 16, 15 );
	setSize( PARTS_RAMP_NOTE, 208, 88, 16, 16 );

	// フェーダー
	setSize( PARTS_FADER_H, 197, 73, 11, 31 );
	setSize( PARTS_FADER_V, 177, 73, 20, 19 );

	// プレイサイン
	setSize( PARTS_SIGN_PLAY, 0, 107, 17, 20 );
	setSize( PARTS_SIGN_PAUSE, 17, 107, 15, 20 );
	setSize( PARTS_SIGN_REC, 32, 107, 21, 21 );

	// 波形サイン
	setSize( PARTS_SIGN_CURVE, 163, 67, 14, 13 );
	setSize( PARTS_SIGN_SAWTOOTH, 151, 67, 12, 13 );
	setSize( PARTS_SIGN_SQUARE, 142, 67, 9, 13 );
	setSize( PARTS_SIGN_TRIANGLE, 133, 67, 9, 13 );

	// エフェクトサイン
	setSize( PARTS_SIGN_HIGH_PASS_FILTER, 57, 103, 11, 12 );
	setSize( PARTS_SIGN_BAND_PASS_FILTER, 69, 103, 11, 12);
	setSize( PARTS_SIGN_LOW_PASS_FILTER, 57, 116, 11, 12 );
	setSize( PARTS_SIGN_BAND_ELIMINATE_FILTER, 69, 116, 11, 12 );

	setSize( PARTS_SIGN_DISTORTION1, 80, 98, 12, 16 );
	setSize( PARTS_SIGN_DISTORTION2, 92, 98, 12, 12 );
	setSize( PARTS_SIGN_DISTORTION3, 93, 112, 13, 15 );

	setSize( PARTS_SIGN_VIBRATO, 80, 115, 13, 13 );
	setSize( PARTS_SIGN_CHORUS, 105, 67, 14, 12 );
	setSize( PARTS_SIGN_COMPRESSOR, 119, 67, 14, 12 );

	setSize( PARTS_SIGN_NOISE_GATE, 105, 79, 14, 12 );
	setSize( PARTS_SIGN_TREMOLO, 119, 80, 14, 13 );
	setSize( PARTS_SIGN_DELAY, 133, 81, 17, 10 );

	// コードサイン
	int add = 13;
	int i = -1;
	setSize( PARTS_SIGN_SCALE_BM, 105 + ( ++i ) * add, 92, 13, 12 );
	setSize( PARTS_SIGN_SCALE_AM, 105 + ( ++i ) * add, 92, 13, 12 );
	setSize( PARTS_SIGN_SCALE_GM, 105 + ( ++i ) * add, 92, 13, 12 );
	setSize( PARTS_SIGN_SCALE_FM, 105 + ( ++i ) * add, 92, 13, 12 );
	setSize( PARTS_SIGN_SCALE_EM, 105 + ( ++i ) * add, 92, 13, 12 );
	setSize( PARTS_SIGN_SCALE_DM, 105 + ( ++i ) * add, 92, 13, 12 );
	setSize( PARTS_SIGN_SCALE_CM, 105 + ( ++i ) * add, 92, 13, 12 );
	i = -1;
	setSize( PARTS_SIGN_SCALE_B, 105 + ( ++i ) * add, 104, 13, 12 );
	setSize( PARTS_SIGN_SCALE_A, 105 + ( ++i ) * add, 104, 13, 12 );
	setSize( PARTS_SIGN_SCALE_G, 105 + ( ++i ) * add, 104, 13, 12 );
	setSize( PARTS_SIGN_SCALE_F, 105 + ( ++i ) * add, 104, 13, 12 );
	setSize( PARTS_SIGN_SCALE_E, 105 + ( ++i ) * add, 104, 13, 12 );
	setSize( PARTS_SIGN_SCALE_D, 105 + ( ++i ) * add, 104, 13, 12 );
	setSize( PARTS_SIGN_SCALE_C, 105 + ( ++i ) * add, 104, 13, 12 );
}
void Synthesizer::setSize( PartsID id, int startX, int startY, int width, int height )
{
	PartsSize &setData = mPartsSize[ id ];
	setData.startX = startX;
	setData.startY = startY;
	setData.width = width;
	setData.height = height;
}
