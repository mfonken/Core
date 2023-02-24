/************************************************************************
 *  File: master.h
 *  Group: Rho Core
 ***********************************************************************/

#ifndef master_h
#define master_h

/***************************************************************************************/
/*                                    Includes                                         */
/***************************************************************************************/
#include "system.h"

/***************************************************************************************/
/*                              Function Definitions                                   */
/***************************************************************************************/
void Master_Connect( master_ios_t * ios );
void Master_Init( void );
void Master_Run( void );

/***************************************************************************************/
/*                              Function Structures                                    */
/***************************************************************************************/
typedef struct
{
  void (*Connect)( master_ios_t * );
  void (*Init)( void );
  void (*Run)( void );
} master_functions_t;

static master_functions_t MasterFunctions =
{
  .Connect = Master_Connect,
  .Init    = Master_Init,
  .Run     = Master_Run
};

/***************************************************************************************/
/*                                  Routines Definitions                               */
/***************************************************************************************/
void InitializePlatform( void );
void ConnectToHost( void );
void ConfigureApplication( void );
void ExitInitialization( void );
void ApplicationCore( void );
void SystemError( void );

/***************************************************************************************/
/*                                Core State List                                      */
/***************************************************************************************/
static system_states_list_t global_states_list =
{// State				Next State			Routine Handle
  { INITIALIZING,       CONNECTING_TO_HOST, InitializePlatform    },
  { CONNECTING_TO_HOST, CONFIGURING,        ConnectToHost         },
  { CONFIGURING,        READY,              ConfigureApplication  },
  { READY,              ACTIVE,             ExitInitialization    },
  { ACTIVE,             IDLE,               ApplicationCore       },
  { SYS_ERROR,          IDLE,               SystemError           }
};

#endif
