#include "zregex.h"

int main() {
	std::string s("a*|b*");
	auto pattern = zregex::compile_to_nfa(s);
	pattern.print();
	std::string text("aa");
	std::cout << nfa::matches(pattern, text);
}