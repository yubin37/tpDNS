#include "tpPacket.h"
#include <stdlib.h>

int getDnsMessage(const char* message, struct packetMessage **packet)
{
  struct packetMessage *temp;
  temp = (struct packetMessage*)calloc(1, sizeof(struct packetMessage));
  if (temp == NULL) {
    return -1;
  }
  unsigned char *ptr = (unsigned char *)message;

  temp->id = GET_NUMBER_FROM_TWO_BYTES(*ptr, *(ptr + 1)); 
  ptr += 2; 

  temp->qr = GET_QR(*ptr);
 
  temp->opcode = GET_OPCODE(*ptr);
 
  temp->aa = GET_AA(*ptr);

  temp->tc = GET_TC(*ptr);

  temp->rd = GET_RD(*ptr++);
 
  temp->ra = GET_RA(*ptr);
  
  temp->rcode = GET_RCODE(*ptr++);

  temp->qdCount = GET_NUMBER_FROM_TWO_BYTES(*ptr, *(ptr + 1));
  ptr += 2;

  temp->anCount = GET_NUMBER_FROM_TWO_BYTES(*ptr, *(ptr + 1));
  ptr += 2;

  temp->nsCount = GET_NUMBER_FROM_TWO_BYTES(*ptr, *(ptr + 1));
  ptr += 2;

  temp->arCount = GET_NUMBER_FROM_TWO_BYTES(*ptr, *(ptr + 1));
  ptr += 2;

  struct question *question;
  question = (struct question*)calloc(1, sizeof(struct question));
  if (question == NULL) {
    return -1;
  }

  int length = getName(question->qName, ptr, DOMAIN_NAME_LENGTH);
  ptr += length;


  question->qType = GET_NUMBER_FROM_TWO_BYTES(*ptr, *(ptr + 1));
  ptr += 2;
 
  question->qClass = GET_NUMBER_FROM_TWO_BYTES(*ptr, *(ptr + 1));
  ptr += 2;

  question->next = NULL;

  temp->question = question;
 
 
  *packet = temp;
  return 0;
} 

int freePacketMessage(struct packetMessage *packet)
{
  struct question *question = packet->question;
  while(question != NULL) {
    struct question *temp = question->next;
    free(question);
    question = temp;
  }

  struct answer *answer = packet->answer;
  while(answer != NULL) {
    struct answer *temp = answer->next;
    free(answer);
    answer = temp;
  }
 
  free(packet);
  packet = NULL;
  return 0;
} 

int getName(char *dst, const char  *src, size_t maxLength)
{
  const char *ptr = src;
  size_t nameLength = 0;  
  unsigned short labelLength = 0;
  while ((labelLength = (unsigned short)(*ptr++)) != 0) {
    unsigned short i;
    for (i = 0; 
         i < labelLength && nameLength < maxLength; 
         i++) {
      dst[nameLength++] = *ptr++;
    }
    dst[nameLength++] = '.';
  }
  return ptr - src;
}
