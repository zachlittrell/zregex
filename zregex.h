#pragma once
#include "nfa.h"
namespace zregex {
	nfa::nfa compile_to_nfa(std::string& pattern);
}
