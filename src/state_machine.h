#pragma once
#include "stdint.h"

typedef void (*enter_action_t)(int16_t);

typedef struct StateTransition_t{
	int16_t state_mask;
	int16_t event_mask;
	enter_action_t action;
	int16_t next_state;
}StateTransition_t;

typedef struct StateMachine_t{
	const char* name;
	const StateTransition_t* table;
	int8_t tbsize;
	int16_t state;
	const int16_t default_state;
}StateMachine_t;

// assumes event and state are bitmasks
int update_state_bitmasks(StateMachine_t* sm, int16_t event);

int update_state_value(StateMachine_t* sm, int16_t event);
int update_sequencer(StateMachine_t* sm, int16_t event);

void pass(int16_t event);