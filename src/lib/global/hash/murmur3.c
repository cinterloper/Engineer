#include "murmur3.h"

#define getblock(p, i) (p[i])
#define BIG_CONSTANT(x) (x##LLU)
#define ROTL(x, r) (x << r) | (x >> (64 - r));

uint64_t engineer_hash_murmur3(const void *key, const int64_t len, const uint64_t seed)
{
  const uint8_t * data = (const uint8_t*)key;
  const int nblocks = len / 8;
  int i;

  uint64_t h1 = seed;

  uint64_t c1 = BIG_CONSTANT(0x87c37b91114253d5);
  uint64_t c2 = BIG_CONSTANT(0x4cf5ad432745937f);

  // Body
  const uint64_t * blocks = (const uint64_t *)(data);

  for(i = 0; i < nblocks; i++)
  {
    uint64_t k1 = getblock(blocks,i*2+0);

    k1 *= c1;
    k1  = ROTL(k1, 31);
    k1 *= c2;

    h1 ^= k1;
    h1 = ROTL(h1, 27);
    h1 = h1 * 5 + 0x52dce729;
  }

  // Tail
  const uint8_t * tail = (const uint8_t*)(data + nblocks*8);

  uint64_t k1 = 0;

  switch(len & 7)
  {
  case  7: k1 ^= (uint64_t)(tail[ 6]) << 48;
  case  6: k1 ^= (uint64_t)(tail[ 5]) << 40;
  case  5: k1 ^= (uint64_t)(tail[ 4]) << 32;
  case  4: k1 ^= (uint64_t)(tail[ 3]) << 24;
  case  3: k1 ^= (uint64_t)(tail[ 2]) << 16;
  case  2: k1 ^= (uint64_t)(tail[ 1]) << 8;
  case  1: k1 ^= (uint64_t)(tail[ 0]) << 0;
           k1 *= c1; k1  = ROTL(k1, 31); k1 *= c2; h1 ^= k1;
  };

  // Finalization.
  h1 ^= len;

  h1 ^= h1 >> 33;
  h1 *= BIG_CONSTANT(0xff51afd7ed558ccd);
  h1 ^= h1 >> 33;
  h1 *= BIG_CONSTANT(0xc4ceb9fe1a85ec53);
  h1 ^= h1 >> 33;

  return h1;
}
