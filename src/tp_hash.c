#include "tp_hash.h"

#include <string.h>

struct hash_element hash_table[MAX_ELEMENTS];
hash_type Fnv_hash_value(const unsigned char *input)
{
  hash_type hash = FNV_OFFSET_BASIS;
  int length = strlen(input);
  int i = 0;

  for ( i; i < length; ++i) {
    hash = hash * (hash_type)FNV_PRIME;
    hash = hash ^ input[i];
  }

  return hash;
}
