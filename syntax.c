struct token *Expression(struct token *tk){
	printf("EXPRESSION START: %s\n", tk->content);
	if(tk->id == KEYWORD_IF){
		//printf("%s\n", tk->content);
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
	printf("0\n");
	if(tk->id == KEYWORD_IF){
		tk = tk->next;
		if(tk->id == PAREN_L){
			tk = tk->next;
			if(tk->id == VARIABLE_NAME){
				printf("3. %s\n", tk->content);
				tk = tk->next;
				if(tk->id == PAREN_R){
					printf("%s\n", tk->content);
					tk = tk->next;
					if(tk->id == LLAVE_L){
						printf("%s\n", tk->content);
						tk = tk->next;
						if(tk->id == LLAVE_R){
							printf("%s\n", tk->content);
							printf("NICE\n");
							return tk->next;
						}
					}
				}
			}
			else{
				printf("2. %s\n", tk->content);
				tk = Variable(tk);
				if(tk != NULL){
				printf("3. %s\n", tk->content);
				tk = tk->next;
				if(tk->id == PAREN_R){
					printf("%s\n", tk->content);
					tk = tk->next;
					if(tk->id == LLAVE_L){
						printf("%s\n", tk->content);
						tk = tk->next;
						if(tk->id == LLAVE_R){
							printf("%s\n", tk->content);
							printf("THE END\n");
							return tk->next;
						}
					}
				}
				}
			}
		}
	}
	return NULL;
}
struct token *Variable(struct token *tk){
	tk = Comparison(tk);
	if(tk != NULL){
		printf("Not comparison\n");
		return tk->next;
	}
	else{
		// tk = Operation(tk);
		// if(tk!=NULL){
		// 	printf("Not operation\n");
		// 	return tk->next;
		// }
		// else 
		if(tk->id == INTEGER || tk->id == DECIMAL || tk->id == STRING){
			printf("IS VARIABLE: %s\n",tk->content);
			return tk->next;
		}
	}

	return NULL;
}
struct token *Comparison(struct token *tk){
	//printf("Checking: %s\n", tk->content);
	if(tk->id == PAREN_L){
		tk = tk->next;
		if(Comparison(tk) != NULL){
			tk = tk->next;
			if(tk->id == PAREN_R){
				return tk->next;
			}
		}
	}
	else{ 
		//printf("AAAH");
		if(tk->id == INTEGER || tk->id == DECIMAL || tk->id == STRING){
			printf("CONSTANT: %s\n", tk->content);
			tk = tk->next;
			if(tk->id == COMPARE_OP){
				printf("COMPARE: %s\n", tk->content);
				printf("VARIABLE? %s\n", tk->next->content);
				tk = Variable(tk->next);
				printf("AH)\n");
				if(tk != NULL){
					printf("EEEH");
					return tk;
				}
			}
		}
		
		tk = Variable(tk);
		if(tk != NULL){
			printf("V %s\n",tk->content);
			tk = tk->next;
			if(tk->id = COMPARE_OP){
				tk = tk->next;
				tk = Variable(tk);
				if(tk != NULL){
					return tk->next;
				}
			}
		}
	}
	printf("VOY A RETURNEAR NULL\n");
	return NULL;
}
struct token *Operation(struct token *tk){
	return NULL;
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