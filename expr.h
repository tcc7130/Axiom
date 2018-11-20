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
	EXPR_INTEGER_LITERAL,
	EXPR_STRING_LITERAL,
	EXPR_CHAR_LITERAL,
	EXPR_FLOAT_LITERAL,
} expr_t;

struct expr {
	expr_t kind;
	struct expr *left;
	struct expr *right;
	int integer_literal;
	const char * string_literal;
	const char char_literal;
	float float_literal; // float o double??
};

struct expr *createExpr(expr_t )