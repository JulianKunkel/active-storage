/******************************************************************************
*
* NGI log utilities
*
******************************************************************************/

#ifndef COMMON_NGI_LOG_H
#define COMMON_NGI_LOG_H

#include <stdlib.h>
#include <stdio.h>

enum ngi_log_level
{
    NGI_LOG_DBG,
    NGI_LOG_WARN,
    NGI_LOG_ERROR,
    NGI_LOG_MAX
};
enum ngi_log_level NGI_Log_Level = NGI_LOG_DBG;


/*
#define ngi_log(lvl, fmt, ...) \
        do { if (lvl >= NGI_Log_Level) fprintf(stderr, "%s:%d:%s(): %s" fmt,\
                                __func__, __VA_ARGS__); } while (0)
	*/
#define ngi_log(lvl, fmt, ...) \
          do { if (lvl >= NGI_Log_Level ) fprintf(stderr, "== ngi_log == %s: " fmt, __func__,  ## __VA_ARGS__);}\
	  while (0)



#define ngi_dbg(msg, ...)    ngi_log(NGI_LOG_DBG, msg, ##__VA_ARGS__)
#define ngi_warn(msg, ...)   ngi_log(NGI_LOG_WARN, msg, ##__VA_ARGS__)
#define ngi_error(msg, ...)  ngi_log(NGI_LOG_ERROR, msg, ##__VA_ARGS__)

/* getter and setters */
#define ngi_log_level_set(ngi_log_level) NGI_Log_Level = ngi_log_level;
#define ngi_log_level_get(ngi_log_level) ngi_log_level;

#endif
