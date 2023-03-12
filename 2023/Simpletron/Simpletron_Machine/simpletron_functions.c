//
// Created by Magoimortal_br on 12/03/2023.
//

#include "headers\simpletron_machine.h"

/* Execução de input */
void read_instruction(simpletron *v1) {
    mem_type temp;
    fprintf(stderr, "Digite a entrada [-9999 - 9999]\n>: ");
    scanf_s("%hd", &temp);
    while(temp < -9999 || temp > 9999) {
        scanf_s("%hd", &temp);
    }
    v1->memory[v1->operand] = temp;
}

void write_instruction(simpletron *v1) {
    fprintf(stderr, ANSI_COLOR_GREEN "[OUTPUT]:" ANSI_COLOR_RESET "%+05d\n", v1->memory[v1->operand]);
}

void load_instruction(simpletron *v1) {
    v1->accumulator = v1->memory[v1->operand];
}

void store_instruction(simpletron *v1) {
    v1->memory[v1->operand] = v1->accumulator;
}

void add_instruction(simpletron *v1) {
    v1->accumulator += v1->memory[v1->operand];
}

void subtract_instruction(simpletron *v1) {
    v1->accumulator -= v1->memory[v1->operand];
}

void multiply_instruction(simpletron *v1) {
    v1->accumulator *= v1->memory[v1->operand];
}

enum exit_val divide_instruction(simpletron *v1) {
    if(v1->memory[v1->operand] == 0)
        return ERROR_DIVIDE_ZERO;
    if(v1->accumulator == MEM_MIN and v1->memory[v1->operand] == -1)
        return ERROR_SIG_OVERFLOW;
    v1->accumulator /= v1->memory[v1->operand];
}

enum exit_val remainder_instruction(simpletron *v1) {
    if(v1->memory[v1->operand] == 0)
        return ERROR_REM_ZERO;
    if(v1->accumulator == MEM_MIN and v1->memory[v1->operand] == -1)
        return ERROR_SIG_OVERFLOW;
    v1->accumulator %= v1->memory[v1->operand];
}

void branch_instruction(simpletron *v1) {
    v1->program_counter = v1->operand;
}

void branch_negative_instruction(simpletron *v1) {
    if (v1->accumulator < 0)
        v1->program_counter = v1->operand;
}

void branch_zero_instruction(simpletron *v1) {
    if (v1->accumulator == 0)
    v1->program_counter = v1->operand;
}

enum exit_val halt_instruction(simpletron *v1) {
    fprintf(stderr, "*** Execução do Simpletron foi terminada ***");
    v1->program_counter = 100;
    return ERROR_NONE;
}

/* Execução de arquivo */
bool read_instruction_from_file(simpletron *v1) {
    if(get_instruction_from_file(stdin, &(v1->memory[v1->operand])) == 0)
        return false;
    else
        v1->program_counter++;
    return true;
}

void write_instruction_from_file(simpletron *v1) {
    fprintf(stderr, ANSI_COLOR_GREEN "[OUTPUT]:" ANSI_COLOR_RESET "%+05d\n", v1->memory[v1->operand]);
    v1->program_counter++;
}

void load_instruction_from_file(simpletron *v1) {
    v1->accumulator = v1->memory[v1->operand];
    v1->program_counter++;
}

void store_instruction_from_file(simpletron *v1) {
    v1->memory[v1->operand] = v1->accumulator;
    v1->program_counter++;
}

void add_instruction_from_file(simpletron *v1) {
    v1->accumulator += v1->memory[v1->operand];
    v1->program_counter++;
}

void subtract_instruction_from_file(simpletron *v1) {
    v1->accumulator -= v1->memory[v1->operand];
    v1->program_counter++;
}

void multiply_instruction_from_file(simpletron *v1) {
    v1->accumulator *= v1->memory[v1->operand];
    v1->program_counter++;
}

enum exit_val divide_instruction_from_file(simpletron *v1) {
    if(v1->memory[v1->operand] == 0)
        return ERROR_DIVIDE_ZERO;
    if(v1->accumulator == MEM_MIN and v1->memory[v1->operand] == -1)
        return ERROR_SIG_OVERFLOW;
    v1->accumulator /= v1->memory[v1->operand];
    v1->program_counter++;
}

enum exit_val remainder_instruction_from_file(simpletron *v1) {
    if(v1->memory[v1->operand] == 0)
        return ERROR_REM_ZERO;
    if(v1->accumulator == MEM_MIN and v1->memory[v1->operand] == -1)
        return ERROR_SIG_OVERFLOW;
    v1->accumulator %= v1->memory[v1->operand];
    v1->program_counter++;
}

void branch_instruction_from_file(simpletron *v1) {
    if(v1->accumulator < 0)
        return;
    else
        v1->program_counter++;
}

void branch_negative_instruction_from_file(simpletron *v1) {
    if (v1->accumulator < 0)
        v1->program_counter = v1->operand;
    else
        v1->program_counter++;
}

void branch_zero_instruction_from_file(simpletron *v1) {
    if (v1->accumulator == 0)
        v1->program_counter = v1->operand;
    else
        v1->program_counter++;
}

enum exit_val halt_instruction_from_file() {
    return ERROR_NONE;
}