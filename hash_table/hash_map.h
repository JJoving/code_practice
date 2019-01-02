// Copyright 2018
// Author: junjie chen
#ifndef CODE_PRACTICE_HASH_TABLE_HASH_MAP_H_
#define CODE_PRACTICE_HASH_TABLE_HASH_MAP_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct HashMember {
  HashMember(std::string word_ = "", int value_ = 0,
              HashMember* next_member_ = NULL):
    word(word_), value(value_), next_member(next_member_) {}

  std::string word;
  int value;
  HashMember* next_member;
};


class HashTable {
 public:
  explicit HashTable(int length = 65536): length_(length), index_(length, NULL) {}
  bool Insert(const std::string word) {
    int n = GetHash(word);
    if (n >= length_) return false;
    HashMember* item = new HashMember;
    (*item).word = word;
    (*item).value = 1;
    if (index_[n] == NULL) {
      index_[n] = item;
    } else {
      HashMember* tmp = index_[n];
      while ((*tmp).next_member != NULL) {
        if ((*item).word == (*tmp).word) {
          (*tmp).value++;
          return true;
        } else {
          tmp = (*tmp).next_member;
        }
      }
      if ((*item).word == (*tmp).word) {
        (*tmp).value++;
        delete item;
        return true;
      } else {
        (*tmp).next_member = item;
      }
    }
    return true;
  }

  int GetValue(const std::string word) {
    int n = GetHash(word);
    if (n >= length_) return 0;
    if (index_[n] == NULL) {
      return 0;
    } else {
      HashMember* tmp = index_[n];
      while (word != (*tmp).word) {
        if ((*tmp).next_member != NULL) {
          return 0;
        } else {
          tmp = (*tmp).next_member;
        }
      }
      return (*tmp).value;
    }
  }

 private:
  int GetHash(const std::string word) {
    int hash_value = 0;
    for (int i = 0; i < word.size(); ++i) {
      hash_value += ((word[i] * word[i]) % length_);
    }
    return (hash_value % length_);
  }
  std::vector<HashMember*> index_;
  int length_;
};

#endif  // CODE_PRACTICE_HASH_TABLE_HASH_MAP_H_
