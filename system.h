/************************************************************************
 *  File: system.h
 *  Group: Rho Core
 ***********************************************************************/

#ifndef system_h
#define system_h

/***************************************************************************************/
/*                                    Includes                                         */
/***************************************************************************************/
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "platform.h"
#ifdef APPLICATION_STATE_HEADER
#include APPLICATION_STATE_HEADER
#else
#include "templates/states_template.h"
#endif
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
void InitSystem(               system_t *, system_states_list_t * );
void NextStateSystem(          system_t *                         );
void SetStateSystem(           system_t *,  system_state_enum     );
void PerformStateSystem(       system_t *                         );
void EnterStateSystem(         system_t *,  system_state_enum     );
bool IsInStateSystem(          system_t *,  system_state_enum     );
system_state_t * GetStateSystem( system_t *                            );
system_state_t * GetStateFromListSystem( system_t *, system_state_enum );

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
  .Init           = InitSystem,
  .State.Next     = NextStateSystem,    /* Enter next state               */
  .State.Set      = SetStateSystem,     /* Set state, no perform          */
  .State.Perform  = PerformStateSystem, /* Peform current state's routine */
  .State.Enter    = EnterStateSystem,   /* Set and perform state          */
  .State.IsIn     = IsInStateSystem,    /* Check if system is in state    */
  .State.Get      = GetStateSystem,     /* Get current state              */
  .State.GetFromList = GetStateFromListSystem /* Get state data from list */
};

#endif
