//
// Created by zcy on 2022/9/21.
//

#include "skiplist.hpp"

// skiplist interface implementation.
template <typename Key, typename Value, int  MaxLevel>
void skiplist<Key, Value, MaxLevel>::put(skiplist::KeyType &key, skiplist::ValueType &value) {

}

template <typename Key, typename Value, int  MaxLevel>
void skiplist<Key, Value, MaxLevel>::put(skiplist::KeyType &&key, skiplist::ValueType &&value) {

}

template <typename Key, typename Value, int  MaxLevel>
typename skiplist<Key, Value, MaxLevel>::ValueType & skiplist<Key, Value, MaxLevel>::get(skiplist::KeyType &key) {

}

template <typename Key, typename Value, int MaxLevel>
void skiplist<Key, Value, MaxLevel>::remove(skiplist::KeyType &key) {

}

template <typename Key, typename Value, int MaxLevel>
void skiplist<Key, Value, MaxLevel>::clear() {

}

// skip list iterator implementation.
template<typename Key, typename Value, int MaxLevel>
bool skiplist<Key, Value, MaxLevel>::iterator::hasNext() {
  return true;
}

template<typename Key, typename Value, int MaxLevel>
typename skiplist<Key, Value, MaxLevel>::KVPairType skiplist<Key, Value, MaxLevel>::iterator::next() {

}