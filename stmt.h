typedef enum {
	STMT_START,
	STMT_DECL,
	STMT_EXPR,
	STMT_IF_ELSE,
	STMT_FOR,
	STMT_PRINT,
	STMT_RETURN,
	STMT_BLOCK,
	STMT_READ
} stmt_t;

struct stmt {
	stmt_t kind;
	struct decl *decl;
	struct expr *init_expr;
	struct expr *expr;
	struct expr *next_expr;
	struct stmt *body;
	struct stmt *else_body;
	struct stmt *next;
};


struct stmt createStmt(stmt_t k);

struct stmt createStmt(stmt_t k){
	struct stmt *s = malloc(sizeof(*s));
	s->kind=k;
	s->next=NULL;

	return s;
}

