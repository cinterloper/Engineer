#include "murmur3.h"

#define getblock(p, i) (p[i])
#define ROTL(x, r) (x << r) | (x >> (32 - r));

uint64_t
engineer_hash_murmur3(const void *key, const int32_t len, const uint32_t seed)
{
  const uint8_t* data = (const uint8_t*)key;
  const int nblocks = len / 4;
  int i;

  uint32_t h1 = seed;

  uint32_t c1 = 0xcc9e2d51;
  uint32_t c2 = 0x1b873593;

  // body

  const uint32_t* blocks = (const uint32_t*)(data + nblocks * 4);

  for(i = -nblocks; i; i++)
  {
    uint32_t k1 = getblock(blocks, i);

    k1 *= c1;
    k1 = ROTL(k1, 15);
    k1 *= c2;

    h1 ^= k1;
    h1 = ROTL(h1, 13);
    h1 = h1*5+0xe6546b64;
  }

  // tail

  const uint8_t* tail = (const uint8_t*)(data + nblocks * 4);

  uint32_t k1 = 0;

  switch(len & 3)
  {
  case 3: k1 ^= tail[2] << 16;
  case 2: k1 ^= tail[1] << 8;
  case 1: k1 ^= tail[0];
          k1 *= c1; k1 = ROTL(k1,15 ); k1 *= c2; h1 ^= k1;
  };

  // finalization

  h1 ^= len;

  h1 ^= h1 >> 16;
  h1 *= 0x85ebca6b;
  h1 ^= h1 >> 13;
  h1 *= 0xc2b2ae35;
  h1 ^= h1 >> 16;

  return h1 + ((uint64_t)seed << 32);
}

uint64_t
engineer_hash_from_string(const void *key, uint32_t seed)
{
   return engineer_hash_murmur3(key, strlen(key), seed);
}

