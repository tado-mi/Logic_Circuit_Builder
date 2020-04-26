#include "../postfix.h"

char* postfix(char* exp) {

	char* answer = malloc((strlen(exp) + 1) * sizeof(char));
	int j = 0;

	STACK S = new_STACK();

	while(*exp != '\0'){

		char temp = *exp;

		if(temp == ' '){

		    exp++;
		    temp = *exp;

		}

		if (temp == 'a' || temp == 'o' || temp == 'n' || temp == '('){

			if (temp == '(') {

			    push(S, "(");
			    exp++;
			    continue;

			}

			char* to_push;

			if (temp == 'n') {

				// operator is either not, nor or nand
				exp++; // cover for 'n'
				exp++; // ignore the second character
				char t = *(exp);

				if (t == 'n'){

					to_push = "/";
					exp++; // covering for second 'n'

				}

				if (t == 'r') to_push = "-";

				if (t == 't') to_push = "!";

			}

			if (temp == 'o') {

				to_push = "+";
				exp++; // covering for 'r'

			}

			if (temp == 'a'){

				to_push = "*";
				exp++; //covering for 'n';
				exp++; //covering for 'd'

			}

			push(S, to_push);


		} else if (temp == ')'){

			char* top = peek(S);

			while(strcmp(top, "(") != 0){

				pop(S);
				*(answer + j) = top[0];
				j = j + 1;
				top = peek(S);

			}

			pop(S); // popping the opening bracket

		} else {

			*(answer + j) = temp;
			j = j + 1;

		}

       	exp++;

	}

	while(!is_empty(S)){

	   char* temp = pop(S);
		*(answer + j) = temp[0];
		j = j + 1;

	}

	*(answer + j) = '\0';

	return answer;

}
