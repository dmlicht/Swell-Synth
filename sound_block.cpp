#include "sound_block.h"
#include <iostream>
#include <cmath>

//handles adding new processors to the signal chain
void sound_block::add_after(sound_block *block_to_add){
	if (after->is_block_type(MIXER)){
		after->set_front_m(block_to_add, this);
	}
	else {
		after->set_front(block_to_add);
	}
	block_to_add->set(this, after);
	after = block_to_add;
}

void sound_block::set(sound_block *before, sound_block *after){
	this->before = before;
	this->after = after;
}

void sound_block::set_back(sound_block *after){
	this->after = after;
}

void sound_block::set_front(sound_block* before){
	this->before = before;
}

//Is overwritten in mixer class (so does nothing unless object is of type mixer)
void sound_block::set_front_m(sound_block *b, sound_block *t){}

bool sound_block::is_block_type(block_type t){
	return (bt == t);
}
