#ifndef GUARD_MIXER_H
#define GUARD_MIXER_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include "sound_block.h"
#include "mixee.h"
#include "generator.h"
#include "note.h"

class mixer : public sound_block {

private:
	std::vector<mixee *> mixees;
	void adjust_scale();
public:
  void add_mixee(generator *); //add a generator to be mixed
	void add_mixee(generator *, float);
//	void set_front_m(sound_block *, sound_block *);
	void get_samps(float *, int, note *);
	void get_samps(float *, int);
	void get_samps(float *);
	void get_samps(note *);
	void set(sound_block *, sound_block *);
	mixer();
	~mixer();
//	mixer(mixee *);
//	mixer(generator *);
};
#endif
