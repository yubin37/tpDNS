#include "tpDNS.h"
#include "tpPacket.h"

#include <arpa/inet.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
  openlog(PROGRAM_NAME, LOG_OPTIONS, LOG_LOCAL1);
  syslog(LOG_NOTICE, "START");

  
  int listenfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (listenfd < 0) {
    syslog(LOG_ERR, "socket initial fail.");
    return 1;
  } 

  int reuseVal = 0;
  setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuseVal, 
             sizeof(reuseVal));

  struct sockaddr_in server;
  bzero(&server, sizeof(struct sockaddr_in));
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons(DNS_PORT);

  if (bind(listenfd, (struct sockaddr *)&server, sizeof(struct sockaddr_in)) < 0) {
    syslog(LOG_ERR, "socket bind fail: %m");
    return 1;
  }
  
  char buff[MAX_LINE];
  int nread;
  struct sockaddr_in client;
  int clientLength;
  while ( 1 ) {
    nread = recvfrom(listenfd, buff, MAX_LINE, 0, 
                      (struct sockaddr*)&client,
                       &clientLength);
    buff[nread] = '\0';
    printf("----------------------------------------------------\n");
    struct packetMessage* packet;
    getDnsMessage(buff, &packet);
    printf("The cname is : %s\n", packet->question->qName);
    freePacketMessage(packet);
    printf("----------------------------------------------------\n");
  }

  syslog(LOG_NOTICE, "END"); 
  closelog();
  return 0;
}
