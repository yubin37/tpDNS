/******************************************************************************
 * 该文件提供两种日志记录方式。一种使用系统提供的syslog函数进行日志记录，一种
 * 则是使用标准错误流输出。syslog的配置由makefile自动实现。
 * Author: Eric Yang      
 * Date: 2015-07-07
 * Email: yubin@cnyubin.com
 * ***************************************************************************/

#ifndef TPDNS_TP_LOG_INCLUDE_H_
#define TPDNS_TP_LOG_INCLUDE_H_

#include <syslog.h>
#define PROGRAM_NAME             "TP-DNS"
#define LOG_OPTIONS  LOG_CONS | LOG_PID
#define LOG_FACILITY LOG_LOCAL1

/******************************************************************************
 * 该函数将日志输出到标准错误流
 * @type: 日志的类型，与syslog函数的type参数一致。
 * @format: 日志的输出格式
 * ***************************************************************************/
void Stderr_log(int level, const char *format, ...);

/******************************************************************************
 * 在使用系统日志函数前，需要先进行初始化。
 * ***************************************************************************/
void Init_log(void);

extern void closelog(void);

extern void syslog(int type, const char *format, ...);
#endif
