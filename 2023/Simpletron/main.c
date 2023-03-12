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
    bool dump_status;
    fprintf(stderr,ANSI_COLOR_BLUE "Deseja ver o dump da memória ? " ANSI_COLOR_GREEN " [S] " ANSI_COLOR_RED " [N]\n" ANSI_COLOR_RESET);
    scanf_s("%c", &aux_dump_status, 1);
    dump_status = aux_dump_status == 'S' ? true : false;
    fprintf(stderr, "%d", start_machine(argc, argv, dump_status));
    return 0;
}
