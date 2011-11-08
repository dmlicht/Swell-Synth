#include "mixer.h"
#include "mixee.h"
#include "synth.h"

mixee::mixee(sound_block *before, float weight){
	this->before = before;
	scale = weight;
	pre_mix = new float[synth::get_ksmps()];
}

mixee::~mixee(){
	delete pre_mix;
}
