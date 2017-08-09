#include "ipasir.h"
#include "ipasir_max.h"
#include <stdio.h>

int main(int argc, char **argv) {
    printf("%s\n", ipasir_signature());
    void* solver = ipasir_init();

    ipasir_add(solver, 1);
    ipasir_add_soft(solver, 15);

    if (ipasir_solve(solver) == 10) {
        printf("SAT %d %d\n", ipasir_val(solver, 1), 0/*ipasir_val(solver, 2)*/);
    } else {
        printf("UNSAT");
    }

    ipasir_release(solver);
}