#ifndef PLAYING_RETURN_VALUE
#define PLAYING_RETURN_VALUE

/**
*detailed descriptionreturns if the players won, died, paused, quit the game or did nothing at all
*/
typedef enum PlayingReturnValue {
	NONE,
	QUIT,
	PAUSE,
	DEAD
} PlayValue;

#endif
