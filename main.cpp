#include <iostream>
#include "src/skiplist.hpp"
#include <vector>
#include <algorithm>

// a playground for c++ language.

class util {
 private:
  int value;
 public:
  explicit util(int v) {
    this->value = v;
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
    util u(0);
    v.push_back(u);
    u.increment();
    std::cout << v[0].getValue() << std::endl;
    v[0].increment();
    std::cout << v[0].getValue() << std::endl;

    skiplist<int, int>::KVPair pair(10, 15);
    std::cout << pair.key << ","<< pair.value << std::endl;

    random_util rand(time(nullptr));
    for(auto i = 0; i <= 10; i++){
      std::cout << rand.next() << std::endl;
    }
    return 0;
}
