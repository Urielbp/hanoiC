#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "estado.h"
#include "aEstrella.h"


int main() {
    bool suceso = false;

    suceso = aEstrella();

    if(suceso == true) {
        printf("\nRetorno con suceso\n");
        return EXIT_SUCCESS;
    }
    else {
        printf("\nRetorno con fallo\n");
        return EXIT_FAILURE;
    }
}