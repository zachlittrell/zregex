#include "nfa.h"
#include "zregex.h"
#include <cstdlib>
#include <string>

namespace zregex {

	nfa::nfa compile_to_nfa(std::string& pattern) {

		nfa::nfa compiling;
		bool started = false;
		nfa::nfa disjunctive;
		bool needdisjunctive = false;
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
				if (needdisjunctive) {
					nfa::disjunction_nfa(compiling, disjunctive);
				}
				disjunctive = compiling;
				needdisjunctive = true;
				started = false;
				break;
			default: 
				nfa::nfa s = nfa::singleton_nfa(c);
				if (started)
					nfa::compose(compiling, s);
				else {
					compiling = s;
					started = true;
				}
			}
		}
		if (needdisjunctive) {
			nfa::disjunction_nfa(compiling, disjunctive);
		}
		return compiling;
	}
}