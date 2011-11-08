#ifndef GUARD_NOTE_H
#define GUARD_NOTE_H

#include <queue>

class note {
private:
	double frequency;
	int note_num;
	int velocity;	
	bool on;					//specifies whether note is still being held down
	int ticks;				//current number of samples drawn from note 
	int rel_ticks;		//ticks after note is released

public:
	note(int);				//creates note with specified note num
	note(int, int);		//creates note with specified note num and vel
	~note();
	double num_to_freq(int);	//converts note number to frequency
	void add_ticks(int);			//increments sample counting ticks
	void add_rel_ticks(int);
	int get_ticks();
	int get_rel_ticks();
	double get_frequency();
	float *ndata;			//buffer to hold note sample data
	bool first;
	bool is_on();
	void turn_off();
	int note_length;	//length note is held down for (pending midi implementation)
	std::queue<int> indices;
};

#endif
