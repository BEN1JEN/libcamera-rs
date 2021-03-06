#include "core.hpp"

#include "libcamera-rs/src/bridge.rs.h"

BindMemoryBuffer MemoryBuffer::sub_buffer(size_t offset, size_t length) {
  if (offset > this->length || offset + length > this->length) {
    throw std::runtime_error("Sub buffer out of range of outer buffer.");
  }
  BindMemoryBuffer buffer{
      // The point of this class is to safely wrap raw memory pointers.
      // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
      .inner = std::make_unique<MemoryBuffer>(this->pointer + offset, length)};
  return buffer;
}

rust::Vec<uint8_t> MemoryBuffer::read_to_vec() const {
  rust::Vec<uint8_t> buf;
  buf.reserve(this->length);
  for (size_t i = 0; i < this->length; i++) {
    // The point of this class is to safely wrap raw memory pointers.
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    buf.push_back(this->pointer[i]);
  }
  return buf;
}
