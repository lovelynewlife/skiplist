//
// Created by zcy on 2022/9/21.
//

#include "gtest/gtest.h"
#include <string>
#include "skiplist.hpp"

TEST(exp_test, greeting) {
    std::cout<<"Hello world!\n";
}

struct test_struct{
  int int_value{};
  double double_value{};
  std::string string_value;
};

class test_class{
 private:
  int int_value{};
  double double_value{};
  std::string string_value;
 public:
  void setInt(int v) {
    this->int_value = v;
  }

  int getInt() const {
    return this->int_value;
  }

  void setDouble(double v) {
    this->double_value = v;
  }

  double getDouble() const {
    return this->double_value;
  }

  void setString(const std::string& v) {
    this->string_value = v;
  }

  std::string getString() const {
    return this->string_value;
  }

};

TEST(skiplist_test, init) {
  std::cout << "Test skip list init(construct)\n";
  skiplist<int, int> int2int_list;
  auto it = int2int_list.begin();
  skiplist<std::string, int> string2int_list;
  skiplist<int, test_struct> int2struct_list;
  skiplist<int, int, 24> int2int_list_24;
}
