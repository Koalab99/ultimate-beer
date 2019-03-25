#include <iostream>
#include <TextPlay.h>
#include <PlayState.h>
#include <Map.h>
#include <Rectangle.h>
#include <Player.h>
#include <Enemy.h>
#include <Bloc.h>
#include <signal.h>
#include <curses.h>

TextPlay::TextPlay(Map *map, Player *player, std::vector<Enemy> *enemies) 
	: PlayState(map, player) {
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	nodelay(stdscr, TRUE);
	m_enemies = enemies;
}

TextPlay::~TextPlay() {
	// Follow PlayState Destructor
	endwin();
	curs_set(1);
}

void TextPlay::render() {
	clear();
	if(((int)m_player->getX() < COLS/2)) {
		getMapArray(0, COLS-1);		
		for(int j = (int)m_player->getY(); j <= (int)(m_player->getY() + m_player->getH()); j++) {
			for(int i = m_player->getX(); i < m_player->getX() + m_player->getW(); i++) {
				mvprintw(m_map->getH() - j, i, "8");
			}
		}
	}
	else if(m_player->getX() >= COLS/2 && m_player->getX() <= m_map->getW() - COLS/2) {
		getMapArray((int)(m_player->getX() - COLS/2), (int)(m_player->getX() + COLS/2));
		for(int j = (int)m_player->getY(); j <= (int)(m_player->getY() + m_player->getH()); j++) {
			for(int i = COLS/2; i < COLS/2 + m_player->getW(); i++) {
				mvprintw(m_map->getH() - j, i, "8");
			}
		}
	}
	else {
		getMapArray(m_map->getW() - COLS, m_map->getW());
		for(int j = (int)m_player->getY(); j <= (int)(m_player->getY() + m_player->getH()); j++) {
			for(int i = (int)m_player->getX() % (int)(m_map->getW() - COLS); i < ((int)m_player->getX() % (int)(m_map->getW() - COLS)) + m_player->getW(); i++) {
				mvprintw(m_map->getH() - j, i, "8");
			}
		}
	}
	mvprintw(m_map->getH() + 2, 0, "x Player = %d", (int)m_player->getX());
	mvprintw(m_map->getH() + 3, 0, "w Map    = %d", (int)m_map->getW());
	mvprintw(m_map->getH() + 4, 0, "COLS     = %d", COLS);
	refresh();
}

void TextPlay::getMapArray(int min, int max) {
	int nb = 0;

	std::vector<Bloc> *visibleBlocs = m_map->getBlocsInRange(nb, (float)min, (float)max);

	for(std::vector<Bloc>::iterator i = visibleBlocs->begin(); i != visibleBlocs->end(); ++i) {
		for(int x = ((int)i->GetX() < min) ? 0 : i->GetX() - min ; 
				x < COLS && x < (int)i->GetX() + (int)i->GetWidth() - min; 	x++) {
			for(int y = (int)i->GetY() + (int)i->GetHeight(); y > (int)i->GetY(); y--) {
				mvprintw(m_map->getH() - y, x, "#");
			}
		}
	}
}

int TextPlay::update() {
	m_player->update();
	std::vector<Enemy>::iterator i;
	for(i = m_enemies->begin(); i != m_enemies->end(); ++i) {
		if(i->isAlive()) {
			i->update();
		}
	}
	return m_quit;	
}

void TextPlay::input() {
	int c;
	if((c = getch()) != ERR) {
		switch(c) {
			case KEY_UP:
				m_player->jump();
				break;
			case KEY_RIGHT:
				m_player->setDirection(1);
				break;
			case KEY_LEFT:
				m_player->setDirection(-1);
				break;
			case (int)'q':
				m_quit = true;
				break;
			default:
				break;
		}
	}
	else {
		m_player->setDirection(0);
	}
}

void TextPlay::loop() {

}
