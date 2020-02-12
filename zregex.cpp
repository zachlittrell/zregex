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
			if (c == '?') {
				nfa::optional_nfa(compiling);
				continue;
			}
			nfa::nfa s = nfa::singleton_nfa(c);
			nfa::compose(compiling, s);
		}
		return compiling;
	}
}