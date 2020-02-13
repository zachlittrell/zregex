#include "nfa.h"
#include "zregex.h"
#include <cstdlib>
#include <string>
namespace zregex {

	nfa::nfa compile_to_nfa(std::string& pattern) {
		auto it = pattern.begin();
		nfa::nfa compiling = nfa::singleton_nfa(*it++);
		for (; it != pattern.end(); it++) {
			symbol c = *it;
			switch (c) {
			case '?':
				nfa::optional_nfa(compiling);
				break;
			case '+':
				nfa::kleene_plus_nfa(compiling);
				break;
		//	case '*':
			//	nfa::kleene_star_nfa(compiling);
			default: 
				nfa::nfa s = nfa::singleton_nfa(c);
				nfa::compose(compiling, s);
			}
			
			
		}
		return compiling;
	}
}