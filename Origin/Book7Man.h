
void Book7::drawMan( ManState* target )
{
	int windowWidth = Main::SceneManager::windowWidth;
	int windowHeight = Main::SceneManager::windowHeight;
	int viewX = static_cast< int >( target->count / ANIME_SPEED ) * USE_MAN_IMAGE_WIDTH;
	int viewY = target->line * USE_OBJ_IMAGE_HEIGHT;

	switch( target->image ) {
		case IMAGE_MAN_STAY:
		case IMAGE_MAN_WALK:
			if( target->isLeft ) {
				if( target->isEnter ) {
					if( target->state == 0 ) {
						mManImageArr[ target->image ]->drawWindowOr( target->x, target->line * USE_OBJ_IMAGE_HEIGHT, viewX, 0, USE_MAN_IMAGE_WIDTH - ( target->x % USE_MAN_IMAGE_WIDTH ), USE_MAN_IMAGE_HEIGHT );
					} else {
						mManImageArr[ target->image ]->drawWindowOr( target->x + USE_MAN_IMAGE_WIDTH - target->x % USE_MAN_IMAGE_WIDTH, target->line * USE_OBJ_IMAGE_HEIGHT, viewX + ( USE_MAN_IMAGE_WIDTH - target->x % USE_MAN_IMAGE_WIDTH ), 0, ( target->x % USE_MAN_IMAGE_WIDTH ), USE_MAN_IMAGE_HEIGHT );
					}
				} else {
					mManImageArr[ target->image ]->drawWindowOr( target->x, target->line * USE_OBJ_IMAGE_HEIGHT, viewX, 0, USE_MAN_IMAGE_WIDTH, USE_MAN_IMAGE_HEIGHT );
					if( target->x < 0 ) {
						mManImageArr[ target->image ]->drawWindowOr( target->x + windowWidth, target->line * USE_OBJ_IMAGE_HEIGHT, viewX, 0, USE_MAN_IMAGE_WIDTH, USE_MAN_IMAGE_HEIGHT );
					} else if( target->x > windowWidth - USE_MAN_IMAGE_WIDTH ) {
						mManImageArr[ target->image ]->drawWindowOr( target->x - windowWidth, target->line * USE_OBJ_IMAGE_HEIGHT, viewX, 0, USE_MAN_IMAGE_WIDTH, USE_MAN_IMAGE_HEIGHT );
					}
				}
			} else {
				if( target->isEnter ) {
					mManImageArr[ target->image ]->drawWindowOr( target->x - target->x % USE_MAN_IMAGE_WIDTH, target->line * USE_OBJ_IMAGE_HEIGHT, viewX + ( USE_MAN_IMAGE_WIDTH - target->x % USE_MAN_IMAGE_WIDTH ), USE_MAN_IMAGE_HEIGHT, ( target->x % USE_MAN_IMAGE_WIDTH ), USE_MAN_IMAGE_HEIGHT );
					if( target->x < 0 ) {
						mManImageArr[ target->image ]->drawWindowOr( target->x + windowWidth - target->x % USE_MAN_IMAGE_WIDTH, target->line * USE_OBJ_IMAGE_HEIGHT, viewX + ( USE_MAN_IMAGE_WIDTH - target->x % USE_MAN_IMAGE_WIDTH ), USE_MAN_IMAGE_HEIGHT, ( target->x % USE_MAN_IMAGE_WIDTH ), USE_MAN_IMAGE_HEIGHT );
					} else if( target->x > windowWidth - USE_MAN_IMAGE_WIDTH ) {
						mManImageArr[ target->image ]->drawWindowOr( target->x - windowWidth - target->x % USE_MAN_IMAGE_WIDTH, target->line * USE_OBJ_IMAGE_HEIGHT, viewX + ( USE_MAN_IMAGE_WIDTH - target->x % USE_MAN_IMAGE_WIDTH ), USE_MAN_IMAGE_HEIGHT, ( target->x % USE_MAN_IMAGE_WIDTH ), USE_MAN_IMAGE_HEIGHT );
					}
				} else {
					mManImageArr[ target->image ]->drawWindowOr( target->x, target->line * USE_OBJ_IMAGE_HEIGHT, viewX, USE_MAN_IMAGE_HEIGHT, USE_MAN_IMAGE_WIDTH, USE_MAN_IMAGE_HEIGHT );
					if( target->x < 0 ) {
						mManImageArr[ target->image ]->drawWindowOr( target->x + windowWidth, target->line * USE_OBJ_IMAGE_HEIGHT, viewX, USE_MAN_IMAGE_HEIGHT, USE_MAN_IMAGE_WIDTH, USE_MAN_IMAGE_HEIGHT );
					} else if( target->x > windowWidth - USE_MAN_IMAGE_WIDTH ) {
						mManImageArr[ target->image ]->drawWindowOr( target->x - windowWidth, target->line * USE_OBJ_IMAGE_HEIGHT, viewX, USE_MAN_IMAGE_HEIGHT, USE_MAN_IMAGE_WIDTH, USE_MAN_IMAGE_HEIGHT );
					}
				}
			}
			break;
		case IMAGE_MAN_LADDER:
			mManImageArr[ target->image ]->drawWindowOr( target->x, target->line * USE_OBJ_IMAGE_HEIGHT, viewX, 0, USE_MAN_IMAGE_WIDTH, USE_MAN_IMAGE_LADDER_HEIGHT );
			if( target->line == 0 ) {
				mManImageArr[ target->image ]->drawWindowOr( target->x, ( OBJ_Y_NUM - 1 ) * USE_OBJ_IMAGE_HEIGHT, viewX, USE_MAN_IMAGE_HEIGHT, USE_MAN_IMAGE_WIDTH, USE_MAN_IMAGE_HEIGHT );
			} else if( target->line == ( OBJ_Y_NUM - 1 ) ) {
				mManImageArr[ target->image ]->drawWindowOr( target->x, 0, viewX, USE_MAN_IMAGE_HEIGHT, USE_MAN_IMAGE_WIDTH, USE_MAN_IMAGE_HEIGHT );
			}
			break;
	}
}

void Book7::moveMan( ManState* target )
{
	switch( target->image ) {
		case IMAGE_MAN_STAY:
			moveManStay( target );
			break;
		case IMAGE_MAN_WALK:
			moveManWalk( target );
			break;
		case IMAGE_MAN_LADDER:
			moveManLadder( target );
			break;
	}
}

void Book7::moveManStay( ManState* target )
{
	++target->count;
	if( target->count >= static_cast< int >( mManImageArr[ target->image ]->mWidth / USE_MAN_IMAGE_WIDTH * ANIME_SPEED ) ) {
		target->count = 0;
	}

	++target->state;
	if( target->state > STAY_COUNT ) {
		target->count = 0;
		target->state = 0;
		target->image = IMAGE_MAN_WALK;
		if( target->target != 0 ) {
			target->isLeft = !target->isLeft;
			--target->target->useNum;
			target->target = 0;
		}
	}
}

void Book7::moveManWalk( ManState* target )
{
	int windowWidth = Main::SceneManager::windowWidth;

	if( target->x % USE_OBJ_IMAGE_WIDTH == 0 ) {
		int targetX = target->x / OBJ_X_NUM - 1;
		if( targetX >= OBJ_X_NUM ) targetX = 0;
		if( !target->isLeft ) {
			ObjState* targetObj = &mObjState[ target->line ][ targetX ];
			if( !targetObj->isHold ) {
				if( targetObj->image == IMAGE_OBJ_WALL ) {
					// ‰E‚Ì•Ç
					target->count = 0;
					target->image = IMAGE_MAN_STAY;
					target->target = targetObj;
					++target->target->useNum;
					return;
				} else if( target->target == 0 && targetObj->image == IMAGE_OBJ_ENTRANCE ) {
					// ‰E‚Ì“ü‚èŒû
					if( targetObj == mEntranceState[ 0 ].target && !mEntranceState[ 1 ].target->isHold ) {
						++mEntranceState[ 1 ].target->useNum;
						target->target = targetObj;
						++target->target->useNum;
					} else if( targetObj == mEntranceState[ 1 ].target && !mEntranceState[ 0 ].target->isHold  ) {
						++mEntranceState[ 0 ].target->useNum;
						target->target = targetObj;
						++target->target->useNum;
					}
				}
			}
		} else {
			targetX = ( targetX + 2 ) % OBJ_X_NUM;
			ObjState* targetObj = &mObjState[ target->line ][ targetX ];
			if( !targetObj->isHold ) {
				if( targetObj->image == IMAGE_OBJ_WALL ) {
					// ¶‚Ì•Ç
					target->count = 0;
					target->image = IMAGE_MAN_STAY;
					target->target = targetObj;
					++target->target->useNum;
					return;
				} else if( target->target == 0 && targetObj->image == IMAGE_OBJ_ENTRANCE ) {
					// ¶‚Ì“ü‚èŒû
					if( targetObj == mEntranceState[ 0 ].target && !mEntranceState[ 1 ].target->isHold ) {
						++mEntranceState[ 1 ].target->useNum;
						target->target = targetObj;
						++target->target->useNum;
					} else if( targetObj == mEntranceState[ 1 ].target && !mEntranceState[ 0 ].target->isHold  ) {
						++mEntranceState[ 0 ].target->useNum;
						target->target = targetObj;
						++target->target->useNum;
					}
				}
			}
		}
	}

	if( target->isLeft ) {
		target->x += 2;
		if( target->x >= windowWidth ) {
			target->x = target->x - windowWidth;
		}
	} else {
		target->x -= 2;
		if( target->x <= -USE_MAN_IMAGE_WIDTH ) {
			target->x = target->x + windowWidth;
		}
	}

	++target->count;
	if( target->count >= static_cast< int >( mManImageArr[ target->image ]->mWidth / USE_MAN_IMAGE_WIDTH * ANIME_SPEED ) ) {
		target->count = 0;
	}


	if( ( target->x - USE_OBJ_IMAGE_WIDTH ) % USE_OBJ_IMAGE_WIDTH == 0 ) {
		// ã‚Ö‚Ì‚Í‚µ‚²
		int targetLine = target->line;
		ObjState* targetObj = &mObjState[ targetLine ][ target->x / OBJ_X_NUM ];
		if( !targetObj->isHold && targetObj->image == IMAGE_OBJ_LADDER ) {
			target->count = 0;
			target->image = IMAGE_MAN_LADDER;
			target->state = 0;
			--target->line;
			if( target->line < 0 ) {
				target->line = OBJ_Y_NUM - 1;
			}
			target->target = targetObj;
			++target->target->useNum;
			return;
		} else {
			// ‰º‚Ö‚Ì‚Í‚µ‚²
			++targetLine;
			if( targetLine >= OBJ_Y_NUM ) {
				targetLine = 0;
			}
			targetObj = &mObjState[ targetLine ][ target->x / OBJ_X_NUM ];
			if( !targetObj->isHold && targetObj->image == IMAGE_OBJ_LADDER ) {
				target->count = static_cast< int >( mManImageArr[ IMAGE_OBJ_LADDER ]->mWidth / USE_MAN_IMAGE_WIDTH * ANIME_SPEED ) - 1;
				target->image = IMAGE_MAN_LADDER;
				target->state = 1;
				target->target = targetObj;
				++target->target->useNum;
				return;
			}
		}
	}

	if( target->target != 0 && target->image == IMAGE_OBJ_ENTRANCE ) {
		int targetX = target->x / OBJ_X_NUM;
		int entranceX = target->target->x / OBJ_X_NUM;
		if( target->state == 0 ) {
			if( entranceX == targetX ) {
				target->isEnter = TRUE;
			}
			entranceX = ( entranceX + 1 ) % OBJ_X_NUM;
			if( entranceX == targetX ) {
				if( target->target == mEntranceState[ 0 ].target ) {
					EntranceState* entTarget = &mEntranceState[ 1 ];
					target->x = ( entTarget->indexX - 1 ) * USE_OBJ_IMAGE_WIDTH;
					target->line = entTarget->indexY;
					target->state = 1;
					target->target = entTarget->target;
				} else if( target->target == mEntranceState[ 1 ].target ) {
					EntranceState* entTarget = &mEntranceState[ 0 ];
					target->x = ( entTarget->indexX - 1 ) * USE_OBJ_IMAGE_WIDTH;
					target->line = entTarget->indexY;
					target->state = 1;
					target->target = entTarget->target;
				}
			}
		} else {
			if( entranceX == targetX ) {
				target->isEnter = FALSE;
				--target->target->useNum;
				if( target->target == mEntranceState[ 0 ].target ) {
					--mEntranceState[ 1 ].target->useNum;
				} else if( target->target == mEntranceState[ 1 ].target ) {
					--mEntranceState[ 0 ].target->useNum;
				}

				target->target = 0;
				target->state = 0;
			}
		}
	}
}

void Book7::moveManLadder( ManState* target )
{
	if( target->state == 0 ) {
		++target->count;
		if( target->count >= static_cast< int >( mManImageArr[ target->image ]->mWidth / USE_MAN_IMAGE_WIDTH * ANIME_SPEED ) ) {
			target->count = 0;
			target->image = IMAGE_MAN_STAY;
			--target->target->useNum;
			target->target = 0;
		}
	} else {
		--target->count;
		if( target->count < 0 ) {
			++target->line;
			if( target->line >= OBJ_Y_NUM ) {
				target->line = 0;
			}
			target->count = 0;
			target->image = IMAGE_MAN_STAY;
			--target->target->useNum;
			target->target = 0;
		}
	}
}



BOOL Book7::checkEntrance( ManState* target )
{
	return FALSE;
}

BOOL Book7::checkLadder( ManState* target )
{
	return FALSE;
}

BOOL Book7::checkWall( ManState* target )
{
	return FALSE;
}

