
void Book4::moveBall( void )
{
	int mouseX = Main::HandManager::inst()->getX();
	int mouseY = Main::HandManager::inst()->getY();
	BOOL isClick = Main::HandManager::isClick;

	switch( mBallState.image ) {
		case IMAGE_BALL_NORMAL:
			moveBallNormal( isClick, mouseX, mouseY );
			break;
		case IMAGE_BALL_LEFT:
			moveBallLeft( isClick, mouseX, mouseY );
			break;
		case IMAGE_BALL_RIGHT:
			moveBallRight( isClick, mouseX, mouseY );
			break;
		case IMAGE_BALL_STOP:
			moveBallStop( isClick, mouseX, mouseY );
			break;
		case IMAGE_BALL_JUMP:
			moveBallJump( isClick, mouseX, mouseY );
			break;
		case IMAGE_BALL_FALL:
			moveBallFall( isClick, mouseX, mouseY );
			break;
		case IMAGE_BALL_SHAKE:
			moveBallShake( isClick, mouseX, mouseY );
			break;
	}
}

void Book4::moveBallNormal( BOOL isClick, int mouseX, int mouseY )
{
	int disX = mouseX - ( mBallState.x + USE_BALL_IMAGE_SIZE_HALF );
	int disY = mouseY - ( mBallState.y + USE_BALL_IMAGE_SIZE_HALF );
	int dis = disX * disX + disY * disY;
	int maxDis = 60 * 60;
	
	if( dis < maxDis ) {
		if( isClick ) {
			Main::HandManager::inst()->setState( Main::HandManager::HAND_PUSH_AFTER );
			mBallState.image = IMAGE_BALL_SHAKE;
			mWasKeep = TRUE;
		} else {
			Main::HandManager::inst()->setState( Main::HandManager::HAND_PUSH_BEFORE );
		}
	} else if( isHitBoard( mouseX, mouseY ) ) {
		if( isClick ) {
			Main::HandManager::inst()->setState( Main::HandManager::HAND_PUSH_AFTER );
			mBallState.image = IMAGE_BALL_JUMP;
			mBallState.state = STATE_BALL_JUMP_START;
			mBoardState.state = 1;
		} else {
			Main::HandManager::inst()->setState( Main::HandManager::HAND_PUSH_BEFORE );
		}
	} else if( mouseX > 400 + USE_BALL_IMAGE_SIZE_HALF ) {
		Main::HandManager::inst()->setState( Main::HandManager::HAND_RIGHT );
		if( isClick ) {
			mBallState.image = IMAGE_BALL_RIGHT;
			mBallState.state = STATE_BALL_FALL;
		}
	} else if( mouseX < 400 ) {
		Main::HandManager::inst()->setState( Main::HandManager::HAND_LEFT );
		if( isClick ) {
			mBallState.image = IMAGE_BALL_LEFT;
			mWasKeep = TRUE;
		}
	}
}

void Book4::moveBallLeft( BOOL isClick, int mouseX, int mouseY )
{
	mBallState.x -= MOVE_SPEED;
	++mBallState.count;
	if( mBallState.count >= static_cast< int >( mBallImageArr[ mBallState.image ]->mWidth / USE_BALL_IMAGE_SIZE * ANIME_SPEED ) ) {
		mBallState.count = 0;
	}
	if( mBallState.x < - USE_BALL_IMAGE_SIZE ) {
		resetBall();
	}
}

void Book4::moveBallRight( BOOL isClick, int mouseX, int mouseY )
{
	mBallState.x += MOVE_SPEED;

	++mBallState.count;
	switch( mBallState.state ) {
		case STATE_BALL_SETTING:
			if( mBallState.count >= static_cast< int >( mBallImageArr[ mBallState.image ]->mWidth / USE_BALL_IMAGE_SIZE * ANIME_SPEED ) ) {
				if( mBallState.x > 350 ) mBallState.image = IMAGE_BALL_STOP;
				mBallState.count = 0;
			}
			break;

		case STATE_BALL_FALL:
			if( mBallState.count >= static_cast< int >( mBallImageArr[ mBallState.image ]->mWidth / USE_BALL_IMAGE_SIZE * ANIME_SPEED ) ) {
				mBallState.count = 0;
			}
			if( mBallState.x > 515 ) {
				mBallState.image = IMAGE_BALL_FALL;
				mBallState.count = 0;
			}
			break;
	}
}

void Book4::moveBallStop( BOOL isClick, int mouseX, int mouseY )
{
	++mBallState.count;
	if( mBallState.count >= static_cast< int >( mBallImageArr[ mBallState.image ]->mWidth / USE_BALL_IMAGE_SIZE * ANIME_SPEED ) ) {
		mBallState.image = IMAGE_BALL_NORMAL;
		mBallState.count = 0;
	}
}

void Book4::moveBallJump( BOOL isClick, int mouseX, int mouseY )
{
	switch( mBallState.state ) {
		case STATE_BALL_JUMP_START:
			mBallState.vy += 1;
			if( mBallState.x >= 470 ) {
				mBallState.state = STATE_BALL_JUMP;
				mBallState.vy = static_cast< int >( static_cast< double >( rand() ) / RAND_MAX * -20 - 20 );
			}
			break;
		case STATE_BALL_JUMP:
			mBallState.vy += 1;
			break;
	}
	
	mBallState.x += FALL_SPEED;
	mBallState.y += mBallState.vy;

	++mBallState.count;
	if( mBallState.count >= static_cast< int >( mBallImageArr[ mBallState.image ]->mWidth / USE_BALL_IMAGE_SIZE * ANIME_SPEED ) ) {
		mBallState.count = 0;
	}

	if( mBallState.x >= Main::SceneManager::VIEW_WIDTH ) {
		mWasFall = TRUE;
		breakBallX();
		resetBall();
	}
	if( mBallState.y >= Main::SceneManager::VIEW_HEIGHT ) {
		mWasFall = TRUE;
		breakBallY();
		resetBall();
	}
}

void Book4::moveBallFall( BOOL isClick, int mouseX, int mouseY )
{
	mBallState.x += MOVE_SPEED;
	mBallState.vy += 1;
	mBallState.y += mBallState.vy;

	++mBallState.count;
	if( mBallState.count >= static_cast< int >( mBallImageArr[ mBallState.image ]->mWidth / USE_BALL_IMAGE_SIZE * ANIME_SPEED ) ) {
		mBallState.count = 0;
	}

	if( mBallState.y >= Main::SceneManager::VIEW_HEIGHT ) {
		mWasFall = TRUE;
		breakBallY();
		resetBall();
	}
}

void Book4::moveBallShake( BOOL isClick, int mouseX, int mouseY )
{
	++mBallState.count;
	switch( static_cast< int >( mBallState.count / ANIME_SPEED ) ) {
		case 0:
			mBallState.x += 1;
			break;
		case 3:
		case 4:
			mBallState.x -= 1;
			break;
		case 7:
			mBallState.x += 1;
			break;
	}
	if( mBallState.count >= static_cast< int >( mBallImageArr[ mBallState.image ]->mWidth / USE_BALL_IMAGE_SIZE * ANIME_SPEED ) ) {
		mBallState.image = IMAGE_BALL_NORMAL;
		mBallState.count = 0;
	}
}

void Book4::resetBall( void )
{
	mBallState.x = - USE_BALL_IMAGE_SIZE;
	mBallState.y = ( Main::SceneManager::VIEW_HEIGHT - USE_BALL_IMAGE_SIZE ) / 2;
	mBallState.vy = 0;
	mBallState.state = STATE_BALL_SETTING;
	mBallState.count = 0;
	mBallState.image = IMAGE_BALL_RIGHT;
}

BOOL Book4::isHitBoard( int mouseX, int mouseY )
{
	if( mouseY >= mBoardState.y + 210 || mouseX >= USE_BOARD_IMAGE_SIZE + USE_BOARD_IMAGE_SIZE ) {
		return FALSE;
	}
	if( mouseY > mBoardState.y + 150 ) {
		return TRUE;
	} else if( mouseY > mBoardState.y + 90 ) {
		int startX = USE_BOARD_IMAGE_SIZE + USE_BOARD_IMAGE_SIZE - 50;
		if( mouseX < startX ) {
			return TRUE;
		} else if( ( mouseX - startX ) < ( mouseY - mBoardState.y - 90 ) * 0.7 ) {
			return TRUE;
		}
	}
	return FALSE;
}

void Book4::breakBallX( void )
{
	for( int i = 0; i < MAX_SPLASH_NUM; ++i ) {
		SplashState* target = &mSplashState[ i ];
		target->x = mBallState.x - 15;
		target->y = mBallState.y + static_cast< int >( static_cast< double >( rand() ) / RAND_MAX * 50 );
		target->vx = static_cast< int >( static_cast< double >( rand() ) / RAND_MAX * -15 );
		target->count = 0;
		if( target->y < mBallState.y + 10 ) {
			target->vy = static_cast< int >( static_cast< double >( rand() ) / RAND_MAX * 4 );
			target->kind = 3;
		} else if( target->y < mBallState.y + 20 ) {
			target->vy = static_cast< int >( static_cast< double >( rand() ) / RAND_MAX * 8 );
			target->kind = 4;
		} else if( target->y < mBallState.y + 30 ) {
			target->vy = static_cast< int >( static_cast< double >( rand() ) / RAND_MAX * 12 );
			target->kind = 5;
		} else if( target->y < mBallState.y + 40 ) {
			target->vy = static_cast< int >( static_cast< double >( rand() ) / RAND_MAX * 16 );
			target->kind = 6;
		} else {
			target->vy = static_cast< int >( static_cast< double >( rand() ) / RAND_MAX * 20 );
			target->kind = 7;
		}
	}

	for( int i = 0; i < MAX_PIECE_NUM; ++i ) {
		PieceState* target = &mPieceState[ i ];
		target->x = mBallState.x - 15;
		target->y = mBallState.y - static_cast< int >( static_cast< double >( rand() - RAND_MAX * 0.5 ) / ( RAND_MAX * 0.5 ) * 50 );
		target->vx = static_cast< int >( static_cast< double >( rand() ) / RAND_MAX * -20 );
		target->vy = static_cast< int >( static_cast< double >( rand() ) / RAND_MAX * 20 );
		target->count = 0;
		float random = static_cast< float >( rand() ) / RAND_MAX;
		if( random < 0.3 ) {
			target->kind = 0;
		} else if( random < 0.6 ) {
			target->kind = 2;
		} else {
			target->kind = 1;
		}
	}
}

void Book4::breakBallY( void )
{
	for( int i = 0; i < MAX_SPLASH_NUM; ++i ) {
		SplashState* target = &mSplashState[ i ];
		target->x = mBallState.x + static_cast< int >( static_cast< double >( rand() - RAND_MAX * 0.5 ) / ( RAND_MAX * 0.5 ) * 100 );
		target->y = mBallState.y - 15;
		target->vy = static_cast< int >( static_cast< double >( rand() ) / RAND_MAX * -10 - 10 );
		target->count = 0;
		if( target->x < mBallState.x - 50 ) {
			target->vy = static_cast< int >( static_cast< double >( rand() ) / RAND_MAX * -20 );
			target->kind = 4;
		} else if( target->x < mBallState.x - 10 ) {
			target->vx = static_cast< int >( static_cast< double >( rand() ) / RAND_MAX * -10 );
			target->kind = 3;
		} else if( target->x < mBallState.x + 10 ) {
			target->vx = static_cast< int >( static_cast< double >( rand() ) / RAND_MAX * -1 );
			target->kind = 2;
		} else if( target->x < mBallState.x + 50 ) {
			target->vx = static_cast< int >( static_cast< double >( rand() ) / RAND_MAX * 10 );
			target->kind = 1;
		} else {
			target->vx = static_cast< int >( static_cast< double >( rand() ) / RAND_MAX * 20 );
			target->kind = 0;
		}
	}

	for( int i = 0; i < MAX_PIECE_NUM; ++i ) {
		PieceState* target = &mPieceState[ i ];
		target->x = mBallState.x + static_cast< int >( static_cast< double >( rand() - RAND_MAX * 0.5 ) / ( RAND_MAX * 0.5 ) * 120 );
		target->y = mBallState.y - 15;
		if( target->x < mBallState.x - 50 ) {
			target->vx = static_cast< int >( static_cast< double >( rand() ) / RAND_MAX * -15 );
		} else if( target->x < mBallState.x + 50 ) {
			target->vx = static_cast< int >( static_cast< double >( rand() - RAND_MAX * 0.5 ) / ( RAND_MAX * 0.5 ) * 5 );
		} else {
			target->vx = static_cast< int >( static_cast< double >( rand() ) / RAND_MAX * 15 );
		}
		target->vy = static_cast< int >( static_cast< double >( rand() ) / RAND_MAX * -25 - 2 );
		target->count = 0;
		float random = static_cast< float >( rand() ) / RAND_MAX;
		if( random < 0.3 ) {
			target->kind = 0;
		} else if( random < 0.6 ) {
			target->kind = 2;
		} else {
			target->kind = 1;
		}
	}
}
