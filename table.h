
struct table{
	struct symbol *start;
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

struct symbol createSymbol(char *n){
	struct symbol *s = malloc(sizeof(*s));
	s->name=n;
	s->next=NULL;
	return s;
}