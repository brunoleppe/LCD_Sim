//
// Created by bleppe on 16/05/23.
//
#include "debug_bsp.h"
#include <cstdio>
#include <cstdarg>

void debug_printf(const char *fmt, ...)
{
    va_list list;
    va_start(list,fmt);
    vprintf(fmt,list);
    va_end(list);
}