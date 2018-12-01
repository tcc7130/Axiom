struct table *t;
struct token *Expression(struct token *tk){
	printf("EXPRESSION START: %s\n", tk->content);
	switch(tk->id){
		case KEYWORD_IF:
			tk = Condition(tk);
			break;	
		case VARIABLE_TYPE:
			tk = Declare(tk);
			break;
		case VARIABLE_NAME:
			tk = Assign(tk);
			break;
		case KEYWORD_WHILE:
			tk = Loop_While(tk);
			break;
		case KEYWORD_FOR:
			tk = Loop_For(tk);
			break;
		case KEYWORD_READ:
			tk = Read(tk);
			break;
		case KEYWORD_PRINT:
			tk = Write(tk);
			break;
		case KEYWORD_PRINTLN:
			tk = Write(tk);
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

struct token *Condition(struct token *tk){
	struct token *temp;
	if(tk->id == KEYWORD_IF){
		tk = tk->next;
		if(tk->id == PAREN_L){
			tk = Operand(tk->next);
			if(tk != NULL){
				if(tk->id == PAREN_R){
					tk = tk->next;
					if(tk->id == LLAVE_L){
						tk = tk->next;
						do{
							printf("Looking for an expression\n");
							temp = Expression(tk);
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
struct token *Operation(struct token *tk){
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
			if(sy!=NULL)
				{sy=checkTypeAssign(sy, tk->next);}
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

struct token *Loop_While(struct token *tk){
	printf("LOOP_WHILE\n");
	struct token *temp;
	if(tk->id == KEYWORD_WHILE){
		tk=tk->next;
		if(tk->id == PAREN_L){
			tk=Operand(tk->next);
			if(tk != NULL) {
				if(tk->id == PAREN_R){
					tk=tk->next;
					if(tk->id == LLAVE_L){
						tk = tk->next;
						do{
							printf("Looking for an expression\n");
							temp = Expression(tk);
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
struct token *Loop_For(struct token *tk){
	printf("LOOP_FOR\n");
	struct token *temp;
	if(tk->id == KEYWORD_FOR){
		tk=tk->next;
		if(tk->id == PAREN_L){
			tk=Declare(tk->next);
			if(tk != NULL){
				if(tk->id == SEMICOLON){
					tk=Operand(tk->next);
					if(tk != NULL){
						if(tk->id == SEMICOLON){
							tk=Assign(tk->next);
							if(tk != NULL){
								tk=tk->next;
								if(tk->id == PAREN_R){
									tk=tk->next;
									if(tk->id == LLAVE_L){
										do{
											printf("Looking for an expression\n");
											temp = Expression(tk);
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
				tk=Assign(tk->next);
				if(tk != NULL){
					if(tk->id == SEMICOLON){
						tk=Operand(tk->next);
						if(tk != NULL){
							if(tk->id == SEMICOLON){
								tk=Assign(tk->next);
								if(tk != NULL){
									tk=tk->next;
									if(tk->id == PAREN_R){
										tk=tk->next;
										if(tk->id == LLAVE_L){
											do{
												printf("Looking for an expression\n");
												temp = Expression(tk);
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
struct token *Read(struct token *tk){
	struct token *temp=NULL;
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

struct token *Write(struct token *tk){
	if(tk->id == KEYWORD_PRINT || tk->id == KEYWORD_PRINTLN){
		tk = tk->next;
		if(tk->id == PAREN_L){
			printf("...\n");
			tk = Operand(tk->next);
			if(tk != NULL){
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
struct token *Operand(struct token *tk){
	printf("Starting to analyze Operand: %s\n", tk->content);
	struct token *temp = NULL;
	if(tk->id==VARIABLE_NAME || tk->id==INTEGER || tk->id==DECIMAL || tk->id==STRING || tk->id==KCHAR){
		tk=tk->next;
		temp = ArrayVariable(tk);
		if(temp != NULL) tk=temp;		
		while(1){
			if(tk->id == ARITMETIC_OP || tk->id == COMPARE_OP){
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
			} else
				break;
		} // end while
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
struct token *OperandInt(struct token *tk){
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
					tk = Operand(tk->next);
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
struct token *ArrayVariable(struct token *tk){	
	if(tk->id == CORCHETE_L){
		tk = OperandInt(tk->next);
		if(tk != NULL && tk->id == CORCHETE_R){
			return tk->next;
		} else
			printf("Unexpected token %s in line %i\n",tk->content,tk->line);
	} 	
	return NULL;
}