#define VARIABLE_NAME 0
#define VARIABLE_TYPE 1
#define KEYWORD_WHILE 2
#define KEYWORD_FOR 3
#define KEYWORD_IF 4
#define KEYWORD_ELSE 5
#define KEYWORD_ELIF 6
#define KEYWORD_READ 7
#define KEYWORD_PRINT 8
#define KEYWORD_PRINTLN 9

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