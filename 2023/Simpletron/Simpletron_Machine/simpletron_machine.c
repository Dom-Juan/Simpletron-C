//
// Created by Magoimortal_br on 11/03/2023.
//
#include <locale.h>
#include "headers/simpletron_machine.h"

#define is ==

void pause() {
    fprintf(stderr,"Press any key to continue . . .");
    while (1) if (_kbhit()) break;
    fflush(stdin);
    fflush(stdout);
}

void print_intro() {
    if(setlocale(LC_ALL, "") == NULL) {
        fprintf(stderr, "error while setlocale()\n");
    }
    fprintf(stderr, ANSI_COLOR_CYAN "\n\t***                 Bem vindo ao Simpletron!                ***\n");
    fprintf(stderr, "\t***    Por favor digite o programa uma instrução ou pa-     ***\n");
    fprintf(stderr, "\t***    lavra de dados por vez. Eu vou mosrar a posição      ***\n");
    fprintf(stderr, "\t***    e uma marcação de interrogação(?) como indicação.    ***\n");
    fprintf(stderr, "\t***    Você então digite a palavra para aquela posição.     ***\n");
    fprintf(stderr, "\t***    Digite -9999 para parar o programa.                  ***\n"ANSI_COLOR_RESET);
    fflush(stdin);
    fflush(stdout);
}

void print_menu(bool machine_status) {
    if(setlocale(LC_ALL, "") == NULL) {
        fprintf(stderr, "error while setlocale()\n");
    }
    if(machine_status is true)
        fprintf(stderr, ANSI_COLOR_RED "\n\t***                 * Simpletron com memória cheia *                ***\n"ANSI_COLOR_RESET);
    else 
        fprintf(stderr, ANSI_COLOR_GREEN "\n\t***                 * Simpletron com memória livre *                ***\n"ANSI_COLOR_RESET);
    fprintf(stderr, ANSI_COLOR_CYAN "\n\t***                 Bem vindo ao Simpletron!                ***\n"ANSI_COLOR_RESET);
    fprintf(stderr,ANSI_COLOR_RESET " [" ANSI_COLOR_GREEN "1" ANSI_COLOR_RESET "] " ANSI_COLOR_RESET " - Inserir outro programa\n" ANSI_COLOR_RESET);
    fprintf(stderr,ANSI_COLOR_RESET " [" ANSI_COLOR_GREEN "2" ANSI_COLOR_RESET "] " ANSI_COLOR_RESET " - Salvar Arquivo\n" ANSI_COLOR_RESET);
    fprintf(stderr,ANSI_COLOR_RESET " [" ANSI_COLOR_GREEN "3" ANSI_COLOR_RESET "] " ANSI_COLOR_RESET " - Carregar Arquivo\n" ANSI_COLOR_RESET);
    fprintf(stderr,ANSI_COLOR_RESET " [" ANSI_COLOR_RED "0" ANSI_COLOR_RESET "] " ANSI_COLOR_RESET " - Sair do programa\n" ANSI_COLOR_RESET);
    fflush(stdin);
    fflush(stdout);
}

bool check_arguments(const int num_arguments) {
    return num_arguments < 2 ? false : true;
}

bool valid_input(int word) {
    if(word <= 9999 && word >= -9999) return true;
    else return false;
}

int start_machine(int argc, char *argv[], bool dump_status, bool trace_status) {
    fprintf(stderr, "\n             [start_machine]\n");
    fflush(stdin);
    if(setlocale(LC_ALL, "") == NULL) {
        fprintf(stderr, "error while setlocale()\n");
    }
    enum exit_val e_val;
    simpletron v1;
    v1.status = false;
    int option = 0;
    if (check_arguments(argc)) {
        char file_name[20];
        strcpy_s(file_name, sizeof(file_name), argv[1]);
        memory_init(&v1);
        print_intro();
        load(&v1, file_name);
        e_val = execute_code(&v1, trace_status);
        print_warning(v1, e_val);
        if(dump_status) dump(v1);
        return e_val;
    } else {
        print_intro();
        while(true) {
            fflush(stdout);
            fflush(stdin);
            if(v1.status is true) 
                memory_reset(&v1);
            else {
                memory_init(&v1);
                fprintf(stderr, "\n");
                print_menu(v1.status);
                scanf_s("%d", &option);
                if(option is 1) {
                    input(&v1);
                    size_t i = 0;
                    while(v1.memory[i] not_eq -9999 and v1.memory[i] not_eq 0) {
                        fprintf(
                                stderr,
                                ANSI_COLOR_CYAN "Memory" "[%zu]" ": " ANSI_COLOR_YELLOW "%hd\n" ANSI_COLOR_RESET,
                                i, v1.memory[i]
                                );
                        i++;
                    }
                    e_val = execute_code_input(&v1, trace_status);
                    print_warning(v1, e_val);
                    if(dump_status) dump(v1);
                    v1.status = true;
                    break;
                }
            }
        }
        return e_val;
    }
}

static void memory_init(simpletron *v1) {
    fflush(stdin);
    static mem_type mem[MEM_SIZE];
    v1->mem_size = MEM_SIZE;
    v1->memory = mem;
    v1->status = false;
    fprintf(stderr, ANSI_COLOR_GREEN "[Memory allocated]" ANSI_COLOR_RESET "\n");
    pause();
}

static void memory_reset(simpletron *v1) {
    fflush(stdin);
    static mem_type mem[MEM_SIZE];
    v1->mem_size = MEM_SIZE;
    v1->memory = mem;
    v1->op_code = 0;
    v1->operand = 0;
    v1->instruction_register = 0;
    v1->accumulator = 0;
    v1->status = false;
    fprintf(stderr, ANSI_COLOR_GREEN "[Memory re-allocated]" ANSI_COLOR_RESET "\n");
    pause();
}

static void input(simpletron *v1) {
    mem_type instruction = 0;
    size_t i = 0;
    fprintf(stderr, "00 ?");
    scanf_s("%hd", &instruction);
    fseek(stdin, 0, SEEK_END);
    while(i < v1->mem_size) {
        if(instruction is -9999) break;
        if (valid_input(instruction)) {
            v1->memory[i] = instruction;
        } else {
            fprintf(stderr, ANSI_COLOR_RED "[ERROR] - INVALID WORD!!!\n" ANSI_COLOR_RESET);
            i--;
        }
        fprintf(stderr, "%4d ?", instruction);
        scanf_s("%hd", &instruction);
        fseek(stdin, 0, SEEK_END);
        i++;
    }
}

static void load(simpletron *v1, char file_name[]) {
    mem_type instruction = 0;
    FILE *file_point;
    size_t i;
    int errnum;
    errno_t err;
    fprintf(stderr, ANSI_COLOR_GREEN "[file name]: %s\n" ANSI_COLOR_RESET, file_name);
    if((err = fopen_s(&file_point, file_name, "r")) not_eq 0) {
        errnum = errno;
        char buf[255];
        strerror_s(buf, sizeof buf, err);
        fprintf(stderr, "ERROR: %d Cannot open file %s %s\n",
                errnum, file_name, buf);
        pause();
        exit(EXIT_FAILURE);
    } else {
        for(i = 0; !feof(file_point) and i < v1->mem_size; i++) {
            if(instruction is -9999) break;
            if(get_instruction_from_file(file_point, &instruction) == 0) {
                fprintf(stderr, "ERROR: Improper program\n");
                pause();
                exit(ERROR_INPUT);
            }
            fprintf(stderr, ANSI_COLOR_YELLOW "Instruction: %+05d\n" ANSI_COLOR_RESET, instruction);
            v1->memory[i] = instruction;
        }
        fclose(file_point);
    }
}

int get_instruction_from_file(FILE *file_path, mem_type *instruction) {
    size_t i;
    int c, num = 0, sign;
    while(isspace(c = getc(file_path)));
    if(c is EOF) return 1;
    sign = (c is '-' ? -1 : 1);
    if(c not_eq '+' and c not_eq '-') return 0;
    else c = getc(file_path);
    for(i = 0; i < INSTRUCTION_SIZE; i++) {
        if(not isdigit(c))
            return 0;
        num = num * 10 + c - '0';
        c = getc(file_path);
    }
    while(c not_eq '\n' and c not_eq EOF) {
        c = getc(file_path);
    }
    *instruction = sign * num;
    return 1;
}

static void print_warning(simpletron v1, enum exit_val e_val) {
    char buffer[120];
    if(e_val == ERROR_NONE)
        return;
    if(e_val == ERROR_INVALID)
        sprintf(buffer, "WARNING:%+05d: %s\n", v1.instruction_register,warning[e_val]);
    else
        sprintf(buffer, "WARNING: %s\n", warning[e_val]);
}

static enum exit_val execute_code(simpletron *v1, bool trace) {
    v1->program_counter = 0;
    v1->accumulator = 0;

    while(v1->program_counter < v1->mem_size) {
        v1->instruction_register = v1->memory[v1->program_counter];
        v1->op_code = v1->instruction_register / 100;
        v1->operand = v1->instruction_register % 100;
        if(trace)
            fprintf(
                    stderr,
                    ANSI_COLOR_CYAN  "%02zu: " ANSI_COLOR_YELLOW "%+05d\n" ANSI_COLOR_RESET,
                    v1->program_counter,
                    v1->instruction_register
                    );
        switch(v1->op_code) {
            case READ:
                read_instruction_from_file(v1);
                break;
            case WRITE:
                write_instruction_from_file(v1);
                break;
            case LOAD:
                load_instruction_from_file(v1);
                break;
            case STORE:
                store_instruction_from_file(v1);
                break;
            case ADD:
                add_instruction_from_file(v1);
                break;
            case SUBTRACT:
                subtract_instruction_from_file(v1);
                break;
            case DIVIDE:
                divide_instruction_from_file(v1);
                break;
            case MULTIPLY:
                multiply_instruction_from_file(v1);
                break;
            case REMAINDER:
                remainder_instruction_from_file(v1);
                break;
            case BRANCH:
                branch_instruction_from_file(v1);
                break;
            case BRANCH_ZERO:
                branch_zero_instruction_from_file(v1);
                break;
            case BRANCH_NEG:
                branch_negative_instruction_from_file(v1);
                break;
            case HALT:
                return halt_instruction_from_file(v1);
            default:
                return ERROR_INVALID;
        }
        if (v1->accumulator < MEM_MIN or v1->accumulator > MEM_MAX)
            return ERROR_INT_OVERFLOW;
    }
    fprintf(stderr, "%d\n", ERROR_MEMORY);
    return ERROR_MEMORY;
}

static enum exit_val execute_code_input(simpletron *v1, bool trace) {
    v1->program_counter = 0;
    v1->accumulator = 0;

    while(v1->program_counter < v1->mem_size) {
        v1->instruction_register = v1->memory[v1->program_counter];
        v1->op_code = v1->instruction_register / 100;
        v1->operand = v1->instruction_register % 100;
        ++v1->program_counter;
        if(trace)
            fprintf(
                    stderr,
                    ANSI_COLOR_CYAN  "%02zu: " ANSI_COLOR_YELLOW "%+05d\n" ANSI_COLOR_RESET,
                    v1->program_counter,
                    v1->instruction_register
            );
        switch(v1->op_code) {
            case READ:
                read_instruction(v1);
                break;
            case WRITE:
                write_instruction(v1);
                break;
            case LOAD:
                load_instruction(v1);
                break;
            case STORE:
                store_instruction(v1);
                break;
            case ADD:
                add_instruction(v1);
                break;
            case SUBTRACT:
                subtract_instruction(v1);
                break;
            case DIVIDE:
                divide_instruction(v1);
                break;
            case MULTIPLY:
                multiply_instruction(v1);
                break;
            case REMAINDER:
                remainder_instruction(v1);
                break;
            case BRANCH:
                branch_instruction(v1);
                break;
            case BRANCH_ZERO:
                branch_zero_instruction(v1);
                break;
            case BRANCH_NEG:
                branch_negative_instruction(v1);
                break;
            case HALT:
                return halt_instruction(v1);
            default:
                return ERROR_INVALID;
        }
        if (v1->accumulator < MEM_MIN or v1->accumulator > MEM_MAX)
            return ERROR_INT_OVERFLOW;
    }
    fprintf(stderr, "%d\n", ERROR_MEMORY);
    return ERROR_MEMORY;
}

static void dump(simpletron v1) {
    fprintf(stderr, ANSI_COLOR_MAGENTA "\nREGISTERS:");
    fprintf(stderr, "\nACCUMULATOR:                 %+05d", v1.accumulator);
    fprintf(stderr, "\nINSTRUCTION REGISTER:        %+05d", v1.instruction_register);
    fprintf(stderr, "\nPROGRAM COUNTER:             %5zu",  v1.program_counter);
    fprintf(stderr, "\nOPERAND CODE:                %02d",  v1.op_code);
    fprintf(stderr, "\nOPERAND:                     %02d\n" ANSI_COLOR_RESET,  v1.operand);
    for(size_t i = 0; i < v1.mem_size / 10; i++) {
        fprintf(stderr, ANSI_COLOR_GREEN "%2zu   ", i * 10);
        for(size_t j = 0; j < v1.mem_size / 10; j++) {
            fprintf(
                    stderr,
                    ANSI_COLOR_GREEN "%+05d%s",
                    v1.memory[(i * 10) + j],
                    (j is v1.mem_size / 10 - 1) ? "\n" : " " ANSI_COLOR_RESET
                    );
        }
    }
}