#include "tri_table.h"
#include "wavetable.h"
#include <cmath>
#include <iostream>

tri_table::tri_table() : wavetable::wavetable(){
  fill_table();
}

tri_table::tri_table(int x) : wavetable::wavetable(x){
  fill_table();
}

void tri_table::fill_table(){
  int i;
  for (i = 0; i < length/4; ++i){
    table[i] = 4 * (double)i/ length;
  }
  for (; i < length / 2; ++i){
    table[i] = 2 - (4 * (double)i / length);
  }
  for (; (i < (3 * length) / 4); ++i){
    table[i] = 2 - (4 * (double)i / length);
  }
  for (; i < length; ++ i){
    table[i] = (4 * (double) i / length) - 4;
  }
}
