#ifndef GUARD_SAW_TABLE_H     
#define GUARD_SAW_TABLE_H     

#include <iostream>
#include <cmath>
#include "wavetable.h"

class saw_table: public wavetable{
public:
  saw_table();
  saw_table(int);
private:
  void fill_table();
};

#endif
