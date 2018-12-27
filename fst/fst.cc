// Copyright 2018
// Author: junjie chen

#include "fst.h"

void Fst::ReadTopo(const Symbol &isymbol,
                   const Symbol &osymbol,
                   const std::string &topo_file) {
  FILE *fp = fopen(topo_file.c_str(), "r");
  char buffer[1024], ilabel[1024], olabel[1024];
  int state, next_state, num;
  float weight;
  std::vector<std::vector<Arc> > all_arcs;
  while (fgets(buffer, 1024, fp)) {
    num = sscanf(buffer, "%d %d %s %s %f", &state, &next_state, ilabel,
                 olabel, &weight);
    if (num >= 4) {
      if (num == 4) weight = 0;
      Arc arc(next_state, isymbol.GetId(ilabel), osymbol.GetId(olabel),
              weight);
      if (state >= all_arcs.size()) all_arcs.resize(state + 1);
      if (next_state >= all_arcs.size()) all_arcs.resize(next_state + 1);
      all_arcs[state].push_back(arc);
    } else if (sscanf(buffer, "%d %f", &state, &weight) == 2) {
      final_states_[state] = weight;
    } else {
    printf("ERROR\n");
    break;
    }
  }
  fclose(fp);
  arc_offset_.resize(all_arcs.size());
  int offset = 0;
  for (int i = 0; i < all_arcs.size(); i++) {
    arc_offset_[i] = offset;
    arcs_.insert(arcs_.end(), all_arcs[i].begin(), all_arcs[i].end());
    offset += all_arcs[i].size();
  }
}

void Fst::Dot(const Symbol &isymbol,
         const Symbol &osymbol,
         const std::string &dot_file) const {
  printf("digraph FSM {\nrankdir = LR;\nnode [shape = \"circle\"]\n");
  for (int i = 0; i <arc_offset_.size(); ++i) {
    if (final_states_.find(i) != final_states_.end()) {
      printf("%d [label = \"%d\" shape = doublecircle ]\n", i, i);
    } else {
      printf("%d [label = \"%d\" ]\n", i, i);
    }
    int state_size;
    if (i < arc_offset_.size() - 1) {
      state_size = arc_offset_[i+1] - arc_offset_[i];
    } else {
      state_size = arcs_.size() - arc_offset_[i];
    }
    // Arc *arc = arcs_.data() + i;
    // for (int j =0; j <= state_size; ++j, ++arc){
    for (const Arc *arc = ArcStart(i); arc != ArcEnd(i); arc++) {
      printf("\t %d -> %d [label = \"%s:%s/%f\" ]\n", i, arc->next_state,
              isymbol.GetSymbol(arc->ilabel).c_str(),
              osymbol.GetSymbol(arc->olabel).c_str(),
              arc->weight);
    }
  }
  printf("}\n");
}

void Fst::MakeTableFloyd() {
  floyd_table_ = new float* [NumStates()];
  floyd_dis_table_ = new float* [NumStates()];
  floyd_path_table_ = new int* [NumStates()];

  for (int i = 0; i < NumStates(); ++i) {
    floyd_table_[i] = new float[NumStates()];
    floyd_dis_table_[i] = new float[NumStates()];
    floyd_path_table_[i] = new int[NumStates()];
    for (int j = 0; j < NumStates(); ++j) {
      floyd_table_[i][j] = INT_MAX;
    }
  }
  for (int i = 0; i < NumStates(); ++i) {
    for (const Arc *arc = ArcStart(i); arc != ArcEnd(i); arc++) {
      floyd_table_[i][arc->next_state] = arc->weight;
    }
  }
}

void Fst::Floyd() {
  for (int i = 0; i < NumStates(); ++i) {
    for (int j = 0; j < NumStates(); ++j) {
      floyd_dis_table_[i][j] = floyd_table_[i][j];
      floyd_path_table_[i][j] = j;
    }
  }
  
  for (int i = 0; i < NumStates(); ++i) {
    for (int j = 0; j < NumStates(); ++j) {
      for (int k = 0; k < NumStates(); ++k) {
        float tmp = 0;
        if (floyd_dis_table_[j][i] == INT_MAX ||
            floyd_dis_table_[i][k] == INT_MAX ){
          tmp = INT_MAX;
        } else {
          tmp = floyd_dis_table_[j][i] + floyd_dis_table_[i][k];
        }
        
        if (floyd_dis_table_[j][k] > tmp){
          floyd_dis_table_[j][k] = tmp;
          floyd_path_table_[j][k] = floyd_path_table_[j][i];
        }
      }
    }
  }
  //for (int i = 0; i < NumStates(); ++i) {
  //  for (int j = 0; j < NumStates(); ++j) {
  //    printf("%f ",floyd_dis_table_[i][j]); 
  //  }
  //  printf("\n");
  //}
}

void Fst::PrintBestPath(){
  int start_state = 0;
  int end_state = NumStates() - 1;
  printf("start state: %d end state %d total weight:%f \n", start_state, end_state, floyd_dis_table_[start_state][end_state]);

  int tmp = floyd_path_table_[start_state][end_state];
  printf("path: %d -> ", start_state);
  while (tmp != end_state){
    printf("%d ->", tmp);
    tmp = floyd_path_table_[tmp][end_state];
  }
  printf("%d \n", end_state);
}

