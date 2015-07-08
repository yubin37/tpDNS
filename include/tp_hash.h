/******************************************************************************
 * 该文件提供哈希表数据结构，并提供哈希表的增、删、改、查的接口。哈希算法为
 * fnv hash
 * Author: Eric Yang
 * Date: 2015-07-08
 * Email: yubin@cnyubin.com
 * ***************************************************************************/
#ifndef TPDNS_TP_HASH_INCLUDE_H_
#define TPDNS_TP_HASH_INCLUDE_H_

#include <stdint.h>

#define FNV_OFFSET_BASIS   0xcbf29ce484222325
#define FNV_PRIME          0x100000001b3
#define SLOT_NUMBER        997

#define MAX_ELEMENTS       256

typedef  uint64_t  hash_type;

struct element {
  char name[256];
  char **rr;
  char **value;
}

struct hash_element {
  int num;
  struct element *p;
}

extern struct hash_element hash_table[];

/******************************************************************************
 * 该函数将传入的字符串，根据fnv hash算法，将其转化为64位的整型数值
 * @input: 待转化的字符串值
 * 返回值: 字符串值对应的64位整数。
 * ***************************************************************************/
hash_type Fnv_hash_value(const unsigned char *input);

/******************************************************************************
 * 初始化
int Init_hash_table(void);
#endif
