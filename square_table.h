#ifndef GUARD_SQUARE_TABLE_H
#define GUARD_SQUARE_TABLE_H

#include <iostream>
#include <cmath>
#include "wavetable.h"

class square_table: public wavetable{
public:
  square_table();
  square_table(int);
private:
  void fill_table();
};

#endif
