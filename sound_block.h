#ifndef GUARD_SOUND_BLOCK_H
#define GUARD_SOUND_BLOCK_H

# include "note.h"
enum block_type {GENERATOR, PROCESSOR, MIXER, SYNTH};

class sound_block {
protected:
  sound_block *after;
	sound_block *before;
  block_type bt;
public:
	virtual void get_samps(float *) = 0;												//if the array size is prespecified by ksmps
  virtual void get_samps(float *, int) = 0;										//array to be filled, size of array
  virtual void get_samps(float *, int, note *) = 0;										//array to be filled, size of array
	virtual void get_samps(note *) = 0;
	virtual void add_after(sound_block *);									//adds block after in signal chain
	virtual void set(sound_block *, sound_block *);					//takes two soundblock references and sets them as before nd after
	virtual void set_front(sound_block *);									//sets before pointer
	virtual void set_front_m(sound_block *, sound_block *); //handles case for mixer
	virtual void set_back(sound_block *);										//sets just the back
	bool is_block_type(block_type); 												//returns true if it is that block_type
};

#endif
