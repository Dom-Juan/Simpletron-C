//
// Created by Magoimortal_br on 11/03/2023.
//

#ifndef SIMPLETRON_HELPERS_H
#define SIMPLETRON_HELPERS_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>

void pause(){
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)	// Caso seja Linux ou Mac
    system("read -p 'Press Enter to continue...' var");
#endif

#if defined(_WIN32) || defined(_WIN64) 								// Windows 32 ou 64 bits
    system("pause");
#endif

}

// Limpando a tela conforme o sistema operacional do usuario, tambem definido por macros
void clrscr(){
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)	// Caso seja Linux ou Mac
    system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)								// Windows 32 ou 64 bits
    system("cls");
#endif
}

// Compara os sufixo do nome do arquivo com a o sufixo dado e retorna um valor boleano
int ends_with_suffix(const char *string, const char *sufix) { // Compra os sufixo do nome do arquivo com a o sufixo dado
    int string_size = strlen(string); // Pegando o tamanho da string
    int sufix_size = strlen(sufix); // Pegando o tamanho do sufixo

    return (string_size >= sufix_size) &&
           (strcmp(string + (string_size-sufix_size), sufix) == 0); // Retorna um valor booleano, depedendo da condicao.
}

#endif //SIMPLETRON_HELPERS_H
