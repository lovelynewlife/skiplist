//
// Created by zcy on 2022/9/21.
//

#include "gtest/gtest.h"
#include <string>
#include "skiplist.cpp"
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

TEST(skiplist_test, basic_put_get) {
  std::cout << "Test skip list basic put get\n";
  skiplist<int, int> l;
  l.put(1,1);
  l.put(2,2);
  int v = l.get(1);
  ASSERT_EQ(v, 1);
  int k = 2;
  v = l.get(k);
  ASSERT_EQ(v, 2);
  v = 3;
  int vg = l.get(k);
  ASSERT_EQ(vg, 2);

  int k4 = 4;
  int v5 = 5;
  l.put(k4, 4);
  ASSERT_EQ(l.get(k4), 4);
  l.put(k4,v5);
  ASSERT_EQ(l.get(k4), 5);
}
