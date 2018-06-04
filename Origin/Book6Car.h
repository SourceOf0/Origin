
void Book6::drawCar( void )
{
	double cosine = cos( mCarState.rotation );
	double sine = sin( mCarState.rotation );

	double x1 = PANEL_SIZE * 0.2 - PANEL_SIZE_HALF;
	double y1 = PANEL_SIZE * 0.2 - PANEL_SIZE_HALF;
	double x2 = PANEL_SIZE * 0.75 - PANEL_SIZE_HALF;
	double y2 = PANEL_SIZE * 0.8 - PANEL_SIZE_HALF;
	double x3 = PANEL_SIZE * 0.95 - PANEL_SIZE_HALF;
	double y3 = PANEL_SIZE * 0.5 - PANEL_SIZE_HALF;
	POINT pos[ 5 ];

	mCarBmp->setBlack();

	HBRUSH hBrush = CreateSolidBrush( RGB( 255, 255, 255 ) );

	SelectObject( mCarBmp->mHdcBmp, hBrush );
	
	pos[ 0 ].x = static_cast< int >( cosine * x3 + sine * y3 + PANEL_SIZE_HALF + 0.5 );
	pos[ 0 ].y = static_cast< int >( -sine * x3 + cosine * y3 + PANEL_SIZE_HALF + 0.5 );
	pos[ 1 ].x = static_cast< int >( cosine * x2 + sine * y1 + PANEL_SIZE_HALF + 0.5 );
	pos[ 1 ].y = static_cast< int >( -sine * x2 + cosine * y1 + PANEL_SIZE_HALF + 0.5 );
	pos[ 2 ].x = static_cast< int >( cosine * x1 + sine * y1 + PANEL_SIZE_HALF + 0.5 );
	pos[ 2 ].y = static_cast< int >( -sine * x1 + cosine * y1 + PANEL_SIZE_HALF + 0.5 );
	pos[ 3 ].x = static_cast< int >( cosine * x1 + sine * y2 + PANEL_SIZE_HALF + 0.5 );
	pos[ 3 ].y = static_cast< int >( -sine * x1 + cosine * y2 + PANEL_SIZE_HALF + 0.5 );
	pos[ 4 ].x = static_cast< int >( cosine * x2 + sine * y2 + PANEL_SIZE_HALF + 0.5 );
	pos[ 4 ].y = static_cast< int >( -sine * x2 + cosine * y2 + PANEL_SIZE_HALF + 0.5 );

	Polygon( mCarBmp->mHdcBmp, pos, 5 );

	DeleteObject( hBrush );
}

void Book6::checkNext( void )
{
	for( int i = 0; i < BUTTON_MAX_NUM; ++i ) {
		switch( mButtonState[ i ].instruction ) {
			case CAR_FORWARD:
				mCarState.state = CAR_FORWARD;
				return;
				break;
			case CAR_TURN_LEFT:
				mCarState.state = CAR_TURN_LEFT;
				return;
				break;
			case CAR_TURN_RIGHT:
				mCarState.state = CAR_TURN_RIGHT;
				return;
				break;
		}
	}
	mIsMove = FALSE;
}

void Book6::endMove( void )
{
	for( int i = 0; i < BUTTON_MAX_NUM; ++i ) {
		if( mButtonState[ i ].instruction == CAR_NONE ) continue;
		mButtonState[ i ].instruction = CAR_NONE;
		break;
	}
	mCarState.state = CAR_NONE;
}

void Book6::forwardCar( void )
{
	int fieldWidth = PANEL_SIZE * ( PANEL_X_NUM * 2 - 1 );
	int fieldHeight = PANEL_SIZE * ( PANEL_Y_NUM * 2 - 1 );
	BOOL isEnd = FALSE;

	switch( mCarState.direction ) {
		case DIR_UPSIDE:
			if( mCarState.y == 0 ) {
				isEnd = TRUE;
				break;
			}
			mCarState.y -= MOVE_SPEED;
			isEnd = ( mCarState.y % PANEL_SIZE_TWICE == 0 );
			break;
		case DIR_DOWNSIDE:
			if( mCarState.y == PANEL_SIZE_TWICE * ( PANEL_Y_NUM - 1 ) ) {
				isEnd = TRUE;
				break;
			}
			mCarState.y += MOVE_SPEED;
			isEnd = ( mCarState.y % PANEL_SIZE_TWICE == 0 );
			break;
		case DIR_LEFTSIDE:
			if( mCarState.x == 0 ) {
				isEnd = TRUE;
				break;
			}
			mCarState.x -= MOVE_SPEED;
			isEnd = ( mCarState.x % PANEL_SIZE_TWICE == 0 );
			break;
		case DIR_RIGHTSIDE:
			if( mCarState.x == PANEL_SIZE_TWICE * ( PANEL_X_NUM - 1 ) ) {
				isEnd = TRUE;
				break;
			}
			mCarState.x += MOVE_SPEED;
			isEnd = ( mCarState.x % PANEL_SIZE_TWICE == 0 );
			break;
	}

	if( !isEnd ) return;
	endMove();
}

void Book6::turnLeftCar( void )
{
	mCarState.rotation += TURN_SPEED;

	switch( mCarState.direction ) {
		case DIR_UPSIDE:
			if( mCarState.rotation < ROTATION_LEFT_NUM ) break;
			mCarState.direction = DIR_LEFTSIDE;
			mCarState.rotation = ROTATION_LEFT_NUM;
			endMove();
			break;
		case DIR_DOWNSIDE:
			if( mCarState.rotation < ROTATION_MAX_NUM ) break;
			mCarState.direction = DIR_RIGHTSIDE;
			mCarState.rotation = ROTATION_RIGHT_NUM;
			endMove();
			break;
		case DIR_LEFTSIDE:
			if( mCarState.rotation < ROTATION_DOWN_NUM ) break;
			mCarState.direction = DIR_DOWNSIDE;
			mCarState.rotation = ROTATION_DOWN_NUM;
			endMove();
			break;
		case DIR_RIGHTSIDE:
			if( mCarState.rotation < ROTATION_UP_NUM ) break;
			mCarState.direction = DIR_UPSIDE;
			mCarState.rotation = ROTATION_UP_NUM;
			endMove();
			break;
	}
}

void Book6::turnRightCar( void )
{
	mCarState.rotation -= TURN_SPEED;

	switch( mCarState.direction ) {
		case DIR_UPSIDE:
			if( mCarState.rotation > ROTATION_RIGHT_NUM ) break;
			mCarState.direction = DIR_RIGHTSIDE;
			mCarState.rotation = ROTATION_RIGHT_NUM;
			endMove();
			break;
		case DIR_DOWNSIDE:
			if( mCarState.rotation > ROTATION_LEFT_NUM ) break;
			mCarState.direction = DIR_LEFTSIDE;
			mCarState.rotation = ROTATION_LEFT_NUM;
			endMove();
			break;
		case DIR_LEFTSIDE:
			if( mCarState.rotation > ROTATION_UP_NUM ) break;
			mCarState.direction = DIR_UPSIDE;
			mCarState.rotation = ROTATION_UP_NUM;
			endMove();
			break;
		case DIR_RIGHTSIDE:
			if( mCarState.rotation < 0.0 ) mCarState.rotation += ROTATION_MAX_NUM;
			if( mCarState.rotation > ROTATION_DOWN_NUM ) break;
			mCarState.direction = DIR_DOWNSIDE;
			mCarState.rotation = ROTATION_DOWN_NUM;
			endMove();
			break;
	}
}

void Book6::updateCar( void )
{
	if( !mIsMove ) return;

	switch( mCarState.state ) {
		case CAR_FORWARD:
			forwardCar();
			break;

		case CAR_TURN_LEFT:
			turnLeftCar();
			break;

		case CAR_TURN_RIGHT:
			turnRightCar();
			break;

		case CAR_NONE:
			checkNext();
			return;
			break;
	}

	drawCar();
}

