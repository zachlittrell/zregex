#include "zregex.h"

int main() {
	std::string s("a*");
	auto pattern = zregex::compile_to_nfa(s);
	pattern.print();
	std::string text("aaaaaaaa");
	std::cout << nfa::matches(pattern, text);
}