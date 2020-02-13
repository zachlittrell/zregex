#include "zregex.h"

int main() {
	std::string s("ab+");
	auto pattern = zregex::compile_to_nfa(s);
	pattern.print();
	std::string text("ab");
	std::cout << nfa::matches(pattern, text);
}