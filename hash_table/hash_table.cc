// Copyright 2018
// Author: junjie chen

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string.h>

#include "hash_map.h"

std::vector<std::string> split(const std::string& str, const std::string& delim) {
  std::vector<std::string> res;
  if ("" == str) return res;
  char* strs = new char[str.length() + 1];
  strcpy(strs, str.c_str());
  char* d = new char[delim.length() + 1];
  strcpy(d, delim.c_str());
  char* p = strtok_r(strs, d);
  while (p) {
    std::string s = p;
    res.push_back(s);
    p = strtok_r(NULL, d);
  }
  return res;
}

int main(int argc, char *argv[]) {
  std::string word_file = argv[1];
  std::fstream fp(word_file.c_str());
  HashTable map;
  std::string buffer;
  while (getline(fp, buffer)) {
    std::vector<std::string> s = split(buffer, " ");
    for (int i = 0; i < s.size(); i++) {
      map.Insert(s[i].c_str());
    }
  }
  printf("%d\n", map.GetValue("and"));
  printf("%d\n", map.GetValue("word"));
  return 0;
}
