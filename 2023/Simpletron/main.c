#include "Simpletron_Machine/headers/simpletron_machine.h"
#include <locale.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main(int argc, char *argv[]) {
    if(setlocale(LC_ALL, "") == NULL) {
        fprintf(stderr, "error while setlocale()\n");
    }
    setlocale(LC_ALL, "");
    char aux_dump_status;
    char aux_trace_status;

    fprintf(stderr,ANSI_COLOR_BLUE "Deseja ver o dump da Memória ? " ANSI_COLOR_RESET " [" ANSI_COLOR_GREEN "S" ANSI_COLOR_RESET "] " ANSI_COLOR_RESET " [" ANSI_COLOR_RED "N" ANSI_COLOR_RESET "]\n" ANSI_COLOR_RESET);
    scanf_s("%c", &aux_dump_status, 1);
    fseek(stdin, 0, SEEK_END);

    fprintf(stderr,ANSI_COLOR_BLUE "Deseja ver o trace da Execução ? " ANSI_COLOR_RESET " [" ANSI_COLOR_GREEN "S" ANSI_COLOR_RESET "] " ANSI_COLOR_RESET " [" ANSI_COLOR_RED "N" ANSI_COLOR_RESET "]\n" ANSI_COLOR_RESET);
    scanf_s("%c", &aux_trace_status, 1);
    fseek(stdin, 0, SEEK_END);

    bool dump_status = aux_dump_status == 'S' ? true : false;
    bool trace = aux_trace_status == 'S' ? true : false;
    int execution_result = start_machine(argc, argv, dump_status, trace);
    fprintf(stderr, "\nEXIT: %d - %s\n", execution_result, end_execution[execution_result]);
    fprintf(stderr,"Press any key to continue . . .");
    while (1) if (_kbhit()) break;
    return 0;
}
