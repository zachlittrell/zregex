#include "zregex.h"

int main() {
	std::string s("c|(a(b|d))");
	auto pattern = zregex::compile_to_nfa(s);
	pattern.print();
	std::string text("cd");
	std::cout << nfa::matches(pattern, text);
}