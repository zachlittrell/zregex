#include "nfa.h"
#include "zregex.h"
#include <cstdlib>
#include <string>
#include <stack>

namespace zregex {

	nfa::nfa compile_to_nfa(std::string& pattern) {
		if (pattern.empty()) return nfa::noop();
		nfa::nfa compiling;
		std::stack<bool> starteds;
		std::stack<bool> needdisjunctives;
		std::stack<nfa::nfa> disjunctives;
		std::stack<nfa::nfa> groups;
		needdisjunctives.push(false);
		starteds.push(false);
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
				if (needdisjunctives.top()) {
					nfa::disjunction_nfa(compiling, disjunctives.top());
				}
				else {
					needdisjunctives.pop();
					needdisjunctives.push(true);
					disjunctives.push(compiling);
				}
				starteds.pop();
				starteds.push(false);
				break;
			case '(':

				//Starting a new group.
				//Stash what we're working on
				if (starteds.top()) groups.push(compiling);
				needdisjunctives.push(false);
				starteds.push(false);

				break;
			case ')':
				//Take the opportunity to see if disjunction in progress
				if (needdisjunctives.top()) {
					nfa::disjunction_nfa(compiling, disjunctives.top());
					disjunctives.pop();
				}
				needdisjunctives.pop();

				starteds.pop();
				if (starteds.top()) {
					//Pop off whatever we stashed and compose it with what 
					progress = groups.top();
					groups.pop();
					nfa::compose(progress, compiling);
					compiling = progress;
				}
				else {
					starteds.pop();
					starteds.push(true);
				}
	
				break;
			default: 
				nfa::nfa s = nfa::singleton_nfa(c);
				if (starteds.top())
					nfa::compose(compiling, s);
				else {
					compiling = s;
					starteds.pop();
					starteds.push(true);
				}
			}
		}
		if (needdisjunctives.top()) {
			nfa::disjunction_nfa(compiling, disjunctives.top());
		}
		return compiling;
	}
}