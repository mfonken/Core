/************************************************************************
 *  File: system.h
 *  Group: Rho Core
 ***********************************************************************/

#ifndef system_h
#define system_h

/***************************************************************************************/
/*                                    Includes                                         */
/***************************************************************************************/
#include "platform.h"

#include "../App/states.h"
/***************************************************************************************/
/*                              Type Definitions                                       */
/***************************************************************************************/

typedef struct
{
  system_state_enum
    state,
    next;
  void (*routine)(void);
} system_state_t;

typedef system_state_t system_states_list_t[NUM_SYSTEM_STATES];

typedef struct
{
  uint8_t id;
} system_header_t;

typedef struct
{
  /* Header */
  system_header_t header;

  /* State Control */
  system_state_enum state;
  system_states_list_t * state_list;
} system_t;

static system_t System =
{
  { THIS_ID },
  IDLE,
};

/***************************************************************************************/
/*                             Function Definitions                                    */
/***************************************************************************************/
void System_Init(              system_t *, system_states_list_t * );
void System_State_Next(        system_t *                         );
void System_State_Set(         system_t *,  system_state_enum     );
void System_State_Perform(     system_t *                         );
void System_State_Enter(       system_t *,  system_state_enum     );
bool System_State_IsIn(        system_t *,  system_state_enum     );
system_state_t * System_State_Get( system_t *                            );
system_state_t * System_State_GetFromList( system_t *, system_state_enum );

/***************************************************************************************/
/*                             Function Structures                                     */
/***************************************************************************************/
typedef struct
{
  void (*Next)(           system_t *                       );
  void (*Set)(            system_t *, system_state_enum    );
  void (*Perform)(        system_t *                       );
  void (*Enter)(          system_t *, system_state_enum    );
  bool (*IsIn)(           system_t *, system_state_enum    );
  system_state_t * (*Get)(         system_t *                    );
  system_state_t * (*GetFromList)( system_t *, system_state_enum );
} system_state_functions;

typedef struct
{
  void (*Init)( system_t *, system_states_list_t * );
  system_state_functions State;
} system_functions;

/***************************************************************************************/
/*                               Global Instances                                      */
/***************************************************************************************/
static system_functions SystemFunctions =
{
  .Init           = System_Init,          /* Initialize system with states  */
  .State.Next     = System_State_Next,    /* Enter next state               */
  .State.Set      = System_State_Set,     /* Set state, no perform          */
  .State.Perform  = System_State_Perform, /* Peform current state's routine */
  .State.Enter    = System_State_Enter,   /* Set and perform state          */
  .State.IsIn     = System_State_IsIn,    /* Check if system is in state    */
  .State.Get      = System_State_Get,     /* Get current state              */
  .State.GetFromList = System_State_GetFromList /* Get state data from list */
};

#endif
