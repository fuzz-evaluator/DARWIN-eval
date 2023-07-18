#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef DARWIN_H
#define DARWIN_H

void RAND_DARWIN_init(unsigned);

int RAND_DARWIN_SelectOperator();

#endif
