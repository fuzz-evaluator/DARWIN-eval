#include "afl_darwin.h"
#include "rand.h"
#include <stdio.h>

unsigned kAflNumMutationOperators;
uint8_t *choices;
uint32_t weight_sum;
uint32_t mutations_since_reweight;

#ifndef MUTATION_LOGGING
  #define MUTATION_LOGGING 0
#endif

#if MUTATION_LOGGING == 1
FILE *mutation_log;
#endif

#define MUTATIONS_BEFORE_REWEIGHT (1 << 20)
#define MUTATION_SELECT_PRECISION 128

/*
 * Initialize data structures for DARWIN
 * @nr_mutations: number of mutation operators
*/
void RAND_DARWIN_init(unsigned nr_mutations) {
    // init RNG
    rand_init();

    kAflNumMutationOperators = nr_mutations;

    // initialise mutations with equal weight
    mutations_since_reweight = 0;
    choices = calloc(kAflNumMutationOperators, MUTATION_SELECT_PRECISION);
    for (size_t i = 0; i < kAflNumMutationOperators; i++) {
        choices[i] = i;
    }
    weight_sum = kAflNumMutationOperators;

#if MUTATION_LOGGING == 1
    mutation_log = fopen("mutations.log", "w");
    fprintf(mutation_log, "Initialised mutations with equal weight, let's fuzz!\n");
#endif
}

/*
 * Choose an AFL mutation operator
 * @seed: seed to select per-seed vector
*/
int RAND_DARWIN_SelectOperator()
{
    if (mutations_since_reweight >= MUTATIONS_BEFORE_REWEIGHT) {
#if MUTATION_LOGGING == 1
        fprintf(mutation_log, "Reweights: ");
#endif
        mutations_since_reweight = 0;
        weight_sum = 0;
        for (size_t i = 0; i < kAflNumMutationOperators; i++) {
            uint16_t weight = 1 + rand_32_int(MUTATION_SELECT_PRECISION);
            for (size_t j = 0; j < weight; j++, weight_sum++) {
                choices[weight_sum] = i;
            }
#if MUTATION_LOGGING == 1
            fprintf(mutation_log, "(%ld, %d), ", i, weight);
#endif
        }
#if MUTATION_LOGGING == 1
        fprintf(mutation_log, "sum: %d\n", weight_sum);
#endif
    } else {
        mutations_since_reweight += 1;
    }
    uint32_t selection = rand_32_int(weight_sum);
    int choice = choices[selection];
#if MUTATION_LOGGING == 1
    fprintf(mutation_log, "%d\n", choice);
#endif
    return choice;
}
