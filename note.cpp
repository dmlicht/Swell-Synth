#include "note.h"
#include "synth.h"
#include <cmath>

note::note(int num){
	on = true;
	first = true;
	ticks = 0;
	rel_ticks = 0;
	note_num = num;
  frequency = num_to_freq(num);
	velocity = 100;
	note_length = 44100;					//SETS NOTE LENGTH TO 1 SECOND PENDING MIDI IMPLEMENTATION
	ndata = new float[synth::get_ksmps()];
}

note::note(int num, int vel){
	on = true;
	first = true;
	ticks = 0;
	rel_ticks = 0;
	note_num = num;
  frequency = num_to_freq(num);
	velocity = vel;
	note_length = 44100;					//SETS NOTE LENGTH TO 1 SECOND PENDING MIDI IMPLEMENTATION
	ndata = new float[synth::get_ksmps()];
}

note::~note(){
	delete ndata;
}

void note::add_ticks(int add){
	ticks += add;
}

void note::add_rel_ticks(int add){
	rel_ticks += add;
}

int note::get_ticks(){
	return ticks;
}

int note::get_rel_ticks(){
	return rel_ticks;
}


double note::get_frequency(){
	return frequency;
}

double note::num_to_freq(int num){
	return std::pow(2, (num / 12.0)) * 8.1757989156;
}

bool note::is_on(){
	return on;
}

void note::turn_off(){
	on = false;
}
