//
// Created by zcy on 2022/9/21.
//

#include "skiplist.hpp"

template <typename Key, typename Value, int MaxLevel>
inline typename skiplist<Key, Value, MaxLevel>::NodePtr
skiplist<Key, Value, MaxLevel>::_upsert(const KeyType &key, const ValueType &value) {
  NodePtr cur = this->_head;
  assert(cur != nullptr);
  NodePtr update[maxLevel];

  for(int i = this->_level - 1; i >= 0; i--) {
    while(cur->getForward()[i] != nullptr && *(cur->getForward()[i]->getKey()) < key) {
      cur = cur->getForward()[i];
    }
    update[i] = cur;
  }

  cur = cur->getForward()[0];
  if(cur!= nullptr && *cur->getKey() == key) {
    cur->setValue(value);
  }else {
    int newlevel = this->randomLevel();
    if(newlevel > this->_level) {
      for(int i = this->_level; i < newlevel; i++) {
        update[i] = this->_head;
      }
      this->_level = newlevel;
    }
    cur = new KVNode(key, value, newlevel);
    for(int i = 0; i < newlevel; i++) {
      cur->getForward()[i] = update[i]->getForward()[i];
      update[i]->getForward()[i] = cur;
    }
    this->_size += 1;
  }
  return cur;
}

template <typename Key, typename Value, int MaxLevel>
inline Value &skiplist<Key, Value, MaxLevel>::_get(const KeyType &key) {
    NodePtr cur = this->_head;
    assert(cur != nullptr);
    NodePtr update[maxLevel];

    for(int i = this->_level - 1; i >= 0; i--) {
      while(cur->getForward()[i] != nullptr && *(cur->getForward()[i]->getKey()) < key) {
        cur = cur->getForward()[i];
      }
      update[i] = cur;
    }

    cur = cur->getForward()[0];
    if(cur!= nullptr && *cur->getKey() == key) {
      return *cur->getValue();
    }else {
      // failure, not found.
      // insert a new empty value.
      int newlevel = this->randomLevel();
      if(newlevel > this->_level) {
        for(int i = this->_level; i < newlevel; i++) {
          update[i] = this->_head;
        }
        this->_level = newlevel;
      }
      cur = new KVNode(key, ValueType(), newlevel);
      for(int i = 0; i < newlevel; i++) {
        cur->getForward()[i] = update[i]->getForward()[i];
        update[i]->getForward()[i] = cur;
      }
      this->_size += 1;
      return *cur->getValue();
    }
}

// skiplist interface implementation.
template <typename Key, typename Value, int  MaxLevel>
inline void skiplist<Key, Value, MaxLevel>::put(const KeyType &key, const ValueType &value) {
  this->_upsert(key, value);
}

template <typename Key, typename Value, int  MaxLevel>
inline typename skiplist<Key, Value, MaxLevel>::ValueType & skiplist<Key, Value, MaxLevel>::get(const KeyType &key) {
  return this->_get(key);
}

template <typename Key, typename Value, int MaxLevel>
inline void skiplist<Key, Value, MaxLevel>::remove(const KeyType &key) {
  NodePtr cur = this->_head;
  assert(cur != nullptr);
  NodePtr update[maxLevel];

  for(int i = this->_level - 1; i >= 0; i--) {
    while(cur->getForward()[i] != nullptr && *(cur->getForward()[i]->getKey()) < key) {
      cur = cur->getForward()[i];
    }
    update[i] = cur;
  }

  cur = cur->getForward()[0];
  assert(cur->getKey() != nullptr);
  if(cur!= nullptr && *(cur->getKey()) == key) {
    for(int i = 0; i < this->_level; i++) {
      if(update[i]->getForward()[i] != cur) {
        break;
      }
      update[i]->getForward()[i] = cur->getForward()[i];
    }
    delete cur;
    this->_size -= 1;
    while(this->_level > 0 && this->_head->getForward()[this->_level - 1] == nullptr) {
      this->_level -= 1;
    }
  }
}

template <typename Key, typename Value, int MaxLevel>
inline void skiplist<Key, Value, MaxLevel>::clear() {
  NodePtr cur = this->_head->getForward()[0];
  while(cur != nullptr) {
    NodePtr del = cur;
    cur = cur->getForward()[0];
    delete del;
  }
  for(int i = 0; i < maxLevel; i++) {
    this->_head->getForward()[i] = nullptr;
  }
  this->_level = 0;
  this->_size = 0;
}

template <typename Key, typename Value, int MaxLevel>
bool skiplist<Key, Value, MaxLevel>::contains(const KeyType &key) const {
  NodePtr cur = this->_head;
  assert(cur != nullptr);

  for(int i = this->_level - 1; i >= 0; i--) {
    while(cur->getForward()[i] != nullptr && *(cur->getForward()[i]->getKey()) < key) {
      cur = cur->getForward()[i];
    }
  }

  cur = cur->getForward()[0];
  if(cur!= nullptr && *cur->getKey() == key) {
    return true;
  }
  return false;
}
template <typename Key, typename Value, int MaxLevel>
Value & skiplist<Key, Value, MaxLevel>::operator[](const KeyType &key) {
  return this->_get(key);
}

// skip list iterator implementation.
template<typename Key, typename Value, int MaxLevel>
inline bool skiplist<Key, Value, MaxLevel>::_iterator::hasNext() {
  return this->pos != nullptr;
}

template<typename Key, typename Value, int MaxLevel>
inline typename skiplist<Key, Value, MaxLevel>::KVPairType skiplist<Key, Value, MaxLevel>::_iterator::next() {
  KVPair ret(*this->pos->getKey(), *this->pos->getValue());
  this->pos = this->pos->getForward()[0];
  return ret;
}