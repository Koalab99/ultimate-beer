#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

using namespace std;

int main(int argc, char **argv) {
	if(argc < 2) {
		cout << "Usage : " << argv[0] << " [FILE1, ...]" << endl;
	}
	else {
		fstream file;
		string someString;
		int nbElem, type;
		float width, height, x, y, w, h;
		// Loop throught each files given as an argument.
		for(int i = 1; i < argc; i++) {
			cout << "Testing file " << argv[i] << "...";
			file.open(argv[i]);
			assert(file.is_open());
			// Get the title
			assert(getline(file, someString));
			assert(someString != "");
			// Get the miniature
			assert(getline(file, someString));
			// Get the background image path
			assert(getline(file, someString));
			// Get the width
			assert(file >> width);
			assert(width > 0 && width < 2000);
			// Get the height
			assert(file >> height);
			assert(height > 0 && height < 50);
			// Get the number of Elements
			assert(file >> nbElem);
			assert(nbElem > 1);
			// Loop through each element
			for(int i = 0; i < nbElem; i++) {
				assert(file >> x);
				assert(file >> y);
				assert(file >> w);
				assert(file >> h);
				assert(file >> type);
				assert(x >= 0);
				assert(y >= 0);
				assert(w >= 0);
				assert(h >= 0);
				assert(w + x <= width);
				assert(h + y <= height);
			}
			file.close();
			cout << " OK!" << endl;
		}

	}
	return 0;
}
