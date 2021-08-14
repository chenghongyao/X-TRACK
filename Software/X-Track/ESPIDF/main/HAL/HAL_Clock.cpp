#include "Common/HAL/HAL.h"
#include <time.h>
#include <stdio.h>
#include <sys/time.h>


void HAL::Clock_GetInfo(Clock_Info_t* info)
{
    struct tm* t;
    time_t tt;
    time(&tt);
    t = localtime(&tt);

    info->year = t->tm_year + 1900;
    info->month = t->tm_mon + 1;
    info->day = t->tm_mday;
    info->week = t->tm_wday;
    info->hour = t->tm_hour;
    info->minute = t->tm_min;
    info->second = t->tm_sec;
    info->millisecond = t->tm_sec;
}

void HAL::Clock_SetInfo(const Clock_Info_t* info)
{

    struct tm tptr;
    struct timeval tv;

    tptr.tm_year = info->year - 1900;
    tptr.tm_mon = info->month - 1;  
    tptr.tm_mday = info->day;
    tptr.tm_hour = info->hour;
    tptr.tm_min = info->minute;
    tptr.tm_sec = info->second;

    tv.tv_sec = mktime(&tptr);
    tv.tv_usec = 0;
    settimeofday(&tv, NULL);

    // printf(
    //     "Clock set: %04d-%02d-%02d %02d:%02d:%02d\n",
    //     info->year,
    //     info->month,
    //     info->day,
    //     info->hour,
    //     info->minute,
    //     info->second
    // );
}
