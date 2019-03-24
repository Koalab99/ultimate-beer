#include <iostream>
#include <TextPlay.h>
#include <PlayState.h>
#include <Rectangle.h>
#include <Player.h>
#include <Bloc.h>

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
	clear();
	if((int)m_player->getX() < DIMW/2) {
		getMapArray(0, DIMW);		
	}
	else {
		getMapArray((int)(m_player->getX() - DIMW/2), (int)(m_player->getX() + DIMW/2));
	}
	for(int i = 0; i < DIMW; i++) {
		for(int j = m_map->getH(); j > 0; j--) {
			std::cout << m_mapArray[i][j];
		}
		std::cout << std::endl;
	}
}

void TextPlay::clear() {
	for(int i = 0; i < DIMW; i++) {
		for(int j = m_map->getH(); j>0; j--) {
			m_mapArray[i][j] = ' ';
		}
	}
}

void TextPlay::getMapArray(int min, int max) {
	int nb = 0;

	std::vector<Bloc> *visibleBlocs = m_map->getBlocsInRange(nb, (float)min, (float)max);

	for(std::vector<Bloc>::iterator i = visibleBlocs->begin(); i != visibleBlocs->end(); ++i) {
		for(int x = ((int)i->GetX() < min) ? 0 : i->GetX() - min ; 
				x < DIMW && x < (int)i->GetX() + (int)i->GetWidth(); 	x++) {
			for(int y = (int)i->GetY() + (int)i->GetHeight(); y > (int)i->GetY(); y--) {
				m_mapArray[x][y] = '#';
			}
		}
	}
}

int TextPlay::update() {
	return 0;	
}

void TextPlay::input() {
	
}

void TextPlay::loop() {

}
