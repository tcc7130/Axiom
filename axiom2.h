#define VARIABLE_NAME 0
#define VARIABLE_TYPE 1
#define LOOP_WHILE 2

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
struct token *createToken(int id, char *word, struct token *tok);
void lex(FILE *fp);