#ifndef _ENGINEER_HASH_MURMUR3_H_
#define _ENGINEER_HASH_MURMUR3_H_

#include <Ecore_Getopt.h>
#include <stdint.h>

uint64_t engineer_hash_murmur3(const void *key, const int64_t len, const uint64_t seed);

#endif
