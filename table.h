struct table{
	struct symbol *start;
	int size;
};

struct symbol{
	char *name;
	TokenType type;
	int valueI;
	float valueF;
	char valueC;
	char *valueS;
	struct symbol *next;
};

struct table *createTable(){
	struct table *t = malloc(sizeof(struct table));
	t->start = NULL;
	t->size = 0;
	return t;
}
void addSymbol(struct symbol *s, struct table *t){
	int size = 0;
	size = t->size;
	struct symbol *temp = malloc(sizeof(struct symbol));

	if(t->start == NULL){
		t->start = s;
	}
	 else {
	 	temp=t->start;
	 	while(temp->next!=NULL)
	 		temp=temp->next;
	 	temp->next=s;		
	}
	t->size=size+1;
}
struct symbol *createSymbol(char *n, TokenType t){
	struct symbol *s = malloc(sizeof(*s));
	s->name=n;
	s->next=NULL;
	s->type=t;
	return s;
}

struct symbol *checkTypeAssign(struct symbol *s, struct token *t){
	int b = s->type == t->id ? 1: 0;
	if(b==1){
		switch(t->id){
			case INTEGER: 
				s->valueI = atol(t->content); 
				break;
			case DECIMAL: 
				s->valueF = atof(t->content); 
				break;
			case STRING: 
				s->valueS=malloc(sizeof(t->content));
				strcpy(s->valueS,t->content);
				break;
			case KCHAR:	
				s->valueC = t->content[0];
		}
	} else if(s->type == INTEGER){
		switch(t->id){
			case DECIMAL: 
				s->valueI = atol(t->content); 
				break;
			case STRING: 
				printf("ERROR: Variable %s is type int and value is str in line %i\n",s->name,t->line);
				s->valueI = 0;
				break;
			case KCHAR:	
				s->valueI = t->content[0];
		}
	} else if(s->type == KCHAR){
		switch(t->id){
			case INTEGER: 
				s->valueC = atol(t->content); 
				break;
			case DECIMAL: 
				s->valueC = atol(t->content); 
				break;
			case STRING: 
				printf("ERROR: Variable %s is type char and value is str in line\n",s->name,t->line);				
				s->valueC = 0;
		}
	} else if(s->type == DECIMAL){
		switch(t->id){
			case INTEGER: 
				s->valueF = atof(t->content); 
				break;
			case STRING: 
				printf("ERROR: Variable %s is type double and value is str in line\n",s->name,t->line);
				s->valueF = 0; 
				break;
			case KCHAR:	
				s->valueF = atof(t->content);
		}
	} else{
		s->valueS=malloc(sizeof(t->content));
		strcpy(s->valueS,t->content);
	}
	return s;
}

TokenType checkType(char *word){
	TokenType t;
	if(!strcmp(word, "int"))
		t=INTEGER;
	else if(!strcmp(word, "double"))
		t= DECIMAL;
	else if(!strcmp(word, "char"))
		t= KCHAR;
	else
		t=STRING;
	return t;
}

struct symbol *checkVariable(char *word, struct table *t){
	struct symbol *temp;
	temp=t->start;
	while(temp!=NULL){
		if(!strcmp(temp->name, word))
			return temp;
		temp=temp->next;
	}
	return NULL;
}

void printTable(struct table *t){
	struct symbol *temp;
	if(t->start!=NULL){
		temp=t->start;
		while(temp!=NULL){
			switch(temp->type){
				case INTEGER: 
					printf("Variable name: %s type: %i value: %i\n", temp->name,temp->type,temp->valueI);
					break;
				case STRING:  
					printf("Variable name: %s type: %i value: %s\n", temp->name,temp->type,temp->valueS);
					break;
				case KCHAR:	
					printf("Variable name: %s type: %i value: %c\n", temp->name,temp->type,temp->valueC);
					break;
				case DECIMAL:
					printf("Variable name: %s type: %i value: %f\n", temp->name,temp->type,temp->valueF);

			}
			temp=temp->next;
		}
	}
	printf("Table size: %i\n",t->size);
}
