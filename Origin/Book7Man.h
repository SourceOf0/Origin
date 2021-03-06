
void Book7::drawMan( ManState* target )
{
	const int VIEW_WIDTH = Main::SceneManager::VIEW_WIDTH;
	int viewX = getCount( target->count );
	int viewY = target->line * USE_OBJ_IMAGE_HEIGHT;
	int fixX = 0;
	
	switch( target->state ) {
		case MAN_WALK:
			if( target->isLeft ) {
				mManImageArr[ target->image ]->drawWindowOr( target->x, target->line * USE_OBJ_IMAGE_HEIGHT, viewX, USE_MAN_IMAGE_HEIGHT, USE_MAN_IMAGE_WIDTH, USE_MAN_IMAGE_HEIGHT );
				if( target->x < 0 ) {
					mManImageArr[ target->image ]->drawWindowOr( target->x + VIEW_WIDTH, target->line * USE_OBJ_IMAGE_HEIGHT, viewX, USE_MAN_IMAGE_HEIGHT, USE_MAN_IMAGE_WIDTH, USE_MAN_IMAGE_HEIGHT );
				} else if( target->x > VIEW_WIDTH - USE_MAN_IMAGE_WIDTH ) {
					mManImageArr[ target->image ]->drawWindowOr( target->x - VIEW_WIDTH, target->line * USE_OBJ_IMAGE_HEIGHT, viewX, USE_MAN_IMAGE_HEIGHT, USE_MAN_IMAGE_WIDTH, USE_MAN_IMAGE_HEIGHT );
				}
			} else {
				mManImageArr[ target->image ]->drawWindowOr( target->x, target->line * USE_OBJ_IMAGE_HEIGHT, viewX, 0, USE_MAN_IMAGE_WIDTH, USE_MAN_IMAGE_HEIGHT );
				if( target->x < 0 ) {
					mManImageArr[ target->image ]->drawWindowOr( target->x + VIEW_WIDTH, target->line * USE_OBJ_IMAGE_HEIGHT, viewX, 0, USE_MAN_IMAGE_WIDTH, USE_MAN_IMAGE_HEIGHT );
				} else if( target->x > VIEW_WIDTH - USE_MAN_IMAGE_WIDTH ) {
					mManImageArr[ target->image ]->drawWindowOr( target->x - VIEW_WIDTH, target->line * USE_OBJ_IMAGE_HEIGHT, viewX, 0, USE_MAN_IMAGE_WIDTH, USE_MAN_IMAGE_HEIGHT );
				}
			}
			break;

		case MAN_ENTER_START:
			fixX = target->x % USE_MAN_IMAGE_WIDTH;
			if( target->isLeft ) {
				if( target->x >= 0 ) {
					mManImageArr[ target->image ]->drawWindowOr( target->x + USE_MAN_IMAGE_WIDTH - fixX, target->line * USE_OBJ_IMAGE_HEIGHT, viewX + ( USE_MAN_IMAGE_WIDTH - fixX ), USE_MAN_IMAGE_HEIGHT, fixX, USE_MAN_IMAGE_HEIGHT );
				} else {
					fixX = USE_MAN_IMAGE_WIDTH + target->x;
					mManImageArr[ target->image ]->drawWindowOr( target->x + USE_MAN_IMAGE_WIDTH - fixX, target->line * USE_OBJ_IMAGE_HEIGHT, viewX + ( USE_MAN_IMAGE_WIDTH - fixX ), USE_MAN_IMAGE_HEIGHT, fixX, USE_MAN_IMAGE_HEIGHT );
				}
			} else {
				mManImageArr[ target->image ]->drawWindowOr( target->x, target->line * USE_OBJ_IMAGE_HEIGHT, viewX, 0, USE_MAN_IMAGE_WIDTH - fixX, USE_MAN_IMAGE_HEIGHT );
			}
			break;

		case MAN_ENTER_END:
			fixX = target->x % USE_MAN_IMAGE_WIDTH;
			if( target->isLeft ) {
				mManImageArr[ target->image ]->drawWindowOr( target->x, target->line * USE_OBJ_IMAGE_HEIGHT, viewX, USE_MAN_IMAGE_HEIGHT, ( USE_MAN_IMAGE_WIDTH - fixX ), USE_MAN_IMAGE_HEIGHT );
			} else {
				if( target->x >= 0 ) {
					mManImageArr[ target->image ]->drawWindowOr( target->x + USE_MAN_IMAGE_WIDTH - fixX, target->line * USE_OBJ_IMAGE_HEIGHT, viewX + ( USE_MAN_IMAGE_WIDTH - fixX ), 0, fixX, USE_MAN_IMAGE_HEIGHT );
				} else {
					mManImageArr[ target->image ]->drawWindowOr( target->x, target->line * USE_OBJ_IMAGE_HEIGHT, viewX, 0, USE_MAN_IMAGE_WIDTH, USE_MAN_IMAGE_HEIGHT );
				}
			}
			break;

		case MAN_STAY_TURN:
		case MAN_STAY_REST:
			if( target->isLeft ) {
				mManImageArr[ target->image ]->drawWindowOr( target->x, target->line * USE_OBJ_IMAGE_HEIGHT, viewX, USE_MAN_IMAGE_HEIGHT, USE_MAN_IMAGE_WIDTH, USE_MAN_IMAGE_HEIGHT );
			} else {
				mManImageArr[ target->image ]->drawWindowOr( target->x, target->line * USE_OBJ_IMAGE_HEIGHT, viewX, 0, USE_MAN_IMAGE_WIDTH, USE_MAN_IMAGE_HEIGHT );
			}
			break;

		case MAN_LADDER_UP:
		case MAN_LADDER_DOWN:
			mManImageArr[ target->image ]->drawWindowOr( target->x, target->line * USE_OBJ_IMAGE_HEIGHT, viewX, 0, USE_MAN_IMAGE_WIDTH, USE_MAN_IMAGE_LADDER_HEIGHT );
			if( target->line == ( OBJ_Y_NUM - 1 ) ) {
				mManImageArr[ target->image ]->drawWindowOr( target->x, 0, viewX, USE_MAN_IMAGE_HEIGHT, USE_MAN_IMAGE_WIDTH, USE_MAN_IMAGE_HEIGHT );
			}
			break;
	}
}

void Book7::moveMan( ManState* target )
{
	switch( target->state ) {
		case MAN_ENTER_START:
		case MAN_ENTER_END:
		case MAN_WALK:
			moveManWalk( target );
			break;
		case MAN_STAY_TURN:
			moveManTurn( target );
			break;
		case MAN_STAY_REST:
			moveManRest( target );
			break;
		case MAN_LADDER_UP:
			moveManLadderUp( target );
			break;
		case MAN_LADDER_DOWN:
			moveManLadderDown( target );
			break;
	}
}


void Book7::moveManWalk( ManState* target )
{
	const int VIEW_WIDTH = Main::SceneManager::VIEW_WIDTH;

	if( checkWall( target ) ) return;

	if( target->isLeft ) {
		target->x -= WALK_SPEED;
		if( target->x <= -USE_MAN_IMAGE_WIDTH ) {
			target->x = target->x + VIEW_WIDTH;
		}
	} else {
		target->x += WALK_SPEED;
		if( target->x >= VIEW_WIDTH ) {
			target->x = target->x - VIEW_WIDTH;
		}
	}

	++target->count;
	if( target->count >= getMaxCount( target->image ) ) {
		target->count = 0;
	}

	if( checkLadder( target ) ) return;

	if( target->state == MAN_ENTER_START ) {
		moveManEnterStart( target );
		return;
	} else if( target->state == MAN_ENTER_END ) {
		moveManEnterEnd( target );
		return;
	}

	if( checkEntrance( target ) ) return;
}

void Book7::moveManEnterStart( ManState* target )
{
	if( target->target == 0 ) return;
	if( target->target->image != IMAGE_OBJ_ENTRANCE ) return;

	if( ++target->animeState < USE_OBJ_IMAGE_WIDTH_HALF ) return;

	for( int i = 0; i < ENTRANCE_PAIR_NUM; ++i ) {
		ObjState* entTarget = 0;
		if( target->target == mEntranceState[ i ][ 0 ] ) {
			entTarget = mEntranceState[ i ][ 1 ];
		} else if( target->target == mEntranceState[ i ][ 1 ] ) {
			entTarget = mEntranceState[ i ][ 0 ];
		} else {
			continue;
		}
		if( target->isLeft ) {
			target->x = ( entTarget->indexX + 1 ) * USE_OBJ_IMAGE_WIDTH - WALK_SPEED;
		} else {
			target->x = ( entTarget->indexX - 1 ) * USE_OBJ_IMAGE_WIDTH;
		}
		target->line = entTarget->indexY;
		target->target = entTarget;
		setManState( target, MAN_ENTER_END );
	}
}

void Book7::moveManEnterEnd( ManState* target )
{
	if( target->target == 0 ) return;
	if( target->target->image != IMAGE_OBJ_ENTRANCE ) return;

	if( !checkWall( target, FALSE ) ) {
		if( ++target->animeState < USE_OBJ_IMAGE_WIDTH_HALF ) return;
	}

	for( int i = 0; i < ENTRANCE_PAIR_NUM; ++i ) {
		if( target->target == mEntranceState[ i ][ 0 ] ) {
			--mEntranceState[ i ][ 1 ]->useNum;
			break;
		} else if( target->target == mEntranceState[ i ][ 1 ] ) {
			--mEntranceState[ i ][ 0 ]->useNum;
			break;
		}
	}
	removeTarget( target );
	if( target->animeState < USE_OBJ_IMAGE_WIDTH_HALF ) {
		setManState( target, MAN_STAY_TURN );
		return;
	}
	setManState( target, MAN_WALK );
}

void Book7::moveManTurn( ManState* target )
{
	++target->count;
	if( target->count >= getMaxCount( target->image ) ) {
		target->count = 0;
	}

	++target->animeState;
	if( target->animeState > STAY_COUNT ) {
		setManState( target, MAN_WALK );
		target->isLeft = !target->isLeft;
	}
}

void Book7::moveManRest( ManState* target )
{
	++target->count;
	if( target->count >= getMaxCount( target->image ) ) {
		target->count = 0;
	}

	++target->animeState;
	if( target->animeState > STAY_COUNT ) {
		setManState( target, MAN_WALK );
	}
}

void Book7::moveManLadderUp( ManState* target )
{
	ObjState* checkObj = &mObjState[ target->line ][ target->x / OBJ_X_NUM ];
	if( !checkObj->isHold && checkObj->image == IMAGE_OBJ_WALL ) {
		target->animeState = 0;
		target->state = MAN_LADDER_DOWN;
		target->image = IMAGE_MAN_LADDER;
		return;
	}

	++target->count;
	if( target->count >= getMaxCount( target->image ) ) {
		setManState( target, MAN_STAY_REST );
		removeTarget( target );
	}
}

void Book7::moveManLadderDown( ManState* target )
{
	--target->count;
	if( target->count < 0 ) {
		++target->line;
		if( target->line >= OBJ_Y_NUM ) {
			target->line = 0;
		}
		setManState( target, MAN_STAY_REST );
		removeTarget( target );
	}
}



BOOL Book7::checkEntrance( ManState* target, BOOL isSet )
{
	if( target->isLeft ) {
		if( ( target->x + WALK_SPEED ) % USE_OBJ_IMAGE_WIDTH != 0 ) return FALSE;
	} else {
		if( target->x % USE_OBJ_IMAGE_WIDTH != 0 ) return FALSE;
	}
	if( isSet && target->target != 0 ) return FALSE;

	int targetX = ( target->x + ( ( target->isLeft )? WALK_SPEED : 0 ) ) / OBJ_X_NUM;

	ObjState* targetObj = &mObjState[ target->line ][ targetX ];

	if( targetObj->image != IMAGE_OBJ_ENTRANCE ) return FALSE;
	if( targetObj->isHold ) return FALSE;


	for( int i = 0 ; i < ENTRANCE_PAIR_NUM; ++i ) {
		if( targetObj == mEntranceState[ i ][ 0 ] && !mEntranceState[ i ][ 1 ]->isHold ) {
			if( !isSet ) return TRUE;
			++mEntranceState[ i ][ 1 ]->useNum;
			addTarget( target, targetObj );
			setManState( target, MAN_ENTER_START );
			return TRUE;
		} else if( targetObj == mEntranceState[ i ][ 1 ] && !mEntranceState[ i ][ 0 ]->isHold  ) {
			if( !isSet ) return TRUE;
			++mEntranceState[ i ][ 0 ]->useNum;
			addTarget( target, targetObj );
			setManState( target, MAN_ENTER_START );
			return TRUE;
		}
	}

	return FALSE;
}

BOOL Book7::checkWall( ManState* target, BOOL isSet )
{
	if( target->x % USE_OBJ_IMAGE_WIDTH != 0 ) return FALSE;
	if( isSet && target->target != 0 ) return FALSE;

	int targetX = target->x / OBJ_X_NUM;

	if( target->isLeft ) {
		// 左の壁
		--targetX;
		if( targetX < 0 ) targetX = OBJ_X_NUM - 1;
	} else {
		// 右の壁
		targetX = ( targetX + 1 ) % OBJ_X_NUM;
		if( targetX >= OBJ_X_NUM ) targetX = 0;
	}

	ObjState* targetObj = &mObjState[ target->line ][ targetX ];

	if( targetObj->image != IMAGE_OBJ_WALL ) return FALSE;
	if( targetObj->isHold ) return FALSE;
	
	if( !isSet ) return TRUE;
	setManState( target, MAN_STAY_TURN );
	return TRUE;
}

BOOL Book7::checkLadder( ManState* target, BOOL isSet )
{
	if( ( target->x - USE_OBJ_IMAGE_WIDTH ) % USE_OBJ_IMAGE_WIDTH != 0 ) return FALSE;
	if( isSet && target->target != 0 ) return FALSE;

	int targetLine = target->line;

	// 上へのはしご（一応こっちを優先）
	ObjState* targetObj = &mObjState[ targetLine ][ target->x / OBJ_X_NUM ];
	if( !targetObj->isHold && targetObj->image == IMAGE_OBJ_LADDER ) {
		int checkY = targetLine - 1;
		if( checkY < 0 ) checkY = OBJ_Y_NUM - 1;
		ObjState* checkObj = &mObjState[ checkY ][ target->x / OBJ_X_NUM ];
		if( checkObj->isHold || checkObj->image != IMAGE_OBJ_WALL ) {
			if( !isSet ) return TRUE;
			setManState( target, MAN_LADDER_UP );
			addTarget( target, targetObj );
			--target->line;
			if( target->line < 0 ) {
				target->line = OBJ_Y_NUM - 1;
			}
			return TRUE;
		}
	}

	// 下へのはしご
	++targetLine;
	if( targetLine >= OBJ_Y_NUM ) {
		targetLine = 0;
	}
	targetObj = &mObjState[ targetLine ][ target->x / OBJ_X_NUM ];
	if( !targetObj->isHold && targetObj->image == IMAGE_OBJ_LADDER ) {
		if( !isSet ) return TRUE;
		setManState( target, MAN_LADDER_DOWN );
		addTarget( target, targetObj );
		return TRUE;
	}

	return FALSE;
}



int Book7::getCount( int count )
{
	return static_cast< int >( count / ANIME_SPEED ) * USE_MAN_IMAGE_WIDTH;
}
int Book7::getMaxCount( ManImageID image )
{
	return static_cast< int >( mManImageArr[ image ]->mWidth / USE_MAN_IMAGE_WIDTH ) * ANIME_SPEED;
}

void Book7::setManState( ManState* target, ManStateID state )
{
	target->animeState = 0;

	switch( state ) {
		case MAN_WALK:
			if( target->state != MAN_ENTER_START && target->state != MAN_ENTER_END ) target->count = ANIME_SPEED * 2;
			target->image = IMAGE_MAN_WALK;
			break;
		case MAN_STAY_TURN:
			target->count = 0;
			target->image = IMAGE_MAN_STAY;
			break;
		case MAN_STAY_REST:
			target->count = 0;
			target->image = IMAGE_MAN_STAY;
			break;
		case MAN_ENTER_START:
		case MAN_ENTER_END:
			target->image = IMAGE_MAN_WALK;
			break;
		case MAN_LADDER_UP:
			target->count = 0;
			target->image = IMAGE_MAN_LADDER;
			break;
		case MAN_LADDER_DOWN:
			target->count = getMaxCount( IMAGE_MAN_LADDER ) - 1;
			target->image = IMAGE_MAN_LADDER;
			break;
	}
	target->state = state;
}

void Book7::addTarget( ManState* targetMan, ObjState* targetObj )
{
	targetMan->target = targetObj;
	++targetObj->useNum;
}

void Book7::removeTarget( ManState* targetMan )
{
	--targetMan->target->useNum;
	targetMan->target = 0;
}

