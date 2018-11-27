struct table{
	struct symbol *start;
	struct symbol *current;
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
				s->valueI = t->content;
				break;
			case DECIMAL:
				s->valueF = t->content;
				break;
			case STRING:
				s->valueS = t->content;
				break;
			case KCHAR:
				s->valueC = t->content;
		}
		return s;
	} else
		return NULL;
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