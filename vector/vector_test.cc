// Copyright 2018
// Author: junjie chen

#include <string>
#include <iostream>
#include <fstream>

#include "vector.h"

int main() {
  Vector<int> arr;
  arr.push_back(1);
  arr[0] = 2;
  arr.set_item(1, 3);
  printf("%d %d %d %d\n", arr.size(), arr[0], arr.get_item(1), arr[8]);
  return 0;
}

