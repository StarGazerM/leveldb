//  MemBuffer using std's hash map

// Yihao Sun
// 2020 Syracuse

#pragma once

#include "db/dbformat.h"
#include <string>
#include <unordered_map>

#include "leveldb/db.h"

namespace leveldb {
class MemBuffer {
 public:
  explicit MemBuffer(uint64_t max_size);

  // no copy
  MemBuffer(const MemBuffer&) = delete;
  MemBuffer& operator=(const MemBuffer&) = delete;

  // Increase reference count.
  void Ref() { ++refs_; }

  // Drop reference count.  Delete if no more references exist.
  void Unref() {
    --refs_;
    assert(refs_ >= 0);
    if (refs_ <= 0) {
      delete this;
    }
  }

  // basic operation but in levelDB's code flavor

  void Find(const Slice& key, std::string* value);
  void Add(const Slice& key, const Slice& val);
  bool Get(const LookupKey& key, std::string* value, Status* s);

  // return approximate memory usage
  // TODO: need more precise overhead
  size_t ApproximateMemoryUsage();

 private:

  size_t refs_;
  uint64_t _size;
  uint64_t _max_size;

  std::unordered_map<std::string, std::string> _map;
};
}  // namespace leveldb
