struct decl {
	char *name;
	struct type *type;
	struct expr *value;
	struct decl *next;
};

struct decl *createDecl (char *n, struct type *t, struct expr *v);

struct decl *createDecl (char *n, struct type *t, struct expr *v){
	struct decl *d = malloc(sizeof(*d));
	d->name = n;
	d->type = t;
	d->value = v;
	d->next = NULL;

	return d;
}