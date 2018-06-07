
void Book6::drawButton( void ) 
{
	mButtonBmp->setBlack();

	HPEN hPenW = CreatePen( PS_SOLID, BUTTON_LINE_SIZE, RGB( 255, 255, 255 ) );
	HBRUSH hBrushB = CreateSolidBrush( RGB( 0, 0, 0 ) );
	HBRUSH hBrushW = CreateSolidBrush( RGB( 255, 255, 255 ) );

	SelectObject( mButtonBmp->mHdcBmp, hPenW );
	
	int fixX = static_cast< int >( mButtonBmp->mX );
	int fixY = static_cast< int >( mButtonBmp->mY );
	int half = static_cast< int >( BUTTON_SIZE_HALF * 0.5 );
	for( int i = 0; i < BUTTON_MAX_NUM; ++i ) {
		ButtonState *target = &mButtonState[ i ];
		int size = target->partsSize;
		int setX = target->x - fixX;
		int setY = target->y - fixY;

		switch( target->instruction ) {
			case CAR_FORWARD:
				MoveToEx( mButtonBmp->mHdcBmp, setX + BUTTON_SIZE_HALF, setY, NULL );
				LineTo( mButtonBmp->mHdcBmp, setX + BUTTON_SIZE_HALF, setY + size );
				break;
			case CAR_TURN_LEFT:
				MoveToEx( mButtonBmp->mHdcBmp, setX, setY + BUTTON_SIZE_HALF, NULL );
				LineTo( mButtonBmp->mHdcBmp, setX + size, setY + BUTTON_SIZE_HALF );
				break;
			case CAR_TURN_RIGHT:
				MoveToEx( mButtonBmp->mHdcBmp, setX + BUTTON_SIZE - size, setY + BUTTON_SIZE_HALF, NULL );
				LineTo( mButtonBmp->mHdcBmp, setX + BUTTON_SIZE, setY + BUTTON_SIZE_HALF );
				break;
		}
		if( mIsMove && target->instruction == CAR_NONE ) continue;
		MoveToEx( mButtonBmp->mHdcBmp, setX + BUTTON_SIZE_HALF, setY, NULL );
		LineTo( mButtonBmp->mHdcBmp, setX, setY + BUTTON_SIZE_HALF );
		LineTo( mButtonBmp->mHdcBmp, setX + half, setY + BUTTON_SIZE_HALF + half );
		LineTo( mButtonBmp->mHdcBmp, setX + BUTTON_SIZE_HALF + half, setY + BUTTON_SIZE_HALF + half );
		LineTo( mButtonBmp->mHdcBmp, setX + BUTTON_SIZE, setY + BUTTON_SIZE_HALF );
		LineTo( mButtonBmp->mHdcBmp, setX + BUTTON_SIZE_HALF, setY );
	}

	int setX = mStartButton.x - fixX;
	int setY = mStartButton.y - fixY;
	int r = 10;
	SelectObject( mButtonBmp->mHdcBmp, hBrushB );
	RoundRect( mButtonBmp->mHdcBmp, setX, setY, setX + BUTTON_WIDTH, setY + BUTTON_HEIGHT, r, r );
	
	int sizeX = static_cast< int >( BUTTON_WIDTH * 0.5 - BUTTON_WIDTH * 0.4 * mStartButton.partsSize / BUTTON_MOVE_COUNT_MAX );
	int sizeY = static_cast< int >( BUTTON_HEIGHT * 0.9 );
	SelectObject( mButtonBmp->mHdcBmp, hBrushW );
	RoundRect( mButtonBmp->mHdcBmp, setX + sizeX, setY + sizeY, setX + BUTTON_WIDTH - sizeX, setY + BUTTON_HEIGHT - sizeY, r, r );

	DeleteObject( hPenW );
	DeleteObject( hBrushB );
	DeleteObject( hBrushW );
}

void Book6::updateButton( void ) 
{
	int mouseX = Main::HandManager::inst()->getX();
	int mouseY = Main::HandManager::inst()->getY();

	BOOL isClick = Main::HandManager::isClick;
	BOOL isReady = FALSE;

	if( mIsMove ) {
		if( mStartButton.partsSize > 0 ) --mStartButton.partsSize;
		drawButton();
		return;
	}

	for( int i = 0; i < BUTTON_MAX_NUM; ++i ) {
		ButtonState *target = &mButtonState[ i ];
		int x = mouseX - target->x;
		int y = mouseY - target->y;
		int size = target->partsSize;
		int fixSize = 20;
		int hitSize = 25;
		if( x > BUTTON_SIZE_HALF - hitSize && x < BUTTON_SIZE_HALF + hitSize && y > -fixSize && y < size + fixSize ) {
			if( isClick ) {
				target->instruction = ( target->instruction == CAR_FORWARD )? CAR_NONE : CAR_FORWARD;
				Main::HandManager::inst()->setState( Main::HandManager::HAND_PUSH_AFTER );
			} else {
				Main::HandManager::inst()->setState( Main::HandManager::HAND_PUSH_BEFORE );
			}
			break;
		} else if( y > BUTTON_SIZE_HALF - hitSize && y < BUTTON_SIZE_HALF + hitSize ) {
			if( x > -fixSize && x < size + fixSize ) {
				if( isClick ) {
					target->instruction = ( target->instruction == CAR_TURN_LEFT )? CAR_NONE : CAR_TURN_LEFT;
					Main::HandManager::inst()->setState( Main::HandManager::HAND_PUSH_AFTER );
				} else {
					Main::HandManager::inst()->setState( Main::HandManager::HAND_PUSH_BEFORE );
				}
				break;
			} else if( x > BUTTON_SIZE - size - fixSize && x < BUTTON_SIZE + fixSize ) {
				if( isClick ) {
					target->instruction = ( target->instruction == CAR_TURN_RIGHT )? CAR_NONE : CAR_TURN_RIGHT;
					Main::HandManager::inst()->setState( Main::HandManager::HAND_PUSH_AFTER );
				} else {
					Main::HandManager::inst()->setState( Main::HandManager::HAND_PUSH_BEFORE );
				}
				break;
			}
		}
	}

	int moveNum = 0;
	for( int i = 0; i < BUTTON_MAX_NUM; ++i ) {
		if( mButtonState[ i ].instruction == CAR_NONE ) continue;
		isReady = TRUE;
		++moveNum;
	}
	if( isReady ) {
		if( mStartButton.partsSize < BUTTON_MOVE_COUNT_MAX ) ++mStartButton.partsSize;
	} else {
		if( mStartButton.partsSize > 0 ) --mStartButton.partsSize;
		drawButton();
		return;
	}

	int targetX = mouseX - mStartButton.x;
	int targetY = mouseY - mStartButton.y;
	if( targetX > -10 && targetX < BUTTON_WIDTH + 10 && targetY > -10 && targetY < BUTTON_HEIGHT + 10 ) {
		if( isClick ) {
			mIsMove = TRUE;
			Main::HandManager::inst()->setState( Main::HandManager::HAND_PUSH_AFTER );
			if( moveNum > mMaxMoveNum ) mMaxMoveNum = moveNum;
		} else {
			Main::HandManager::inst()->setState( Main::HandManager::HAND_PUSH_BEFORE );
		}
	}

	drawButton();
}
