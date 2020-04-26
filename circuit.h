#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

typedef struct circuit *circuit;

extern circuit set_switch(circuit c, circuit* input);
extern circuit build(char* post);
extern circuit* create_switch(char* assign, int n);
extern int eval_circ(circuit c);
