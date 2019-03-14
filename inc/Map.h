#ifndef MAP_H
#define MAP_H

#include <Bloc.h>
#include <Position.h>

class Map {
private:
	std::vector<Bloc> blocs;
	Position pointCollide(float x, float y);
public:
	Position collide(float x, float y, float w, float h);
};

#endif
