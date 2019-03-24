#ifndef MAP_H
#define MAP_H

#include <Bloc.h>
#include <Position.h>
#include <vector>
#include <string>

class Map {
private:
	std::vector<Bloc> m_blocs;
	float m_h;
	float m_w;
public:
	Map(const std::string &filename);
	~Map();
	Bloc collide(float x, float y);
	bool blocExists(Bloc c);
	std::vector<Bloc> *getBlocsInRange(int &number, float x, float w);
	float getH();
	float getW();
};

#endif
