typedef enum {
	TYPE_FLOAT,
	TYPE_CHARACTER,
	TYPE_INTEGER,
	TYPE_STRING,
	TYPE_ARRAY,
	TYPE_VOID
} type_t;

struct type {
	type_t kind;
	struct type *subtype;
};