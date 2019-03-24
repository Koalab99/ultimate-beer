#include <iostream>
#include <Game.h>
#include <unistd.h>

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

	return 0;
}
