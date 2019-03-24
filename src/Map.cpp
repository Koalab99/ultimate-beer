#include <Map.h>
#include <Bloc.h>
#include <Position.h>
#include <vector>
#include <string>
#include <algorithm>

Map::Map(const std::string &filename) {
	// Do something.
}

Bloc Map::collide(float x, float y) {
	std::vector<Bloc>::iterator b = std::find_if(m_blocs.begin(), m_blocs.end(), [&x, &y](Bloc i) { return (
			x > i.GetX() && 
			y > i.GetY() && 
			x < i.GetWidth() + i.GetX() &&
			y < i.GetHeight() + i.GetY()
		);});
	return b[0];	
}

std::vector<Bloc> *Map::getBlocsInRange(int &number, float x, float w) {
	std::vector<Bloc> *ret = new std::vector<Bloc>();
	std::copy_if (m_blocs.begin(), m_blocs.end(), std::back_inserter(*ret), 
			[&x, &w](Bloc i) { return ( 
				(i.GetX() + i.GetWidth() > x &&
				i.GetX() < x + w) ||
				(i.GetX() < x &&
				i.GetX() + i.GetWidth() > x + w)
			);} );
	return ret;
}

bool Map::blocExists(Bloc c) {
	return c != m_blocs.end()[0];
}

float Map::getH() {
	return m_h;
}

float Map::getW() {
	return m_w;
}
