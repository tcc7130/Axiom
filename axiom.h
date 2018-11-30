
typedef enum {START,VARIABLE_NAME,VARIABLE_TYPE,KEYWORD_WHILE, KEYWORD_FOR, KEYWORD_IF, KEYWORD_ELSE, KEYWORD_ELIF, KEYWORD_READ,KEYWORD_PRINT, KEYWORD_PRINTLN, INTEGER, ARITMETIC_OP, COMPARE_OP, ASSIGN, INCREMENT, DECREMENT, PAREN_L, PAREN_R,CORCHETE_L, CORCHETE_R, LLAVE_L, LLAVE_R, SEMICOLON, COMILLA_DOB, COMILLA_SIN, COMA, STRING,	DECIMAL, KCHAR,	OPERAND} TokenType;


struct token{
	TokenType id;
	int line;
	char *content;
	struct token *next;
};

struct tokenList{
	struct token *start;
	int size;
};

int endsToken(char c);
struct token *checksToken(char *word, struct token *tok, int line);
struct token *createToken(int id, char *word, struct token *tok, int line);
struct tokenList *lex(FILE *fp);
void syntax(struct tokenList *tokens);

struct token *Expression(struct token *tk);
struct token *Condition(struct token *tk);
struct token *Operation(struct token *tk);
struct token *Declare(struct token *tk);
struct token *Assign(struct token *tk);
struct token *Loop_While(struct token *tk);
struct token *Loop_For(struct token *tk);
struct token *Read(struct token *tk);
struct token *Write(struct token *tk);
struct token *Operand(struct token *tk);
struct token *OperandInt(struct token *tk);
struct token *ArrayVariable(struct token *tk);