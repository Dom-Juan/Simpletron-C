//
// Created by Magoimortal_br on 11/03/2023.
//

#ifndef SIMPLETRON_SIMPLETRON_MEMORY_H
#define SIMPLETRON_SIMPLETRON_MEMORY_H

#include <stdint.h>

#define MEM_SIZE 100
#define MEM_MAX 9999
#define MEM_MIN -9999
#define INSTRUCTION_SIZE 4
#define OP_SIZE 2

typedef int16_t mem_type;

enum operations {
    READ = 10,
    WRITE = 11,
    LOAD = 20,
    STORE = 21,
    ADD = 30,
    SUBTRACT = 31,
    DIVIDE = 32,
    MULTIPLY = 33,
    REMAINDER = 34,
    BRANCH = 50,
    BRANCH_NEG = 51,
    BRANCH_ZERO = 52,
    HALT = 53
};

#endif //SIMPLETRON_SIMPLETRON_MEMORY_H
