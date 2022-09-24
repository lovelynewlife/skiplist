## Young men's first SkipList Implementation

----

Guess what did I do when I was "Touching fish" in the lab？

But This is for leveldb learning.

Leveldb Memtable data structure

Also, It's young fellow's first from-scratch cmake project and
test using gtest

### Requirements
**gtest**
```shell
mkdir third_party && cd third_party
git clone https://github.com/google/googletest.git  
```
### Notice
* didn't take concurrency into account, not thread-safe.
* didn't use memory pool, use new operator for simplicity.
* didn't think too much about iterator unvalid during iteration, maybe refer to java's impl later.

### Featurs
* "get(k)" acts just like STL map[k], so you can do l.get(k) = xxx.
* iterator is java style.

### Thoughts
* Writing a general data structure/container is difficult, it's not necessary to do this in real scenarios, design a
special structure for the special case or use other's general implementation(STL).
* Don't think too much about java/go or other modern OO languages when using cpp, cpp reference is not the
same as the reference in those languages, much like a kind of object container in cpp. 

  May see Rust's design concepts later.
* Writing codes along with unit tests, maybe there are too much cases to cover, but still useful to conduct some
tests early.
* Template programming is power but sometimes useless when handling real work, it may distract you from what really matters.


### To be continued
* use std::move and std::forward to get better performance.
* rvalue edition apis.
* bechmark tests.
* some code duplication...

### Reference
Skip Lists: A Probabilistic Alternative to Balanced Tree
