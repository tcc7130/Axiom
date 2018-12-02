struct table *t;
struct token *Expression(struct token *tk){
void syntax(struct tokenList *lists){
	//printf("%i\n", lists->start->id);
	struct token *tk;
	struct token *temp;
	//struct table *t;
	// struct symbol *s=createSymbol("inicio");
	// t->start =s;
	// t->current=s;
	tk = lists->start;
	tk = tk->next;

	FILE *fp;
	fp = fopen("wall.e", "wb+");
	if(!fp)
		printf("Could not create output file\n");

	while(1){
		temp = Expression(tk, fp);
		if(temp!= NULL)
			tk = temp;
		else break;
	}
	printf("Done");
	//Expression(tk, fp);
}

struct token *Expression(struct token *tk, FILE *fp){
	printf("EXPRESSION START: %s\n", tk->content);
	switch(tk->id){
		case KEYWORD_IF:
			tk = Condition(tk, fp);
			break;	
		case VARIABLE_TYPE:
			tk = Declare(tk, fp);
			break;
		case VARIABLE_NAME:
			tk = Assign(tk, fp);
			break;
		case KEYWORD_WHILE:
			tk = Loop_While(tk, fp);
			break;
		case KEYWORD_FOR:
			tk = Loop_For(tk, fp);
			break;
		case KEYWORD_READ:
			tk = Read(tk, fp);
			break;
		case KEYWORD_PRINT:
			tk = Write(tk, fp);
			break;
		case KEYWORD_PRINTLN:
			tk = WriteLN(tk, fp);
			break;
		default:
	 		return NULL;
	}
	if(tk->id == SEMICOLON){
		tk = tk->next;
		printf("Omedetou\n");
	} else
		printf("Unexpected token %s in line %i\n",tk->content,tk->line);
	return tk;
}

struct token *Condition(struct token *tk, FILE *fp){
	struct token *temp;
	if(tk->id == KEYWORD_IF){
		tk = tk->next;
		if(tk->id == PAREN_L){
			tk = Operand(tk->next, fp);
			if(tk != NULL){
				if(tk->id == COMPARE_OP){
					printf("HI");
					tk = Operand(tk->next, fp);
					printf("BYE");
					if(tk != NULL){
						if(tk->id == PAREN_R){
							printf("NICE");
							tk = tk->next;
							if(tk->id == LLAVE_L){
								tk = tk->next;
								do{
									printf("Looking for an expression\n");
									temp = Expression(tk, fp);
									if(temp!=NULL) tk = temp;
								}while(temp != NULL);
								if(tk->id == LLAVE_R){
									printf("NICE\n");
									tk = tk->next;
									if (tk->id == KEYWORD_ELSE) {
										tk = tk->next;
										if (tk->id == LLAVE_L) {
											tk = tk->next;
											do {
												printf("Looking for an expression\n");
												temp = Expression(tk, fp);
												if (temp != NULL) tk = temp;
											} while (temp != NULL);
											if (tk->id == LLAVE_R) {
												printf("NICE\n");
												return tk->next;
											}
											else
												printf("Unexpected token %s in line %i\n", tk->content, tk->line);
										}
										else
											printf("Unexpected token %s in line %i\n", tk->content, tk->line);
									}
									if (tk->id== KEYWORD_ELIF) {
										tk = Condition_Elif(tk, fp);
										printf("NICE\n");

										return tk;
									}
									printf("NICE\n");
									return tk->next;
								} else
									printf("Unexpected token %s in line %i\n",tk->content,tk->line);
							} else
								printf("Unexpected token %s in line %i\n",tk->content,tk->line);						
						} else
							printf("Unexpected token %s in line %i\n",tk->content,tk->line);
					} else
						printf("Unexpected token %s in line %i\n",tk->content,tk->line);
				} else
					printf("Unexpected token %s in line %i\n",tk->content,tk->line);
			} else
				printf("Unexpected token %s in line %i\n",tk->content,tk->line);
			}
		}
	printf("CONDITION\n");
	return NULL;
}

struct token *Condition_Elif(struct token *tk, FILE *fp){
	struct token *temp;
	if (tk->id == KEYWORD_ELIF) {
		tk = tk->next;
		if (tk->id == PAREN_L) {
			tk = Operand(tk->next, fp);
			if (tk != NULL) {
				if(tk->id == COMPARE_OP){
					tk = Operand(tk->next, fp);
					if(tk != NULL){		
						if (tk->id == PAREN_R) {
							tk = tk->next;
							if (tk->id == LLAVE_L) {
								tk = tk->next;
								do {
									printf("Looking for an expression\n");
									temp = Expression(tk, fp);
									if (temp != NULL) tk = temp;
								} while (temp != NULL);
								if (tk->id == LLAVE_R) {
									tk = tk->next;
									if (tk->id == KEYWORD_ELSE) {
										tk = tk->next;
										if (tk->id == LLAVE_L) {
											tk = tk->next;
											do {
												printf("Looking for an expression\n");
												temp = Expression(tk, fp);
												if (temp != NULL) tk = temp;
											} while (temp != NULL);
											if (tk->id == LLAVE_R) {
												printf("NICE\n");
												return tk->next;
											}
											else
												printf("Unexpected token %s in line %i\n", tk->content, tk->line);
										}
										else
											printf("Unexpected token %s in line %i\n", tk->content, tk->line);
									}
									else if (tk->id == KEYWORD_ELIF) {
										tk = Condition_Elif(tk, fp);
									}
									printf("NICE");
									printf(tk->content);
									return tk;
								}
								else
									printf("Unexpected token %s in line %i\n", tk->content, tk->line);
							}
							else
								printf("Unexpected token %s in line %i\n", tk->content, tk->line);
						}
						else
							printf("Unexpected token %s in line %i\n", tk->content, tk->line);
					}
					else
						printf("Unexpected token %s in line %i\n", tk->content, tk->line);
				}
				else
					printf("Unexpected token %s in line %i\n", tk->content, tk->line);
			}
		}
	}
	else
		printf("Unexpected token %s in line %i\n", tk->content, tk->line);
	printf("CONDITION\n");
	return NULL;
}
struct token *Declare(struct token *tk){
	struct symbol *sy;
	TokenType type;
	struct token *temp = NULL;
	char *word = malloc(sizeof(*word));

	if(tk->id == VARIABLE_TYPE){
		type=checkType(tk->content);
		tk = tk->next;
		if(tk->id == VARIABLE_NAME){
			word=tk->content;
			sy=createSymbol(word,type);
			tk=tk->next;
			temp=ArrayVariable(tk);
			addSymbol(sy,t);

			if(temp != NULL) tk = temp;

			if(tk->id == ASSIGN){				
				sy=checkVariable(word,t);
				if(sy!=NULL)
					{sy=checkTypeAssign(sy, tk->next);}
				else 
					{printf("ERROR: Variable %s is not declared, can not assign value\n",word);}
				tk = Operand(tk->next);
				if(tk == NULL) return NULL;
			} else if(tk->id == COMA){
				while(1){
					if(tk->id == COMA){
						tk = tk->next;
						if(tk->id == VARIABLE_NAME){
							word=tk->content;
							sy=createSymbol(word,type);
							addSymbol(sy,t);
							tk=tk->next;
							temp = ArrayVariable(tk);					
							if(temp != NULL) tk = temp;

							if(tk->id == ASSIGN){
								sy=checkVariable(word,t);
								if(sy!=NULL)
									{sy=checkTypeAssign(sy, tk->next);}
								else 
									{printf("ERROR: Variable %s is not declared, can not assign value\n",word);}
								tk = Operand(tk->next);
								if(tk == NULL){
									printf("Unexpected token %s in line %i operand \n",tk->content,tk->line);
									return NULL;
								} else
									continue;
							} else if(tk->id == SEMICOLON){
								break;
							} else {
								printf("Unexpected token %s in line %i ASSIGN \n",tk->content,tk->line);
								tk=tk->next;
								continue;
							}
						} else
							printf("Unexpected token %s in line %i VARIABLE_NAME\n",tk->content,tk->line);
					} else break;
				}				
			} else if(tk->id != SEMICOLON){
				printf("Unexpected token %s in line %i ASSIGN \n",tk->content,tk->line);
				tk=tk->next;
			}			
			printf("Hi: %s\n", tk->content);

			return tk;
		}
	}		
	printf("DECLARE\n");
	return NULL;
}
struct token *Assign(struct token *tk){
	struct token *temp=NULL;
	struct symbol *sy;
	char *word=malloc(sizeof(*word));
	if(tk->id == VARIABLE_NAME){
		word=tk->content;
		tk=tk->next;

		temp=ArrayVariable(tk);
		if(temp!=NULL) tk=temp;

		if(tk->id == ASSIGN){
			sy=checkVariable(word,t);
			if(sy!=NULL) {sy=checkTypeAssign(sy, tk->next); }
			else 
				{printf("ERROR: Variable %s is not declared, can not assign value\n",word);}
			tk = Operand(tk->next);

			if(tk != NULL){
				if(tk->id == INCREMENT || tk->id == DECREMENT){
					return tk->next;
				} else return tk;
			} else
				printf("Unexpected token %s in line %i\n",tk->content,tk->line);
		} else 
			printf("Unexpected token %s in line %i\n",tk->content,tk->line);
	}	
	printf("ASSIGN\n");
	return NULL;
}

struct token *Loop_While(struct token *tk, FILE *fp){
	printf("LOOP_WHILE\n");
	struct token *temp;
	if(tk->id == KEYWORD_WHILE){
		tk=tk->next;
		if(tk->id == PAREN_L){
			tk=Operand(tk->next, fp);
			if(tk != NULL) {
				if(tk->id == PAREN_R){
					tk=tk->next;
					if(tk->id == LLAVE_L){
						tk = tk->next;
						do{
							printf("Looking for an expression\n");
							temp = Expression(tk, fp);
							if(temp!=NULL) tk = temp;
						} while(temp != NULL);
						if(tk->id == LLAVE_R){
							printf("%s\n", tk->content);
							printf("NICE\n");
							return tk->next;
						} else
							printf("Unexpected token %s in line %i\n",tk->content,tk->line);
					} else
						printf("Unexpected token %s in line %i\n",tk->content,tk->line);
				} else
					printf("Unexpected token %s in line %i\n",tk->content,tk->line);			
			} else
				printf("Unexpected token %s in line %i\n",tk->content,tk->line);		
		} else
			printf("Unexpected token %s in line %i\n",tk->content,tk->line);
	} else
		printf("Unexpected token %s in line %i\n",tk->content,tk->line);
	printf("LOOP_WHILE\n");
	return NULL;
}

struct token *Loop_For(struct token *tk, FILE *fp){
	printf("LOOP_FOR\n");
	struct token *temp;
	if(tk->id == KEYWORD_FOR){
		tk=tk->next;
		if(tk->id == PAREN_L){
			tk=Declare(tk->next, fp);
			if(tk != NULL){
				if(tk->id == SEMICOLON){
					tk=Operand(tk->next, fp);
					if(tk != NULL){
						if(tk->id == SEMICOLON){
							tk=Assign(tk->next, fp);
							if(tk != NULL){
								tk=tk->next;
								if(tk->id == PAREN_R){
									tk=tk->next;
									if(tk->id == LLAVE_L){
										do{
											printf("Looking for an expression\n");
											temp = Expression(tk, fp);
											if(temp!=NULL) tk = temp;
										} while(temp != NULL);
										if(tk->id == LLAVE_R){
											printf("%s\n", tk->content);
											printf("NICE\n");
											return tk->next;
										} else
											printf("Unexpected token %s in line %i\n",tk->content,tk->line);
									} else
										printf("Unexpected token %s in line %i\n",tk->content,tk->line);
								} else
									printf("Unexpected token %s in line %i\n",tk->content,tk->line);
							} else
								printf("Unexpected token %s in line %i\n",tk->content,tk->line);
						} else
							printf("Unexpected token %s in line %i\n",tk->content,tk->line);
					} else
						printf("Unexpected token %s in line %i\n",tk->content,tk->line);
				} else
					printf("Unexpected token %s in line %i\n",tk->content,tk->line);
			} else {
				tk=Assign(tk->next, fp);
				if(tk != NULL){
					if(tk->id == SEMICOLON){
						tk=Operand(tk->next, fp);
						if(tk != NULL){
							if(tk->id == SEMICOLON){
								tk=Assign(tk->next, fp);
								if(tk != NULL){
									tk=tk->next;
									if(tk->id == PAREN_R){
										tk=tk->next;
										if(tk->id == LLAVE_L){
											do{
												printf("Looking for an expression\n");
												temp = Expression(tk, fp);
												if(temp!=NULL) tk = temp;
											} while(temp != NULL);
											if(tk->id == LLAVE_R){
												printf("%s\n", tk->content);
												printf("NICE\n");
												return tk->next;
											} else
												printf("Unexpected token %s in line %i\n",tk->content,tk->line);
										} else
											printf("Unexpected token %s in line %i\n",tk->content,tk->line);
									} else
										printf("Unexpected token %s in line %i\n",tk->content,tk->line);
								} else
									printf("Unexpected token %s in line %i\n",tk->content,tk->line);
							} else
								printf("Unexpected token %s in line %i\n",tk->content,tk->line);
						} else
							printf("Unexpected token %s in line %i\n",tk->content,tk->line);
					} else
						printf("Unexpected token %s in line %i\n",tk->content,tk->line);
				} else
					printf("Unexpected token %s in line %i\n",tk->content,tk->line);
			}
		}
	}
	printf("LOOP_FOR\n");
	return NULL;
}

struct token *Read(struct token *tk, FILE *fp){
	struct token *temp;
	if(tk->id == KEYWORD_READ){
		tk = tk->next;
		if(tk->id == PAREN_L){
			tk = tk->next;
			if(tk->id == VARIABLE_NAME){
				tk=tk->next;
				temp = ArrayVariable(tk);
				if(temp != NULL) tk=temp;
				while(1){
					if(tk->id == COMA){
						tk = tk->next;
						if(tk->id == VARIABLE_NAME){
							tk=tk->next;
							temp = ArrayVariable(tk);
							if(temp != NULL) tk=temp;							
						}
						else {
							printf("Unexpected token %s in line %i\n",tk->content,tk->line);
							return NULL;

						}
					}
					else break;
				}
				if(tk->id == PAREN_R){
					return tk->next;
				} else
					printf("Unexpected token %s in line %i\n",tk->content,tk->line);
			}
		} else
			printf("Unexpected token %s in line %i\n",tk->content,tk->line);
	} else
		printf("Unexpected token %s in line %i\n",tk->content,tk->line);
	printf("READ\n");
	return NULL;
}

struct token *Write(struct token *tk, FILE *fp){
	if(tk->id == KEYWORD_PRINT){
		tk = tk->next;
		if(tk->id == PAREN_L){
			printf("...\n");
			tk = Operand(tk->next, fp);
			if(tk != NULL){
				fputs("WRT\n", fp);
				if(tk->id == PAREN_R){
					return tk->next;
				} else
					printf("Unexpected token %s in line %i\n",tk->content,tk->line);
			} else
				printf("Unexpected token %s in line %i\n",tk->content,tk->line);
		} else
			printf("Unexpected token %s in line %i\n",tk->content,tk->line);
	} else
		printf("Unexpected token %s in line %i\n",tk->content,tk->line);
	printf("WRITE\n");
	return NULL;
}

struct token *WriteLN(struct token *tk, FILE *fp){
	if(tk->id == KEYWORD_PRINTLN){
		tk = tk->next;
		if(tk->id == PAREN_L){
			printf("...\n");
			tk = Operand(tk->next, fp);
			if(tk != NULL){
				fputs("WRT\nWRTLN\n", fp);
				if(tk->id == PAREN_R){
					return tk->next;
				} else
					printf("Unexpected token %s in line %i\n",tk->content,tk->line);
			} else
				printf("Unexpected token %s in line %i\n",tk->content,tk->line);
		} else
			printf("Unexpected token %s in line %i\n",tk->content,tk->line);
	} else
		printf("Unexpected token %s in line %i\n",tk->content,tk->line);
	printf("WRITE\n");
	return NULL;
}

struct token *Operand(struct token *tk, FILE *fp){
	// struct token *(opStack[32]);
	// opStack = malloc(32*sizeof(struct token));
	struct token **opStack = malloc(32 * sizeof(struct token));
	int top = -1;

	printf("Starting to analyze Operand: %s\n", tk->content);
	struct token *temp = NULL;
	if(tk->id == VARIABLE_NAME || tk->id == INTEGER || tk->id == DECIMAL || tk->id == STRING || tk->id == KCHAR){
		tk=tk->next;
		temp = ArrayVariable(tk);
		if(temp != NULL) tk=temp;

		if(tk->id == VARIABLE_NAME){
			fputs("PUSH ", fp);
			fputs(strcat(tk->content, "\n"), fp);
		}
		else if(tk->id == INTEGER){
			fputs("PUSHKI ", fp);
			fputs(strcat(tk->content, "\n"), fp);
		}
		else if(tk->id == DECIMAL){
			fputs("PUSHKD ", fp);
			fputs(strcat(tk->content, "\n"), fp);
		}
		else if(tk->id == STRING){
			fputs("PUSHKS ", fp);
			fputs(strcat(tk->content, "\n"), fp);
		}
		else if(tk->id == KCHAR){
			fputs("PUSHKC ", fp);
			fputs(strcat(tk->content, "\n"), fp);
		}

		while(1){
			if(tk->id == ARITMETIC_OP){
				tk = tk->next;
				if(tk->id == VARIABLE_NAME || tk->id == INTEGER || tk->id == DECIMAL || tk->id == STRING || tk->id == KCHAR){
					tk=tk->next;
					temp = ArrayVariable(tk);
					if(temp != NULL) tk = temp;	
				} else if(tk->id == PAREN_L){
					tk=Operand(tk->next);
					if(tk->id == PAREN_R)
						tk=tk->next;
					else
						printf("Unexpected token %s in line %i op1\n",tk->content,tk->line);
				}				
				if(top > -1){
					if(strcmp(tk->content, "*") != 0 && strcmp(tk->content, "/") != 0){
						printf("Current node is %s, node on top of stack is %s\n", tk->content, opStack[top]->content);
						while(top > - 1){
							printf("YES");
							if(!strcmp(opStack[top]->content, "+"))
								fputs("ADD\n", fp);
							else if(!strcmp(opStack[top]->content, "-"))
								fputs("SUB\n", fp);
							else if(!strcmp(opStack[top]->content, "*"))
								fputs("MUL\n", fp);
							else if(!strcmp(opStack[top]->content, "/"))
								fputs("DIV\n", fp);
							else if(!strcmp(opStack[top]->content, "%"))
								fputs("MOD\n", fp);
							top--;
						}
					}
					else{
						while(top > -1 && (!strcmp(opStack[top]->content, "*") || !strcmp(opStack[top]->content, "/"))){
							if(!strcmp(opStack[top]->content, "*"))
								fputs("MUL\n", fp);
							else if(!strcmp(opStack[top]->content, "/"))
								fputs("DIV\n", fp);
						}
					}
				}
				printf("DONE WITH\n");
				opStack[++top] = tk;
				printf("THe new node on tope of stack is %s\n", opStack[top]->content);

				tk = tk->next;
				temp = ArrayVariable(tk, fp);
				if(temp != NULL) tk = temp;
				if(temp != NULL || tk->id == VARIABLE_NAME || tk->id == INTEGER || tk->id == DECIMAL || tk->id == STRING || tk->id == KCHAR){
					if(tk->id == VARIABLE_NAME){
						fputs("PUSH ", fp);
						fputs(strcat(tk->content, "\n"), fp);
					}
					else if(tk->id == INTEGER){
						fputs("PUSHKI ", fp);
						fputs(strcat(tk->content, "\n"), fp);
					}
					else if(tk->id == DECIMAL){
						fputs("PUSHKD ", fp);
						fputs(strcat(tk->content, "\n"), fp);
					}
					else if(tk->id == STRING){
						fputs("PUSHKS ", fp);
						fputs(strcat(tk->content, "\n"), fp);
					}
					else if(tk->id == KCHAR){
						fputs("PUSHKC ", fp);
						fputs(strcat(tk->content, "\n"), fp);
					}
				} 		
			} else break;			
		} // end while
		return tk;
		printf("Found an operand, yay\n");
		//printf("Token %s at position: %i\n", opStack[top]->content, top);
		while(top > -1){
			if(!strcmp(opStack[top]->content, "+"))
				fputs("ADD\n", fp);
			else if(!strcmp(opStack[top]->content, "-"))
				fputs("SUB\n", fp);
			else if(!strcmp(opStack[top]->content, "*"))
				fputs("MUL\n", fp);
			else if(!strcmp(opStack[top]->content, "/"))
				fputs("DIV\n", fp);
			else if(!strcmp(opStack[top]->content, "%"))
				fputs("MOD\n", fp);
			else if(!strcmp(opStack[top]->content, "=="))
				fputs("CEQ\n", fp);
			else if(!strcmp(opStack[top]->content, "!="))
				fputs("CNE\n", fp);
			else if(!strcmp(opStack[top]->content, ">"))
				fputs("CGT\n", fp);
			else if(!strcmp(opStack[top]->content, ">="))
				fputs("CGE\n", fp);
			else if(!strcmp(opStack[top]->content, "<"))
				fputs("CLT\n", fp);
			else if(!strcmp(opStack[top]->content, "<="))
				fputs("CLE\n", fp);
			top--;
		}
		return tk;
	} else if(tk->id == PAREN_L){
		tk=Operand(tk->next);
		if(tk->id == PAREN_R)
			tk=tk->next;
		else
			printf("Unexpected token %s in line %i op2\n",tk->content,tk->line);
	} 
	return NULL;
}
  
struct token *OperandInt(struct token *tk, FILE *fp){
	printf("Starting to analyze Operand: %s\n", tk->content);
	if(tk->id == VARIABLE_NAME || tk->id == INTEGER){
		tk = tk->next;
		while(1){
			if(tk->id == ARITMETIC_OP || tk->id == COMPARE_OP){
				tk = tk->next;
				if(tk->id == VARIABLE_NAME || tk->id == INTEGER){
					tk = tk->next;
				}
				else if(tk->id == PAREN_L){
					tk = Operand(tk->next, fp);
					if(tk->id == PAREN_R){
						tk = tk->next;
					}
					else {
						printf("Unexpected token %s in line %i\n",tk->content,tk->line);
						return NULL;
					}
				}
				else {
					printf("Unexpected token %s in line %i\n",tk->content,tk->line);
					return NULL;
				}
			}
			else{ 
				printf("Unexpected token %s in line %i\n",tk->content,tk->line);
				break;
			}
		}
		printf("Found an operand, yay\n");
		return tk;
	}
	return NULL;
}

struct token *ArrayVariable(struct token *tk, FILE *fp){
	if(tk->id == CORCHETE_L){
		tk = OperandInt(tk->next, fp);
		if(tk != NULL && tk->id == CORCHETE_R){
			return tk->next;
		} else
			printf("Unexpected token %s in line %i\n",tk->content,tk->line);
	} 
	return NULL;
=======
int if_count;
int for_count;
int while_count;

void syntax(struct tokenList *lists){
	//printf("%i\n", lists->start->id);
	struct token *tk;
	struct token *temp;

	if_count = 0;
	for_count = 0;
	while_count = 0;
	//struct table *t;
	// struct symbol *s=createSymbol("inicio");
	// t->start =s;
	// t->current=s;
	tk = lists->start;
	tk = tk->next;

	FILE *fp;
	fp = fopen("wall.e", "wb+");
	if(!fp){
		printf("Could not create output file\n");
		return;
	}

	while(1){
		temp = Expression(tk, fp);
		if(temp!= NULL)
			tk = temp;
		else break;
	}
	fputs("EXT\n", fp);
	printf("Done");
	//Expression(tk, fp);
}

struct token *Expression(struct token *tk, FILE *fp){
	printf("EXPRESSION START: %s\n", tk->content);
	switch(tk->id){
		case KEYWORD_IF:
			tk = Condition(tk, fp);
			break;	
		case VARIABLE_TYPE:
			tk = Declare(tk, fp);
			break;
		case VARIABLE_NAME:
			tk = Assign(tk, fp);
			break;
		case KEYWORD_WHILE:
			tk = Loop_While(tk, fp);
			break;
		case KEYWORD_FOR:
			tk = Loop_For(tk, fp);
			break;
		case KEYWORD_READ:
			tk = Read(tk, fp);
			break;
		case KEYWORD_PRINT:
			tk = Write(tk, fp);
			break;
		case KEYWORD_PRINTLN:
			tk = WriteLN(tk, fp);
			break;
		default:
	 		return NULL;
	}
	if(tk->id == SEMICOLON){
		tk = tk->next;
		printf("Omedetou\n");
	} else
		printf("Unexpected token %s in line %i\n",tk->content,tk->line);
	return tk;
}

struct token *Condition(struct token *tk, FILE *fp){
	struct token *temp;
	if(tk->id == KEYWORD_IF){
		tk = tk->next;
		if(tk->id == PAREN_L){
			tk = Operand(tk->next, fp);
			if(tk != NULL){
				if(tk->id == COMPARE_OP){
					printf("HI");
					tk = Operand(tk->next, fp);
					printf("BYE");
					if(tk != NULL){
						if(tk->id == PAREN_R){
							printf("NICE");
							tk = tk->next;
							if(tk->id == LLAVE_L){
								tk = tk->next;
								do{
									printf("Looking for an expression\n");
									temp = Expression(tk, fp);
									if(temp!=NULL) tk = temp;
								}while(temp != NULL);
								if(tk->id == LLAVE_R){
									printf("NICE\n");
									tk = tk->next;
									if (tk->id == KEYWORD_ELSE) {
										tk = tk->next;
										if (tk->id == LLAVE_L) {
											tk = tk->next;
											do {
												printf("Looking for an expression\n");
												temp = Expression(tk, fp);
												if (temp != NULL) tk = temp;
											} while (temp != NULL);
											if (tk->id == LLAVE_R) {
												printf("NICE\n");
												return tk->next;
											}
											else
												printf("Unexpected token %s in line %i\n", tk->content, tk->line);
										}
										else
											printf("Unexpected token %s in line %i\n", tk->content, tk->line);
									}
									if (tk->id== KEYWORD_ELIF) {
										tk = Condition_Elif(tk, fp);
										printf("NICE\n");

										return tk;
									}
									printf("NICE\n");
									return tk->next;
								} else
									printf("Unexpected token %s in line %i\n",tk->content,tk->line);
							} else
								printf("Unexpected token %s in line %i\n",tk->content,tk->line);						
						} else
							printf("Unexpected token %s in line %i\n",tk->content,tk->line);
					} else
						printf("Unexpected token %s in line %i\n",tk->content,tk->line);
				} else
					printf("Unexpected token %s in line %i\n",tk->content,tk->line);
			} else
				printf("Unexpected token %s in line %i\n",tk->content,tk->line);
			}
		}
	printf("CONDITION\n");
	return NULL;
}

struct token *Condition_Elif(struct token *tk, FILE *fp){
	struct token *temp;
	if (tk->id == KEYWORD_ELIF) {
		tk = tk->next;
		if (tk->id == PAREN_L) {
			tk = Operand(tk->next, fp);
			if (tk != NULL) {
				if(tk->id == COMPARE_OP){
					tk = Operand(tk->next, fp);
					if(tk != NULL){		
						if (tk->id == PAREN_R) {
							tk = tk->next;
							if (tk->id == LLAVE_L) {
								tk = tk->next;
								do {
									printf("Looking for an expression\n");
									temp = Expression(tk, fp);
									if (temp != NULL) tk = temp;
								} while (temp != NULL);
								if (tk->id == LLAVE_R) {
									tk = tk->next;
									if (tk->id == KEYWORD_ELSE) {
										tk = tk->next;
										if (tk->id == LLAVE_L) {
											tk = tk->next;
											do {
												printf("Looking for an expression\n");
												temp = Expression(tk, fp);
												if (temp != NULL) tk = temp;
											} while (temp != NULL);
											if (tk->id == LLAVE_R) {
												printf("NICE\n");
												return tk->next;
											}
											else
												printf("Unexpected token %s in line %i\n", tk->content, tk->line);
										}
										else
											printf("Unexpected token %s in line %i\n", tk->content, tk->line);
									}
									else if (tk->id == KEYWORD_ELIF) {
										tk = Condition_Elif(tk, fp);
									}
									printf("NICE");
									printf(tk->content);
									return tk;
								}
								else
									printf("Unexpected token %s in line %i\n", tk->content, tk->line);
							}
							else
								printf("Unexpected token %s in line %i\n", tk->content, tk->line);
						}
						else
							printf("Unexpected token %s in line %i\n", tk->content, tk->line);
					}
					else
						printf("Unexpected token %s in line %i\n", tk->content, tk->line);
				}
				else
					printf("Unexpected token %s in line %i\n", tk->content, tk->line);
			}
		}
	}
	else
		printf("Unexpected token %s in line %i\n", tk->content, tk->line);
	printf("CONDITION\n");
	return NULL;
}

struct token *Declare(struct token *tk, FILE *fp){
	//struct symbol *sy;
	//TokenType type;
	struct token *temp;
	if(tk->id == VARIABLE_TYPE){
		//type=checkType(id->content);
		tk = tk->next;
		temp = ArrayVariable(tk, fp);
		if(temp != NULL) tk = temp;
		if(temp != NULL || tk->id == VARIABLE_NAME){
			//sy=createSymbol(tk->content,type);
			if(temp == NULL) tk = tk->next;
			if(tk->id == ASSIGN){
				//sy=checkTypeAssign(sy,tk->next, fp);
				tk = Operand(tk->next, fp);
				if(tk == NULL) return NULL;
			} else
				printf("Unexpected token %s in line %i\n",tk->content,tk->line);
			while(1){
				if(tk->id == COMA){
					tk = tk->next;
					temp = ArrayVariable(tk, fp);
					if(temp != NULL) tk = temp;
					if(temp != NULL || tk->id == VARIABLE_NAME){
						if(temp == NULL) tk = tk->next;
						if(tk->id == ASSIGN){
							tk = Operand(tk->next, fp);
							if(tk == NULL){
								return NULL;
							} else
								printf("Unexpected token %s in line %i\n",tk->content,tk->line);
						}
						else {
							printf("Unexpected token %s in line %i\n",tk->content,tk->line);
							continue;
						}
					} else
						printf("Unexpected token %s in line %i\n",tk->content,tk->line);
				}
				else break;
			}
			printf("Hi: %s", tk->content);
			return tk;
		}
	}
	printf("DECLARE\n");
	return NULL;
}

struct token *Assign(struct token *tk, FILE *fp){
	struct token *temp;
	temp = ArrayVariable(tk, fp);
	if(temp != NULL) tk = temp;
	if(temp != NULL || tk->id == VARIABLE_NAME){
		if(temp == NULL) tk = tk->next;
		if(tk->id == ASSIGN){
			tk = Operand(tk->next, fp);
			if(tk != NULL){
				if(tk->id == INCREMENT || tk->id == DECREMENT){
					return tk->next;
				} else {
					printf("Unexpected token %s in line %i\n",tk->content,tk->line);
					return tk;
				}
			} else
				printf("Unexpected token %s in line %i\n",tk->content,tk->line);
		} else 
			printf("Unexpected token %s in line %i\n",tk->content,tk->line);
	} else
		printf("Unexpected token %s in line %i\n",tk->content,tk->line);
	printf("ASSIGN\n");
	return NULL;
}

struct token *Loop_While(struct token *tk, FILE *fp){
	printf("LOOP_WHILE\n");
	struct token *temp;
	char *op = malloc(2*sizeof(char));
	char *count = malloc(2*sizeof(char));
	sprintf(count, "%i", while_count++);

	fputs("WHILE", fp);
	fputs(count, fp);
	fputs(":\n", fp);

	if(tk->id == KEYWORD_WHILE){
		tk=tk->next;
		if(tk->id == PAREN_L){
			tk=Operand(tk->next, fp);
			if(tk != NULL) {
				if(tk->id == COMPARE_OP){
					strcpy(op, tk->content);
					tk = Operand(tk->next, fp);
					if(tk != NULL){
						if(!strcmp(op, ">"))
							fputs("CGT\n", fp);
						if(!strcmp(op, ">="))
							fputs("CGE\n", fp);
						if(!strcmp(op, "<"))
							fputs("CLT\n", fp);
						if(!strcmp(op, "<="))
							fputs("CLE\n", fp);
						if(!strcmp(op, "=="))
							fputs("CEQ\n", fp);
						if(!strcmp(op, "!="))
							fputs("CNE\n", fp);
						fputs("JMPC WHILE_END", fp);
						fputs(count, fp);
						fputs(":\n", fp);
						if(tk->id == PAREN_R){
							tk=tk->next;
							if(tk->id == LLAVE_L){
								tk = tk->next;
								do{
									printf("Looking for an expression\n");
									temp = Expression(tk, fp);
									if(temp!=NULL) tk = temp;
								} while(temp != NULL);
								if(tk->id == LLAVE_R){
									printf("%s\n", tk->content);
									printf("NICE\n");

									fputs("JMP WHILE", fp);
									fputs(count, fp);
									fputs(":\n", fp);
									fputs("WHILE_END", fp);
									fputs(count, fp);
									fputs(":\n", fp);

									return tk->next;
								} else
									printf("Unexpected token %s in line %i\n",tk->content,tk->line);
							} else
								printf("Unexpected token %s in line %i\n",tk->content,tk->line);
						} else
							printf("Unexpected token %s in line %i\n",tk->content,tk->line);			
					} else
						printf("Unexpected token %s in line %i\n",tk->content,tk->line);		
				} else
					printf("Unexpected token %s in line %i\n",tk->content,tk->line);
			} else
				printf("Unexpected token %s in line %i\n",tk->content,tk->line);
			}
		}
	printf("LOOP_WHILE\n");
	return NULL;
}

struct token *Loop_For(struct token *tk, FILE *fp){
	printf("LOOP_FOR\n");
	struct token *temp;
	if(tk->id == KEYWORD_FOR){
		tk=tk->next;
		if(tk->id == PAREN_L){
			tk=Declare(tk->next, fp);
			if(tk != NULL){
				if(tk->id == SEMICOLON){
					tk=Operand(tk->next, fp);
					if(tk != NULL){
						if(tk->id == SEMICOLON){
							tk=Assign(tk->next, fp);
							if(tk != NULL){
								tk=tk->next;
								if(tk->id == PAREN_R){
									tk=tk->next;
									if(tk->id == LLAVE_L){
										do{
											printf("Looking for an expression\n");
											temp = Expression(tk, fp);
											if(temp!=NULL) tk = temp;
										} while(temp != NULL);
										if(tk->id == LLAVE_R){
											printf("%s\n", tk->content);
											printf("NICE\n");
											return tk->next;
										} else
											printf("Unexpected token %s in line %i\n",tk->content,tk->line);
									} else
										printf("Unexpected token %s in line %i\n",tk->content,tk->line);
								} else
									printf("Unexpected token %s in line %i\n",tk->content,tk->line);
							} else
								printf("Unexpected token %s in line %i\n",tk->content,tk->line);
						} else
							printf("Unexpected token %s in line %i\n",tk->content,tk->line);
					} else
						printf("Unexpected token %s in line %i\n",tk->content,tk->line);
				} else
					printf("Unexpected token %s in line %i\n",tk->content,tk->line);
			} else {
				tk=Assign(tk->next, fp);
				if(tk != NULL){
					if(tk->id == SEMICOLON){
						tk=Operand(tk->next, fp);
						if(tk != NULL){
							if(tk->id == SEMICOLON){
								tk=Assign(tk->next, fp);
								if(tk != NULL){
									tk=tk->next;
									if(tk->id == PAREN_R){
										tk=tk->next;
										if(tk->id == LLAVE_L){
											do{
												printf("Looking for an expression\n");
												temp = Expression(tk, fp);
												if(temp!=NULL) tk = temp;
											} while(temp != NULL);
											if(tk->id == LLAVE_R){
												printf("%s\n", tk->content);
												printf("NICE\n");
												return tk->next;
											} else
												printf("Unexpected token %s in line %i\n",tk->content,tk->line);
										} else
											printf("Unexpected token %s in line %i\n",tk->content,tk->line);
									} else
										printf("Unexpected token %s in line %i\n",tk->content,tk->line);
								} else
									printf("Unexpected token %s in line %i\n",tk->content,tk->line);
							} else
								printf("Unexpected token %s in line %i\n",tk->content,tk->line);
						} else
							printf("Unexpected token %s in line %i\n",tk->content,tk->line);
					} else
						printf("Unexpected token %s in line %i\n",tk->content,tk->line);
				} else
					printf("Unexpected token %s in line %i\n",tk->content,tk->line);
			}
		}
	}
	printf("LOOP_FOR\n");
	return NULL;
}

struct token *Read(struct token *tk, FILE *fp){
	struct token *temp;
	if(tk->id == KEYWORD_READ){
		tk = tk->next;
		if(tk->id == PAREN_L){
			tk = tk->next;
			temp = ArrayVariable(tk, fp);
			if(temp != NULL) tk=temp;
			if(temp != NULL || tk->id == VARIABLE_NAME){
				if(temp == NULL) tk = tk->next;
				while(1){
					if(tk->id == COMA){
						tk = tk->next;
						temp = ArrayVariable(tk, fp);
						if(temp != NULL) tk=temp;
						if(temp != NULL || tk->id == VARIABLE_NAME){
							if(temp == NULL) tk = tk->next;
						}
						else return NULL;
					}
					else break;
				}
				if(tk->id == PAREN_R){
					return tk->next;
				} else
					printf("Unexpected token %s in line %i\n",tk->content,tk->line);
			}
		} else
			printf("Unexpected token %s in line %i\n",tk->content,tk->line);
	} else
		printf("Unexpected token %s in line %i\n",tk->content,tk->line);
	printf("READ\n");
	return NULL;
}

struct token *Write(struct token *tk, FILE *fp){
	if(tk->id == KEYWORD_PRINT){
		tk = tk->next;
		if(tk->id == PAREN_L){
			printf("...\n");
			tk = Operand(tk->next, fp);
			if(tk != NULL){
				fputs("WRT\n", fp);
				if(tk->id == PAREN_R){
					return tk->next;
				} else
					printf("Unexpected token %s in line %i\n",tk->content,tk->line);
			} else
				printf("Unexpected token %s in line %i\n",tk->content,tk->line);
		} else
			printf("Unexpected token %s in line %i\n",tk->content,tk->line);
	} else
		printf("Unexpected token %s in line %i\n",tk->content,tk->line);
	printf("WRITE\n");
	return NULL;
}

struct token *WriteLN(struct token *tk, FILE *fp){
	if(tk->id == KEYWORD_PRINTLN){
		tk = tk->next;
		if(tk->id == PAREN_L){
			printf("...\n");
			tk = Operand(tk->next, fp);
			if(tk != NULL){
				fputs("WRT\nWRTLN\n", fp);
				if(tk->id == PAREN_R){
					return tk->next;
				} else
					printf("Unexpected token %s in line %i\n",tk->content,tk->line);
			} else
				printf("Unexpected token %s in line %i\n",tk->content,tk->line);
		} else
			printf("Unexpected token %s in line %i\n",tk->content,tk->line);
	} else
		printf("Unexpected token %s in line %i\n",tk->content,tk->line);
	printf("WRITE\n");
	return NULL;
}

struct token *Operand(struct token *tk, FILE *fp){
	// struct token *(opStack[32]);
	// opStack = malloc(32*sizeof(struct token));
	struct token **opStack = malloc(32 * sizeof(struct token));
	int top = -1;

	printf("Starting to analyze Operand: %s\n", tk->content);
	struct token *temp;
	temp = ArrayVariable(tk, fp);
	if(temp != NULL) tk = temp;
	if(temp != NULL || tk->id == VARIABLE_NAME || tk->id == INTEGER || tk->id == DECIMAL || tk->id == STRING || tk->id == KCHAR){
		if(tk->id == VARIABLE_NAME){
			fputs("PUSH ", fp);
			fputs(strcat(tk->content, "\n"), fp);
		}
		else if(tk->id == INTEGER){
			fputs("PUSHKI ", fp);
			fputs(strcat(tk->content, "\n"), fp);
		}
		else if(tk->id == DECIMAL){
			fputs("PUSHKD ", fp);
			fputs(strcat(tk->content, "\n"), fp);
		}
		else if(tk->id == STRING){
			fputs("PUSHKS ", fp);
			fputs(strcat(tk->content, "\n"), fp);
		}
		else if(tk->id == KCHAR){
			fputs("PUSHKC ", fp);
			fputs(strcat(tk->content, "\n"), fp);
		}

		if(temp == NULL) tk = tk->next;
		while(1){
			if(tk->id == ARITMETIC_OP){
				if(top > -1){
					if(strcmp(tk->content, "*") != 0 && strcmp(tk->content, "/") != 0){
						printf("Current node is %s, node on top of stack is %s\n", tk->content, opStack[top]->content);
						while(top > - 1){
							printf("YES");
							if(!strcmp(opStack[top]->content, "+"))
								fputs("ADD\n", fp);
							else if(!strcmp(opStack[top]->content, "-"))
								fputs("SUB\n", fp);
							else if(!strcmp(opStack[top]->content, "*"))
								fputs("MUL\n", fp);
							else if(!strcmp(opStack[top]->content, "/"))
								fputs("DIV\n", fp);
							else if(!strcmp(opStack[top]->content, "%"))
								fputs("MOD\n", fp);
							top--;
						}
					}
					else{
						while(top > -1 && (!strcmp(opStack[top]->content, "*") || !strcmp(opStack[top]->content, "/"))){
							if(!strcmp(opStack[top]->content, "*"))
								fputs("MUL\n", fp);
							else if(!strcmp(opStack[top]->content, "/"))
								fputs("DIV\n", fp);
						}
					}
				}
				printf("DONE WITH\n");
				opStack[++top] = tk;
				printf("THe new node on tope of stack is %s\n", opStack[top]->content);

				tk = tk->next;
				temp = ArrayVariable(tk, fp);
				if(temp != NULL) tk = temp;
				if(temp != NULL || tk->id == VARIABLE_NAME || tk->id == INTEGER || tk->id == DECIMAL || tk->id == STRING || tk->id == KCHAR){
					if(tk->id == VARIABLE_NAME){
						fputs("PUSH ", fp);
						fputs(strcat(tk->content, "\n"), fp);
					}
					else if(tk->id == INTEGER){
						fputs("PUSHKI ", fp);
						fputs(strcat(tk->content, "\n"), fp);
					}
					else if(tk->id == DECIMAL){
						fputs("PUSHKD ", fp);
						fputs(strcat(tk->content, "\n"), fp);
					}
					else if(tk->id == STRING){
						fputs("PUSHKS ", fp);
						fputs(strcat(tk->content, "\n"), fp);
					}
					else if(tk->id == KCHAR){
						fputs("PUSHKC ", fp);
						fputs(strcat(tk->content, "\n"), fp);
					}
					if(temp == NULL) tk = tk->next;
				} 
				else {
					printf("Unexpected token %s in line %i\n",tk->content,tk->line);
					if(tk->id == PAREN_L){
						tk = Operand(tk->next, fp);
						if(tk->id == PAREN_R){
							tk = tk->next;
						}
						else {
							printf("Unexpected token %s in line %i\n",tk->content,tk->line);
							return NULL;
						}
					} else {
						printf("Unexpected token %s in line %i\n",tk->content,tk->line);
						return NULL;
					}
				}				
			}
			else{ 
				printf("Unexpected token %s in line %i\n",tk->content,tk->line);
				break;
			}
		}
		printf("Found an operand, yay\n");
		//printf("Token %s at position: %i\n", opStack[top]->content, top);
		while(top > -1){
			if(!strcmp(opStack[top]->content, "+"))
				fputs("ADD\n", fp);
			else if(!strcmp(opStack[top]->content, "-"))
				fputs("SUB\n", fp);
			else if(!strcmp(opStack[top]->content, "*"))
				fputs("MUL\n", fp);
			else if(!strcmp(opStack[top]->content, "/"))
				fputs("DIV\n", fp);
			else if(!strcmp(opStack[top]->content, "%"))
				fputs("MOD\n", fp);
			else if(!strcmp(opStack[top]->content, "=="))
				fputs("CEQ\n", fp);
			else if(!strcmp(opStack[top]->content, "!="))
				fputs("CNE\n", fp);
			else if(!strcmp(opStack[top]->content, ">"))
				fputs("CGT\n", fp);
			else if(!strcmp(opStack[top]->content, ">="))
				fputs("CGE\n", fp);
			else if(!strcmp(opStack[top]->content, "<"))
				fputs("CLT\n", fp);
			else if(!strcmp(opStack[top]->content, "<="))
				fputs("CLE\n", fp);
			top--;
		}
		return tk;
	}
	printf("Unexpected token %s in line %i\n",tk->content,tk->line);
	return NULL;
}
struct token *OperandInt(struct token *tk, FILE *fp){
	printf("Starting to analyze Operand: %s\n", tk->content);
	if(tk->id == VARIABLE_NAME || tk->id == INTEGER){
		tk = tk->next;
		while(1){
			if(tk->id == ARITMETIC_OP || tk->id == COMPARE_OP){
				tk = tk->next;
				if(tk->id == VARIABLE_NAME || tk->id == INTEGER){
					tk = tk->next;
				}
				else if(tk->id == PAREN_L){
					tk = Operand(tk->next, fp);
					if(tk->id == PAREN_R){
						tk = tk->next;
					}
					else {
						printf("Unexpected token %s in line %i\n",tk->content,tk->line);
						return NULL;
					}
				}
				else {
					printf("Unexpected token %s in line %i\n",tk->content,tk->line);
					return NULL;
				}
			}
			else{ 
				printf("Unexpected token %s in line %i\n",tk->content,tk->line);
				break;
			}
		}
		printf("Found an operand, yay\n");
		return tk;
	}
	return NULL;
}
struct token *ArrayVariable(struct token *tk, FILE *fp){
	if(tk->id == VARIABLE_NAME){
		tk = tk->next;
		if(tk->id == CORCHETE_L){
			tk = OperandInt(tk->next, fp);
			if(tk != NULL && tk->id == CORCHETE_R){
				return tk->next;
			} else
				printf("Unexpected token %s in line %i\n",tk->content,tk->line);
		} else
			printf("Unexpected token %s in line %i\n",tk->content,tk->line);
	}
	printf("Unexpected token %s in line %i\n",tk->content,tk->line);
	return NULL;
}