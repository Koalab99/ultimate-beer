#include <Map.h>
#include <Bloc.h>
#include <Position.h>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>

Map::Map(const std::string &filename) {
	open(filename);
}

Map::~Map(){
}

Bloc *Map::collide(float x, float y) {
	std::vector<Bloc>::iterator b = std::find_if(m_blocs.begin(), m_blocs.end(), [&x, &y](Bloc i) { 
			return (
				x > i.GetX() && 
				y > i.GetY() && 
				x < i.GetWidth() + i.GetX() &&
				y < i.GetHeight() + i.GetY()
			);
		}
	);
	return &b[0];
}

std::vector<Bloc> *Map::getBlocsInRange(float x, float w) {
	std::vector<Bloc> *ret = new std::vector<Bloc>();
	std::copy_if (m_blocs.begin(), m_blocs.end(), std::back_inserter(*ret), 
			[&x, &w](Bloc i) { return ( 
				(i.GetX() + i.GetWidth() > x &&
				 i.GetX() < x + w) ||
				(i.GetX() < x &&
				 i.GetX() + i.GetWidth() > x + w)
			);
		} 
	);
	return ret;
}

bool Map::blocExists(Bloc *c) {
	return *c != m_blocs.end()[0];
}

std::vector<Bloc> *Map::getBlocs(){
	return &m_blocs;
}

std::vector<Enemy> Map::getEnemies() {
	return m_enemies;
}

std::vector<Item> Map::getItems() {
	return m_items;
}

float Map::getH() {
	return m_h;
}

float Map::getW() {
	return m_w;
}

bool Map::fall(float x, float y, float w) {
	return (!blocExists(collide(x, y-0.01)) && !blocExists(collide(x+w, y-0.01)));
}

void Map::open(const std::string &path){
	int nbBlocks;
	ifstream fileStream(path.c_str(), ios::in);
	if(fileStream){
		// Get the title
		getline(fileStream, m_title);
		// Get the path of the miniature of the level
		getline(fileStream, m_minipath);
		// This one get the background image path
		getline(fileStream, m_path);
		fileStream>> m_w;
		fileStream>> m_h;
		fileStream>> m_spawnX;
		fileStream>> m_spawnY;
		fileStream>> nbBlocks;
		float h,w,x,y;
		int t;

		for(int i=0; i< nbBlocks;i++){
			fileStream>> x >> y >> w >> h >> t;
			if(t == 1) {
				Bloc b(w,h,x,y);
				m_blocs.push_back(b);
			}
			else if(t == 2) {
				Enemy n(x, y);
				m_enemies.push_back(n);
			}
			else if(t == 3) {
				Item i(x, y, 1);
				m_items.push_back(i);
			}
			else if(t == 4) {
				Item i(x, y, 2);
				m_items.push_back(i);
			}	
		}

		fileStream.close();
	}
	else{
		cout << "Erreur : Impossible d'ouvrir le fichier." << endl;
	}
}

float Map::getSpawnX() const {
	return m_spawnX;
}

float Map::getSpawnY() const {
	return m_spawnY;
}

std::string Map::getPath() {
	return m_path;
}


std::string Map::getMiniPath() {
	return m_minipath;
}

std::string Map::getTitle() {
	return m_title;
}
