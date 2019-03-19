#ifndef MAP_H
#define MAP_H

#include <Bloc.h>
#include <Position.h>
#include <vector>

class Map {
private:
	std::vector<Bloc> blocs;
	Position pointCollide(Position &p);
public:
	Position collide(float x, float y, float w, float h);
};

#endif
