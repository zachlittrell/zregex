#include "zregex.h"

int main() {
	std::string s("ab?c");
	auto pattern = zregex::compile_to_nfa(s);
	pattern.print();
}