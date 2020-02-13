#include "nfa.h"
#include <stack>
namespace nfa {
	/**
	 * Returns an nfa that matches just symbol s
	 */
	nfa singleton_nfa(symbol s) {
		nfa n;
		n.start_state = new_state();
		state end = new_state();
		n.end_states.insert(end);
		n.next_state.insert({ {n.start_state,s},end });
		return n;
	}
	/**
	 * Returns an nfa that matches only ""
	 */
	nfa noop() {
		nfa n;
		state end = new_state();
		n.start_state = end;
		n.end_states.insert(end);
		n.epsilon_jumps.insert({n.start_state,{end} });
		return n;
	}
	/** 
	 * Modifies left so it will match only patterns that are concatenates
	 * of left and right's valid strings.
	 */
	void compose(nfa& left, nfa& right) {
		//We want the end states of left to continue on to the start of right
		for (auto end_state : left.end_states) {
			left.epsilon_jumps[end_state].insert(right.start_state);
		}
		//Merge epsilon jumps
		left.epsilon_jumps.insert(right.epsilon_jumps.begin(), right.epsilon_jumps.end());
		//Add all the edges from right 
		left.next_state.insert(right.next_state.begin(), right.next_state.end());
		//Set the end states left to match right
		left.end_states = right.end_states;
	}
	state currentstate = 0;
	/**
	 * Returns a new, unused state
	 * TODO come up with a sleeker solution.
	 */
	state new_state() {
		return currentstate++;
	}
	/**
	 * Modifies n so it can match either n's pattern or ""
	 */
	void optional_nfa(nfa& n) {
		//Make an epsilon jump from the start to the end state.
		n.epsilon_jumps[n.start_state].insert(n.end_states.begin(), n.end_states.end());
	}
	/**
	 * Modifies n so it can match n+
	 */
	void kleene_plus_nfa(nfa& n) {
		//Put an epsilon jump from the end states to the start state;
		for (state estate : n.end_states) {
			n.epsilon_jumps[estate].insert(n.start_state);
		}
	}
	/**
	 * Modifies n so it can match n*
	 */
	void kleene_star_nfa(nfa& n) {
		//Combine optional and kleene +
		kleene_plus_nfa(n);
		optional_nfa(n);
	}

	/**
	 * Modifies left so it can match left|right
	 */
	void disjunction_nfa(nfa& left, nfa& right) {
		//Allow an epsilon jump to hop form left's start to right's start
		left.epsilon_jumps[left.start_state].insert(right.start_state);
		left.epsilon_jumps.insert(right.epsilon_jumps.begin(), right.epsilon_jumps.end());
		left.end_states.insert(right.end_states.begin(), right.end_states.end());
		left.next_state.insert(right.next_state.begin(), right.next_state.end());
	
	}
	/**
	 * Returns true if input is matched exactly by n
	 */
	bool matches(nfa& n, std::string& input) {

		std::stack<state> states;
		std::stack<std::string::iterator> its;
		states.push(n.start_state);
		its.push(input.begin());

		//We need to keep track of where we've been to avoid looping
		typedef std::pair<state,std::string::iterator> state_and_it;
		std::set<state_and_it> seen;

		state state;
		do {
			state = states.top();
			auto it = its.top();
			states.pop();
			its.pop();
			//Have we been at this node before with this symbol?
			if (seen.find({ state,it }) != seen.end()) {
				continue;
			}
			seen.insert({ state,it });

			if (it == input.end()) {
				if (n.end_states.find(state) != n.end_states.end())
				  return true;
				else {
					//Add epsilon jumps
					for (auto estate : n.epsilon_jumps[state]) {
						states.push(estate);
						its.push(it);
					}
					continue;
				}
			}
			//Add epsilon jumps
			for (auto estate : n.epsilon_jumps[state]) {
				states.push(estate);
				its.push(it);
			}
			state_and_symbol ss({ state,*it });
			auto nextstate = n.next_state.find(ss);

			//Is there an edge for the state/symbol pair?
			if (nextstate != n.next_state.end()) {
				//We're not at the end of the input are we?
				if (it != input.end()) {
					states.push((*nextstate).second);
					its.push(it+1);
				}

			}


		} while (!states.empty());
		return false;
	}
}