#include "../include/tpDNS.h"
#include "../include/tpHash.h"

hash_type fnvHash(const unsigned char *input)
{
  hash_type hash = FNV_OFFSET_BASIS;
  int length = strlen(input);
  int i = 0;

  for ( i; i < length; ++i) {
    hash = hash * (hash_type)FNW_PRIIME;
    hash = hash ^ input[i];
  }

  return hash;
}
