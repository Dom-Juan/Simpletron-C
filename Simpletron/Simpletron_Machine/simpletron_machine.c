//
// Created by Magoimortal_br on 11/03/2023.
//
#include <locale.h>
#include <windows.h>
#include "headers/simpletron_machine.h"

// Arquivo com o loop principal do Simpletron.

// Estou usando uma ISO do C que permite operandos como em python pq acho legal.
#define is ==

// Pause feito na mão pq o do windows estava uma merda...
void pause() {
    fprintf(stderr,"Press any key to continue . . .");
    while (1) if (_kbhit()) break;
    fflush(stdin);
    fflush(stdout);
    fprintf(stderr, "\n");
}

// Introdução do simpletron.
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

// Menu de interação do simpletron.
void print_menu(bool machine_status) {
    if(setlocale(LC_ALL, "") == NULL) {
        fprintf(stderr, "error while setlocale()\n");
    }
    if(machine_status is true)
        fprintf(stderr, ANSI_COLOR_RED "\n\t***                 * Simpletron com memória cheia *                ***\n"ANSI_COLOR_RESET);
    else 
        fprintf(stderr, ANSI_COLOR_GREEN "\n\t***                 * Simpletron com memória livre *                ***\n"ANSI_COLOR_RESET);
    fprintf(stderr,ANSI_COLOR_RESET " [" ANSI_COLOR_GREEN "1" ANSI_COLOR_RESET "] " ANSI_COLOR_RESET " - Inserir outro programa\n" ANSI_COLOR_RESET);
    fprintf(stderr,ANSI_COLOR_RESET " [" ANSI_COLOR_GREEN "2" ANSI_COLOR_RESET "] " ANSI_COLOR_RESET " - Salvar Arquivo\n" ANSI_COLOR_RESET);
    fprintf(stderr,ANSI_COLOR_RESET " [" ANSI_COLOR_GREEN "3" ANSI_COLOR_RESET "] " ANSI_COLOR_RESET " - Carregar Arquivo\n" ANSI_COLOR_RESET);
    fprintf(stderr,ANSI_COLOR_RESET " [" ANSI_COLOR_GREEN "4" ANSI_COLOR_RESET "] " ANSI_COLOR_RESET " - Limpar Memória Simpletron\n" ANSI_COLOR_RESET);
    fprintf(stderr,ANSI_COLOR_RESET " [" ANSI_COLOR_RED "0" ANSI_COLOR_RESET "] " ANSI_COLOR_RESET " - Sair do programa\n" ANSI_COLOR_RESET);
    fflush(stdin);
    fflush(stdout);
}

// Verificar os argumentos caso iniciado direito pelo CMD passando uma arquivo.
bool check_arguments(const int num_arguments) {
    return num_arguments < 2 ? false : true;
}

// Verifica se o input é válido.
bool valid_input(int word) {
    if(word <= 9999 && word >= -9999) return true;
    else return false;
}

// Função principal responsável por executar a lógica do simpletron.
int start_machine(int argc, char *argv[], bool dump_status, bool trace_status) {
    fprintf(stderr, "\n             [start_machine]\n");
    fflush(stdin);
    if(setlocale(LC_ALL, "") == NULL) {
        fprintf(stderr, "error while setlocale()\n");
    }
    enum exit_val e_val = ERROR_NONE;
    simpletron v1;
    v1.status = false;
    int option = -1;
    print_intro();
    memory_init(&v1);
    if (check_arguments(argc)) {
        char filename[20];
        strcpy_s(filename, sizeof(filename), argv[1]);
        if(load_program(&v1, filename))
            fprintf(stderr, "\nPrograma carregado com sucesso!\n");
        else
            exit(EXIT_FAILURE);
        e_val = execute_code(&v1);
        print_warning(v1, e_val);
        if(save_program(&v1)) {
            fprintf(stderr, "\nPrograma salvo com sucesso!\n");
        } else {
            fprintf(stderr, "\nErro ao salvar o programa\n");
            return ERROR_INVALID;
        }
        if(dump_status) dump(v1);
        return e_val;
    } else {
        input(&v1);
        size_t i = 0;
        while(v1.memory[i] not_eq -9999 and v1.memory[i] not_eq 0) {
            fprintf(
                    stderr,
                    "Memoria[%zu]:" ANSI_COLOR_YELLOW "%hd\n" ANSI_COLOR_RESET, i, v1.memory[i]
                    );
            i++;
        }
        e_val = execute_code_input(&v1, trace_status);
        print_warning(v1, e_val);
        if(dump_status) dump(v1);
        v1.status = true;
        print_menu(v1.status);
        while(option not_eq 0) {    // se for 0, sai do loop e do programa, ultimo e_val é retornado por padrão.
            fflush(stdout);
            fflush(stdin);
            fprintf(stderr, "\n>: ");
            fflush(stdin);
            fflush(stdout);
            scanf_s("%d", &option);
            fflush(stdin);
            fflush(stdout);
            if(option is 1) {   // Carregar instruções de um programa e realizar operação.
                if(v1.status is true) {
                    fprintf(stderr,
                            ANSI_COLOR_YELLOW
                            "\n[AVISO!]: Limpe a memória do simpletron antes de executar um programa.\n"
                            ANSI_COLOR_RESET
                            );
                } else {
                    input(&v1);
                    i = 0;
                    while(v1.memory[i] not_eq -9999 and v1.memory[i] not_eq 0) {
                        fprintf(
                                stderr,
                                ANSI_COLOR_CYAN
                                "Memoria[%zu]:" ANSI_COLOR_YELLOW "%hd\n" ANSI_COLOR_RESET, i, v1.memory[i]
                                );
                        i++;
                    }
                    e_val = execute_code_input(&v1, trace_status);
                    print_warning(v1, e_val);
                    if(dump_status) dump(v1);
                    v1.status = true;
                }
            } else if(option is 2) {   // Salvar o programa em um arquivo.
                if(save_program(&v1)) {
                    fprintf(stderr, "Programa salvo com sucesso!");
                } else {
                    fprintf(stderr, "Erro ao salvar o programa");
                    return ERROR_INVALID;
                }
            } else if(option is 3) {   // Carregar o programa de um arquivo.
                char filename[20];
                fprintf(stderr, ANSI_COLOR_BLUE "* Digite o nome do arquivo (.txt ou .sml) *\n" ANSI_COLOR_RESET "\n>: ");
                scanf_s("%s", filename, sizeof(filename));
                if(load_program(&v1, filename)) {
                    fprintf(stderr, ANSI_COLOR_GREEN "\nPrograma carregado com sucesso!\n" ANSI_COLOR_RESET);
                    e_val = execute_code_input(&v1, trace_status);
                    print_warning(v1, e_val);
                    if(dump_status) dump(v1);
                    v1.status = true;
                } else {
                    fprintf(stderr, ANSI_COLOR_RED "\n[Erro ao carregar o programa]\n" ANSI_COLOR_RESET);
                    exit(EXIT_FAILURE);
                }
            } else if(option is 4) {
                memory_reset(&v1);
            } else if(option is 0){
                return ERROR_NONE;
            } else {
                fprintf(stderr, ANSI_COLOR_YELLOW "\n[AVISO!]: Opção inválida.\n" ANSI_COLOR_RESET);
            }
            print_menu(v1.status);
        }
        return e_val;
    }
}

// Inicia a memória do simpletron.
static void memory_init(simpletron *v1) {
    fflush(stdin);
    static mem_type mem[MEM_SIZE];
    v1->mem_size = MEM_SIZE;
    v1->memory = mem;
    v1->status = false;
    fprintf(stderr, ANSI_COLOR_GREEN "[Memória alocada]" ANSI_COLOR_RESET "\n");
    pause();
}

// Limpa a memória do simpletron.
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
    fprintf(stderr, ANSI_COLOR_GREEN "[Memória re-alocada]" ANSI_COLOR_RESET "\n");
}

// Leitura de input pelo usuário
static void input(simpletron *v1) {
    mem_type instruction = 0;
    size_t i = 0;
    fflush(stdin);
    fprintf(stderr, "\n00 ?");
    scanf_s("%hd", &instruction);
    fflush(stdout);
    fseek(stdin, 0, SEEK_END);
    while(i < v1->mem_size) {
        if(instruction is -9999) break;
        if (valid_input(instruction)) {
            v1->memory[i] = instruction;
        } else {
            fprintf(stderr, ANSI_COLOR_RED "[ERROR] - PALAVRA INVÁLIDA!!!\n" ANSI_COLOR_RESET);
            i--;
        }
        fprintf(stderr, "%4d ?", instruction);
        scanf_s("%hd", &instruction);
        fseek(stdin, 0, SEEK_END);
        i++;
    }
}

// Salva o programa na memória para um arquivo saída
// TODO: por alguma desgraça infernal o fopen_s se recusa a ler uma string para salvar o arquivo, então deixei uma constante.
bool save_program(simpletron *v1) {
    FILE *out;
    if(fopen_s(&out, "out.sml", "w+")) {    // se ocorrer um erro, sair da função de save.
        fclose(out);
        return false;
    } else {
        size_t index = 0;
        fprintf(stderr, ANSI_COLOR_YELLOW "\n           [SAVE]\n" ANSI_COLOR_RESET);
        while(index < v1->program_counter) {    // Enquanto index for menor que o program counter.
            // Salvar apenas instruções válidas e evitar salvar lixo da memória caso ocorra.
            fprintf(stderr, "*");
            Sleep(2);
            if(((int)v1->memory[(int)index] > 999) && ((int)v1->memory[(int)index] < 9999)) {
                fprintf(out, "%hd\n", v1->memory[(int)index]);
            }
            index++;
        }
        fprintf(stderr,"\n");
    }
    fprintf(out, "%d\n", -9999);
    fclose(out);
    fflush(out);
    return true;
}

// Carrega o programa para o simpletron de um arquivo.
bool load_program(simpletron *v1, char filename[]) {
    FILE *in;
    int errnum;
    errno_t err;
    if(filename is NULL) {
        char buf[255];
        strerror_s(buf, sizeof buf, err);
        fprintf(stderr, "ERROR: %d Não foi possível abrir %s %s\n",
                errnum, filename, buf);
        pause();
        return false;
    }
    if(fopen_s(&in, filename, "r")) { // deu ruim
        fclose(in);     // fecha o arquivo.
        return false;
    } else {
        char cursor;                    // "cursor" em char.
        char ignore[1024];              // buffer de lixo/comentário, não é processado.
        char buffer[1024];              // buffer de entrada do arquivo para o programa.
        char string_instruction[4];     // instrução até 5 espaços: {+/- N N N N \0}

        int j = 0,  k = 0, sign = 1;    // index controlador das instruções e gerações da string de instrução.
        int instruction;                // usado para gerar a instrução do arquivo.
        int index = 0;                  // index percorrer o buffer.
        // Lendo instrução char por char.
        fprintf(stderr, ANSI_COLOR_YELLOW "\n           [LOAD] - " ANSI_COLOR_GREEN "%s\n" ANSI_COLOR_RESET, filename);
        while((cursor = fgetc(in)) not_eq EOF) {    // enquanto não chega no fim do arquivo, ler char a char.
            fprintf(stderr, "*");
            Sleep(2);
            if(cursor == '#') {
                fgets(ignore, sizeof(ignore), in);
                continue;
            } else if(cursor is ' ') {  // ignora espaço
                continue;
            } else {    // lendo char a char e armazenando no buffer.
                buffer[index] = cursor;
                index++;
            }
        }
        fprintf(stderr,"\n");
        // Convertendo para inteiro e armazenando o resultado.
        for(int i = 0; i < index; i++) {
            if(j == 4) {
                j = 0;
                sscanf_s(string_instruction, "%d", &instruction); // converte a string para inteiro.
                v1->memory[k] = (mem_type) (instruction * sign);
                fprintf(stderr, ANSI_COLOR_YELLOW "[Instrução]: %+05d\n" ANSI_COLOR_RESET, v1->memory[k]);
                k++;                                    // incrementa o index da memória.
            } else if(buffer[i] is '+') {
                sign = 1;
            } else if(buffer[i] is '-') {
                sign = -1;
            } else {    // constroi a string de instrução.
                string_instruction[j] = buffer[i];
                j++;
            }
        }
        fclose(in);
        fflush(in);
        return true;
    }
}

// Mostra uma mensagem de aviso caso necessário.
static void print_warning(simpletron v1, enum exit_val e_val) {
    char buffer[120];
    if(e_val == ERROR_NONE)
        return;
    if(e_val == ERROR_INVALID)
        sprintf(buffer, "AVISO:%+05d: %s\n", v1.instruction_register,warning[e_val]);
    else
        sprintf(buffer, "AVISO: %s\n", warning[e_val]);
}

// Função onde as instruções são lidas, carregadas e executadas.
static enum exit_val execute_code(simpletron *v1) {
    v1->program_counter = 0;
    v1->accumulator = 0;

    while(v1->program_counter < v1->mem_size) {
        v1->instruction_register = v1->memory[v1->program_counter];
        v1->op_code = v1->instruction_register / 100;
        v1->operand = v1->instruction_register % 100;

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