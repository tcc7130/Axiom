typedef enum {
	EXPR_ADD,
	EXPR_SUB,
	EXPR_MUL,
	EXPR_DIV,
	EXPR_EQS,
	EXPR_NEQ,
	EXPR_GRT,
	EXPR_GRE,
	EXPR_LST,
	EXPR_LSE,
	EXPR_ASN,
	EXPR_NAME,
	EXPR_INTEGER_LITERAL,
	EXPR_STRING_LITERAL,
	EXPR_CHAR_LITERAL,
	EXPR_FLOAT_LITERAL,
} expr_t;

struct expr {
	expr_t kind;
	struct expr *left;
	struct expr *right;
	const char *name;
	int integer_literal;
	const char * string_literal;
	char char_literal;
	float float_literal; // float o double??
};

struct expr *createExpr(expr_t k, struct expr *l, struct expr *r);
struct expr *createExprIntegerLiteral(int i);
struct expr *createExprStringLiteral(const char *s);
struct expr *createExprCharLiteral(char c);
struct expr *createExprFloatLiteral(float f);

struct expr *createExpr(expr_t k, struct expr *l, struct expr *r){
	struct expr *e = malloc(sizeof(*e));
	e->kind = k;
	e->left = l;
	e->right = r;

	return e;
}

struct expr *createExprIntegerLiteral(int i){
	struct expr *e = malloc(sizeof(*e));
	e->kind = EXPR_INTEGER_LITERAL;
	e->integer_literal = i;
	return e;
}
struct expr *createExprStringLiteral(const char *s){
	struct expr *e = malloc(sizeof(*e));
	e->kind = EXPR_STRING_LITERAL;
	e->string_literal = s;
	return e;
}
struct expr *createExprCharLiteral(char c){
	struct expr *e = malloc(sizeof(*e));
	e->kind = EXPR_CHAR_LITERAL;
	e->char_literal = c;
	return e;
}
struct expr *createExprFloatLiteral(float f){
	struct expr *e = malloc(sizeof(*e));
	e->kind = EXPR_FLOAT_LITERAL;
	e->float_literal = f;
	return e;
}

