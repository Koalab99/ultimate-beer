#ifndef MAP_H
#define MAP_H

#include <Bloc.h>
#include <Position.h>
#include <Enemy.h>
#include <Item.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
class Enemy;
class Map {
private:
	float spawnX;
	float spawnY;
	std::vector<Bloc> m_blocs;
	std::vector<Enemy> m_enemies;
	std::vector<Item> m_items;
	std::string m_title;
	std::string m_minipath;
	std::string m_path;
	float m_h;
	float m_w;
	
public:
	Map(const std::string &filename);
	~Map();
	Bloc *collide(float x, float y);
	bool blocExists(Bloc *c);
	std::vector<Bloc> *getBlocsInRange(float x, float w);
	
	int getNbBloc();

	std::vector<Bloc> getBlocs();
	std::vector<Enemy> getEnemies();
	std::vector<Item> getItems();

	void open(const string &path);
	
	float getH();
	float getW();
	std::string getMiniPath();
	std::string getPath();
	std::string getTitle();

	bool fall(float x, float y, float w);
};

#endif
