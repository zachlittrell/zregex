#include "nfa.h"
#include "zregex.h"
#include <cstdlib>
#include <string>
#include <stack>

namespace zregex {
	/**
	 * Returns an nfa to match the regex in pattern
	 */
	nfa::nfa compile_to_nfa(std::string& pattern) {
		if (pattern.empty()) return nfa::noop();
		nfa::nfa compiling;
		std::stack<bool> started;
		std::stack<bool> active_disjunction;
		std::stack<nfa::nfa> disjunctives;
		std::stack<nfa::nfa> leftoff;
		active_disjunction.push(false);
		started.push(false);
		nfa::nfa progress;
		
		
		for (symbol c : pattern) {
			switch (c) {
			case '?':
				nfa::optional_nfa(compiling);
				break;
			case '+':
				nfa::kleene_plus_nfa(compiling);
				break;
			case '*':
				nfa::kleene_star_nfa(compiling);
				break;
			case '|':
				//We were already disjuncting something!
				if (active_disjunction.top()) {
					nfa::disjunction_nfa(compiling, disjunctives.top());
				}
				else {
					active_disjunction.pop();
					active_disjunction.push(true);
					disjunctives.push(compiling);
				}
				started.pop();
				started.push(false);
				break;
			case '(':

				//Starting a new group.
				//Stash what we're working on
				if (started.top()) leftoff.push(compiling);
				active_disjunction.push(false);
				started.push(false);

				break;
			case ')':
				//Take the opportunity to see if disjunction in progress
				if (active_disjunction.top()) {
					nfa::disjunction_nfa(compiling, disjunctives.top());
					disjunctives.pop();
				}
				active_disjunction.pop();

				started.pop();
				if (started.top()) {
					//Pop off whatever we stashed and compose it with what 
					progress = leftoff.top();
					leftoff.pop();
					nfa::compose(progress, compiling);
					compiling = progress;
				}
				else {
					started.pop();
					started.push(true);
				}
	
				break;
			default: 
				nfa::nfa s = nfa::singleton_nfa(c);
				if (started.top())
					nfa::compose(compiling, s);
				else {
					compiling = s;
					started.pop();
					started.push(true);
				}
			}
		}
		//If we still have an active disjunction, we've reached 
		//end of the pattern so we can go ahead and complete it
		if (active_disjunction.top()) {
			nfa::disjunction_nfa(compiling, disjunctives.top());
		}
		return compiling;
	}
}