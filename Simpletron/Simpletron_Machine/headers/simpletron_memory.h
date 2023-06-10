//
// Created by Magoimortal_br on 11/03/2023.
//

#ifndef SIMPLETRON_SIMPLETRON_MEMORY_H
#define SIMPLETRON_SIMPLETRON_MEMORY_H

#include <stdint.h>

#define MEM_SIZE 100        // Total de instru��es que cabem na palavra.
#define MEM_MAX 9999        // M�ximo na mem�ria.
#define MEM_MIN -9999       // M�nimo na mem�ria.
#define INSTRUCTION_SIZE 4  // Tamanho da palavra/instri��o.
// #define OP_SIZE 2        N�o sei pq fiz isso.

typedef int16_t mem_type;

enum operations {
    READ = 10,              // Leitura da instru��o para a mem�ria.
    WRITE = 11,             // Escrever da mem�ria para a sa�da.
    LOAD = 20,              // Carrega da mem�ria para para o acumulador.
    STORE = 21,             // Armazena do acumulador para um local na mem�ria.
    ADD = 30,               // Adiciona uma palavra da mem�ria para o acumulador.
    SUBTRACT = 31,          // Subtrai uma palavra da mem�ria no acumulador.
    DIVIDE = 32,            // Divide uma palavra da mem�ria para dentro acumulador.
    MULTIPLY = 33,          // Multiplica a palavra da mem�ria pela existente no acumulador.
    REMAINDER = 34,         // Calcula o resto usando o acumulador pela palavra na mem�ria.
    BRANCH = 50,            // Ramifica para um local espec�fico a mem�ria.
    BRANCH_NEG = 51,        // Ramifica para um local a mem�ria se o acumulaor for negativo.
    BRANCH_ZERO = 52,       // Ramifica para um local a mem�ria se o acumulaor for zero.
    HALT = 53               // Termina o programa.
};

#endif //SIMPLETRON_SIMPLETRON_MEMORY_H
