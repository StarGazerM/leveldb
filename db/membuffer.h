//  a thread safe map
#pragma once

#include <map>
#include <string>
#include "leveldb/db.h"

namespace leveldb {
class MemBuffer {

public:
  MemBuffer(uint64_t max_size);
  // find a value by key, return 1 success, 0 fail
  int Find(const Slice& key, std::string* value);


private:
  int _size;

  std::map<Slice, Slice> _map;

  Arena arena_;
};
}  // namespace leveld
