#include "sound_block.h"
#include "mixer.h"
#include "mixee.h"
#include "synth.h"

mixer::mixer(){
	bt = MIXER;
}

mixer::~mixer(){
	int inputs = mixees.size();
	for (int i = inputs; i > 0 ; --i){
		delete mixees.at(i);
	}
}

void mixer::get_samps(note *cur_note){
	get_samps(cur_note->ndata, synth::get_ksmps(), cur_note);
}

void mixer::get_samps(float *buffer, int buffer_size, note *cur_note){
	int inputs = mixees.size();
	float buffer_input;
	for (int i = 0; i < inputs; ++i){
		mixees.at(i)->before->get_samps(mixees.at(i)->pre_mix, buffer_size, cur_note); 	//Fill all buffers
  }
	for (int i = 0; i < buffer_size; ++i){
		buffer_input = 0;
	  for (int j = 0; j < inputs; ++j){
			buffer_input += (mixees.at(j)->pre_mix[i] * mixees.at(j)->scale);
		}
		*buffer = buffer_input;
		++buffer;
	}
}

void mixer::get_samps(float *buffer, int buffer_size){
	int inputs = mixees.size();
	float buffer_input;
	for (int i = 0; i < inputs; ++i){
		mixees.at(i)->before->get_samps(mixees.at(i)->pre_mix, buffer_size); 	//Fill all buffers
  }
	for (int i = 0; i < buffer_size; ++i){
		buffer_input = 0;
	  for (int j = 0; j < inputs; ++j){
			buffer_input += (mixees.at(j)->pre_mix[i] * mixees.at(j)->scale);
		}
		*buffer = buffer_input;
		++buffer;
	}
}

void mixer::get_samps(float *buffer){
	get_samps(buffer, synth::get_ksmps());
}

//changes the scale of all the mixees to add up to 1 to help avoid clipping
void mixer::adjust_scale(){
	float total_weight = 0;
	for (unsigned int i = 0; i < mixees.size(); ++i){
		total_weight += mixees.at(i)->scale;
	}
	float fix_value = 1.0 / total_weight;
	for (unsigned int i = 0; i < mixees.size(); ++i){
		mixees.at(i)->scale = mixees.at(i)->scale * fix_value;
	}
}

void mixer::add_mixee(generator *new_wave){
	mixees.push_back(new mixee(new_wave, 1.0));
	new_wave->set_back(this);
	adjust_scale();
}

void mixer::add_mixee(generator *new_wave, float scale){
	mixees.push_back(new mixee(new_wave, scale));
	new_wave->set_back(this);
	adjust_scale();
}

void mixer::set(sound_block *before, sound_block *after){
	generator *b = (generator *) before;
	this->add_mixee(b);
	this->after = after;
}
