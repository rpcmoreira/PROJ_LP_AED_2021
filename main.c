#include <stdio.h>
#include "funct.h"
#include "structs.h"
#include "cidade.h"
#include "viagem.h"
#include "cliente.h"


int main(int argc, const char * argv[]) {
    int i = cidade(argc,argv);
    printf("%d", i);
    return 0;
}
