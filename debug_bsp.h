//
// Created by bleppe on 24/03/23.
//

#ifndef READER_DEBUG_BSP_H
#define READER_DEBUG_BSP_H


#define DEBUG_PRINT(...)     debug_printf(__VA_ARGS__)
#define ERROR_PRINT(...)     error_printf(__VA_ARGS__)

#ifdef __cplusplus
extern "C"{
#endif

void debug_printf(const char *fmt, ...);
void error_printf(const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif //READER_DEBUG_BSP_H
