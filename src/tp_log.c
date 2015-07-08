#include "tp_log.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

int Print_stderr_header(char *header)
{
  return fprintf(stderr, "%s %s ", PROGRAM_NAME, header);
}

int Print_to_stderr(const char *format, va_list args)
{
  return vfprintf(stderr, format, args);
}


void Stderr_log(int level, const char *format, ...)
{
  if ( LOG_EMERG == level) {
    Print_stderr_header("[EMERG]");
  } else if ( LOG_ALERT == level) {
    Print_stderr_header("[ALERT]");
  } else if ( LOG_CRIT == level) {
    Print_stderr_header("[CRIT]");
  } else if ( LOG_ERR == level) {
    Print_stderr_header("[ERR]");
  } else if ( LOG_WARNING == level) {
    Print_stderr_header("[WARNING]");
  } else if ( LOG_NOTICE == level) {
    Print_stderr_header("[NOTICE]");
  } else if ( LOG_INFO == level) {
    Print_stderr_header("[INFO]");
  } else {
    Print_stderr_header("[DEBUG]");
  }

  va_list args;
  va_start(args, format);
  Print_to_stderr(format, args);
  va_end(args);
  
  fprintf(stderr, "\n");    /* flush std err */
}

void Init_log(void)
{
  openlog(PROGRAM_NAME, LOG_OPTIONS, LOG_FACILITY);
}

