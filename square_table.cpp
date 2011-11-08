#include "square_table.h"
#include "wavetable.h"
#include <cmath>
#include <iostream>

square_table::square_table(): wavetable::wavetable(){
  fill_table();
}

square_table::square_table(int size): wavetable::wavetable(size){
  fill_table();
}

void square_table::fill_table(){
  for (int i = 0; i < length; ++i){
    if (std::sin((double)i * 2 * M_PI / length) >= 0){
      table[i] = 1;
    }
    else {
      table[i] = -1;
    }
  }
}
