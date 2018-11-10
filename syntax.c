struct token *Expression(struct token *tk){
			printf("%s\n", tk->id);
	if(tk->id == KEYWORD_IF){
		printf("%s\n", tk->content);
		tk = Condition(tk);
	}
	else if(tk->id == VARIABLE_TYPE){
		tk = Declare(tk);
	}
	else if(tk->id == VARIABLE_NAME){
		tk = Assign(tk);
	}
	else if(tk->id == KEYWORD_WHILE){
		tk = Loop_While(tk);
	}
	else if(tk->id == KEYWORD_FOR){
		tk = Loop_For(tk);
	}
	else if(tk->id == KEYWORD_READ){
		tk = Read(tk);
	}
	else if(tk->id == KEYWORD_PRINT){
		tk = Write(tk);
	}
	if(tk->id == SEMICOLON){
	 	printf("Omedetou\n");
	}
	return NULL;
}

struct token *Condition(struct token *tk){
	if(tk->id == KEYWORD_IF){
		printf("%s\n", tk->content);
		tk = tk->next;
		if(tk->id == PAREN_L){
					printf("%s\n", tk->content);
			tk = tk->next;
			//AQUI FALTAN LAS VARIABLES
			if(tk->id == VARIABLE_NAME || Variable(tk)){
						printf("%s\n", tk->content);
				tk = tk->next;
				if(tk->id == PAREN_R){
						printf("%s\n", tk->content);
					tk = tk->next;
					if(tk->id == LLAVE_L){
								printf("%s\n", tk->content);
						tk = tk->next;
						if(tk->id == LLAVE_R){
								printf("%s\n", tk->content);
							tk = tk->next;
						}
					}
				}
			}
		}
	}
	return tk;
}
struct token *Variable(struct token *tk){
	if(Number(tk))
}
struct token *Declare(struct token *tk){
	return NULL;
}
struct token *Assign(struct token *tk){
	return NULL;
}
struct token *Loop_While(struct token *tk){
	return NULL;
}
struct token *Loop_For(struct token *tk){
	return NULL;
}
struct token *Read(struct token *tk){
	return NULL;
}
struct token *Write(struct token *tk){
	return NULL;
}