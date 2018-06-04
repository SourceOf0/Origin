
void Book1::motion1( void )
{
	mMaskBmp->setBlack();
	mMainBmp->setBlack();
	
	if( mAnimeState == 3 ) {
		if( ++mAnimeCount == REST_COUNT ) nextMotion();
		return;
	}

	for( int i = 0; i < 4; ++i ) {
		MaskState *mask = &mMask[ i ];
		mBmp[ mask->kind ]->drawImageOr( mMaskBmp->mHdcBmp, mask->x, mask->y );
		( mask->count == 0 )? ++mask->y : --mask->y;
	}

	ImageState* target = &mImage[ 0 ];
	mBmp[ target->kind ]->drawImageOr( mMainBmp->mHdcBmp, target->x, target->y );
	target = &mImage[ 1 ];
	mBmp[ target->kind ]->drawImageOr( mMainBmp->mHdcBmp, target->x, target->y );

	mMaskBmp->drawImageAnd( mMainBmp->mHdcBmp, 0, 0 );
	
	target = &mImage[ 2 ];
	mBmp[ target->kind ]->drawImageOr( mMainBmp->mHdcBmp, target->x, target->y );

	drawTone( mMainBmp->mHdcBmp, mToneIndex );

	switch( mAnimeState ) {
		case 0:
			if( fadeIn( 10 ) ) mAnimeState = 1;
			break;
		case 1:
			if( mMask[ 0 ].y > static_cast< int >( Main::SceneManager::windowHeight / 2 ) ) mAnimeState = 2;
			break;
		case 2:
			if( fadeOut( 10 ) ) mAnimeState = 3;
			break;
	}
}

void Book1::motion2( void )
{
	mMaskBmp->setBlack();
	mMainBmp->setBlack();
	
	if( mAnimeState == 2 ) {
		if( ++mAnimeCount == REST_COUNT ) nextMotion();
		return;
	}

	ImageState* target = &mImage[ 0 ];
	Image::DCBitmap *bmp = mBmp[ target->kind ];
	int fix = target->count;
	bmp->drawImageOr( mMainBmp->mHdcBmp, target->x + fix, target->y, fix, 0, bmp->mWidth - fix * 2, bmp->mHeight );

	switch( mAnimeState ) {
		case 0:
			++mAnimeCount;
			if( mAnimeCount == 100 ) mAnimeState = 1;
			break;
		case 1:
			target->count += 2;
			if( target->count >= static_cast< int >( bmp->mWidth / 2 ) ) {
				mAnimeCount = 0;
				mAnimeState = 2;
			}
			break;
	}
}

void Book1::motion3( void )
{
	mMaskBmp->setBlack();
	mMainBmp->setBlack();
	
	if( mAnimeState == 4 ) {
		if( ++mAnimeCount == REST_COUNT ) nextMotion();
		return;
	}

	ImageState* target = 0;
	switch( mAnimeState ) {
		case 0:
			target = &mImage[ 0 ];
			mBmp[ target->kind ]->drawImageOr( mMainBmp->mHdcBmp, target->x, target->y );
			drawTone( mMainBmp->mHdcBmp, mToneIndex );
			if( fadeIn( 10 ) ) {
				mToneIndex = TONE_NONE - 1;
				mAnimeCount = 0;
				mAnimeState = 1;
			}
			break;

		case 1:
			target = &mImage[ 1 ];
			mBmp[ target->kind ]->drawImageOr( mMainBmp->mHdcBmp, target->x, target->y );
			drawTone( mMainBmp->mHdcBmp, mToneIndex );
			target = &mImage[ 0 ];
			mBmp[ target->kind ]->drawImageOr( mMainBmp->mHdcBmp, target->x, target->y );

			if( fadeIn( 10 ) ) mAnimeState = 2;
			break;

		case 2:
			target = &mImage[ 0 ];
			mBmp[ target->kind ]->drawImageOr( mMainBmp->mHdcBmp, target->x, target->y );
			drawTone( mMainBmp->mHdcBmp, mToneIndex );
			target = &mImage[ 1 ];
			mBmp[ target->kind ]->drawImageOr( mMainBmp->mHdcBmp, target->x, target->y );

			if( fadeOut( 10 ) ) {
				mToneIndex = 0;
				mAnimeCount = TONE_NONE * 10 - 1;
				mAnimeState = 3;
			}
			break;

		case 3:
			target = &mImage[ 1 ];
			mBmp[ target->kind ]->drawImageOr( mMainBmp->mHdcBmp, target->x, target->y );
			drawTone( mMainBmp->mHdcBmp, mToneIndex );

			if( fadeOut( 10 ) ) mAnimeState = 4;
			break;
	}
	for( int i = 0; i < 8; ++i ) {
		MaskState *mask = &mMask[ i ];
		mBmp[ mask->kind ]->drawImageOr( mMaskBmp->mHdcBmp, mask->x, mask->y );
		++mask->y;
	}
	mMaskBmp->drawImageAnd( mMainBmp->mHdcBmp, 0, 0 );
}

void Book1::motion4( void )
{
	mMaskBmp->setBlack();
	mMainBmp->setBlack();
	
	if( mAnimeState == 5 ) {
		if( ++mAnimeCount == REST_COUNT ) nextMotion();
		return;
	}

	ImageState* target = 0;

	switch( mAnimeState ) {
		case 0:
			target = &mImage[ 0 ];
			mBmp[ target->kind ]->drawImageOr( mMainBmp->mHdcBmp, target->x, target->y );
			drawTone( mMainBmp->mHdcBmp, mToneIndex );

			if( fadeIn( 10 ) ) {
				mAnimeState = 1;
				mToneIndex = TONE_NONE - 1;
				mAnimeCount = 0;
				break;
			}
			break;

		case 1:
			target = &mImage[ 1 ];
			mBmp[ target->kind ]->drawImageOr( mMainBmp->mHdcBmp, target->x, target->y );
			drawTone( mMainBmp->mHdcBmp, mToneIndex );
			target = &mImage[ 0 ];
			mBmp[ target->kind ]->drawImageOr( mMainBmp->mHdcBmp, target->x, target->y );

			if( fadeIn( 8 ) ) mAnimeState = 2;
			break;

		case 2:
			target = &mImage[ 0 ];
			mBmp[ target->kind ]->drawImageOr( mMainBmp->mHdcBmp, target->x, target->y );
			drawTone( mMainBmp->mHdcBmp, mToneIndex );
			target = &mImage[ 2 ];
			mBmp[ target->kind ]->drawImageOr( mMainBmp->mHdcBmp, target->x, target->y );
			if( fadeOut( 8 ) ) {
				mAnimeState = 3;
				mToneIndex = 0;
			}
			break;

		case 3:
			target = &mImage[ 3 ];
			mBmp[ target->kind ]->drawImageOr( mMainBmp->mHdcBmp, target->x, target->y );
			drawTone( mMainBmp->mHdcBmp, mToneIndex );
			if( mAnimeCount == TONE_NONE * 5 - 1 ) {
				mAnimeState = 4;
			} else if( ++mAnimeCount % 10 == 0 ) ++mToneIndex;
			break;

		case 4:
			target = &mImage[ 4 ];
			mBmp[ target->kind ]->drawImageOr( mMainBmp->mHdcBmp, target->x, target->y );
			drawTone( mMainBmp->mHdcBmp, mToneIndex );

			if( fadeOut( 10 ) ) {
				mAnimeState = 5;
				mAnimeCount = 0;
			}
			break;
	}
}

void Book1::motion5( void )
{
	mMaskBmp->setBlack();
	mMainBmp->setBlack();
	
	if( mAnimeState == 3 ) {
		if( ++mAnimeCount == REST_COUNT ) nextMotion();
		return;
	}

	ImageState* target = &mImage[ 0 ];
	Image::DCBitmap *bmp = mBmp[ target->kind ];
	int viewSize = 100;
	int fix = target->count - viewSize;
	bmp->drawImageOr( mMainBmp->mHdcBmp, target->x, target->y + fix, 0, fix, bmp->mWidth, viewSize );

	switch( mAnimeState ) {
		case 0:
			target->count += viewSize / 10;
			if( target->count >= static_cast< int >( bmp->mHeight + viewSize ) ) {
				mAnimeCount = 0;
				mAnimeState = 1;
				target->count = 0;
			}
			break;

		case 1:
			if( ++mAnimeCount == 100 ) mAnimeState = 2;
			break;

		case 2:
			target->count += viewSize / 10;
			if( target->count >= static_cast< int >( bmp->mHeight + viewSize ) ) {
				mAnimeCount = 0;
				mAnimeState = 3;
			}
			break;
	}
}

void Book1::motion6( void )
{
	mMaskBmp->setBlack();
	mMainBmp->setBlack();
	
	if( mAnimeState == 2 ) {
		if( ++mAnimeCount == REST_COUNT ) nextMotion();
		return;
	}

	ImageState* target = &mImage[ 0 ];
	mBmp[ target->kind ]->drawImageOr( mMainBmp->mHdcBmp, target->x, target->y );
	drawTone( mMainBmp->mHdcBmp, mToneIndex );

	switch( mAnimeState ) {
		case 0:
			if( fadeIn( 20 ) ) mAnimeState = 1;
			break;
		case 1:
			if( fadeOut( 20 ) ) mAnimeState = 2;
			break;
	}
}

void Book1::motion7( void )
{
	mMainBmp->setBlack();
	if( mAnimeState == BOOK1_MASK_NUM + 1 ) {
		if( ++mAnimeCount == REST_COUNT ) nextMotion();
		return;
	}
	
	ImageState* target = &mImage[ 0 ];
	mBmp[ target->kind ]->drawImageOr( mMainBmp->mHdcBmp, target->x, target->y );
	mMaskBmp->drawImageAnd( mMainBmp->mHdcBmp, 0, 0 );

	if( mAnimeState < BOOK1_MASK_NUM ) {
		MaskState *mask = &mMask[ mAnimeState ];
		if( ++mAnimeCount % 2 == 0 ) {
			drawDot( mMaskBmp->mHdcBmp, mask->x + ( rand() % ( mBmp[ target->kind ]->mWidth + mDotBmp->mHeight ) ), mask->y, mask->count );
			mask->y += 50;
		}
		if( mask->y > Main::SceneManager::windowHeight ) ++mAnimeState;
		if( mAnimeState == BOOK1_MASK_NUM ) {
			mAnimeCount = TONE_NONE * 10 - 1;
			mToneIndex = 0;
		}
	} else {
		drawTone( mMainBmp->mHdcBmp, mToneIndex );
		if( fadeOut( 10 ) ) {
			mMaskBmp->setBlack();
			++mAnimeState;
		}
	}
}

void Book1::motion8( void )
{
	mMaskBmp->setBlack();
	mMainBmp->setBlack();
	
	if( mAnimeState == 1 ) {
		if( ++mAnimeCount == REST_COUNT ) nextMotion();
		return;
	}

	ImageState* target = &mImage[ 0 ];
	mBmp[ target->kind ]->drawImageOr( mMainBmp->mHdcBmp, target->x, target->y );

	for( int i = 0; i < 3; ++i ) {
		MaskState *mask = &mMask[ i ];
		mBmp[ mask->kind ]->drawImageOr( mMaskBmp->mHdcBmp, mask->x, mask->y );
		mask->y += ( i + 2 );
	}

	mMaskBmp->drawImageAnd( mMainBmp->mHdcBmp, 0, 0 );
	
	if( mMask[ 0 ].y > Main::SceneManager::windowHeight ) mAnimeState = 1;
}

void Book1::motion9( void )
{
	if( mAnimeState == 11 ) {
		if( ++mAnimeCount == REST_COUNT ) {
			nextMotion();
			mMaskBmp->setBlack();
			mMainBmp->setBlack();
		}
		return;
	}

	MaskState *mask = &mMask[ 0 ];
	Image::DCBitmap* maskBmp = mBmp[ mask->kind ];

	if( mAnimeState == 10 ) {
		mMaskBmp->drawImageAnd( mMainBmp->mHdcBmp, mask->x, mask->y, 0, 0, maskBmp->mWidth, maskBmp->mHeight );
		mask->y -= 10;
		if( mask->y < - static_cast< int >( maskBmp->mHeight ) ) ++mAnimeState;
		return;
	}
	mMainBmp->setBlack();
	
	ImageState* target = &mImage[ 0 ];
	mBmp[ target->kind ]->drawImageOr( mMainBmp->mHdcBmp, target->x, target->y );

	if( mAnimeState % 2 == 0 ) {
		maskBmp->drawImageOr( mMaskBmp->mHdcBmp, mask->x, mask->y, 0, 0, mask->count, maskBmp->mHeight );
		mask->count += 20;
		if( mask->count >= static_cast< int >( maskBmp->mWidth ) ) {
			mask->x = rand() % ( Main::SceneManager::windowWidth - maskBmp->mWidth );
			mask->y = rand() % ( Main::SceneManager::windowHeight ) - maskBmp->mHeight / 2;
			mask->count = static_cast< int >( maskBmp->mWidth );
			++mAnimeState;
		}
		mMaskBmp->drawImageAnd( mMainBmp->mHdcBmp, 0, 0 );
	} else {
		maskBmp->drawImageOr( mMaskBmp->mHdcBmp, mask->x + mask->count, mask->y, mask->count, 0, maskBmp->mWidth - mask->count, maskBmp->mHeight );
		mask->count -= 20;
		if( mask->count < 0 ) {
			mask->x = rand() % ( Main::SceneManager::windowWidth - maskBmp->mWidth );
			mask->y = rand() % ( Main::SceneManager::windowHeight ) - maskBmp->mHeight / 2;
			mask->count = 0;
			++mAnimeState;
		}
		mMaskBmp->drawImageAnd( mMainBmp->mHdcBmp, 0, 0 );
		if( mAnimeState == 10 ) {
			mMaskBmp->setWhite();
			maskBmp->drawImageInv( mMaskBmp->mHdcBmp, 0, 0 );
			mask->x = static_cast< int >( ( Main::SceneManager::windowWidth - maskBmp->mWidth ) / 2 );
			mask->y = static_cast< int >( Main::SceneManager::windowHeight );
		}
	}
}

void Book1::motion10( void )
{
	if( mAnimeState == 3 ) {
		if( ++mAnimeCount == REST_COUNT ) {
			nextMotion();
			mMaskBmp->setBlack();
			mMainBmp->setBlack();
		}
		return;
	}

	ImageState* target = &mImage[ 0 ];
	switch( mAnimeState ) {
		case 0:
			mMainBmp->setBlack();
			mBmp[ target->kind ]->drawImageOr( mMainBmp->mHdcBmp, target->x, target->y );
			drawToneOr( mMaskBmp->mHdcBmp, mToneIndex );
			mMaskBmp->drawImageAnd( mMainBmp->mHdcBmp, 0, 0 );
			if( mAnimeCount == 7 * 30 - 1 ) {
				mAnimeCount = 0;
				mAnimeState = 1;
				mToneIndex = TONE_NONE - 1;
				break;
			}
			if( ++mAnimeCount % 30 == 0 ) --mToneIndex;
			break;

		case 1:
			mMaskBmp->setBlack();
			drawToneOr( mMaskBmp->mHdcBmp, mToneIndex );
			mMaskBmp->drawImageOr( mMainBmp->mHdcBmp, 0, 0 );
			if( mAnimeCount == 6 * 30 - 1 ) {
				mAnimeState = 2;
				mAnimeCount = 6 * 15 - 1;
				break;
			}
			if( ++mAnimeCount % 30 == 0 ) --mToneIndex;
			break;

		case 2:
			drawTone( mMaskBmp->mHdcBmp, mToneIndex );
			mMaskBmp->drawImage( mMainBmp->mHdcBmp, 0, 0 );
			if( fadeOut( 15 ) ) mAnimeState = 3;
			break;
	}
}

void Book1::motion11( void )
{
	mMaskBmp->setBlack();
	mMainBmp->setBlack();
	
	if( mAnimeState == 1 ) {
		if( ++mAnimeCount == REST_COUNT ) nextMotion();
		return;
	}

	ImageState* target = &mImage[ 0 ];
	mBmp[ target->kind ]->drawImageOr( mMainBmp->mHdcBmp, target->x, target->y );

	int height = static_cast< int >( mBmp[ mMask[ 0 ].kind ]->mHeight );
	BOOL isEnd = TRUE;
	for( int i = 0; i < 5; ++i ) {
		if( mMask[ i ].y < -height ) continue;
		isEnd = FALSE;
		MaskState *mask = &mMask[ i ];
		mBmp[ mask->kind ]->drawImageOr( mMaskBmp->mHdcBmp, mask->x, mask->y );
		mask->y -= mask->count;
	}

	mMaskBmp->drawImageAnd( mMainBmp->mHdcBmp, 0, 0 );
	
	if( isEnd ) mAnimeState = 1;
}

void Book1::motion12( void )
{
	mMainBmp->setBlack();
	
	if( mAnimeState == 3 ) {
		if( ++mAnimeCount == REST_COUNT ) {
			nextMotion();
			mMaskBmp->setBlack();
		}
		return;
	}

	int windowHeight = static_cast< int >( Main::SceneManager::windowHeight );

	ImageState* target = &mImage[ 0 ];
	mBmp[ target->kind ]->drawImageOr( mMainBmp->mHdcBmp, target->x, target->y );
	mMaskBmp->drawImageOr( mMainBmp->mHdcBmp, 0, 0 );
	drawTone( mMainBmp->mHdcBmp, mToneIndex );

	switch( mAnimeState ) {
		case 0:
			if( fadeIn( 15 ) ) {
				mAnimeState = 1;
				mAnimeCount = 0;
			}
			return;
			break;
		case 2:
			if( fadeOut( 15 ) ) mAnimeState = 3;
			return;
			break;
	}
	int bmpWidth = mDotBmp->mHeight;
	int width = Main::SceneManager::windowWidth + bmpWidth;
	int height = windowHeight / 5 + bmpWidth;
	if( ++mAnimeCount % 10 == 0 ) {
		drawDot( mMaskBmp->mHdcBmp, rand() % width - bmpWidth, rand() % height - bmpWidth + windowHeight * 3 / 5, rand() % 3 );
	}
	if( mAnimeCount > 100 ) {
		mAnimeCount = TONE_NONE * 15 - 1;
		mAnimeState = 2;
	}
}

