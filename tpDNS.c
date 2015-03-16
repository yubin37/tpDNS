#include "include/tpDNS.h"

int main(int argc, char **argv)
{
  openlog(PROGRAM_NAME, LOG_OPTIONS, LOG_LOCAL1);
  syslog(LOG_NOTICE, "START");

  syslog(LOG_NOTICE, "END"); 
  closelog();
  return 0;
}
