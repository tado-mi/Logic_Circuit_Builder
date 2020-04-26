#include "../functions.h"

int is_operation(char x){

	return (x == '+') || (x == '-') || (x == '*') || (x == '/') || (x == '!');

}

int power(int base, int power){

	int ans = 1;

	for (int i = 0; i < power; i++){

    	ans = ans * base;

    }

	return ans;

}

// whether a character and index 'end' has occured before the index 'end'
int is_unique(int end, char* string){

	char c = *(string + end);

	for(int i = 0; i < end; i++){

		if (c == *(string + i)) return 0;

	}

	return 1;
}

// counts how many variables are in the provided logic expression
int num_of_input(char* post){

	int count = 0;

	for (int i = 0; *(post + i) != '\0'; i++){

		char c = *(post + i);
		if (!is_operation(c) && is_unique(i, post)) count = count + 1;

	}

	return count;

}

// returns the precedence of the operator for implementation of postfix convertor
int preced(char* op){

	if (strcmp(op, "or") == 0  || strcmp(op, "+") == 0) return 1;

	if (strcmp(op, "and") == 0  || strcmp(op, "*") == 0) return 2;

	if (strcmp(op, "not") == 0  || strcmp(op, "!") == 0) return 3;

	return 4;

}

// hard coded support for conversion of 3 allowed variables to numerical values
int convert(char c) {

	switch(c) {

		case 'x' :
			return 0;
		case 'y' :
			return 1;
		case 'z' :
			return 2;

	}

}
