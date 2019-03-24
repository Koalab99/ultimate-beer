#ifndef TEXTPLAY_H
#define TEXTPLAY_H

#include <PlayState.h>
#include <Map.h>
#include <Player.h>

#define DIMW 30

class TextPlay : public PlayState {
private:
	char *m_mapArray[DIMW];
public:
	TextPlay(Map *map, Player *player);
	~TextPlay();
	void render();
	void getMapArray(int min, int max);
	void loop();
	int update();
	void input();

};

#endif
