#ifndef GUARD_RAND_TABLE_H
#define GUARD_RAND_TABLE_H

#include <iostream>
#include <cmath>
#include "wavetable.h"

class rand_table: public wavetable{
public:
  rand_table();
  rand_table(int);
private:
  void fill_table();
};

#endif
