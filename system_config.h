#ifndef SYSTEM_CONFIG_H_
#define SYSTEM_CONFIG_H_

#include "system.h"
//#include "printers.h"
//#include "resources.h"

//typedef struct
//{
//  uint8_t Address;
//  uint8_t Value;
//} register_t;

typedef volatile bool flag_t;
typedef struct
{
    flag_t Flag;
    void (*Callback)(void);
} callback_t;
typedef uint32_t * generic_handle_t;

#endif /* SYSTEM_CONFIG_H_ */
