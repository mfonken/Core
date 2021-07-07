#ifndef states_template_h
#define states_template_h

typedef enum
{
  INITIALIZING = 1,
  ACTIVE,
  IDLE,
  SYS_ERROR,
  NUM_SYSTEM_STATES
} system_state_enum;

static const char * system_state_enum_strings[] =
{
  "Initalizing",
  "Active",
  "Idle",
  "System Error",
};

#endif
