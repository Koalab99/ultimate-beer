#include <Map.h>
#include <Bloc.h>
#include <Position.h>
#include <vector>

Position Map::collide(float x, float y, float w, float h) {
	for(std::vector<Bloc>::iterator i = blocs.begin(); i < blocs.end(); ++i) {
	
	}
	Position p;
	return p;

}

Position Map::pointCollide(Position &p) {
	return p;
}
