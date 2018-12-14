/*
** SIDENOTE: LOG IS NOT USED
** IT USED TO BE USED, BUT AFTER FINAL TESTING, FUNCTIONALITY WAS UNNECESSARY
** SO IT WAS REMOVED
*/



#include <cstdlib>
#include <cmath>
#include <iostream>
#include "bot.h"

using namespace std;

const int MAX_ROWS = 40;
const int MAX_COLS = 40;

int ROWS;
int COLS;
int NUM;

//all the headers
int noneg(int x);
int mink_1_dist(int r, int c, int rr, int cc);
bool has_P(Dwarf &dwarf, int r, int c);
bool tieneF(Dwarf &dwarf, int r, int c);
bool alt_gotF(Dwarf &dwarf, int r, int c);
bool got_next(Dwarf &dwarf, int r, int c);
bool tiene_none(Dwarf &dwarf, int r, int c, int radius, Place item);
Dir point_empty(Dwarf &dwarf, int r, int c, int radius, Place ITEM);
int full_empty(Dwarf &dwarf, int r, int c, Place ITEM);
Loc nearboi(Dwarf &dwarf, int r, int c, Place ITEM);
void altlum(Dwarf &dwarf, int r, int c, ostream &log);
void fence(Dwarf &dwarf, int r, int c, ostream &log);
void pumpkin(Dwarf &dwarf, int r, int c, ostream &log);
void apple(Dwarf &dwarf, int r, int c, ostream &log);
bool has_EMPTY(Dwarf &dwarf, int r, int c);
bool has_PINE_TREE(Dwarf &dwarf, int r, int c);
bool got_yummyboi(Dwarf &dwarf, int r, int c);
void start_action(Dwarf &dwarf, int r, int c, ostream &log, int action, Dir dir);
void lumber(Dwarf &dwarf, int r, int c, ostream &log);


/* onStart:
   An Initialization procedure called at the start of the game.
   You can use it to initialize certain global variables, or do
   something else before the actual simulation starts.
   Parameters:
   rows: number of rows
   cols: number of columns
   num:  number of dwarfs
   log:  a cout-like log
*/
void onStart(int rows, int cols, int num, std::ostream &log) {
  ROWS = rows; // Save values in global variables for future use
  COLS = cols;
  NUM = num;
}

/* onAction:
   A procedure called each time an idle dwarf is choosing
   their next action.
   Parameters:
   dwarf:   dwarf choosing an action
   day:     day (1+)
   hours:   number of hours in 24-hour format (0-23)
   minutes: number of minutes (0-59)
   log:     a cout-like log
*/
void onAction(Dwarf &dwarf, int day, int hours, int minutes, ostream &log) {
  // Get current position of the dwarf
  int r = dwarf.row();
  int c = dwarf.col();

	//used to be numero here but lol just killed it
	//it was int number = NUM*30; tho just in case

	//kill off one of the dwarves to keep space conserved
	//for some reason, it doesn't work if you don't do this
	//not really sure why LOL but whatever
  if (dwarf.name() == 1) {dwarf.start_walk(0,0);return;}
  // just making sure they don't die
  if((day == 1 && hours > 16) || (day != 1 && (hours > 16 || hours < 7))){
    if(!got_yummyboi(dwarf, r, c) && hours < 20){
      Loc loc = nearboi(dwarf, r, c, APPLE_TREE);
      if(!has_EMPTY(dwarf, loc.r, loc.c)) return;
      start_action(dwarf, loc.r, loc.c, log, 2, NORTH);
    }

    if(has_EMPTY(dwarf, r, c)){
      Dir dir = point_empty(dwarf, r, c, 1, EMPTY);
      dwarf.start_build(dir);
    }
    apple(dwarf, r, c, log);return;
  }
	//case 4, where you're at the end of case 2
  if(hours == 7){if(tieneF(dwarf, r, c)){Dir dir = point_empty(dwarf, r, c, 1, FENCE);dwarf.start_chop(dir);}}
	// now this is extra stuff other than staying alive
  if(day > 4 && (dwarf.lumber() > NUM*30)) fence(dwarf, r, c, log);
	else{
    int pi = full_empty(dwarf, r, c, PINE_TREE);
    int a = full_empty(dwarf, r, c, APPLE_TREE);
    int pu = full_empty(dwarf, r, c, PUMPKIN);       //represents where the pumpkins at
    if(pi > 0 && !(dwarf.name() > pi)) lumber(dwarf, r, c, log);
    else if (a > (NUM*10 + 1) && !(dwarf.name() > a)) altlum(dwarf, r, c, log);
    else if(pu > 0 && !(dwarf.name() > pu)) pumpkin(dwarf, r, c, log); // go and monch that boi
		else apple(dwarf, r, c, log);  //default is to pick apples, since we wanna maximize them and they're p much infinite
	}
}
//LOGS ARE USELESS MWAHAHAHAHAAA LOL

int noneg(int x) {
	if (x < 0) return 0 - x;
	else return x;
}

int mink_1_dist(int r, int c, int rr, int cc){
  return noneg(rr - r) + noneg(cc - c);
}

bool has_P(Dwarf &dwarf, int r, int c){
  return tiene_none(dwarf, r, c, 1, PUMPKIN);
}

//checks if stuff is near enough
bool tiene_none(Dwarf &dwarf, int r, int c, int radius, Place ITEM){
  if (dwarf.look(r, c+radius) == ITEM) return true;
  else if (dwarf.look(r, c-radius) == ITEM) return true;
  else if (dwarf.look(r-radius, c) == ITEM) return true;
  else if (dwarf.look(r+radius, c) == ITEM) return true;
  else return false;
}

//finds the location of the other function
Dir point_empty(Dwarf &dwarf, int r, int c, int radius, Place ITEM){
  if (dwarf.look(r, c+radius) == ITEM) return EAST;
  if (dwarf.look(r, c-radius) == ITEM) return WEST;
  if (dwarf.look(r-radius, c) == ITEM) return NORTH;
  if (dwarf.look(r+radius, c) == ITEM) return SOUTH;
}

// get the number of shits left
int full_empty(Dwarf &dwarf, int r, int c, Place ITEM){
  int ret = 0;

  for(int i = 0; i < ROWS; i++){
    for(int j = 0; j < COLS; j++){
      if(tiene_none(dwarf, i, j, 0, ITEM)) ret += 1; }}
  return ret;
}

//where the apple trees at yo?
bool got_yummyboi(Dwarf &dwarf, int r, int c){
  return tiene_none(dwarf, r, c, 1, APPLE_TREE);
}

bool has_EMPTY(Dwarf &dwarf, int r, int c){return tiene_none(dwarf, r, c, 1, EMPTY);}
bool has_PINE_TREE(Dwarf &dwarf, int r, int c){return tiene_none(dwarf, r, c, 1, PINE_TREE);}
bool tieneF(Dwarf &dwarf, int r, int c){return tiene_none(dwarf, r, c, 1, FENCE);}
bool alt_gotF(Dwarf &dwarf, int r, int c){
  if (dwarf.look(r, c+2) == FENCE && dwarf.look(r, c+1) != FENCE) return true;
  if (dwarf.look(r, c-2) == FENCE && dwarf.look(r, c-1) != FENCE) return true;
  if (dwarf.look(r-2, c) == FENCE && dwarf.look(r-1, c) != FENCE) return true;
  if (dwarf.look(r+2, c) == FENCE && dwarf.look(r+1, c) != FENCE) return true;
  return false;
}
void start_action(Dwarf &dwarf, int r, int c, ostream &log, int thing, Dir dir){
  switch(thing){
  case 0 :
    dwarf.start_chop(dir);  //harvesting lumber case
    break;
  case 1 :
    dwarf.start_pick(dir);  //harvesting apple case
    break;
  case 2 :
    dwarf.start_walk(r, c); //moving case
    break;
  case 3 :
    dwarf.start_build(dir); //making fence case
    break;
  }
}

//when/where to go chop wood in order to build fences for protection
//also, later on, called to build contiguous fence structure
//EDIT: SECOND FUNCTIONALITY MOVED TO FUNCTION altlum
void lumber(Dwarf &dwarf, int r, int c, ostream &log){
  if(has_PINE_TREE(dwarf, r, c)){Dir dir = point_empty(dwarf, r, c, 1, PINE_TREE);
		start_action(dwarf, r, c, log, 0, dir);}
	else if(got_yummyboi(dwarf, r, c)){Dir dir = point_empty(dwarf, r, c, 1, APPLE_TREE);
    start_action(dwarf, r, c, log, 0, dir);}
  Loc loc = nearboi(dwarf, r, c, PINE_TREE);
  start_action(dwarf, loc.r, loc.c, log, 2, NORTH);
}

bool got_next(Dwarf &dwarf, int r, int c){
  if(!tiene_none(dwarf, r, c, 0, FENCE) || tieneF(dwarf, ROWS/2, COLS/2)) return false;
  if(r == ROWS/2 && c == COLS/2)return true;
  return got_next(dwarf, r+1, c) || got_next(dwarf, r-1, c) || got_next(dwarf, r, c+1) || got_next(dwarf, r, c-1);
}
//second case of lumber harvesting, where you do it for the contiguous structure
void altlum(Dwarf &dwarf, int r, int c, ostream &log){
  if(has_PINE_TREE(dwarf, r, c)){
    Dir dir = point_empty(dwarf, r, c, 1, PINE_TREE);
    start_action(dwarf, r, c, log, 0, dir);
  } else if(got_yummyboi(dwarf, r, c)){
    Dir dir = point_empty(dwarf, r, c, 1, APPLE_TREE);
    start_action(dwarf, r, c, log, 0, dir);
  }

  Loc loc = nearboi(dwarf, r, c, APPLE_TREE);
  start_action(dwarf, loc.r, loc.c, log, 2, NORTH);
}

//go get the pumpkins once day breaks
//SIDENOTE: PUMPKINS DON'T MEET REQUIREMENT USUALLY, BUT IT'S FINE, SINCE POINTS ARE IN EXCESS
void pumpkin(Dwarf &dwarf, int r, int c, ostream &log){
  if(has_P(dwarf, r, c)){
    Dir dir = point_empty(dwarf, r, c, 1, PUMPKIN);
    start_action(dwarf, r, c, log, 1, dir);
  }
  Loc loc = nearboi(dwarf, r, c, PUMPKIN);
  if(!has_EMPTY(dwarf, loc.r, loc.c))return;
  start_action(dwarf, loc.r, loc.c, log, 2, NORTH);
}

//build fences for protection from zombies during the night
//also builds fences for contiguous structure that is required
void fence(Dwarf &dwarf, int r, int c, ostream &log){
  if(has_PINE_TREE(dwarf, r, c) || got_yummyboi(dwarf, r, c)) lumber(dwarf, r, c, log);
  if (alt_gotF(dwarf, r, c)){
    Dir dir = point_empty(dwarf, r, c, 2, FENCE);
    start_action(dwarf, r, c, log, 3, dir);
  }
  int rr = 0;
  int cc = 0;
  bool masdeuno = 0;

  for(int i = 0; i < ROWS; i++){
    for(int j = 0; j < COLS; j++){

      if(alt_gotF(dwarf, i, j)){
				masdeuno = 1;
        int dist1 = mink_1_dist(r, c, rr, cc);
				int dist2 = mink_1_dist(r, c, i, j);
				if(dist1 > dist2){
	  			rr = i;
	  			cc = j;
				}}}}
  if(masdeuno == 0 && (r != ROWS/2 && c != COLS)){
    if(dwarf.look(ROWS/2,COLS/2) == EMPTY){rr = ROWS/2;cc = COLS/2;}
		else{ Loc loc = nearboi(dwarf, ROWS/2, COLS/2, EMPTY);rr = loc.r;cc = loc.c;}
  }else if (masdeuno == 0) dwarf.start_build(SOUTH);start_action(dwarf, rr, cc, log, 2, NORTH);}


//find and harvest apples
void apple(Dwarf &dwarf, int r, int c, ostream &log){
  if(got_yummyboi(dwarf, r, c)){Dir dir = point_empty(dwarf, r, c, 1, APPLE_TREE); start_action(dwarf, r, c, log, 1, dir);}

  Loc loc = nearboi(dwarf, r, c, APPLE_TREE);
  if(!has_EMPTY(dwarf, loc.r, loc.c))return;
  start_action(dwarf, loc.r, loc.c, log, 2, NORTH);
}

//returns location of closest ITEM
//SIDENOTE: ASSUMES THAT THE ITEM EXISTS
Loc nearboi(Dwarf &dwarf, int r, int c, Place ITEM){
  int rr = 0;
  int cc = 0;

  // gets at least 1 instance to compare against
  for(int i = 0; i < ROWS; i++){
    for(int j = 0; j < COLS; j++){
      if(tiene_none(dwarf, i, j, 1, ITEM) && tiene_none(dwarf, i, j, 0, EMPTY)){
        rr = i;
				cc = j;
				break;
      }}}

  for(int i = 0; i < ROWS; i++){
    for(int j = 0; j < COLS; j++){
      if(tiene_none(dwarf, i, j, 1, ITEM) && tiene_none(dwarf, i, j, 0, EMPTY)){
	int dist1 = mink_1_dist(r, c, rr, cc);
	int dist2 = mink_1_dist(r, c, i, j);
	if(dist1 > dist2){
	  rr = i;	 cc = j;} }
    }  }  return {rr, cc};
}
