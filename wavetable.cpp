#include <cmath>
#include <iostream>
#include "portaudio.h"
#include "wavetable.h"
#include "synth.h"

wavetable::wavetable(){
  sample_rate = 44100;
  length = 1024;
  amp = 1;
  index = 0;
  table = (double *) calloc(length, sizeof(double));
}

wavetable::wavetable(int size){
  sample_rate = 44100;
  int length = size;
  amp = 1;
  index = 0;
  table = (double *) calloc(length, sizeof(double));
}

wavetable::~wavetable(){
  free(table);
}

void wavetable::normalize(){
  double max_samp = 0.0;		//var to hold max sample value
  for (int i = 0; i < length; ++i){
    if (table[i] > max_samp){
      max_samp = table[i];
    }
  }
  for (int i = 0; i < length; ++i){
    table[i] = table[i]/max_samp;
  }
}

void wavetable::set_frequency(double f){
  frequency = f;
}

void wavetable::set_frequency(int f){
  frequency = f;
}

double wavetable::get_samp(){

  /* Oscil interpolation */
  fraction = index - (int) index;
  double floor_value = *(table + ((int) index));
  double ceiling_value = *(table + ((int) index) + 1);
  double out = floor_value + fraction * (ceiling_value - floor_value);

  incr = frequency * ((double) length / (double) sample_rate);
  index += incr;
  while (index >= length) index -= length;
  while (index < 0) index += length;
  return out; 
}

void wavetable::get_samps(float *buffer){
	get_samps(buffer, synth::get_ksmps());
}

void wavetable::get_samps(note *cur_note){
	get_samps(cur_note->ndata, synth::get_ksmps(), cur_note);
}

void wavetable::get_samps(float *buffer, int buffer_size){
  for (int i = 0; i < buffer_size; ++i){
    /* Oscil interpolation */
    fraction = index - (int) index;
    double floor_value = *(table + ((int) index));
    double ceiling_value = *(table + ((int) index) + 1);
    double out = floor_value + fraction * (ceiling_value - floor_value);
    
    incr = frequency * ((double) length / (double) sample_rate);
    index += incr;
    while (index >= length) index -= length;
    while (index < 0) index += length;
    *buffer = (float) out;
    ++buffer;
  }
}

void wavetable::get_samps(float *buffer, int buffer_size, note *cur_note){
	if(!cur_note->first){
		index = cur_note->indices.front();
		cur_note->indices.pop();
	}
  for (int i = 0; i < buffer_size; ++i){
    /* Oscil interpolation */
    fraction = index - (int) index;
    double floor_value = *(table + ((int) index));
    double ceiling_value = *(table + ((int) index) + 1);
    double out = floor_value + fraction * (ceiling_value - floor_value);
    incr = cur_note->get_frequency() * ((double) length / (double) synth::get_sample_rate());
    index += incr;
    while (index >= length) index -= length;
    while (index < 0) index += length;
    *buffer = (float) out;
    ++buffer;
   }
	 cur_note->indices.push(index);
 }
