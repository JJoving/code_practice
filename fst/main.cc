// Copyright 2018
// Author: junjie chen

#include <stdio.h>

#include "fst.h"
#include "floyd.h"

int main(int argc, char *argv[]) {
  std::string topo_file = argv[1],
              isymbol_file = argv[2],
              osymbol_file = argv[3],
              dot_file = argv[4];

  Symbol isymbol(isymbol_file), osymbol(osymbol_file);

  Fst fst;

  fst.ReadTopo(isymbol, osymbol, topo_file);
  fst.Dot(isymbol, osymbol, dot_file);
  
  fst.MakeTableFloyd();
  fst.Floyd();
  fst.PrintBestPath();

  return 0;
}
