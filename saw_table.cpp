#include "saw_table.h"
#include "wavetable.h"
#include <cmath>
#include <iostream>

saw_table::saw_table() : wavetable::wavetable(){
  fill_table();
}

saw_table::saw_table(int x) : wavetable::wavetable(x){
  fill_table();
}

void saw_table::fill_table(){
  for (int i = 0; i < length; ++i){
    table[i] = 1 - (2 * (double)i / length);
  }
}
