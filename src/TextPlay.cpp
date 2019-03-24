#include <TextPlay.h>
#include <PlayState.h>
#include <Rectangle.h>
#include <Player.h>

TextPlay::TextPlay(Map *map, Player *player) 
	: PlayState(map, player) {
	for(int i = 0; i < DIMW; i++) {
		m_mapArray[i] = new char[(int)map->getH()];
	}
}

TextPlay::~TextPlay() {
	// Follow PlayState Destructor
}

void TextPlay::render() {
	if((int)m_player->getX() < DIMW/2) {
		getMapArray(0, DIMW);
		
	}
	else {
		
	}
}

void TextPlay::getMapArray(int min, int max) {
	
}

int TextPlay::update() {
	return 0;	
}

void TextPlay::input() {
	
}

void TextPlay::loop() {

}
