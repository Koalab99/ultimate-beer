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
	float m_spawnX;
	float m_spawnY;
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
	const Bloc *collide(std::vector<Bloc> *v, const float x, const float y);
	const Enemy *collide(std::vector<Enemy> *v, const float x, const float y);
	const Item *collide(std::vector<Item> *v, const float x, const float y);

	bool blocExists(Bloc *c);
	std::vector<Bloc> *getBlocsInRange(float x, float w);
	std::vector<Enemy> *getEnemiesInRange(float x, float w);
	std::vector<Item> *getItemsInRange(float x, float w);
	
	int getNbBloc();

	std::vector<Bloc> *getBlocs();
	std::vector<Enemy> *getEnemies();
	std::vector<Item> *getItems();

	void open(const string &path);
	
	float getH();
	float getW();
	float getSpawnX() const;
	float getSpawnY() const;
	std::string getMiniPath();
	std::string getPath();
	std::string getTitle();

	bool fall(float x, float y, float w);
};

#endif
