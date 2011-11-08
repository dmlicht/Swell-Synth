#ifndef GUARD_PLAYER_H
#define GUARD_PLAYER_H

/*class to store all important information for the program to run */

class Player {
private:
  int sr; 		//Sample rate
  int cr;		//control rate
  int nchan;		//number of output channels
  int cp;		//control period

public:
  Player(int, int, int, int);

  /* setters */
  void set_sr(int);
  void set_cr(int);
  void set_nchan(int);
  void cp(int);

  /* getters */
  int get_sr();
  int get_cr();
  int get_nchan();
  int get_cp();

}
