# zregex
Toy regular expression engine

This is a just-for-fun little proof-of-concept regex engine.

It works by converting a regex pattern to a non-deterministic finite automaton.


## Example
```cpp
	std::string pattern_string("a*");
	nfa::nfa pattern = zregex::compile_to_nfa(pattern_string);
	std::string text("aaaaaaaa");
	std::cout << nfa::matches(pattern, text);
```

## Capability
zregex can recognize the following operators:
* ? - 1 or 0 occurrences 
* \+ - 1 or many occurrences
* \* - 0 or many occurrences
* a|b - Disjunction/a or b 
