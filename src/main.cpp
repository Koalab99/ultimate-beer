#include <iostream>
#include <Game.h>
#include <unistd.h>
#include "Map.h"
using namespace std;

int main() {
	Game g;
	if(g.init() == 0) {
		while(g.loop()) {
			usleep(5000);
		}
	}
	else {
		std::cerr << "Game couldn't start" << std::endl;
	}
	return 0;
}
