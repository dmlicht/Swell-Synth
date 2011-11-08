#ifndef GUARD_ENVELOPE_H
#define GUARD_ENVELOPE_H

#include "processor.h"

class envelope : public processor{
private:
  double attack;		//attack time
  double decay;			//decay time
  double sustain;		//sustain amplitude
  double release;		//release time
  double max_amp;		//maximum amplitude
  double time_index;
	int samp_position;
public:
  envelope();					//Default constructor
  envelope(double, double, double, double);	//construct envelope with specified ADSR

  double test_duration;				//duration used for testing until midi implemented
  double get_level(int);
	double get_level(note *);

	void process(float *, int);		//function implemented by each indivdual processor called by get_samps to process in specific way
	void process(float *, int, note *);		//function implemented by each indivdual processor called by get_samps to process in specific way

  /* getters */
  double get_attack();
  double get_decay();
  double get_sustain();
  double get_release();

  /* setters */
  void set_attack(double);
  void set_decay(double);
  void set_sustain(double);
  void set_release(double);
};

#endif
