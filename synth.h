#ifndef GUARD_SYNTH_H
#define GUARD_SYNTH_H

#include "wavetable.h"
#include "envelope.h"
#include "generator.h"
#include "sound_block.h"
#include "note.h"
#include <vector>

class synth : public sound_block {
private:
  static int sample_rate;
  static int ksmps;
  static int nchan;
	std::vector<note *> notes;

	int ticks;
public:
  synth(generator *);							//sample rate, control period, nchan
	void get_samps(float *);
	void get_samps(note *);					//note this function does nothing. it does not make sense to pass a note to the synth object, this is just to satisfy sound_blocks function being pure virtual
  void get_samps(float *, int);		//buffer, size of buffer
  void get_samps(float *, int, note *);	//note this function does nothing. it does not make sense to pass a note to the synth object, this is just to satisfy sound_blocks function being pure virtual
	void add_note(note *);

   /* setters */
	static void initialize();

  static void set_sample_rate(int);
  static void set_ksmps(int);
  static void set_nchan(int);

  /* getters */
  static int get_sample_rate();
  static int get_ksmps();
  static int get_nchan();
};

#endif
