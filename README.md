# zregex
Toy regular expression engine

This is a just-for-fun little proof-of-concept regex engine.

It works by converting a regex pattern to a non-deterministic finite automaton.


## Example
```cpp
	std::string pattern_string("(ab)|(b(cd*))");
	nfa::nfa pattern = zregex::compile_to_nfa(pattern_string);
	std::string text("bcd");
	std::cout << nfa::matches(pattern, text);
```

## Capability
zregex can recognize the following operators:
* a? - 1 or 0 occurrences of a
* a\+ - 1 or many occurrences of a
* a\* - 0 or many occurrences of a
* a|b - a or b 
* (ab) - Grouping of ab

## Peculiarities
* \+ and \* apply to everything in front of them, not just the symbol immediately to the left
* There is no error checking whatsoever at the moment in zregex::compile_to_nfa
