#include "rand_table.h"
#include "wavetable.h"
#include <cmath>
#include <iostream>

rand_table::rand_table(): wavetable::wavetable(){
  fill_table();
}

rand_table::rand_table(int size): wavetable::wavetable(size){
  fill_table();
}

void rand_table::fill_table(){
  srand(time(NULL));
  for (int i = 0; i < length; ++i){
    table[i] = (double) (rand() % 10000) / 5000 - 1;
  }
}
