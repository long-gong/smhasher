//  header file Tabulation.h, which provides a simple implementation for
//  Tabulation hashing schemes described in the paper "Fast and Powerful Hashing
//  using Tabulation"

#ifndef TABULATION_HASH_H_
#define TABULATION_HASH_H_

#include <stdlib.h>  // for size_t.
#include <utility>

// Microsoft Visual Studio may not have stdint.h.
#if defined(_MSC_VER) && (_MSC_VER < 1600)
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef unsigned __int64 uint64_t;
#else  // defined(_MSC_VER)
#include <stdint.h>
#endif // !defined(_MSC_VER)

typedef uint8_t uint8;
typedef uint32_t uint32;
typedef uint64_t uint64;

struct uint128 {
  uint64 high;
  uint64 low;
  uint128() : high(0U), low(0U){ }
  uint128(uint64 h, uint64 l) : high(h), low(l){ }
  uint128& operator^=(const uint128& other) {
    this->high ^= other.high;
    this->low ^= other.low;
    return (*this);
  }
  const uint128& operator^=(const uint128& other) {
    this->high ^= other.high;
    this->low ^= other.low;
    return (*this);
  }
};


uint128 operator^(const uint128& a, const uint128& b) {
  return uint128{a.high ^ b.high, a.low ^ b.low};
}

uint32 SimpleTab32(uint32 key, const uint32[4][256] H){
  uint32 i;
  uint32 h = 0;
  uint8 c;
  for(i = 0;i < 4;i ++) {
    c = key;
    h ^= H[i][c];
    key = key >> 8;
  }
  return h;
}

uint64 SimpleTab64(uint64 key, const uint64[8][256] H){
  uint32 i;
  uint64 h = 0;
  uint8 c;
  for(i = 0;i < 8;i ++) {
    c = key;
    h ^= H[i][c];
    key = key >> 8;
  }
  return h;
}

uint32 TwistedTab32(uint32 key, const uint64[4][256] H){
  uint32 i;
  uint64 h = 0;
  uint8 c;
  for(i = 0;i < 3;i ++){
    c = key;
    h ^= H[i][c];
    key = key >> 8;
  }
  c = key^h;
  h ^= H[i][c];
  h >>= 32;
  return ((uint32) h);
}


uint64 TwistedTab64(uint64 key, const uint128[8][256] H){
  uint32 i;
  uint128 h{0, 0};
  uint8 c;
  for(i = 0;i < 7;i ++){
    c = key;
    h ^= H[i][c].first;
    key = key >> 8;
  }
  c = x^h.low;
  h ^= H[i][c];
  return h.high;
}

#endif // TABULATION_HASH_H_
