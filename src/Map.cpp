#include <Map.h>
#include <Bloc.h>
#include <Position.h>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>

Map::Map(const std::string &filename) {
	m_h = 30;
	m_w = 200;
	// Do something.
	open(filename);
}

Map::~Map(){
}

Bloc *Map::collide(float x, float y) {
	std::vector<Bloc>::iterator b = std::find_if(m_blocs.begin(), m_blocs.end(), [&x, &y](Bloc i) { return (
			x > i.GetX() && 
			y > i.GetY() && 
			x < i.GetWidth() + i.GetX() &&
			y < i.GetHeight() + i.GetY()
		);});
	return &b[0];	
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

bool Map::blocExists(Bloc *c) {
	return *c != m_blocs.end()[0];
}

int Map::getNbBloc(){
    return m_nbBlocks;
}

vector<Bloc> Map::getBlocs(){
    return m_blocs;
}


float Map::getH() {
	return m_h;
}

float Map::getW() {
	return m_w;
}

bool Map::fall(float x, float y, float w) {
	return (!blocExists(collide(x, y-0.01)) && !blocExists(collide(x+w, y-0.01)));
}

void Map::open(std::string path){

     ifstream monFlux(path.c_str(), ios::in);
     if(monFlux){
            monFlux>> m_w;
            monFlux>> m_h;
            monFlux>> m_nbBlocks;
            cout<< "nb block: "<<m_nbBlocks << endl;
            float h,w,x,y;
            int t;

            for(int i=0; i<m_nbBlocks;i++){
                monFlux>> w >> h >> x >> y >> t;
                Bloc monblocs(w,h,x,y);
		std::cout << "w:"<<monblocs.GetWidth() <<" h:"<<monblocs.GetHeight() << " x:"<<monblocs.GetX()<< " y:"<< monblocs.GetY() << std::endl;
		if(t == 1) {
	                m_blocs.push_back(monblocs);
		} else if(t == 2) {
			// Do nothing for now
		}
            }

            monFlux.close();
     }
     else{
         cout << "Erreur : Impossible d'ouvrir le fichier." << endl;
     }
}
