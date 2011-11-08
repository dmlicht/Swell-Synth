#ifndef GUARD_PROCESSOR_H
#define GUARD_PROCESSOR_H

#include "sound_block.h"
#include "note.h"

class processor : public sound_block{
protected:
	virtual void process(float *, int) = 0;		//function implemented by each indivdual processor called by get_samps to process in specific way
	virtual void process(float *, int, note *) = 0;		//function implemented by each indivdual processor called by get_samps to process in specific way

public:
	virtual void get_samps(note *);
	virtual void get_samps(float *);							//if the array size is prespecified by ksmps
  virtual void get_samps(float *, int);					//array to be filled, size of array
  virtual void get_samps(float *, int, note *);	//array to be filled, size of array
	processor();
};

#endif
