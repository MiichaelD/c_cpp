/**
 *  Problem:      FindingPatternInDictionary.cc
 *  Programmer:   Michael Duarte
 *  Date:         November 14th 2019
 *  Descroiption: Given a "dictionary" of words, return whether a given pattern can be found in it.
 *                - You can preprocess the input as you want in:
 *                    'void init(const vector<string> &dict);'
 *                - The pattern can be characters or a special WILDCARD (.) which can be replaced by
 *                  any letter.
 *                - Input's characters can be any unicode character.
 * 
 *                As follow up, I was asked for big O notation and to come up with the worst case
 *                scenario I could assign to the dictionary and patterns.
 */

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

struct Trie {
  Trie(char cc) : c{cc} {}
  char c;
  unordered_map<char, shared_ptr<Trie>> children;
  bool isLast = false;
};

int longestWordLength = 0;
shared_ptr<Trie> root;
const char WILDCARD = '.';


void print(shared_ptr<Trie> root, int level = 0) {
  if (!root) { return; }
  cout << "Node " << root->c << (root->isLast ? " (end)" : "");
  if (root->children.empty()) { 
    cout << endl;
    return;
  }
  cout << " has:" << endl;
  ++level;
  for (auto entry : root->children) {
    for (int i = 0; i < level; ++i) {
      cout << "\t";
    }
    print(entry.second, level);
  }
}

void init(const vector<string> &dict) {
  root = make_shared<Trie>(WILDCARD);
  for (string word : dict) {
    shared_ptr<Trie> aux = root;
    for (int i = 0 ; i < word.length(); ++i) {
      char c = word.at(i);
      auto &children = aux->children;
      if (children.find(c) == children.end()) {
        children[c] = make_shared<Trie>(c);
      }
      aux = children[c];
    }
    aux->isLast = true;
    if (longestWordLength < word.length()) {
      longestWordLength = word.length();
    }
  }
}

bool helper(const string &pattern, int index, shared_ptr<Trie> node) {
  // cout << "Index: " << index << endl;
  if (index == pattern.size()) {
    return node->isLast;
  }
  char c = pattern.at(index);
  // cout << "Checking if " << node->c << " has child: " << c << endl;
  if (c == WILDCARD) {
    for (auto it = node->children.begin(); it != node->children.end(); ++it) {
      if (helper(pattern, index + 1, it->second)) {
        return true;
      }
    }
  } else  if (node->children.find(c) != node->children.end()) {
    return helper(pattern, index + 1, node->children[c]);
  }
  return false;
}

bool find(const string &pattern) {
  if (!root || pattern.length() > longestWordLength) {
    return false;
  }
  if (pattern.empty()) {
    return root->isLast;
  }
  return helper(pattern, 0, root);
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  vector<string> input = {"foo", "bar", "baz", ""};
  vector<string> patterns = {"", "foo", "food", "f.o", "ba.", "..o", "bar", "ba", "..."};
  init(input);
  print(root);
  for (const string &pattern : patterns) {
    cout << "Pattern: '" << pattern << "' => " << (find(pattern) ? "Found" : "Not Found") << endl; 
  }
  return EXIT_SUCCESS;
}