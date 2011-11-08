#include "generator.h"

//changes the set functions to only set a behind value, as generators must be at the front of the signal chain
void generator::set(sound_block *before, sound_block *after){
	this->after = after;
}

//changes set_front function to do nothing because generators must be at the front of the signal chain
void generator::set_front(sound_block *front){
}

generator::generator(){
	bt = GENERATOR;
}
