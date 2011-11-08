#include "sine_table.h"
#include "wavetable.h"
#include <cmath>
#include <iostream>

sine_table::sine_table() : wavetable::wavetable(){
  fill_table();
}

sine_table::sine_table(int x) : wavetable::wavetable(x){
  fill_table();
}

void sine_table::fill_table(){
  for (int i = 0; i < length; ++i){
    table[i] = std::sin(i * 2 * M_PI / length);
  }
}
