#ifndef GUARD_TRI_TABLE_H     
#define GUARD_TRI_TABLE_H     

#include <iostream>
#include <cmath>
#include "wavetable.h"

class tri_table: public wavetable{
public:
  tri_table();
  tri_table(int);
private:
  void fill_table();
};

#endif
