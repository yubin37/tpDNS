#ifndef _TP_DNS_HASH_INCLUDE_H_
#define _TP_DNS_HASH_INCLUDE_H_

#include <stdint.h>
#define FNV_OFFSET_BASIS   0xcbf29ce484222325
#define FNV_PRIME          0x100000001b3
#define SLOT_NUMBER        997

typedef  uint64_t  hash_type;

typedef struct {
} hash_element;
// fnv hash function
extern hash_type fnvHash(const unsigned char *input);
#endif
