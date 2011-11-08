#include "synth.h"
#include "generator.h"
#include <iostream>

int synth::sample_rate = 44100;
int synth::ksmps = 128;
int synth::nchan = 1;

synth::synth(generator *start_block){
	ticks = 0;
	before = start_block;
	before->set_back(this);
	bt = SYNTH;
}

/*
void synth::get_samps(float *buffer, int buffer_size){
  float block_reciever[buffer_size];
	float *b = &block_reciever[0];
  before->get_samps(b, buffer_size);
  for (int i = 0; i < buffer_size; ++i){
    *buffer = block_reciever[i];
    ++buffer;
  }
}
*/

void synth::get_samps(float *buffer, int buffer_size){
  for (unsigned int i = 0; i < notes.size(); ++i){
		note *cur_note = notes.at(i);
		before->get_samps(cur_note);
		if (cur_note->get_ticks() > cur_note->note_length){
			cur_note->turn_off();
			cur_note->add_rel_ticks(buffer_size);
		}
		else {
			cur_note->add_ticks(buffer_size);
		}
		cur_note->first = false;
	}
  for (int i = 0; i < buffer_size; ++i){
		float to_buff = 0;
		for (unsigned int j = 0; j < notes.size(); ++j){
			to_buff += notes.at(j)->ndata[i];
		}
    *buffer = to_buff;
    ++buffer;
  }
}

void synth::get_samps(float *buffer){
  float block_reciever[synth::get_ksmps()];
	float *b = &block_reciever[0];
  before->get_samps(b, synth::get_ksmps());
  for (int i = 0; i < synth::get_ksmps(); ++i){
    *buffer = block_reciever[i];
    ++buffer;
  }
}

void synth::get_samps(note *cur_note){}
void synth::get_samps(float *buffer, int buffer_size, note *cur_note){}

void synth::add_note(note *new_note){
	if (notes.size() > 3){
		notes.erase(notes.begin());
	}
	notes.push_back(new_note);
}

   /* setters */

void synth::initialize(){
	sample_rate = 44100;
	ksmps = 128;
	nchan = 1;
}

void synth::set_sample_rate(int sr){
  synth::sample_rate = sr;
}

void synth::set_ksmps(int cp){
  synth::ksmps = cp;
}

void synth::set_nchan(int nc){
  synth::nchan = nc;
}

  /* getters */
int synth::get_sample_rate(){
  return synth::sample_rate;
}

int synth::get_ksmps(){
  return synth::ksmps;
}

int synth::get_nchan(){
  return synth::nchan;
}
