char* postfix(char* exp){
	
	char* answer = malloc((string_length(exp) + 1) * sizeof(char));
	int j = 0;
	
	while(*exp != '\0'){
		
		char temp = *exp;
		
		if(temp == ' '){
		    
		    exp++;
		    temp = *exp;
		        
		}
		
		if (temp == 'a' || temp == 'o' || temp == 'n' || temp == '('){
			
			if (temp == '(') {
			    
			    push("(");
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
			
			push(to_push);
			
			
		} else if (temp == ')'){

			while((*peek()).data != "("){
				
				stack s = pop();
				*(answer + j) = (*s).data[0];
				j = j + 1;
				
			}
			
			pop(); // popping the opening bracket
			
		} else {
			
			*(answer + j) = temp;
			j = j + 1;
			
		}
        
       	exp++;
		
	}
	
	while(head != NULL){
	    
	    stack temp = pop();
		*(answer + j) = (*temp).data[0];
		j = j + 1;
	    
	}
	
	*(answer + j) = '\0';
	
	return answer;
	
}
