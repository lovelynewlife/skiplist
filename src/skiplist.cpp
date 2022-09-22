//
// Created by zcy on 2022/9/21.
//

#include "skiplist.hpp"

// skiplist interface implementation.
template <typename Key, typename Value, int  MaxLevel>
inline void skiplist<Key, Value, MaxLevel>::put(skiplist::KeyType &key, skiplist::ValueType &value) {

}

template <typename Key, typename Value, int  MaxLevel>
inline void skiplist<Key, Value, MaxLevel>::put(skiplist::KeyType &&key, skiplist::ValueType &&value) {

}

template <typename Key, typename Value, int  MaxLevel>
inline const typename skiplist<Key, Value, MaxLevel>::ValueType & skiplist<Key, Value, MaxLevel>::get(skiplist::KeyType &key) const {

}

template <typename Key, typename Value, int  MaxLevel>
inline const typename skiplist<Key, Value, MaxLevel>::ValueType & skiplist<Key, Value, MaxLevel>::get(skiplist::KeyType &&key) const {

}

template <typename Key, typename Value, int MaxLevel>
inline void skiplist<Key, Value, MaxLevel>::remove(skiplist::KeyType &key) {

}

template <typename Key, typename Value, int MaxLevel>
inline void skiplist<Key, Value, MaxLevel>::remove(skiplist::KeyType &&key) {

}

template <typename Key, typename Value, int MaxLevel>
inline void skiplist<Key, Value, MaxLevel>::clear() {

}

// skip list iterator implementation.
template<typename Key, typename Value, int MaxLevel>
inline bool skiplist<Key, Value, MaxLevel>::_iterator::hasNext() {
  return true;
}

template<typename Key, typename Value, int MaxLevel>
inline typename skiplist<Key, Value, MaxLevel>::KVPairType & skiplist<Key, Value, MaxLevel>::_iterator::next() {

}