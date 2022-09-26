//
// Created by zcy on 2022/9/21.
//

#include "gtest/gtest.h"
#include <string>
#include "skiplist.cpp"
#include "skiplist.hpp"

#define TITLE(test) std::cout<<"--Test "#test".\n";
#define PASS std::cout<<"..PASS.\n";
#define CHECK(check) std::cout<<"--Check "#check"...\n";

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
  test_class(): int_value(), double_value(), string_value() {}
  test_class(int i, double d, std::string s): int_value(i), double_value(d), string_value(std::move(s)) {}
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

TEST(basic_test, init) {
  TITLE(init(construct))
  skiplist<int, int> int2int_list;
  skiplist<std::string, int> string2int_list;
  skiplist<int, test_struct> int2struct_list;
  skiplist<int, int, 24> int2int_list_24;
  PASS
}

TEST(basic_test, basic_put) {
  TITLE(basic put)
  skiplist<int, int> l;
  // check pointers point to the proper addr.
  // no segmentation fault crash.
  l.put(2,2);
  l.put(1, 1);
  l.put(3, 3);
  l.put(4,4);

  PASS
}

TEST(basic_test, basic_put_get) {
  TITLE(basic put get)
  skiplist<int, int> l;
  l.put(2,2);
  l.put(1,1);
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
  int v4 = l.get(k4);
  ASSERT_EQ(v4, 4);
  l.put(k4,v5);
  ASSERT_EQ(l.get(k4), 5);

  int k6 = 6;
  ASSERT_EQ(l.get(k6), 0);

  l.put(0,1);
  l.put(6,6);
  l.put(7,7);
  ASSERT_EQ(l.get(0), 1);
  ASSERT_EQ(l.get(6), 6);
  ASSERT_EQ(l.get(7), 7);

  CHECK(size)
  ASSERT_EQ(l.size(), 6);

  PASS
}

TEST(basic_test, basic_contains) {
  TITLE(basic contains)
  skiplist<int, int> l;
  l.put(2,2);
  l.put(1, 1);
  l.put(3, 3);
  l.get(6);
  l.put(4,4);
  ASSERT_EQ(l.contains(1), true);
  ASSERT_EQ(l.contains(2), true);
  ASSERT_EQ(l.contains(3), true);
  ASSERT_EQ(l.contains(4), true);
  ASSERT_EQ(l.contains(6), true);
  ASSERT_EQ(l.contains(0), false);
  CHECK(size)
  ASSERT_EQ(l.size(), 5);
  PASS
}

TEST(basic_test, basic_remove) {
  TITLE(basic remove)
  skiplist<int, int> l;
  l.put(2,2);
  std::cout<<"level: "<<l.level()<<std::endl;
  l.put(1, 1);
  std::cout<<"level: "<<l.level()<<std::endl;
  l.put(3, 3);
  std::cout<<"level: "<<l.level()<<std::endl;
  ASSERT_EQ(l.contains(1), true);
  ASSERT_EQ(l.contains(2), true);
  ASSERT_EQ(l.contains(3), true);
  l.remove(1);
  l.remove(3);
  l.remove(2);
  ASSERT_EQ(l.contains(3), false);
  CHECK(remove all size)
  ASSERT_EQ(l.size(), 0);

  ASSERT_EQ(l.get(3), 0);

  l.put(4, 4);
  l.clear();
  ASSERT_EQ(l.contains(3), false);
  ASSERT_EQ(l.contains(1), false);
  CHECK(clear size)
  ASSERT_EQ(l.size(), 0);
  PASS
}

TEST(class2struct_test, put_get) {
  TITLE(string2struct put get)
  skiplist<std::string , test_struct> l;
  l.put("1",test_struct{1,1,"1"});
  l.put("2",test_struct{2,2,"2"});
  test_struct v = l.get("1");
  ASSERT_EQ(v.string_value, "1");
  std::string k = "2";
  v = l.get(k);
  ASSERT_EQ(v.int_value, 2);
  v.int_value = 3;
  ASSERT_EQ(l.get(k).int_value, 2);
  test_struct &vg = l.get(k);
  vg.int_value = 3;
  ASSERT_EQ(l.get(k).int_value, 3);

  std::string k4 = "4";
  test_struct v5 = test_struct{5, 5, "5"};
  l.put(k4, test_struct{4,4,"4"});
  test_struct v4 = l.get(k4);
  ASSERT_EQ(v4.int_value, 4);
  l.put(k4,v5);
  ASSERT_EQ(l.get(k4).int_value, 5);

  std::string k6 = "6";
  ASSERT_EQ(l.get(k6).int_value, 0);

  l.put("0",test_struct{1,1,"1"});
  l.put("6",test_struct{6,6,"6"});
  l.put("7",test_struct{7,7,"7"});
  ASSERT_EQ(l.get("0").int_value, 1);
  ASSERT_EQ(l.get("6").int_value, 6);
  ASSERT_EQ(l.get("7").int_value, 7);

  CHECK(size)
  ASSERT_EQ(l.size(), 6);

  PASS
}

TEST(class2struct_test, remove_contains) {
  TITLE(string2struct remove&contains)
  skiplist<std::string , test_struct> l;
  l.put("2",test_struct{2,2,"2"});
  std::cout<<"level: "<<l.level()<<std::endl;
  l.put("1",test_struct{1,1,"1"});
  std::cout<<"level: "<<l.level()<<std::endl;
  l.put("3",test_struct{3,3,"3"});
  std::cout<<"level: "<<l.level()<<std::endl;
  ASSERT_EQ(l.contains("1"), true);
  ASSERT_EQ(l.contains("2"), true);
  ASSERT_EQ(l.contains("3"), true);
  l.remove("1");
  l.remove("3");
  l.remove("2");
  ASSERT_EQ(l.contains("3"), false);
  CHECK(remove all size)
  ASSERT_EQ(l.size(), 0);

  ASSERT_EQ(l.get("3").int_value, 0);

  l.put("4", test_struct{4,4,"4"});
  l.clear();
  ASSERT_EQ(l.contains("3"), false);
  ASSERT_EQ(l.contains("1"), false);
  CHECK(clear size)
  ASSERT_EQ(l.size(), 0);
  PASS
}

TEST(class2class_test, put_get) {
  TITLE(string2class put get)
  skiplist<std::string , test_class> l;
  l.put("1",test_class{1,1,"1"});
  l.put("2",test_class{2,2,"2"});
  test_class v = l.get("1");
  ASSERT_EQ(v.getString(), "1");
  std::string k = "2";
  v = l.get(k);
  v.setInt(3);
  ASSERT_EQ(l.get(k).getInt(), 2);
  test_class &vg = l.get(k);
  vg.setInt(3);
  ASSERT_EQ(l.get(k).getInt(), 3);

  std::string k4 = "4";
  test_class v5 = test_class{5, 5, "5"};
  l.put(k4, test_class{4,4,"4"});
  test_class v4 = l.get(k4);
  ASSERT_EQ(v4.getInt(), 4);
  l.put(k4,v5);
  ASSERT_EQ(l.get(k4).getInt(), 5);

  std::string k6 = "6";
  ASSERT_EQ(l.get(k6).getInt(), 0);

  l.put("0",test_class{1,1,"1"});
  l.put("6",test_class{6,6,"6"});
  l.put("7",test_class{7,7,"7"});
  ASSERT_EQ(l.get("0").getInt(), 1);
  ASSERT_EQ(l.get("6").getInt(), 6);
  ASSERT_EQ(l.get("7").getInt(), 7);

  CHECK(size)
  ASSERT_EQ(l.size(), 6);

  PASS
}

TEST(class2class_test, remove_contains) {
  TITLE(string2class remove&contains)
  skiplist<std::string, test_class> l;
  l.put("2",test_class{2,2,"2"});
  std::cout<<"level: "<<l.level()<<std::endl;
  l.put("1",test_class{1,1,"1"});
  std::cout<<"level: "<<l.level()<<std::endl;
  l.put("3",test_class{3,3,"3"});
  std::cout<<"level: "<<l.level()<<std::endl;
  ASSERT_EQ(l.contains("1"), true);
  ASSERT_EQ(l.contains("2"), true);
  ASSERT_EQ(l.contains("3"), true);
  l.remove("1");
  l.remove("3");
  l.remove("2");
  ASSERT_EQ(l.contains("3"), false);
  CHECK(remove all size)
  ASSERT_EQ(l.size(), 0);
  
  ASSERT_EQ(l.get("3").getInt(), 0);

  l.put("4", test_class{4,4,"4"});
  l.clear();
  ASSERT_EQ(l.contains("3"), false);
  ASSERT_EQ(l.contains("1"), false);
  CHECK(clear size)
  ASSERT_EQ(l.size(), 0);
  PASS
}

TEST(iterator_test, basic_iterate) {
  TITLE(test iterator basic)
  skiplist<std::string, test_class> l;
  l.put("2",test_class{2,2,"2"});
  l.put("1",test_class{1,1,"1"});
  l.put("3",test_class{3,3,"3"});
  auto it = l.begin();
  std::string res;
  while (it.hasNext()) {
    res += it.next().value().getString();
  }
  ASSERT_EQ(res, "123");
  l.remove("1");
  l.remove("3");
  res = "";
  it = l.begin();
  while(it.hasNext()) {
    res += it.next().value().getString();
  }
  ASSERT_EQ(res, "2");

  res = "";
  l.clear();
  it = l.begin();
  while (it.hasNext()) {
    res += it.next().value().getString();
  }
  ASSERT_EQ(res, "");
  res = "";
  l.put("2",test_class{2,2,"2"});
  l.put("1",test_class{1,1,"1"});
  l.put("3",test_class{3,3,"3"});
  l.get("4");
  it = l.begin();
  while(it.hasNext()) {
    res += it.next().value().getString();
  }
  ASSERT_EQ(res, "123");
  CHECK(size)
  ASSERT_EQ(l.size(), 4);
  PASS
}

TEST(iterator_test, iterator_valid_guarantee) {
  TITLE(test iterator valid gurantee)
  skiplist<std::string, test_class> l;
  l.put("2",test_class{2,2,"2"});
  l.put("1",test_class{1,1,"1"});
  l.put("3",test_class{3,3,"3"});
  auto it = l.begin();
  // iterate to set value.
  std::string res;
  while (it.hasNext()) {
    it.next().value().setString("0");
  }
  it = l.begin();
  while (it.hasNext()) {
    res += it.next().value().getString();
  }
  ASSERT_EQ(res, "000");

  it = l.begin();
  res = "";
  while (it.hasNext()) {
    // use ref type to hold the obj.
    test_class & t = it.next().value();
    t.setString("1");
  }
  it = l.begin();
  while (it.hasNext()) {
    res += it.next().value().getString();
  }
  ASSERT_EQ(res, "111");

  // iterate to remove every key.
  it = l.begin();
  while (it.hasNext()) {
    auto key = it.next().key();
    l.remove(key);
  }
  res = "";
  it = l.begin();
  while (it.hasNext()) {
    res += it.next().value().getString();
  }
  ASSERT_EQ(res, "");

  l.clear();
  l.put("0",test_class{0,0,"0"});
  l.put("2",test_class{2,2,"2"});
  res = "";
  std::string k5 = "5";
  it = l.begin();
  while (it.hasNext()) {
    res += it.next().value().getString();
    l.put("1",test_class{1,1,"1"});
    l.put("2",test_class{8,8,"8"});
    l["3"] = test_class{3,3,"3"};
    l.put("4",test_class{4,4,"4"});
    l[k5] = test_class{5,5,"5"};
  }
  ASSERT_EQ(res, "08345");
  PASS
}