// Copyright 2018
// Author: junjie chen

#ifndef V2_FST_H_
#define V2_FST_H_

#include <fstream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
#include <map>
#include <algorithm>

#define INT_MAX 2147483647

class Symbol;

struct Arc {
  Arc(int next_state_, int ilabel_, int olabel_, float weight_):
    next_state(next_state_), ilabel(ilabel_), olabel(olabel_), weight(weight_) {
    }

  int next_state, ilabel, olabel;
  float weight;
};

class Fst {
 public:
  int32_t NumStates() const {
    return arc_offset_.size();
  }

  int32_t NumArcs() const {
    return arcs_.size();
  }

  const Arc *ArcStart(int32_t id) const {
    return arcs_.data() + arc_offset_[id];
  }

  const Arc *ArcEnd(int32_t id) const {
    if (id < NumStates() - 1) {
      return arcs_.data() + arc_offset_[id + 1];
    } else {
      return arcs_.data() + arcs_.size();
    }
  }
  void ReadTopo(const Symbol &isymbol,
                const Symbol &osymbol,
                const std::string &topo_file);

  void Dot(const Symbol &isymbol,
           const Symbol &osymbol,
           const std::string &dot_file) const;

  void MakeTableFloyd();

  void Floyd();

  void PrintBestPath();

 private:
  std::vector<Arc> arcs_;
  std::map<int, float> final_states_;
  std::vector<int> arc_offset_;
  float **floyd_table_;
  float **floyd_dis_table_;
  int **floyd_path_table_;
};

class Symbol {
 public:
  explicit Symbol(const std::string &file) {
    ReadSymbolFile(file);
  }

  std::string GetSymbol(const int id) const {
    return symbol_[id];
  }

  int GetId(const std::string &symbol) const {
    for (int i = 0; i <= symbol_.size(); ++i) {
      if (symbol == symbol_[i]) {
        return i;
      }
    }
    return -1;
  }

 private:
  void ReadSymbolFile(const std::string &file) {
    FILE *fp = fopen(file.c_str(), "r");
    char buffer[1024], str[1024];
    int num, id;
    while (fgets(buffer, 1024, fp)) {
      num = sscanf(buffer, "%s %d", str, &id);
      symbol_[id] = str;
    }
    fclose(fp);
  }
  mutable std::map<int, std::string> symbol_;
};

#endif  // V2_FST_H_
