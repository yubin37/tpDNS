#ifndef _TP_DNS_HASH_INCLUDE_H_
#define _TP_DNS_HASH_INCLUDE_H_

#define FNV_OFFSET_BASIS   0xcbf29ce484222325
#define FNV_PRIME          0x100000001b3

// fnv hash function
hash_type fnvHash(const unsigned char *input);
#endif
