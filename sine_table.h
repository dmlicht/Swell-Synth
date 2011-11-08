#ifndef GUARD_SIN_TABLE_H     
#define GUARD_SIN_TABLE_H     

#include <iostream>
#include <cmath>
#include "wavetable.h"

class sine_table: public wavetable{
public:
  sine_table();
  sine_table(int);
private:
  void fill_table();
};

#endif
