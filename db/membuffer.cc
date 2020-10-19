//  MemBuffer using std's hash map

// Yihao Sun
// 2020 Syracuse

#include "membuffer.h"

#include "util/coding.h"

namespace leveldb {

MemBuffer::MemBuffer(uint64_t max_size) {
  this->_size = 0;
  this->_max_size = max_size;
}

void MemBuffer::Add(const Slice& key, const Slice& val) {
  // update size
  size_t key_size = key.size();
  size_t val_size = val.size();
  size_t internal_key_size = key_size + 8;
  // this is just a approximation, in reality should be change to
  // std::unorder_map's overhead
  const size_t encoded_len = VarintLength(internal_key_size) +
                             internal_key_size + VarintLength(val_size) +
                             val_size;
  _size = _size + encoded_len;
  _map[key.ToString()] = val.ToString();
}

size_t MemBuffer::ApproximateMemoryUsage() { return _size; }

bool MemBuffer::Get(const LookupKey& key, std::string* value, Status* s) {
  std::string memkey_str = key.memtable_key().ToString();

  if (_map.find(memkey_str) != _map.end()) {
    value->assign(_map[memkey_str]);
    return true;
  } else {
    return false;
  }
}

void MemBuffer::Remove(const Slice& key) {
  _map.erase(key.ToString());
}

void MemBuffer::Drain(MemTable* memtable) {
  
}

}  // namespace leveldb