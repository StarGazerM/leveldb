
#include "membuffer.h"

namespace leveldb {

MemBuffer::MemBuffer(uint64_t max_size) {
    this->_size = max_size;
}

}