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

// It's a single key-map, like c++ map(STL style).
// but the interfaces are java-style, LOL.
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
      assert(level > 0);
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
  using NodePtr = Node*;

  explicit skiplist():level(0), size(0), rand(time(nullptr)){
    // Head Node of the list has a pre-defined max level.
    // use 12 as default from Google/leveldb.
    assert(maxLevel > 0);
    this->head = new Node*[maxLevel];
    for(int i = 0; i < maxLevel; i++) {
      this->head[i] = nullptr;
    }
  }

  ~skiplist() {
    NodePtr cur = this->head[0];
    while (cur != nullptr) {
      NodePtr del = cur;
      cur = cur->forward[0];
      delete del;
    }
    delete [] this->head;
  }

  void put(KeyType &key, ValueType &value);
  void put(KeyType &&key, ValueType &&value);

  ValueType& get(KeyType &key);

  void remove(KeyType &key);

  void clear();

 private:
  static const int maxLevel = MaxLevel;
  int level{};// The level of a skiplist is the max level of nodes in the list.
  int size{};
  random_util rand;
  NodePtr *head;

  int randomLevel() {
    static const double p = 0.5;
    int newLevel = 1;
    while (this->rand.next() < p && newLevel < maxLevel) {
      newLevel += 1;
    }
    return newLevel;
  }

  class iterator {
   private:
    NodePtr *head;
    using KVPairType = typename skiplist<KeyType, ValueType, MaxLevel>::KVPair;

   public:
    explicit iterator(NodePtr pos) {
      this->head = pos;
    }
    bool hasNext();
    KVPairType next();
  };

 public:
  iterator beginIterator() {
    return iterator(this->head);
  }
};


#endif //SKIPLIST_SKIPLIST_HPP
