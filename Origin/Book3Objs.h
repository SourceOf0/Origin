
BOOL Book3::motion00( AnimeState* target, BOOL wasHit, BOOL isClick, BOOL isMouseDown, int mouseX, int mouseY )
{
	BOOL ret = FALSE;

	if( mouseX > target->x + 110 && mouseX < target->x + 150 && mouseY > target->y + 105 && mouseY < target->y + 150 ) {
		ret = TRUE;
		if( !wasHit ) {
			if( isClick ) {
				if( target->state < 2 ) target->state += 2;
				Main::HandManager::inst()->setState( Main::HandManager::HAND_PUSH_AFTER );
				return ret;
			} else if( target->state < 2 && isMouseDown ) {
				nextAnimeState( target, IMAGE_02 );
				return ret;
			} else {
				Main::HandManager::inst()->setState( Main::HandManager::HAND_PUSH_BEFORE );
			}
		}
	}

	switch( target->state ) {
		case 0:
			++target->count;
			if( ret ) ++target->count;
			if( target->count >= static_cast< int >( mImageArr[ target->image ]->mWidth / USE_IMAGE_SIZE * ANIME_SPEED ) ) {
				target->state = 1;
				target->count = static_cast< int >( mImageArr[ target->image ]->mWidth / USE_IMAGE_SIZE * ANIME_SPEED ) - 1;
			}
			break;
			
		case 1:
			--target->count;
			if( ret ) --target->count;
			if( target->count <= static_cast< int >( ( mImageArr[ target->image ]->mWidth / USE_IMAGE_SIZE - 3 ) * ANIME_SPEED ) ) {
				target->state = 0;
				target->count = static_cast< int >( ( mImageArr[ target->image ]->mWidth / USE_IMAGE_SIZE - 3 ) * ANIME_SPEED );
			}
			break;

		case 2:
			++target->count;
			if( target->count >= static_cast< int >( mImageArr[ target->image ]->mWidth / USE_IMAGE_SIZE * ANIME_SPEED ) ) {
				nextAnimeState( target, IMAGE_01 );
			}
			break;

		case 3:
			--target->count;
			if( target->count <= static_cast< int >( ( mImageArr[ target->image ]->mWidth / USE_IMAGE_SIZE - 3 ) * ANIME_SPEED ) ) {
				target->state = 2;
				target->count = static_cast< int >( ( mImageArr[ target->image ]->mWidth / USE_IMAGE_SIZE - 3 ) * ANIME_SPEED );
			}
			break;
	}

	return ret;
}

BOOL Book3::motion01( AnimeState* target, int mouseX, int mouseY )
{
	if( ( target->count + 1 ) < static_cast< int >( mImageArr[ target->image ]->mWidth / USE_IMAGE_SIZE * ANIME_SPEED ) ) {
		++target->count;
	} else {
		int x = target->x;
		int y = target->y;
		newAnimeState( x - 68, y - 95 );
		newAnimeState( x + 50, y - 100 );
		newAnimeState( x - 100, y + 10 );
		newAnimeState( x + 100, y - 12 );
		return setAnimeState( target, x - 10, y + 95 );
	}
	return TRUE;
}

void Book3::motion02( AnimeState* target, int mouseX, int mouseY )
{
	if( ( target->count + 1 ) < static_cast< int >( mImageArr[ target->image ]->mWidth / USE_IMAGE_SIZE * ANIME_SPEED ) ) {
		++target->count;
	} else {
		nextAnimeState( target, IMAGE_10 );
	}
}

BOOL Book3::motion10( AnimeState* target, BOOL wasHit, BOOL isClick, BOOL isMouseDown, int mouseX, int mouseY )
{
	BOOL ret = FALSE;

	if( mouseX > target->x + 110 && mouseX < target->x + 150 && mouseY > target->y + 40 && mouseY < target->y + 150 ) {
		ret = TRUE;
		if( !wasHit ) {
			if( isClick ) {
				if( target->state < 2 ) target->state = 4;
				Main::HandManager::inst()->setState( Main::HandManager::HAND_PUSH_AFTER );
			} else if( isMouseDown ) {
				if( target->state < 2 ) target->state += 2;
			} else {
				Main::HandManager::inst()->setState( Main::HandManager::HAND_PUSH_BEFORE );
			}
		}
	}

	switch( target->state ) {
		case 0:
			++target->count;
			if( ret ) ++target->count;
			if( target->count >= static_cast< int >( mImageArr[ target->image ]->mWidth / USE_IMAGE_SIZE * ANIME_SPEED ) ) {
				target->state = 1;
				target->count = static_cast< int >( mImageArr[ target->image ]->mWidth / USE_IMAGE_SIZE * ANIME_SPEED ) - 1;
			}
			break;
			
		case 1:
			--target->count;
			if( ret ) --target->count;
			if( target->count <= 0 ) {
				target->state = 0;
				target->count = 0;
			}
			break;

		case 2:
			target->count += 2;
			if( target->count >= static_cast< int >( mImageArr[ target->image ]->mWidth / USE_IMAGE_SIZE * ANIME_SPEED ) ) {
				nextAnimeState( target, IMAGE_12 );
			}
			break;

		case 3:
			target->count -= 2;
			if( target->count <= 0 ) {
				target->state = 2;
				target->count = 0;
			}
			break;

		case 4:
			int targetCount = static_cast< int >( ( mImageArr[ target->image ]->mWidth / USE_IMAGE_SIZE / 2 ) * ANIME_SPEED ) ;
			if( target->count < targetCount ) {
				++target->count;
			} else if( target->count > targetCount ) {
				--target->count;
			} else {
				nextAnimeState( target, IMAGE_11 );
			}
			break;
	}

	return ret;
}

BOOL Book3::motion11( AnimeState* target, int mouseX, int mouseY )
{
	if( ( target->count + 1 ) < static_cast< int >( mImageArr[ target->image ]->mWidth / USE_IMAGE_SIZE * ANIME_SPEED ) ) {
		++target->count;
	} else {
		int x = target->x;
		int y = target->y;
		newAnimeState( x - 100, y + 90 );
		newAnimeState( x + 100, y + 90 );
		return setAnimeState( target, x + 0, y + 70 );
	}
	return TRUE;
}

void Book3::motion12( AnimeState* target, int mouseX, int mouseY )
{
	target->count += 2;
	if( ( target->count + 1 ) >= static_cast< int >( mImageArr[ target->image ]->mWidth / USE_IMAGE_SIZE * ANIME_SPEED ) ) {
		nextAnimeState( target, IMAGE_20 );
	}
}

BOOL Book3::motion20( AnimeState* target, BOOL wasHit, BOOL isClick, BOOL isMouseDown, int mouseX, int mouseY )
{
	BOOL ret = FALSE;
	int disX = mouseX - ( target->x + USE_IMAGE_SIZE_HALF );
	int disY = mouseY - ( target->y + USE_IMAGE_SIZE_HALF - 10 );
	int dis = disX * disX + disY * disY;
	int maxDis = 80 * 80;
	int minDis = 50 * 50;
	if( dis > minDis && dis < maxDis ) {
		ret = TRUE;
		if( !wasHit ) {
			if( isClick ) {
				nextAnimeState( target, IMAGE_21 );
				Main::HandManager::inst()->setState( Main::HandManager::HAND_PUSH_AFTER );
				return ret;
			} else if( isMouseDown ) {
				nextAnimeState( target, IMAGE_22 );
				return ret;
			} else {
				Main::HandManager::inst()->setState( Main::HandManager::HAND_PUSH_BEFORE );
			}
		}
	}

	++target->count;
	if( ret ) ++target->count;
	if( target->count >= static_cast< int >( mImageArr[ target->image ]->mWidth / USE_IMAGE_SIZE * ANIME_SPEED ) ) {
		target->count = 0;
	}

	return ret;
}

BOOL Book3::motion21( AnimeState* target, int mouseX, int mouseY )
{
	if( ( target->count + 1 ) < static_cast< int >( mImageArr[ target->image ]->mWidth / USE_IMAGE_SIZE * ANIME_SPEED ) ) {
		++target->count;
	} else {
		int x = target->x;
		int y = target->y;
		int range = static_cast< int >( RAND_MAX * 0.1 );
		newAnimeState( x - 42, y - 110 );
		newAnimeState( x + 92, y - 35 );
		newAnimeState( x - 92, y + 45 );
		return setAnimeState( target, x + 38, y + 78 );
	}
	return TRUE;
}

void Book3::motion22( AnimeState* target, int mouseX, int mouseY )
{
	if( ( target->count + 1 ) < static_cast< int >( mImageArr[ target->image ]->mWidth / USE_IMAGE_SIZE * ANIME_SPEED ) ) {
		++target->count;
	} else {
		nextAnimeState( target, IMAGE_30 );
	}
}

BOOL Book3::motion30( AnimeState* target, BOOL wasHit, BOOL isClick, BOOL isMouseDown, int mouseX, int mouseY )
{
	BOOL ret = FALSE;

	if( mouseX > target->x + 40 && mouseX < target->x + 210 && mouseY > target->y + 160 && mouseY < target->y + 200 ) {
		ret = TRUE;
		if( !wasHit ) {
			if( isClick ) {
				nextAnimeState( target, IMAGE_31 );
				Main::HandManager::inst()->setState( Main::HandManager::HAND_PUSH_AFTER );
				return ret;
			} else if( isMouseDown ) {
				nextAnimeState( target, IMAGE_32 );
				return ret;
			} else {
				Main::HandManager::inst()->setState( Main::HandManager::HAND_PUSH_BEFORE );
			}
		}
	}

	switch( target->state ) {
		case 0:
			++target->count;
			if( ret ) ++target->count;
			if( target->count >= static_cast< int >( mImageArr[ target->image ]->mWidth / USE_IMAGE_SIZE * ANIME_SPEED ) ) {
				target->state = 1;
				target->count = static_cast< int >( ( mImageArr[ target->image ]->mWidth / USE_IMAGE_SIZE - 1 ) * ANIME_SPEED ) - 1;
			}
			break;
			
		case 1:
			--target->count;
			if( ret ) --target->count;
			if( target->count <= ANIME_SPEED ) {
				target->state = 0;
				target->count = 0;
			}
			break;
	}

	return ret;
}

BOOL Book3::motion31( AnimeState* target, int mouseX, int mouseY )
{
	if( ( target->count + 1 ) < static_cast< int >( mImageArr[ target->image ]->mWidth / USE_IMAGE_SIZE * ANIME_SPEED ) ) {
		++target->count;
	} else {
		int x = target->x;
		int y = target->y;
		return setAnimeState( target, x + 65, y + 50 );
	}
	return TRUE;
}

void Book3::motion32( AnimeState* target, int mouseX, int mouseY )
{
	if( ( target->count + 1 ) < static_cast< int >( mImageArr[ target->image ]->mWidth / USE_IMAGE_SIZE * ANIME_SPEED ) ) {
		++target->count;
	} else {
		nextAnimeState( target, IMAGE_40 );
	}
}

BOOL Book3::motion40( AnimeState* target, BOOL wasHit, BOOL isClick, BOOL isMouseDown, int mouseX, int mouseY )
{
	BOOL ret = FALSE;
	int disX = mouseX - ( target->x + 200 );
	int disY = mouseY - ( target->y + 185 );
	int dis = disX * disX + disY * disY;
	int maxDis = 160 * 160;

	if( disX < 10 && disY < 10 && dis < maxDis ) {
		ret = TRUE;
		if( !wasHit ) {
			if( isClick ) {
				nextAnimeState( target, IMAGE_41 );
				Main::HandManager::inst()->setState( Main::HandManager::HAND_PUSH_AFTER );
				return ret;
			} else if( isMouseDown ) {
				nextAnimeState( target, IMAGE_42 );
				return ret;
			} else {
				Main::HandManager::inst()->setState( Main::HandManager::HAND_PUSH_BEFORE );
			}
		}
	}

	switch( target->state ) {
		case 0:
			++target->count;
			if( ret ) ++target->count;
			if( target->count >= static_cast< int >( mImageArr[ target->image ]->mWidth / USE_IMAGE_SIZE * ANIME_SPEED ) ) {
				target->state = 1;
				target->count = static_cast< int >( mImageArr[ target->image ]->mWidth / USE_IMAGE_SIZE * ANIME_SPEED ) - 1;
			}
			break;
			
		case 1:
			--target->count;
			if( ret ) --target->count;
			if( target->count <= 0 ) {
				target->state = 0;
				target->count = 0;
			}
			break;
	}
	
	return ret;
}

BOOL Book3::motion41( AnimeState* target, int mouseX, int mouseY )
{
	if( ( target->count + 1 ) < static_cast< int >( mImageArr[ target->image ]->mWidth / USE_IMAGE_SIZE * ANIME_SPEED ) ) {
		++target->count;
	} else {
		int x = target->x;
		int y = target->y;
		return setAnimeState( target, x + 70, y + 50 );
	}
	return TRUE;
}

BOOL Book3::motion42( AnimeState* target, int mouseX, int mouseY )
{
	if( ( target->count + 1 ) < static_cast< int >( mImageArr[ target->image ]->mWidth / USE_IMAGE_SIZE * ANIME_SPEED ) ) {
		++target->count;
	} else {
		int x = target->x;
		int y = target->y;
		return setAnimeState( target, x + 50, y + 42 );
	}
	return TRUE;
}
