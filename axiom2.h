struct token{
	int id;
	char *content;
	struct token *next;
};

struct tokenList{
	struct token *start;
	int size;
};

int endsToken(char c);
struct token *checksToken(char *word, struct token *tok);
void lex(FILE *fp);