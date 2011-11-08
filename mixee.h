#ifndef GUARD_MIXEE_H
#define GUARD_MIXEE_H

class mixee {
public:
	sound_block *before;
	float *pre_mix;
	float scale;
	mixee(sound_block *, float);
	~mixee();
};

#endif
