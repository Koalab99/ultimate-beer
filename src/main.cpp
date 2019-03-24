#include <iostream>
#include <Game.h>
#include <unistd.h>
#include "Map.h"
using namespace std;

int main() {
	Game g;
	if(g.init() == 0) {
		while(g.loop()) {
			usleep(50);
			std::system("clear");
		}
	}
	else {
		std::cerr << "Game couldn't start" << std::endl;
	}
	Map carte("text.txt");
    carte.open("text.txt");
    cout << "main nb:"<<carte.getNbBloc() << endl;
    cout << "main X:" <<carte.getBlocs()[1].GetX();
    cout << "main GetType:" <<carte.getBlocs()[1].GetType();
	return 0;
}
