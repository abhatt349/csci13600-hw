
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <ctime>
#include "bot.h"

using namespace std;

const int MAX_ROWS = 40;
const int MAX_COLS = 40;
const int MAX_NUM = 10;

int ROWS;  // global variables
int COLS;
int NUM;


/* onStart:
An Initialization procedure called at the start of the game.
You can use it to initialize certain global variables, or do
something else before the actual simulation starts.
Parameters:
    rows: number of rows
    cols: number of columns
    num:  number of dwarfs
    log:  a cout-like log */

void onStart(int rows, int cols, int num, std::ostream &log) {
  log << "Start!" << endl; // Print a greeting message
	srand(time(NULL));
  ROWS = rows; // Save values in global variables
  COLS = cols;
  NUM = num;
}

int neighbors(Dwarf &dwarf, int r, int c, Place p) {
	int ret = 0;
	if (dwarf.look(r, c+1) == p) {
    ret++;
  }
	if (dwarf.look(r, c-1) == p) {
    ret++;
  }
	if (dwarf.look(r+1, c) == p) {
    ret++;
  }
	if (dwarf.look(r-1, c) == p) {
    ret++;
  }
	return ret;
}
/* onAction:
A procedure called each time an idle dwarf is choosing
their next action.
Parameters:
    dwarf:   dwarf choosing an action
    day:     day (1+)
    hours:   number of hours in 24-hour format (0-23)
    minutes: number of minutes (0-59)
    log:     a cout-like log  */

void onAction(Dwarf &dwarf, int day, int hours, int minutes, ostream &log) {
  // Get current position of the dwarf
  int r = dwarf.row();
  int c = dwarf.col();

  // Look if there is a tree on the right from the dwarf
	if (dwarf.look(r, c+1) == PINE_TREE || dwarf.look(r, c+1) == APPLE_TREE) {
    // If there is a pine tree, chop it
    log << "Found a tree -- chop" << endl;
    dwarf.start_chop(EAST);
    return;
  }
	if (dwarf.look(r, c-1) == PINE_TREE || dwarf.look(r, c-1) == APPLE_TREE) {
    // If there is a pine tree, chop it
    log << "Found a tree -- chop" << endl;
    dwarf.start_chop(WEST);
    return;
  }
	if (dwarf.look(r+1, c) == PINE_TREE || dwarf.look(r+1, c) == APPLE_TREE) {
    // If there is a pine tree, chop it
    log << "Found a tree -- chop" << endl;
    dwarf.start_chop(SOUTH);
    return;
  }
	if (dwarf.look(r-1, c) == PINE_TREE || dwarf.look(r-1, c) == APPLE_TREE) {
    // If there is a pine tree, chop it
    log << "Found a tree -- chop" << endl;
    dwarf.start_chop(NORTH);
    return;
  }

  else {
    // Otherwise, move to a random location
		/*
		int rr = fmax(0, dwarf.row() - ROWS / 4);
		int cc = fmax(0, dwarf.col() - COLS / 4);
		int max = 0;
		int maxr = -1;
		int maxc = -1;

		for (; rr < fmin(ROWS, dwarf.row() + ROWS / 4); ++rr) {
			for (; cc < fmin(COLS, dwarf.col() + COLS / 4); ++cc) {
				int n = neighbors(dwarf, rr, cc, PINE_TREE);
				if ((n > max || ((n == max) && (
					                            abs(dwarf.row() - rr) + abs(dwarf.col() - cc) <
					 	                          abs(dwarf.row() - maxr) + abs(dwarf.col() - maxc)
																		)
											 )
					 ) && dwarf.look(rr,cc) == EMPTY)
					 {
						 maxr = rr;
						 maxc = cc;
						 max = n;
					 }
			}
		}
		if (max == 0) {
			maxr = fmin(fmax(0, dwarf.row() - ROWS / 4 + (rand() % (ROWS / 2))), ROWS - 1);
			maxc = fmin(fmax(0, dwarf.col() - COLS / 4 + (rand() % (COLS / 2))), COLS - 1);
		}
		*/
		int rr = 0;
		int cc = 0;
		int ctr = 0;
		while (((neighbors(dwarf, rr, cc, PINE_TREE) < 1) || dwarf.look(rr,cc) != EMPTY) && ctr < 2000) {
    	rr = dwarf.row() - ROWS / 4 + (rand() % (ROWS / 2));
    	cc = dwarf.col() - COLS / 4 + (rand() % (COLS / 2));
			//buffering
			rr = (dwarf.row() + ROWS / 4) - ((dwarf.row() + ROWS / 4 - rr) * (dwarf.row() + ROWS / 4 - max(dwarf.row() - ROWS / 4, 0))) / (ROWS / 2);
			cc = (dwarf.col() + COLS / 4) - ((dwarf.col() + COLS / 4 - cc) * (dwarf.col() + COLS / 4 - max(dwarf.col() - COLS / 4, 0))) / (COLS / 2);
			rr = (dwarf.row() - ROWS / 4) + ((rr - (dwarf.row() - ROWS / 4)) * (min(ROWS - 1, dwarf.row() + ROWS / 4) - (dwarf.row() - ROWS / 4))) / (ROWS / 2);
			cc = (dwarf.col() - COLS / 4) + ((cc - (dwarf.col() - COLS / 4)) * (min(COLS - 1, dwarf.col() + COLS / 4) - (dwarf.col() - COLS / 4))) / (COLS / 2);
			ctr++;
		}

		if (ctr > 2000) {
			//  this is if you wanna do two trees
			/*
			ctr = 0;
			while (((neighbors(dwarf, rr, cc, PINE_TREE) < 1) || dwarf.look(rr,cc) != EMPTY) && ctr < 2000) {
	    	rr = dwarf.row() - ROWS / 4 + (rand() % (ROWS / 2));
	    	cc = dwarf.col() - COLS / 4 + (rand() % (COLS / 2));
				rr = (dwarf.row() + ROWS / 4) - ((dwarf.row() + ROWS / 4 - rr) * (dwarf.row() + ROWS / 4 - max(dwarf.row() - ROWS / 4, 0))) / (ROWS / 2);
				cc = (dwarf.col() + COLS / 4) - ((dwarf.col() + COLS / 4 - cc) * (dwarf.col() + COLS / 4 - max(dwarf.col() - COLS / 4, 0))) / (COLS / 2);
				ctr++;
			}
			*/
			if (ctr > 2000) {
				rr = rand() % ROWS;
				cc = rand() % COLS;
			}
		}

    log << "Walk to " << rr << " " << cc << endl;
    dwarf.start_walk(rr, cc);
    return;
  }
}
