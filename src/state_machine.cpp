#include "state_machine.h"

int update_state_bits(StateMachine_t* sm, int16_t event){

	// get state lookup table
	const StateTransition_t* stt = sm->table;
	for (int i = 0; i < sm->tbsize; i++){

		StateTransition_t row = stt[i];
		// look up state definition
		if (sm->state & row.state_mask) {
			
			// check if event conditions match
			if (event & row.event_mask) {
				row.action(row.next_state);
				sm->state = row.next_state;

				return 1; // should only transition states once for a given event
			}
		}
	}
	return 0; // no state change
}

int update_state_value(StateMachine_t* sm, int16_t event){

	// get state lookup table
	const StateTransition_t* stt = sm->table;
	for (int i = 0; i < sm->tbsize; i++){

		StateTransition_t row = stt[i];
		// look up state definition
		if (sm->state == row.state_mask) {
			
			// check if event conditions match
			if (event == row.event_mask) {
				row.action(row.next_state);
				sm->state = row.next_state;

				return 1; // should only transition states once for a given event
			}
		}
	}
	return 0; // no state change
}

int update_sequencer(StateMachine_t* sm, int16_t event){

	// get state lookup table
	const StateTransition_t* stt = sm->table;
	for (int i = 0; i < sm->tbsize; i++){

		StateTransition_t row = stt[i];
		// look up state definition
		if (sm->state == row.state_mask) {
			
			// check if event conditions match
			if (event == row.event_mask) {
				row.action(row.next_state);
				sm->state = row.next_state;

				// should only transition states once for a given event
				return sm->state == (sm->tbsize-1); // returns if sequence matches
			}
		}
	}
	
	sm->state = sm->default_state;
	return 0; // no state change
}

void pass(int16_t event){
	// do nothing
}