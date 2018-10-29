#include <stdio.h>
#include <stdlib.h>

#include "header.h"

int evaluate(char* post, char* assign){
	
	printf("truth assignment: %s\n",assign);
	
	// sets up the switches according to the truth assignment
	circuit circ = set_switch(build(post), create_switch(assign, num_of_input(post)));

	int val = eval_circ(circ);
	char c = (val)? 'T' : 'F';
	printf("value of the expression: %c\n\n", c);

	return val;
	
}

char* count(int i, int length, char* var_names){
    
    length = 6 * length + 1;
    
    char* answer = malloc((length + 1) * sizeof(char));
    
    if (i == 0) {
        
        *answer = var_names[0];
        *(answer + 1) = ':';
        *(answer + 2) = ' ';
        *(answer + 3) = 'F';
        *(answer + 4) = ';';
        *(answer + 5) = ' ';
    }
    
    int var_index = 0;
    int j = 0;

    // string juggling for obtaining a nice string of form "x: T; y: F; z: T"
    for (j; i > 0; j = j + 6){
    
        char val = 'F';
    
        if ((i % 2) == 1) val = 'T';
        
        *(answer + j) = var_names[var_index];
        *(answer + j + 1) = ':';
        *(answer + j + 2) = ' ';
        *(answer + j + 3) = val;
        *(answer + j + 4) = ';';
        *(answer + j + 5) = ' ';
        
        var_index = var_index + 1;
        i = i / 2;
    
    }
    
    for (j; j < length; j = j + 6){
        
        *(answer + j) = var_names[var_index];
        *(answer + j + 1) = ':';
        *(answer + j + 2) = ' ';
        *(answer + j + 3) = 'F';
        *(answer + j + 4) = ';';
        *(answer + j + 5) = ' ';
        var_index = var_index + 1;
    }
    
   *(answer + j) = '\0';
   
   return answer;
   
}

void run(char* exp, char* given_assignment){
	
	printf("inputed expresion: %s;\n", exp);
	
	char* post = postfix(exp);

	if (given_assignment != "no_assignment") {

		evaluate(post, given_assignment);
		return;

	}

	// else loop through all possible assignments

	int n	= num_of_input(post); // number of variables
	int num = power(2, n); // number of possible truth assignments
	
	for (int i = 0; i < num; i++){

		// count 'converts' i to binary and uses it to set truth value assignments to the variables
		// i iterates from 0 to num - 1, which covers the possible range
		char* assign = count(i, n - 1, "xyz");

        	evaluate(post, assign);
    	
	}
	
	printf("\n----------------------------\n\n\n");

}

// initiates and test 3 circuits
int main(){

	char* temp = malloc(100 * sizeof(char));

	printf("welcome to logic circuit builder\n\n");

	printf("number of allowed variables:\t 3\n");
	printf("supported operations:\t\t or, and, not, not, nand\n");
	printf("supported characters:\t\t a, d, n, o, r, t, x, y, z, (, )\n");  

	printf("\n");

	while (1) {

		printf("please, enter the expression:\t ");
		fgets(temp, 100, stdin);

		int   len = string_length(temp);
		char* usr_input = malloc(len * sizeof(char));

		for (int i = 0; *(temp + i) != '\n'; i++) {

			*(usr_input + i) = *(temp + i);

		}

		*(usr_input + (len - 1)) = '\0';

		printf("would you like to provide value assignment? [y/n] ");
		fgets(temp, 100, stdin);

		if (*temp == 'y') {

			printf("please follow this sample format exactly\n");
			printf("\tx: F; y: T; z: F\n");

			printf("your input: ");
			fgets(temp, 100, stdin);
			
			int   len = string_length(temp);
			char* usr_assgn = malloc(len * sizeof(char));

			for (int i = 0; *(temp + i) != '\n'; i++) {

				*(usr_assgn + i) = *(temp + i);

			}

			*(usr_assgn + (len - 1)) = '\0';

			run(usr_input, usr_assgn);
		
		} else {

			run(usr_input, "no_assignment");
		
		}

		printf("would you like to continue? [y/n] ");
		fgets(temp, 100, stdin);

		if (*temp == 'n') break;

		printf("\n");

	}
    
	printf("terminated\n");	

	return 0;
	
}
