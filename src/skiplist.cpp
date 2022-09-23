//
// Created by zcy on 2022/9/21.
//

#include "skiplist.hpp"

template <typename Key, typename Value, int MaxLevel>
inline typename skiplist<Key, Value, MaxLevel>::NodePtr
skiplist<Key, Value, MaxLevel>::_upsert(const KeyType &key, const ValueType &value) {
  assert(this->head != nullptr);
  NodePtr cur = this->head[0];
  // empty list.
  if(cur == nullptr) {
    int newlevel = this->randomLevel();
    auto newNode = new Node(key, value, newlevel);
    for(int i = 0; i < newlevel; i++) {
      this->head[i] = newNode;
    }
    this->level = newlevel;
    this->_size += 1;
    return newNode;
  }else {
    assert(this->level > 0);
    auto *update = new NodePtr[maxLevel];
    for(int i = this->level - 1; i >= 0; i--) {
      while(cur->forward[i] != nullptr && cur->forward[i]->key < key) {
        cur = cur->forward[i];
      }
      update[i] = cur;
    }
    cur = cur->forward[0];
    if(cur != nullptr && cur->key == key) {
      cur->value = value;
      return cur;
    }else {
      int newlevel = this->randomLevel();
      auto newNode = new Node(key, value, newlevel);
      for(int i = 0; i < this->level; i++) {
        cur->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = cur;
      }
      if(newlevel > this->level) {
        for(int i = this->level; i < newlevel; i++) {
          this->head[i] = newNode;
        }
        this->level = newlevel;
      }
      this->_size += 1;
      return newNode;
    }
  }
}

template <typename Key, typename Value, int MaxLevel>
inline const Value &skiplist<Key, Value, MaxLevel>::_get(const KeyType &key) {
    assert(this->head != nullptr);
    NodePtr cur = this->head[0];
    // empty list.
    if(cur == nullptr) {
      // failure, not found insert a new empty value.
      NodePtr node = this->_upsert(key, ValueType());
      return node->value;
    }else {
      assert(this->level > 0);
      auto *update = new NodePtr[maxLevel];
      for(int i = this->level - 1; i >= 0; i--) {
        while(cur->forward[i] != nullptr && cur->forward[i]->key < key) {
          cur = cur->forward[i];
        }
        update[i] = cur;
      }
      cur = cur->forward[0];
      if(cur->key == key) {
        return cur->value;
      }else {
        // failure, not found insert a new empty value.
        NodePtr node = this->_upsert(key, ValueType());
        return node->value;
      }
    }
}

// skiplist interface implementation.
template <typename Key, typename Value, int  MaxLevel>
inline void skiplist<Key, Value, MaxLevel>::put(const KeyType &key, const ValueType &value) {
  this->_upsert(key, value);
}

template <typename Key, typename Value, int  MaxLevel>
inline const typename skiplist<Key, Value, MaxLevel>::ValueType & skiplist<Key, Value, MaxLevel>::get(const KeyType &key) {
  return this->_get(key);
}

template <typename Key, typename Value, int MaxLevel>
inline void skiplist<Key, Value, MaxLevel>::remove(const KeyType &key) {

}

template <typename Key, typename Value, int MaxLevel>
inline void skiplist<Key, Value, MaxLevel>::clear() {

}

template <typename Key, typename Value, int MaxLevel>
bool skiplist<Key, Value, MaxLevel>::contains(const KeyType &key) const {
  return false;
}

// skip list iterator implementation.
template<typename Key, typename Value, int MaxLevel>
inline bool skiplist<Key, Value, MaxLevel>::_iterator::hasNext() {
  return true;
}

template<typename Key, typename Value, int MaxLevel>
inline typename skiplist<Key, Value, MaxLevel>::KVPairType skiplist<Key, Value, MaxLevel>::_iterator::next() {

}