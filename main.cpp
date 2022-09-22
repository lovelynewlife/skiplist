#include <iostream>
#include "src/skiplist.hpp"
#include <vector>

class util {
 private:
  int value;
 public:
  util() {
    this->value = 0;
  }
  void increment() {
    this->value += 1;
  }
  int getValue() const{
    return this-> value;
  }
};

int main() {
    std::vector<util> v;
    util u;
    v.push_back(u);
    u.increment();
    std::cout << v[0].getValue() << std::endl;
    skiplist<int, int>::KVPair pair(10, 15);
    std::cout << "Hello, World!" << std::endl;
    std::cout << pair.key << ","<< pair.value << std::endl;
    return 0;
}
