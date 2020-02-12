#include "nfa.h"
#include "zregex.h"
#include <cstdlib>
#include <string>
namespace zregex {

	nfa::nfa compile_to_nfa(std::string& pattern) {
		auto it = pattern.begin();
		nfa::nfa compiling = nfa::singleton_nfa(*it++);
		for (; it != pattern.end(); it++) {
			nfa::nfa s = nfa::singleton_nfa(*it);
			nfa::compose(compiling, s);
		}
		return compiling;
	}
}