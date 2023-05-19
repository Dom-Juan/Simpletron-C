//
// Created by Magoimortal_br on 11/03/2023.
//

#ifndef SIMPLETRON_SIMPLETRON_MACHINE_H
#define SIMPLETRON_SIMPLETRON_MACHINE_H
// Standart Data Stypes.
#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
// Outros imports
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <iso646.h>
#include <conio.h>
//#include <dirent.h> // Apenas POSIX, MSVC não possuir essa lib
//#include <unistd.h> // Apenas POSIX, MSVC não possuir essa lib
#include "unistd.h"
// Includes de headers do programa.
#include "simpletron_memory.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// Struct do Simpletron
typedef struct Simpletron {
    mem_type *memory;           // array unidimensional simulando a memória "RAM".
    size_t mem_size;            // tamanho da memória.
    size_t program_counter;     // contador de programa.
    int accumulator;            // valor sendo processado.
    int instruction_register;   // instrução atual.
    int op_code;                // operaçãoo atual a ser feita
    int operand;                // operador ou local da memória da instrução do operando.
    bool status;                // status para determinar se a struct possui valores.
} simpletron;

// Enum para os valores de saida.
enum exit_val {
    ERROR_NONE = 0,
    ERROR_INPUT,
    ERROR_DIVIDE_ZERO,
    ERROR_REM_ZERO,
    ERROR_SIG_OVERFLOW,
    ERROR_INT_OVERFLOW,
    ERROR_INVALID,
    ERROR_MEMORY
};

// matriz de strings com N strings para printar o erro evitar redundancia no c?digo.
static const char *warning[] = {
    "Input invalido",
    "Divisao por zero",
    "Resto zero",
    "Overflow de inteiro signed",
    "Overflow de inteiro",
    "Instrucao invalida",
    "Execucao chegou no fim da memoria sem HALT"
};

static const char *end_execution[] = {
        "Terminado execução com sucesso!",
        "Divisao por zero",
        "Resto zero",
        "Overflow de inteiro signed",
        "Overflow de inteiro",
        "Instrucao invalida",
        "Execucao chegou no fim da memoria sem HALT"
};

// Declarações de funções do código.
static enum exit_val execute_code(simpletron *, bool trace);
static enum exit_val execute_code_input(simpletron *v1, bool trace);
static void memory_init(simpletron *);
static void memory_reset(simpletron *);
static void input(simpletron *);
static void load(simpletron *v1, char file_name[]);
static void dump(simpletron v1);
static void print_warning(simpletron v1, enum exit_val e_val);
int get_instruction_from_file(FILE *, mem_type *);
int start_machine(int argc, char *argv[], bool dump_status, bool trace_status);
bool valid_input(int word);
bool save_program(simpletron *v1);
bool load_program(simpletron *v1, char filename[]);

// Funções que o simpletron faz.
void read_instruction(simpletron *);
void write_instruction(simpletron *);
void load_instruction(simpletron *);
void store_instruction(simpletron *);
void add_instruction(simpletron *);
void subtract_instruction(simpletron *);
void multiply_instruction(simpletron *);
enum exit_val divide_instruction(simpletron *);
enum exit_val remainder_instruction(simpletron *);
void branch_instruction(simpletron *);
void branch_negative_instruction(simpletron *);
void branch_zero_instruction(simpletron *);
enum exit_val halt_instruction(simpletron *v1);

// funções que o simpletron faz quando lê um arquivo com instruções.
bool read_instruction_from_file(simpletron *);
void write_instruction_from_file(simpletron *);
void load_instruction_from_file(simpletron *);
void store_instruction_from_file(simpletron *);
void add_instruction_from_file(simpletron *);
void subtract_instruction_from_file(simpletron *);
void multiply_instruction_from_file(simpletron *);
enum exit_val divide_instruction_from_file(simpletron *);
enum exit_val remainder_instruction_from_file(simpletron *);
void branch_instruction_from_file(simpletron *);
void branch_negative_instruction_from_file(simpletron *);
void branch_zero_instruction_from_file(simpletron *);
enum exit_val halt_instruction_from_file(simpletron *);

#endif //SIMPLETRON_SIMPLETRON_MACHINE_H
