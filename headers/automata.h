#include <stdlib.h>


typedef struct automata_T {
    int (* rule_life)(struct automata_T * automata, int x, int y); // Function which returns 1 if cell lives
    int (* rule_death)(struct automata_T * automata, int x, int y); // Function which returns 1 if cell dies
    const int size_x, size_y;
    char * cells;
} automata_T;

int create_automata(automata_T * automata);
void destroy_automata(automata_T * automata);
void iterate_automata(automata_T * automata);