/************************************************************************
 *  File: platform_interface_master.h
 *  Group: Rho Hardware Interface
 ***********************************************************************/

#ifndef platform_interface_master_h
#define platform_interface_master_h

#ifdef __STM32__
#include "stm32_interface.h"
#else
#error "No valid platform specified."
#endif

typedef struct
{
  I2C_Handle_t * I2C_Primary;
  UART_Handle_t * UART_Primary;
//  USB_Handle_t * USB_Primary;
} master_ios_t;

typedef struct
{
  TIMER_Handle_t * Timer_Primary;
} master_utilities_t;

typedef struct
{
  master_ios_t IOs;
  master_utilities_t Utilities;
} master_t;

extern master_t Master;

#endif /* platform_interface_master_h */
