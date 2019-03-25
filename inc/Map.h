#ifndef MAP_H
#define MAP_H

#include <Bloc.h>
#include <Position.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Map {
private:
	std::vector<Bloc> m_blocs;
	float m_h;
	float m_w;
    	int m_nbBlocks;
	
public:
	Map(const std::string &filename);
	~Map();
	Bloc *collide(float x, float y);
	bool blocExists(Bloc *c);
	std::vector<Bloc> *getBlocsInRange(int &number, float x, float w);
	
	int getNbBloc();
	std::vector<Bloc> getBlocs();
	void open(string path);
	
	float getH();
	float getW();
	bool fall(float x, float y, float w);
};

#endif
