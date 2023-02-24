/************************************************************************
 *  File: printers.h
 *  Group: PCR Core
 ***********************************************************************/

#ifndef printers_h
#define printers_h

#include "resources.h"
#include "platform.h"
#include "unilog.h"

#define PRINT_BUFFER_LEN ( 1 << 8 )
static char str_buf[PRINT_BUFFER_LEN];

#define CORE_LOG_LEVEL          DEBUG_2
#define STATE_DEBUG             DEBUG_2

void print( char * Buf );
void DrawDensityMap( uint8_t * a, int32_t l );
void PrintDensityMaps( uint8_t * x, int32_t lx, uint8_t * y, int32_t ly );
void PrintBuffer( uint8_t * a, int32_t l );

#endif
