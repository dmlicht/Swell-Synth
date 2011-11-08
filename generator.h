#ifndef GUARD_GENERATOR_H
#define GUARD_GENERATOR_H

#include "sound_block.h"

class generator: public sound_block {
public:
	void set(sound_block *, sound_block *);					//takes two soundblock references and sets them as before nd after
	virtual void set_front(sound_block *);									//sets before pointer
	generator();
};

#endif
