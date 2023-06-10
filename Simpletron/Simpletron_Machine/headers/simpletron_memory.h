//
// Created by Magoimortal_br on 11/03/2023.
//

#ifndef SIMPLETRON_SIMPLETRON_MEMORY_H
#define SIMPLETRON_SIMPLETRON_MEMORY_H

#include <stdint.h>

#define MEM_SIZE 100        // Total de instruções que cabem na palavra.
#define MEM_MAX 9999        // Máximo na memória.
#define MEM_MIN -9999       // Mínimo na memória.
#define INSTRUCTION_SIZE 4  // Tamanho da palavra/instrição.
// #define OP_SIZE 2        Não sei pq fiz isso.

typedef int16_t mem_type;

enum operations {
    READ = 10,              // Leitura da instrução para a memória.
    WRITE = 11,             // Escrever da memória para a saída.
    LOAD = 20,              // Carrega da memória para para o acumulador.
    STORE = 21,             // Armazena do acumulador para um local na memória.
    ADD = 30,               // Adiciona uma palavra da memória para o acumulador.
    SUBTRACT = 31,          // Subtrai uma palavra da memória no acumulador.
    DIVIDE = 32,            // Divide uma palavra da memória para dentro acumulador.
    MULTIPLY = 33,          // Multiplica a palavra da memória pela existente no acumulador.
    REMAINDER = 34,         // Calcula o resto usando o acumulador pela palavra na memória.
    BRANCH = 50,            // Ramifica para um local específico a memória.
    BRANCH_NEG = 51,        // Ramifica para um local a memória se o acumulaor for negativo.
    BRANCH_ZERO = 52,       // Ramifica para um local a memória se o acumulaor for zero.
    HALT = 53               // Termina o programa.
};

#endif //SIMPLETRON_SIMPLETRON_MEMORY_H
