#include "tp_packet.h"
#include <stdlib.h>
#include <syslog.h>
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

  struct packetQuestion *question;
  question = (struct packetQuestion*)calloc(1, 
                     sizeof(struct packetQuestion));
  if (question == NULL) {
    syslog(LOG_ERR, "calloc packetQuestion struct error "
                    "in Method getDnsMessage");
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
 
  struct packetAnswer *answerPtr =  temp->answer;
  int i = 0;
  for (i; i < temp->anCount; i++) {
    struct packetAnswer *answer = (struct packetAnswer*)calloc(1,
                        sizeof(struct packetAnswer));
    if (answer == NULL) {
      syslog(LOG_ERR, "calloc packetAnswer struct error "
                      "in Method getDnsMessage");
      return -1;
    }

    length = getName(answer->aName, ptr, DOMAIN_NAME_LENGTH);
    ptr += length;
    
    answer->rdType = GET_NUMBER_FROM_TWO_BYTES(*ptr, *(ptr + 1));
    ptr += 2;

    answer->aClass = GET_NUMBER_FROM_TWO_BYTES(*ptr, *(ptr + 1));
    ptr += 2;

    answer->aTTL = GET_NUMBER_FROM_FOUR_BYTES(*ptr, *(ptr + 1),
                                              *(ptr + 2), *(ptr + 3));
    ptr += 4;
    
    answer->rdLength = GET_NUMBER_FROM_TWO_BYTES(*ptr, *(ptr + 1));
    ptr += 2;
    
    switch(answer->rdType) {
    case RD_DATA_TYPE_A_RECORD:
      answer->rdData.ip = GET_NUMBER_FROM_FOUR_BYTES(*ptr, *(ptr + 1),
                           *(ptr + 2), *(ptr + 3));
      ptr += 4;
      break;  
    case RD_DATA_TYPE_CNAME:
    case RD_DATA_TYPE_NAME_SERVER:
      length = getName(answer->rdData.aName, ptr, DOMAIN_NAME_LENGTH);
      ptr += length;
      break;
    case RD_DATA_TYPE_MAIL_SERVER:
      answer->rdData.name.preference = 
          GET_NUMBER_FROM_TWO_BYTES(*ptr, *(ptr + 1));
      ptr += 2;
      length = getName(answer->rdData.name.name, ptr, DOMAIN_NAME_LENGTH);
      ptr += length;
      break;
    }
    
    answer->next = NULL;
    answerPtr->next = answer;
    answerPtr = answer;
  }
  *packet = temp;
  return 0;
} 

int freePacketMessage(struct packetMessage *packet)
{
  struct packetQuestion *question = packet->question;
  while(question != NULL) {
    struct packetQuestion *temp = question->next;
    free(question);
    question = temp;
  }

  struct packetAnswer *answer = packet->answer;
  while(answer != NULL) {
    struct packetAnswer *temp = answer->next;
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
