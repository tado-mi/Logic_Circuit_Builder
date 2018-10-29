typedef struct stack *stack;
struct stack{

	char* data;
	stack next;

};

stack new_stack(char* i){
	
	stack me = (stack) malloc(sizeof(struct stack));
	(*me).data = i;
	(*me).next = NULL;
	
	return me;
	
}

stack head;

void print_stack(){
	
	stack temp = head;
	while(temp != NULL){
		
		printf("%s\n", (*temp).data);
		temp = (*temp).next;
		
	}
	
	printf("___\n\n");
	
}

stack pop(){
	
	stack temp = head;
	if (head != NULL) head = (*head).next;	
	return temp;
	
}

stack peek(){
	
	return head;
	
}

void push(char* i){
	
	stack temp = head;
	head = new_stack(i);
	if (temp != NULL) (*head).next = temp;
	
}

