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
  // these Node classes are designed to not store k&v in head node.
  class Node {
 private:
    Node **forward;
   public:
    Node() {
      this->forward = nullptr;
    }
    ~Node() {
      delete [] forward;
    }
    explicit Node(int level) {
      assert(level > 0);
      this->forward = new Node *[level];
      for(int i = 0; i < level; i++) {
        this->forward[i] = nullptr;
      }
    }
    virtual KeyType* getKey() {
      return nullptr;
    }

    virtual ValueType* getValue() {
      return nullptr;
    }

    virtual void setValue(ValueType value) {}

    virtual Node** getForward(){
      return this->forward;
    }

  };

  using NodeType = Node;
  using NodePtr = NodeType *;

  class KVNode: public Node{
   private:
    Key key;
    Value value;
    using KeyType = Key;
    using ValueType = Value;

   public:

    KVNode(const KeyType &key, const ValueType &value, int level):key(key), value(value), Node(level) {}

    KeyType* getKey() {
      return &this->key;
    }

    ValueType* getValue() {
      return &this->value;
    }

    void setValue(ValueType v){
      this->value = v;
    }
  };

  struct KVPair {
   private:
    KeyType &_key;
    ValueType &_value;
   public:
    KVPair(KeyType &key, ValueType &value):_key(key), _value(value) {}
    KeyType & key() {
      return this->_key;
    }
    ValueType & value() {
      return this->_value;
    }
  };

  using KVPairType = KVPair;

 public:

  explicit skiplist(): _level(0), _size(0), _rand(time(nullptr)){
    // Head KVNode of the list has a pre-defined max _level.
    // use 12 as default from Google/leveldb.
    assert(maxLevel > 0);
    this->_head = new Node(maxLevel);
  }

  // shallow copy, because level is not stored in Node type.

  // move constructor.
  skiplist(skiplist<KeyType, ValueType, MaxLevel> &&other) noexcept {
    this->_head = other._head;
    this->_level = other._level;
    this->_size = other._size;
    this->_rand = random_util(time(nullptr));
    assert(maxLevel > 0);
    this->_head = new Node(maxLevel);
  }

  ~skiplist() {
    NodePtr cur = this->_head;
    while (cur != nullptr) {
      NodePtr del = cur;
      cur = cur->getForward()[0];
      delete del;
    }
  }

  void put(const KeyType &key, const ValueType &value);

  ValueType & get(const KeyType &key);

  ValueType & operator [](const KeyType &key);

  void remove(const KeyType &key);

  void clear();

  bool contains(const KeyType &key) const;

  int size() const {
    return this->_size;
  }

  int level() const {
    return this->_level;
  }

 private:
  static const int maxLevel = MaxLevel;
  int _level{};// The _level of a skiplist is the max _level of nodes in the list.
  int _size{};
  random_util _rand;
  NodePtr _head;

  int randomLevel() {
    static const double p = 0.5;
    int newLevel = 1;
    while (this->_rand.next() < p && newLevel < maxLevel) {
      newLevel += 1;
    }
    return newLevel;
  }

  NodePtr _upsert(const KeyType &key, const ValueType &value);
  ValueType & _get(const KeyType &key);

 public:
  class _iterator {
   private:
    NodePtr pos;
    using KVPairType = typename skiplist<KeyType, ValueType, MaxLevel>::KVPair;

   public:
    explicit _iterator(NodePtr pos) {
      this->pos = pos;
    }
    bool hasNext();
    KVPairType next();
  };

  using iterator = _iterator;

  iterator begin() {
    return iterator(this->_head->getForward()[0]);
  }
};


#endif //SKIPLIST_SKIPLIST_HPP
