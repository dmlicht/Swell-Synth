#include "processor.h"
#include "synth.h"
#include <iostream>

processor::processor(){
	bt = PROCESSOR;
}

void processor::get_samps(note *cur_note){
	get_samps(cur_note->ndata, synth::get_ksmps(), cur_note);
}

void processor::get_samps(float *buffer, int buffer_size){
  float block_reciever[buffer_size];
	float *b = &block_reciever[0];
  before->get_samps(b, buffer_size);
	b = &block_reciever[0];
	process(b, buffer_size);
  for (int i = 0; i < buffer_size; ++i){
    *buffer = block_reciever[i];
    ++buffer;
  }
}

void processor::get_samps(float *buffer){
  float block_reciever[synth::get_ksmps()];
	float *b = &block_reciever[0];
  before->get_samps(b, synth::get_ksmps());
	b = &block_reciever[0];
	process(b, synth::get_ksmps());
  for (int i = 0; i < synth::get_ksmps(); ++i){
    *buffer = block_reciever[i];
    ++buffer;
  }
}

void processor::get_samps(float *buffer, int buffer_size, note *cur_note){
  float block_reciever[buffer_size];
	float *b = &block_reciever[0];
  before->get_samps(b, buffer_size, cur_note);
	b = &block_reciever[0];
	process(b, buffer_size, cur_note);
  for (int i = 0; i < buffer_size; ++i){
    *buffer = block_reciever[i];
    ++buffer;
  }
}
