#include <Map.h>
#include <Bloc.h>
#include <Position.h>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <algorithm>

// Map constructor
Map::Map(const std::string &filename) {
	// Such an empty constructor...
	open(filename);
	updateEnemies();
}

// Map destructor
Map::~Map(){
}

// Collisions
Bloc *Map::collide(std::vector<Bloc> *v, const float x, const float y) {
	// Find if there is a bloc colliding the point (x, y)
	int count = 0;
	for(auto i = v->cbegin(); i != v->cend(); i++, count++) {
		if( 	x >= i->GetX() && 
			x <= i->GetWidth() + i->GetX() &&
			y >= i->GetY() && 
			y <= i->GetHeight() + i->GetY()) { 
			return &((v->data())[count]);
		}
	}	
	return nullptr;
}

Enemy *Map::collide(std::vector<Enemy> *v, const float x, const float y) {
	// Find if there is a bloc colliding the point (x, y)
	int count = 0;
	for(auto i = v->cbegin(); i != v->cend(); i++, count++) {
		if( 	i->isAlive() && 
			x >= i->GetX() && 
			x <= i->GetWidth() + i->GetX() &&
			y >= i->GetY() && 
			y <= i->GetHeight() + i->GetY()) {
			return &((v->data())[count]);	
		}
	}	
	return nullptr;
}

const Item *Map::collide(std::vector<Item> *v, const float x, const float y) {
	// Find if there is a bloc colliding the point (x, y)
	for(auto i = v->cbegin(); i != v->cend(); i++) {
		if( 	x >= i->GetX() && 
			x <= i->GetWidth() + i->GetX() &&
			y >= i->GetY() && 
			y <= i->GetHeight() + i->GetY()) {
			return &*i;	
		}
	}	
	return nullptr;
}

std::vector<Bloc> *Map::getBlocsInRange(float x, float w) {
	// Make a copy of blocs that fit the condition below
	std::vector<Bloc> *ret = new std::vector<Bloc>();
	for(auto i = m_blocs.begin(); i != m_blocs.end(); i++) {
		if( 	i->GetX() < w + x &&
			(i->GetX() + i->GetWidth() > x || 
			 i->GetX() > x)) {
			ret->push_back(*i);
		}
	} 
	return ret;
}

std::vector<Enemy> *Map::getEnemiesInRange(float x, float w) {
	// Make a copy of enemies that fit the condition below
	std::vector<Enemy> *ret = new std::vector<Enemy>();
	for(auto i = m_enemies.begin(); i != m_enemies.end(); i++) {
		if( 	i->GetX() < w + x &&
			(i->GetX() + i->GetWidth() > x || 
			 i->GetX() > x)) {
			ret->push_back(*i);
		}
	} 
	return ret;
}

std::vector<Item> *Map::getItemsInRange(float x, float w) {
	// Make a copy of items that fit the condition below
	std::vector<Item> *ret = new std::vector<Item>();
	for(auto i = m_items.begin(); i != m_items.end(); i++) {
		if( 	i->GetX() < w + x &&
			(i->GetX() + i->GetWidth() > x || 
			 i->GetX() > x)) {
			ret->push_back(*i);
		}
	} 
	return ret;
}


bool Map::blocExists(Bloc *c) {
	// That is dirty but it works, need to learn how to use C++ properly, sorry for purists, I'm a C programmer, not a wizard
	return *c != m_blocs.end()[0];
}

// A lot of getterz
std::vector<Bloc> *Map::getBlocs(){
	return &m_blocs;
}

std::vector<Enemy> *Map::getEnemies() {
	return &m_enemies;
}

std::vector<Item> *Map::getItems() {
	return &m_items;
}

float Map::getH() {
	return m_h;
}

float Map::getW() {
	return m_w;
}

// There is really a lot of getters
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

// This could be in the constructor but it seems happy here
void Map::open(const std::string &path){
	int nbElements;
	ifstream fileStream(path.c_str(), ios::in);
	if(fileStream){
		// Get the title
		getline(fileStream, m_title);
		// Get the path of the miniature of the level
		getline(fileStream, m_minipath);
		// This one get the background image path
		getline(fileStream, m_path);
		// Map width
		fileStream>> m_w;
		// Map height
		fileStream>> m_h;
		// Spawn X position
		fileStream>> m_spawnX;
		// Spawn Y position
		fileStream>> m_spawnY;
		// Number of elements
		fileStream>> nbElements;
		// Will store elements values
		float h,w,x,y;
		int t;
		// Loop to get all elements
		for(int i=0; i< nbElements;i++){
			// Read them from the file
			fileStream>> x >> y >> w >> h >> t;
			if(t == 1) {
				// This element is a bloc
				Bloc b(w,h,x,y);
				m_blocs.push_back(b);
			}
			else if(t == 2) {
				// This element is an enemy
				Enemy n(x, y);
				m_enemies.push_back(n);
			}
			else if(t == 3) {
				// This element is the first kind of item
				Item i(x, y, 1);
				m_items.push_back(i);
			}
			else if(t == 4) {
				// This element is the second kind of item
				Item i(x, y, 2);
				m_items.push_back(i);
			}	
		}
		// Never forget to close the file
		fileStream.close();
	}
	else{
		// We could not open the file, so there is no map, no game, no beer, no thing!
		std::cerr << "Error : Unable to open the file." << std::endl;
	}
}

void Map::updateEnemies() {
	for(auto i = m_enemies.begin(); i != m_enemies.end(); i++) {
		int count;
		for(count = 0; count < i->GetY(); count++) {
			Bloc *tmp = collide(&m_blocs, i->GetX() + i->GetWidth()/2, i->GetY()-count); 
			if(tmp != nullptr) {
				auto f = std::find(m_blocs.begin(), m_blocs.end(), *tmp);
				if(f != m_blocs.end()) {
					i->setBloc(&*f);
					i->setY( i->getBloc()->GetY() + i->getBloc()->GetHeight());
				}
				break;
			}
		}
		if(count >= i->GetY()) {
			i->setAlive(false);
		}
	}
}
