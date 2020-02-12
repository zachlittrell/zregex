#pragma once
#include "typedef.h"
#include <vector>
#include <set>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
/**
 * 
 */
namespace nfa {
    
    struct nfa {
        state start_state;
        std::set<state> end_states;
        std::map<state_and_symbol, state> next_state;
        std::map<state, std::set<state>> epsilon_jumps;
        void print() {
            std::cout << "Start state:" << start_state << std::endl;
            std::cout<<"End states: ";
            for (state end_state : end_states) {
                std::cout << end_state << " ";
            }
            std::cout << std::endl;
            std::cout << "State transitions:";
            for (auto kv : next_state) {
                std::cout << kv.first.first << "," << kv.first.second << "->" << kv.second << std::endl;
            }
            std::cout << std::endl;
            std::cout << "Epsilons:";
            for (auto kv : epsilon_jumps) {
                for (state s : kv.second) {
                    std::cout << kv.first << "->" << s << std::endl;
                }
            }
            std::cout << std::endl;
        }
    };
    
    state new_state();
    nfa singleton_nfa(symbol s);
    nfa noop();
    void compose(nfa& left, nfa& right);

}