#ifndef MAP_H
#define MAP_H

#include <Bloc.h>
#include <Position.h>
#include <Enemy.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
class Enemy;
class Map {
private:
	std::vector<Bloc> m_blocs;
	float m_h;
	float m_w;
    	int m_nbBlocks;
	
public:
	Map(const std::string &filename, std::vector<Enemy> *enemies);
	~Map();
	Bloc *collide(float x, float y);
	bool blocExists(Bloc *c);
	std::vector<Bloc> *getBlocsInRange(int &number, float x, float w);
	
	int getNbBloc();
	std::vector<Bloc> getBlocs();
	void open(const string &path, std::vector<Enemy> *enemies);
	
	float getH();
	float getW();
	bool fall(float x, float y, float w);
};

#endif
