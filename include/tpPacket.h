#ifndef _TP_DNS_TP_PACKET_INCLUDE_H_
#define _TP_DNS_TP_PACKET_INCLUDE_H_

#include <stdint.h>
#include <stdlib.h>


#define QR_MASK                        0x80
#define OPCODE_MASK                    0x78
#define AA_MASK                        0x04
#define TC_MASK                        0x02
#define RD_MASK                        0x01
#define RA_MASK                        0x80


#define RCODE_MASK                     0x0f
#define RCODE_NO_ERROR                 0x01
#define RCODE_FORMAT_ERROR             0x02
#define RCODE_SERVER_FAILURE           0x03
#define RCODE_NOT_IMPLEMENTED          0x04
#define RCODE_RESUSED                  0x05

#define RR_TYPE_A_RECORD               0x0001
#define RR_TYPE_MX_RECORD              0x000f
#define RR_TYPE_NS_RECORD              0x0002

#define RD_DATA_TYPE_A_RECORD          0x0001
#define RD_DATA_TYPE_CNAME             0x0005
#define RD_DATA_TYPE_NAME_SERVER       0x0002
#define RD_DATA_TYPE_MAIL_SERVER       0x000f

#define GET_QR(x)                      \
                   (((unsigned char)(x) & QR_MASK) >> 7)
#define GET_OPCODE(x)                  \
                   (((unsigned char)(x) & OPCODE_MASK) >> 3)
#define GET_AA(x)                      \
                   (((unsigned char)(x) & AA_MASK) >> 2)
#define GET_TC(x)                      \
                   (((unsigned char)(x) & TC_MASK) >> 1)
#define GET_RD(x)                      \
                   ((unsigned char)(x)  & RD_MASK)
#define GET_RA(x)                      \
                   (((unsigned char)(x) & RA_MASK) >> 7)
#define GET_RCODE(x)                   \
                   (((unsigned char)(x)) & 0x0f)

#define GET_NUMBER_FROM_TWO_BYTES(x, y)            \
                   (((uint16_t)(x) << 8) + ((uint16_t)(y)))
#define GET_NUMBER_FROM_FOUR_BYTES(x, y, z, v)     \
                   (((uint32_t)(x) << 24) + ((uint32_t)(y) << 16) \
                   + ((uint32_t)(z) << 8) + ((uint32_t)(v)))

#define DOMAIN_NAME_LENGTH    256 

struct packetMessage{
  uint16_t          id;

  unsigned char     qr : 1;
  unsigned char     opcode : 4;
  unsigned char     aa : 1;
  unsigned char     tc : 1;
  unsigned char     rd : 1;
  unsigned char     ra : 1;

  unsigned char     rcode : 4; 
  unsigned char     reserved : 4;
  
  uint16_t          qdCount;
  uint16_t          anCount;
  uint16_t          nsCount;
  uint16_t          arCount;

  struct packetQuestion*  question;
  struct packetAnswer*    answer;
};

struct packetQuestion{
  uint16_t                   qType;
  uint16_t                   qClass;
  char                       qName[DOMAIN_NAME_LENGTH];
  struct packetQuestion      *next;
};

struct mailServer {
  uint16_t                   preference;
  char                       name[DOMAIN_NAME_LENGTH];
};
  
struct packetAnswer{
  char                       aName[DOMAIN_NAME_LENGTH];
  uint16_t                   rdType;
  uint16_t                   aClass;
  uint32_t                   aTTL;
  uint16_t                   rdLength;
  struct packetAnswer        *next;

  union {
    uint32_t                 ip;
    char                     aName[DOMAIN_NAME_LENGTH];
    struct mailServer        name;
  }rdData;
};

extern int getDnsMessage(const char* message, struct packetMessage **packet);
extern int freePacketMessage(struct packetMessage *packet);
extern int getName(char *dst, const char *src, size_t maxLength);
#endif
