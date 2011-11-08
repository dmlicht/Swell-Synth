#ifndef GUARD_wavetable_h
#define GUARD_wavetable_h

#include "generator.h"
#include "note.h"
/* NOTES
Must extend class for all major waveforms of subtractive synthesis + Noise
*/

class wavetable: public generator {
protected:
  int length;											//Length of lookup table
  double *table;									//Hold table values
  double amp;											//amplitude of wave
  double index;										//current position in waveform
  double incr;										//increment value based on frequency
  double frequency;								//current frequency
  double sample_rate;							//TEMPORARY sample rate placeholder for testing
  double fraction;								//fraction used for interpolation

public:
  wavetable();										//Default constructor for wavetable (size defaults to 1024)
  wavetable(int);									//Constructor for wavetable of specific size

  ~wavetable();										//destructor

  void normalize();								//set the peak frequency to 1.0
  void generate_harmonic(double);	//generates harmonic :)

  void set_frequency(double);
  void set_frequency(int);

  double get_samp();							//get next sample for output
  double get_samp(int);					 	//get specified sample
  void get_samps(float *, int, note *);
  void get_samps(float *, int);
	void get_samps(float *);
	void get_samps(note *);
};
#endif
