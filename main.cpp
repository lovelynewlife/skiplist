#include <iostream>
#include "src/skiplist.hpp"
#include <vector>
#include <map>
#include <list>
#include <algorithm>

// some experimental code for c++ STL features.

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

util & add_util(util &u) {
  u.increment();
  return u;
}

util add_util2(util &u) {
  u.increment();
  return u;
}

int main() {
    std::vector<util> v;
    util u(0);
    v.push_back(u);
    u.increment();
    std::cout << v[0].getValue() << std::endl;
    v[0].increment();
    std::cout << v[0].getValue() << std::endl;

    add_util(u);
    u = add_util(u);
    std::cout << u.getValue() << std::endl;

    util u2(0);
    add_util2(u2).increment();
    std::cout << "u2:" << u2.getValue() << std::endl;

    std::map<int, int> m;
    m[1] = 1;
    m[2] = 2;

    std::list<int> l;
    int a = 3;
    l.push_back(1);
    l.push_back(2);
    l.push_back(a);

    std::vector<int> v2;
    v2.push_back(0);
    std::sort(v2.begin(), v2.end());

    random_util rand(time(nullptr));
    for(auto i = 0; i <= 10; i++){
      std::cout << rand.next() << std::endl;
    }
    return 0;
}
