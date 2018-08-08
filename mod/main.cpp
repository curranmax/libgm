
#include "../simple_fso.h"

#include <iostream>
#include <stdio.h>
#include <termios.h>

// From http://stackoverflow.com/questions/7469139/what-is-equivalent-to-getch-getche-in-linux
// -----------------------------------------------
static struct termios old, new0;

// Initialize new terminal i/o settings
void initTermios(int echo) {
	tcgetattr(0, &old);						// grab old terminal i/o settings
	new0 = old;								// make new settings same as old settings
	new0.c_lflag &= ~ICANON;				// disable buffered i/o
	new0.c_lflag &= echo ? ECHO : ~ECHO;	// set echo mode
	tcsetattr(0, TCSANOW, &new0);			// use these new terminal i/o settings now
}

// Restore old terminal i/o settings 
void resetTermios(void)  {
	tcsetattr(0, TCSANOW, &old);
}

// Read 1 character - echo defines echo mode
char getch_(int echo)  {
	char ch;
	initTermios(echo);
	ch = getchar();
	resetTermios();
	return ch;
}

// Read 1 character without echo
int getch() {
	int v = (int)getch_(0);
	return v;
}
// -----------------------------------------------

void printModifyHelp() {
	std::cout << "Arrow Keys or WASD - modify GM position" << std::endl;
	std::cout << "v - print current delta value" << std::endl;
	std::cout << "z - halve current delta value" << std::endl;
	std::cout << "x - double current delta value" << std::endl;
	std::cout << "g - print current GM positions" << std::endl;
	std::cout << "k - save current GM positions" << std::endl;
	std::cout << "l - reload GM positions from file" << std::endl;
	std::cout << "q - quit modify mode" << std::endl;
	std::cout << "h - display help again" << std::endl;
}

void modify(SimpleFSO* fso) {
	int delta = 1;

	printModifyHelp();
	int key = getch();
	std::string error = "";
	while(key != (int)'q') {
		// Arrow keys are triple of the form (27,91,65-68)
		if(key == 27) {
			key = getch();
			if(key == 91) {
				key = getch();
				if(key == 65) {
					// UP
					fso->incrGM1Val(delta);
				} else if(key == 66) {
					// DOWN
					fso->incrGM1Val(-delta);
				} else if(key == 67) {
					// RIGHT
					fso->incrGM2Val(delta);
				} else if(key == 68) {
					// LEFT
					fso->incrGM2Val(-delta);
				} else {
					error = "Invalid Input!";
					break;
				}
			} else {
				error = "Invalid Input!";
				break;
			}
		} else if(key == (int)'w') {
			fso->incrGM1Val(delta);
		} else if(key == (int)'s') {
			fso->incrGM1Val(-delta);
		} else if(key == (int)'d') {
			fso->incrGM2Val(delta);
		} else if(key == (int)'a') {
			fso->incrGM2Val(-delta);
		} else if(key == (int)'v') {
			std::cout << "Current delta value is " << delta << std::endl;
		} else if(key == (int)'z') {
			std::cout << "Delta went from " << delta;
			delta = delta / 2;
			if(delta < 1) {
				delta = 1;
			}
			std::cout << " to " << delta << std::endl;
		} else if(key == (int)'x') {
			std::cout << "Delta went from " << delta;
			delta = delta * 2;
			std::cout << " to " << delta << std::endl;
		} else if(key == (int)'g') {
			// Print current GM positions
			std::cout << "\tGM1 " << fso->getGM1Val() << "  \tGM2 " << fso->getGM2Val() << std::endl;
		} else if(key == (int)'k') {
			fso->save();
		} else if(key == (int)'l') {
			fso->load();
		} else if(key == (int)'h') {
			printModifyHelp();
		}

		key = getch();
	}
	if(error != "") {
		std::cerr << error << std::endl;
		return;
	}
}

int main(int argc, char const *argv[]) {
	if(argc != 2) {
		std::cerr << "Usage is:" << std::endl << "\tmod-gm FSO_FILE" << std::endl;
	}

	std::string filename = argv[1];

	SimpleFSO fso(filename);

	if(!fso.isGM1Connected() || !fso.isGM2Connected()) {
		std::cerr << "Could not connect to at least one GM" << std::endl;
		exit(1);
	}

	modify(&fso);

	fso.save();

	return 0;
}
