struct token *Expression(struct token *tk){
	printf("EXPRESSION START: %s\n", tk->content);
	if(tk->id == KEYWORD_IF){
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
						}
					}
				}
			}
		}
	}
	return NULL;
}
struct token *Operation(struct token *tk){
	return NULL;
}
struct token *Declare(struct token *tk){
	struct token *temp;
	if(tk->id == VARIABLE_TYPE){
		tk = tk->next;
		temp = ArrayVariable(tk);
		if(temp != NULL) tk = temp;
		if(temp != NULL || tk->id == VARIABLE_NAME){
			if(temp == NULL) tk = tk->next;
			if(tk->id == ASSIGN){
				tk = Operand(tk->next);
				if(tk == NULL)
					return NULL;
			}
			while(1){
				if(tk->id == COMA){
					tk = tk->next;
					temp = ArrayVariable(tk);
					if(temp != NULL) tk = temp;
					if(temp != NULL || tk->id == VARIABLE_NAME){
						if(temp == NULL) tk = tk->next;
						if(tk->id == ASSIGN){
							tk = Operand(tk->next);
							if(tk == NULL){
								return NULL;
							}
						}
						else continue;
					}
				}
				else break;
			}
			printf("Hi: %s", tk->content);
			return tk;
		}
	}
	return NULL;
}
struct token *Assign(struct token *tk){
	struct token *temp;
	temp = ArrayVariable(tk);
	if(temp != NULL) tk = temp;
	if(temp != NULL || tk->id == VARIABLE_NAME){
		if(temp == NULL) tk = tk->next;
		if(tk->id == ASSIGN){
			tk = Operand(tk->next);
			if(tk != NULL){
				if(tk->id == INCREMENT || tk->id == DECREMENT){
					return tk->next;
				}
				else return tk;
			}
		}
	}

	return NULL;
}
struct token *Loop_While(struct token *tk){
	return NULL;
}
struct token *Loop_For(struct token *tk){
	return NULL;
}
struct token *Read(struct token *tk){
	struct token *temp;
	if(tk->id == KEYWORD_READ){
		tk = tk->next;
		if(tk->id == PAREN_L){
			tk = tk->next;
			temp = ArrayVariable(tk);
			if(temp != NULL) tk=temp;
			if(temp != NULL || tk->id == VARIABLE_NAME){
				if(temp == NULL) tk = tk->next;
				while(1){
					if(tk->id == COMA){
						tk = tk->next;
						temp = ArrayVariable(tk);
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
				}
			}
		}
	}

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
				}
			}
		}
	}
	return NULL;
}
struct token *Operand(struct token *tk){
	printf("Starting to analyze Operand: %s\n", tk->content);
	struct token *temp;
	temp = ArrayVariable(tk);
	if(temp != NULL) tk = temp;
	if(temp != NULL || tk->id == VARIABLE_NAME || tk->id == INTEGER || tk->id == DECIMAL || tk->id == STRING || tk->id == KCHAR){
		if(temp == NULL) tk = tk->next;
		while(1){
			if(tk->id == ARITMETIC_OP || tk->id == COMPARE_OP){
				tk = tk->next;
				temp = ArrayVariable(tk);
				if(temp != NULL) tk = temp;
				if(temp!= NULL || tk->id == VARIABLE_NAME || tk->id == INTEGER || tk->id == DECIMAL || tk->id == STRING || tk->id == KCHAR){
					if(temp == NULL) tk = tk->next;
				}
				else if(tk->id == PAREN_L){
					tk = Operand(tk->next);
					if(tk->id == PAREN_R){
						tk = tk->next;
					}
					else return NULL;
				}
				else return NULL;
			}
			else{ 
				break;
			}
		}
		printf("Found an operand, yay\n");
		return tk;
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
					else return NULL;
				}
				else return NULL;
			}
			else{ 
				break;
			}
		}
		printf("Found an operand, yay\n");
		return tk;
	}
	return NULL;
}
struct token *ArrayVariable(struct token *tk){
	if(tk->id == VARIABLE_NAME){
		tk = tk->next;
		if(tk->id == CORCHETE_L){
			tk = OperandInt(tk->next);
			if(tk != NULL && tk->id == CORCHETE_R){
				return tk->next;
			}
		}
	}

	return NULL;
}