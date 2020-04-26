#include "../circuit.h"

// definition of a circuit
struct circuit{

	char value;
	circuit left;
	circuit right;

};

circuit new_circuit(char c) {

	circuit me = (circuit) malloc(sizeof(struct circuit));
	(*me).value = c;
	(*me).left = NULL;
	(*me).right = NULL;

	return me;

}

void print_circ(circuit c){

	if ((*c).left != NULL) print_circ((*c).left);
	printf("%c ", (*c).value);
	if ((*c).right != NULL) print_circ((*c).right);

}

// generates an 'expression tree' from the postfix of the provided logic expression
circuit build(char* post){

	STACK root = new_STACK();

	for (int i = 0; *(post + i) != '\0'; i++){

		char c = *(post + i);
		circuit focus = new_circuit(c);

		if (is_operation(c)){

			(*focus).right = pop(root);
			if (c != '!') (*focus).left = pop(root);

		}

		push(root, focus);

	}

	return pop(root);

}

circuit set_switch(circuit c, circuit* input){

	// value of the right branch
	// note: right branch is never null
	char rc_val = (*(*c).right).value;

	if (is_operation(rc_val)) {

		// carry on setting switches on the right branch
		set_switch((*c).right, input);

	} else {

		// modify the value of the right branch
		(*c).right = *(input + convert(rc_val));

	}

	if ((*c).left != NULL) {

		char lc_val = (*(*c).left).value;

		if (is_operation(lc_val)) {

			// carry on setting switches on the left branch
			set_switch((*c).left, input);

		} else {

			// modify the value of the left branch
			(*c).left = *(input + convert(lc_val));

		}

	}

	// now the circuit has been modifies as required
	return c;

}

// assigs truth values to the variables of the circuit
// ie: switches them on or off
circuit* create_switch(char* assign, int n){

	char input_state[n]; 	// state of a variable, on or off
	int  index[n];		// the index of the variable

	for (int i = 0; i < n; i++){

	    while (*assign == ' ' || *assign == ':' || *assign == ';' || *assign == 'T' || *assign == 'F') assign++;

		char var_name = *assign;
		index[i] = convert(var_name);

		while (!(*assign == 'T' || *assign == 'F')) assign++;

		char var_val = *assign;

		if (var_val == 'T') input_state[convert(var_name)] = '1';

		if (var_val == 'F') input_state[convert(var_name)] = '0';

	}

	circuit* input = (circuit*) malloc(n * (sizeof(struct circuit)));

	for (int i = 0; i < n; i++) {

		*(input + index[i]) = new_circuit(input_state[i]);

	}

	return input;

}

int eval_circ(circuit c){

	switch ((*c).value){

		case '+' : // or gate
			return eval_circ((*c).left) + eval_circ((*c).right);
		case '*' : // and gate
			return eval_circ((*c).left) * eval_circ((*c).right);
		case '!' : // not gate
			return (1 + eval_circ((*c).right)) % 2;
		case '-' : // nor gate
			return (1 + (eval_circ((*c).left) + eval_circ((*c).right))) % 2;
		case '/' : // nand gate
			return (1 + (eval_circ((*c).left) * eval_circ((*c).right))) % 2;
		case '1' :
			return 1;
		case '0' :
			return 0;

	}

}
