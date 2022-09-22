//
// Created by zcy on 2022/9/21.
//

#ifndef SKIPLIST_SKIPLIST_HPP
#define SKIPLIST_SKIPLIST_HPP

#include <random>

class random_util {
 private:
  std::default_random_engine engine;
  std::uniform_real_distribution<double> urd;
 public:
  explicit random_util(unsigned int seed):engine(seed),urd(0,1) {}

  double next() {
    return urd(this->engine);
  }
};

// It's a single key-map like c++ map(STL style).
// but the interfaces are java-style, LOL.
// The level of a skiplist is the max level of nodes in the list.
template<typename Key, typename Value, int MaxLevel=12>
class skiplist {
 public:
  using KeyType = Key;
  using ValueType = Value;

  struct Node {
    Key key;
    Value value;
    Node** forward;
    using KeyType = Key;
    using ValueType = Value;

    explicit Node(int level) {
      this->forward = new Node*[level];
    }

    Node(KeyType &key, ValueType &value) {
      this->key = key;
      this->value = value;
      this->forward = nullptr;
    }

    Node(KeyType &key, ValueType &value, int level) {
      this->key = key;
      this->value = value;
      this->forward = new Node*[level];
    }
  };

  struct KVPair {
    KeyType &key;
    ValueType &value;

    KVPair(KeyType &&key, ValueType &&value):key(key), value(value) {}
    KVPair(KeyType &key, ValueType &value):key(key), value(value) {}
  };

  using NodeType = Node;
  using KVPairType = KVPair;

  explicit skiplist():level(0), size(0) {
    // Head Node of the list has a pre-defined max level.
    // use 12 as default from google/leveldb.
    this->rand = random_util(time(nullptr));
    this->head = new Node(this->maxLevel);
  }

  void put(KeyType &key, ValueType &value);
  void put(KeyType &&key, ValueType &&value);

  ValueType& get(KeyType &key);

  void remove(KeyType &key);

  void clear();

  class iterator {
   private:
    NodeType *head;
    using KVPairType = typename skiplist<KeyType, ValueType, MaxLevel>::KVPair;

   public:
    iterator() {
      this->head = skiplist<KeyType, ValueType>::head;
    }
    bool hasNext();
    KVPairType next();
  };

 private:
  const int maxLevel = MaxLevel;
  int level{};
  int size{};
  random_util rand;
  NodeType *head;

  int randomLevel() {
    //TODO: get a random level for a new list Node.
  }
};


#endif //SKIPLIST_SKIPLIST_HPP
