//
// Created by zcy on 2022/9/21.
//

#ifndef SKIPLIST_SKIPLIST_HPP
#define SKIPLIST_SKIPLIST_HPP

#include <random>
#include <cassert>

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

// It's a single key-map, like c++ map(STL container style).
// but the interfaces are java-style, LOL.
template<typename Key, typename Value, int MaxLevel=12>
class skiplist {
 public:
  using KeyType = Key;
  using ValueType = Value;

 private:
  struct Node {
    Key key;
    Value value;
    Node** forward;
    using KeyType = Key;
    using ValueType = Value;

    explicit Node(int level) {
      this->forward = new Node*[level];
    }

    Node(const KeyType &key, const ValueType &value) {
      this->key = key;
      this->value = value;
      this->forward = nullptr;
    }

    Node(const KeyType &key, const ValueType &value, int level):key(key),value(value) {
      assert(level > 0);
      this->forward = new Node*[level];
      for(int i = 0; i < level; i++) {
        this->forward[i] = nullptr;
      }
    }
  };
  using NodeType = Node;
  using NodePtr = NodeType*;

 public:
  struct KVPair {
    KeyType &key;
    ValueType &value;

    KVPair(KeyType &&key, ValueType &&value):key(key), value(value) {}
    KVPair(KeyType &key, ValueType &value):key(key), value(value) {}
  };

  using KVPairType = KVPair;

  explicit skiplist():level(1), _size(0), rand(time(nullptr)){
    // Head Node of the list has a pre-defined max level.
    // use 12 as default from Google/leveldb.
    assert(maxLevel > 0);
    this->head = new NodePtr [maxLevel];
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

  void put(const KeyType &key, const ValueType &value);

  const ValueType & get(const KeyType &key);

  void remove(const KeyType &key);

  void clear();

  bool contains(const KeyType &key) const;

  int size() const {
    return this->_size;
  }

 private:
  static const int maxLevel = MaxLevel;
  int level{};// The level of a skiplist is the max level of nodes in the list.
  int _size{};
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

  NodePtr _upsert(const KeyType &key, const ValueType &value);
  const ValueType & _get(const KeyType &key);

 public:
  class _iterator {
   private:
    NodePtr *access;
    using KVPairType = typename skiplist<KeyType, ValueType, MaxLevel>::KVPair;

   public:
    explicit _iterator(NodePtr *pos) {
      this->access = pos;
    }
    bool hasNext();
    KVPairType next();
  };

  using iterator = _iterator;

  iterator begin() {
    return iterator(this->head);
  }
};


#endif //SKIPLIST_SKIPLIST_HPP
