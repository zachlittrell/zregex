#include "nfa.h"
namespace nfa {

	nfa singleton_nfa(symbol s) {
		nfa n;
		n.start_state = new_state();
		state end = new_state();
		n.end_states.insert(end);
		n.next_state.insert({ {n.start_state,s},end });
		return n;
	}
	nfa noop() {
		nfa n;
		state end = new_state();
		n.start_state = end;
		n.end_states.insert(end);
		n.epsilon_jumps.insert({n.start_state,{end} });
		return n;
	}
	void compose(nfa& left, nfa& right) {
		//We want the end states of left to continue on to the start of right
		for (auto end_state : left.end_states) {
			left.epsilon_jumps[end_state].insert(right.start_state);
		}
		//Add all the edges from right 
		left.next_state.insert(right.next_state.begin(), right.next_state.end());
		//Set the end states left to match right
		left.end_states = right.end_states;
	}
	state currentstate = 0;
	state new_state() {
		return currentstate++;
	}
	void optional_nfa(nfa& n) {
		//Make an epsilon jump from the start to the end state.
		n.epsilon_jumps[n.start_state].insert(n.end_states.begin(), n.end_states.end());
	}
}