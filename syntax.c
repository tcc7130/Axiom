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
				if(tk->id == PAREN_R){
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
	printf("CONDITION\n");
	return NULL;
}

struct token *Operation(struct token *tk, FILE *fp){
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
			if(tk->id == ARITMETIC_OP || tk->id == COMPARE_OP){
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
		printf("Token %s at position: %i\n", opStack[top]->content, top);
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