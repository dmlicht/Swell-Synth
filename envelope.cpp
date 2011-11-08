#include <iostream>
#include <cmath>
#include "envelope.h"
#include "processor.h"

using namespace std;

  envelope::envelope(){
		samp_position = 0;
    max_amp = 1;
    attack = 0;
    decay = 0;
    sustain = 0;
    release = 0;
  }

  envelope::envelope(double att, double dec, double sus, double rel){
		samp_position = 0;
    max_amp = 1;
    attack = att;
    decay = dec;
    sustain = sus;
    release =  rel;
    /* FOR TESTING */
    test_duration = 2.0;
  }

void envelope::process(float* buffer, int buffer_size){
	for (int i = 0; i < buffer_size; ++i){
		buffer[i] = buffer[i] * get_level(samp_position);
		++samp_position;
	}
}

void envelope::process(float* buffer, int buffer_size, note *cur_note){
	for (int i = 0; i < buffer_size; ++i){
		buffer[i] = buffer[i] * get_level(cur_note);
	}
}

/* envelope calculation */
double envelope::get_level(int t){
  time_index = t / 44100.0;

  /* attack period */
  if (time_index < attack){
		cout << "attack" << endl;
    return (time_index / attack) * max_amp;
  }
  /* decay period */
  else if(time_index < (attack + decay)){
		cout << "decay" << endl;
    return (sustain + (max_amp - sustain) * (time_index - attack) / decay);
  }
  /* sustain period */
  else if (time_index < test_duration) {
		cout << "sustain" << endl;
    return sustain;
  }
  /* release period */
  else if (time_index < test_duration + release){
		cout << "release" << endl;
    return (sustain - sustain * (time_index - test_duration)/release);
  }
  /* note finished */
  else { 
    return 0; 
  }
}

double envelope::get_level(note *cur_note){
  time_index = cur_note->get_ticks() / 44100.0;

  /* attack period */
  if (cur_note->is_on() && (time_index < attack)){
    return (time_index / attack) * max_amp;
  }
  /* decay period */
  else if(cur_note->is_on() && (time_index < (attack + decay))){
    return (sustain + (max_amp - sustain) * (time_index - attack) / decay);
  }
  /* sustain period */
  else if (cur_note->is_on()) {
    return sustain;
  }
  /* release period */
  else if (cur_note->get_rel_ticks()/44100.0 < release){
    return (sustain - sustain * (cur_note->get_rel_ticks()/44100.0)/release);
  }
  /* note finished */
  else { 
    return 0; 
  }
}


/* getters */
double envelope::get_attack(){
  return attack;
}
double envelope::get_decay(){
  return decay;
}
double envelope::get_sustain(){
  return sustain;
}
double envelope::get_release(){
  return release;
}

/* setters */
void envelope::set_attack(double att){
  attack = att;
}
void envelope::set_decay(double dec){
  decay = dec;
}
void envelope::set_sustain(double sus){
  sustain = sus;
}
void envelope::set_release(double rel){
  release = rel;
}
