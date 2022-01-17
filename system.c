/************************************************************************
 *  File: system.h
 *  Group: Rho Core
 ***********************************************************************/

#include "system.h"
#include "printers.h"

void System_Init(
  system_t * system,
  system_states_list_t * state_list )
{
  system->state_list = state_list;
  SystemFunctions.State.Set( system, system->state );
}

void System_State_Next( system_t * system )
{
  SystemFunctions.State.Enter( system, SystemFunctions.State.Get(system)->next );
}

system_state_t * System_State_Get( system_t * system )
{
  return SystemFunctions.State.GetFromList( system, system->state );
}

void System_State_Set( system_t * system, system_state_enum new_state )
{
  if( system->state != new_state )
    LOG(STATE_DEBUG, "Entering %s\r\n", system_state_enum_strings[new_state]);
  system->state = new_state;
}

void System_State_Perform( system_t * system )
{
  void (*routine)(void) = SystemFunctions.State.Get(system)->routine;
  if( routine != NULL ) routine();
}

void System_State_Enter( system_t * system, system_state_enum new_state )
{
  SystemFunctions.State.Set( system, new_state );
  SystemFunctions.State.Perform( system );
}

bool System_State_IsIn( system_t * system, system_state_enum check_state )
{
  return ( SystemFunctions.State.Get( system )->state == check_state );
}

system_state_t * System_State_GetFromList( system_t * system, system_state_enum state )
{
  return &(*system->state_list)[state];
    /* Cycle state list to find specified state.
        If not found, return is ERROR_STATE */
    // for( uint8_t i = 0; i < SYS_ERROR; i++ )
    // {
    //     state_type = &(*system->state_list)[i];
    //     if( state_type->state == state ) break;
    // }
    // return state_type;
}
