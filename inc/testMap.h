#ifndef TEST_MAP_H
#define TEST_MAP_H

#include <string>
#include <fstream>

/******
 * In order to make things easier, we must fix some rules 
 * that will describe the way maps work.
 * Not an easy task, but let's try !
 *
 * Here is a list of rules maps need to follow :
 * 	- First line is a string longer than 5 characters.
 * 	- The second line is the path to the background image (need to exist)
 * 	- The third is the width of the map (in blocs)
 * 	- The fourth is supposed fixed but we want it to be a little bit more complicated, 
 * 			so... it is the height of the map (in blocs)
 * 	- The fifth is the number of bloc the level contains (called nbBlocs
 * 		- the 'nbBlocs' following lines are describing blocs (one per line)
 * 				Each lines contain:
 * 			- X position in the plan (must be between 0 and map width)
 * 			- Y position in the plan (must be between 0 and map height)
 * 			- Width of the bloc in the plan (don't get out the plan)
 * 			- Height of the bloc in the plan (dont get out the plan)
 * 	- The next line is the number of Enemies, each lines contains the same as blocs
 * 	- The next line is the number of Items, each lines contains the same as blocs
 * 			but with one extra feature:
 * 				A number which describe the type of item!
 */
/**
	@brief Map have a no problem ? 
	@return bool true if map have a no problem
	*/
bool mapIsOk(std::string &path) {
	std::ifstream file;
	file.open(path);
	if(!file.is_open()) {
		return false;
	}
	std::string name;
	getline(file, name);
	if(name.size() < 5) {
		return false;
	}
	return true;
}

#endif
