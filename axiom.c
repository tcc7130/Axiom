#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "axiom.h"
#include "table.h"
#include "syntax.c"

struct token *checksToken(char *word, struct token *tok,int line){
	int decimal = 0;
	
	if(!strcmp(word, "int") || !strcmp(word, "double") || !strcmp(word, "char") || !strcmp(word, "str")){
		return createToken(VARIABLE_TYPE, word, tok,line);
	}
	else if (isdigit(word[0])) {	
		for (int i = 1; i < strlen(word); i++)
		{
			if (!(isdigit(word[i]) || word[i] == 46)) {
				tok->next = malloc(sizeof(struct token));
					tok = tok->next;
					tok->id = -1;
					tok->line = line;
					tok->content = malloc(sizeof(word));
					strcpy(tok->content, word);
					tok->next = NULL;
					printf("Undefined token: %s\n", tok->content);
					return tok;
			}
			if (word[i] == 46) {
				decimal++;
			}
		}
		if (decimal == 0) {
			return createToken(INTEGER, word, tok,line);
		}
		else if (decimal == 1) {
			if (word[strlen(word) - 1] == 46) {
				tok->next = malloc(sizeof(struct token));
				tok = tok->next;
				tok->id = -1;
				tok->content = malloc(sizeof(word));
				strcpy(tok->content, word);
				tok->next = NULL;
				printf("Point at end: %s\n", tok->content);
				return tok;
			}
			return createToken(DECIMAL, word, tok,line);
		}
		else {
			tok->next = malloc(sizeof(struct token));
			tok = tok->next;
			tok->id = 3;
			tok->content = malloc(sizeof(word));
			strcpy(tok->content, word);
			tok->next = NULL;
			printf("More than one point: %s\n", tok->content);
			return tok;
		}
	}
	else if(!strcmp(word, ";")){
		return createToken(SEMICOLON, word, tok, line);
	}
	else if(!strcmp(word, "(")){
		return createToken(PAREN_L, word, tok, line);
	}
	else if(!strcmp(word, ")")){
		return createToken(PAREN_R, word, tok, line);		
	}
	else if(!strcmp(word, "{")){
		return createToken(LLAVE_L, word, tok, line);
	}
	else if(!strcmp(word, "}")){
		return createToken(LLAVE_R, word, tok, line);
	}
	else if(!strcmp(word, "[")){
		return createToken(CORCHETE_L, word, tok, line);
	}
	else if(!strcmp(word, "]")){
		return createToken(CORCHETE_R, word, tok, line);
	}
	else if(!strcmp(word, "while")){
		return createToken(KEYWORD_WHILE, word, tok, line);
	}
	else if(!strcmp(word, "for")){
		return createToken(KEYWORD_FOR, word, tok, line);
	}
	else if(!strcmp(word, "if")){
		return createToken(KEYWORD_IF, word, tok, line);
	}
	else if(!strcmp(word, "else")){
		return createToken(KEYWORD_ELSE, word, tok, line);
	}
	else if(!strcmp(word, "elif")){
		return createToken(KEYWORD_ELIF, word, tok, line);
	}
	else if(!strcmp(word, "read")){
		return createToken(KEYWORD_READ, word, tok, line);
	}
	else if(!strcmp(word, "print")){
		return createToken(KEYWORD_PRINT, word, tok, line);
	}
	else if(!strcmp(word, "println")){
		return createToken(KEYWORD_PRINTLN, word, tok, line);
	}
	else if(isalpha(word[0])){
		for(int i = 1; i < strlen(word); i++){
			if(!isalpha(word[i]) && !isdigit(word[i])){
				//return createToken(-1, word, tok, line);
				tok->next = malloc(sizeof(struct token));
				tok = tok->next;
				tok->id = -1;
				tok->content = malloc(sizeof(word));
				strcpy(tok->content, word);
				tok->next = NULL;
				printf("Undefined token: %s\n", tok->content);
				return tok;
			}
		}
		return createToken(VARIABLE_NAME, word, tok, line);
	}
	else if(strlen(word) > 0){
		tok->next = malloc(sizeof(struct token));
		tok = tok->next;
		tok->id = -1;
		tok->content = malloc(sizeof(word));
		strcpy(tok->content, word);
		tok->next = NULL;
		printf("Undefined token: %s\n", tok->content);
		return tok;
	}
	//else
		return tok;
}

struct token *createToken(int id, char *word, struct token *tok, int line){
	tok->next = malloc(sizeof(struct token));
	tok = tok->next;
	tok->id = id;
	tok->line= line;
	tok->content = malloc(sizeof(word));
	strcpy(tok->content, word);
	tok->next = NULL;
	//printf("Found token: %s\n", tok->content);
	id != -1 ? printf("Found token: %s\n", tok->content) : printf("Undefined token: %s\n", tok->content); 

	return tok; 
}

struct tokenList *lex(FILE *fp){
	struct tokenList *lists = NULL;
	lists = malloc(sizeof(struct tokenList));

	struct token *head;
	head = malloc(sizeof(struct token));
	head->id = START;
	head->content = "START";
	head->next = NULL;
	lists->start = head;

	struct token *temp;
	struct token *currentToken;
	currentToken = head;

	char c;
	char *buf = "";
	char *tok = "";
	//char *comp ;
	//comp = malloc(255);

	char word[64] = "";
	char *word2 = "";

	int j;
	int isString = 0;
	int line=1;

   	while(fgets(buf, 255, fp)){
   		//printf("\nbuf: %s\n", buf);
		memset(word, 0, sizeof(word));
		j = 0;
		for(int i = 0; buf[i] != 0; i++){
			//printf("index: %i, word: %s\n",i, word);
			if(!isString){
				//printf("1\n");
				switch(buf[i]){
					case ' ':
						currentToken = checksToken(word, currentToken,line);
						memset(word, 0, sizeof(word));
						j = 0;
						break;
					case ';':
						currentToken = checksToken(word, currentToken,line);
						memset(word, 0, sizeof(word));
						j = 0;
						currentToken = checksToken(";", currentToken,line);
						break;
					case ',':
						currentToken = checksToken(word, currentToken,line);
						memset(word, 0, sizeof(word));
						j = 0;
						currentToken = createToken(COMA, ",", currentToken,line);
						break;
					case '(':
						currentToken = checksToken(word, currentToken,line);
						memset(word, 0, sizeof(word));
						j = 0;
						currentToken = checksToken("(", currentToken,line);
						break;
					case ')':
						currentToken = checksToken(word, currentToken,line);
						memset(word, 0, sizeof(word));
						j = 0;
						currentToken = checksToken(")", currentToken,line);
						break;
					case '{':
						currentToken = checksToken(word, currentToken,line);
						memset(word, 0, sizeof(word));
						j = 0;
						currentToken = checksToken("{", currentToken,line);
						break;
					case '}':
						currentToken = checksToken(word, currentToken,line);
						memset(word, 0, sizeof(word));
						j = 0;
						currentToken = checksToken("}", currentToken,line);
						break;
					case '[':
						currentToken = checksToken(word, currentToken,line);
						memset(word, 0, sizeof(word));
						j = 0;
						currentToken = checksToken("[", currentToken,line);
						break;
					case ']':
						currentToken = checksToken(word, currentToken,line);
						memset(word, 0, sizeof(word));
						j = 0;
						currentToken = checksToken("]", currentToken,line);
						break;
					case '"':
						currentToken = checksToken(word, currentToken,line);
						memset(word, 0, sizeof(word));
						j = 0;
						isString = 1;
						break;
					case '\'':
						currentToken = checksToken(word, currentToken,line);
						memset(word, 0, sizeof(word));
						j = 0;
						isString = 2;
						break;
					case '>':
						currentToken = checksToken(word, currentToken,line);
						memset(word, 0, sizeof(word));
						j = 0;
						if(buf[i+1] == '='){
							currentToken = createToken(COMPARE_OP, ">=", currentToken,line);
							i++;
						}
						else
							currentToken = createToken(COMPARE_OP, ">", currentToken,line);
						break;
					case '<':
						currentToken = checksToken(word, currentToken,line);
						memset(word, 0, sizeof(word));
						j = 0;
						if(buf[i+1] == '='){
							currentToken = createToken(COMPARE_OP, "<=", currentToken,line);
							i++;
						}
						else
							currentToken = createToken(COMPARE_OP, "<", currentToken,line);
						break;
					case '=':
						currentToken = checksToken(word, currentToken,line);
						memset(word, 0, sizeof(word));
						j = 0;
						if(buf[i+1] == '='){
							currentToken = createToken(COMPARE_OP, "==", currentToken,line);
							i++;
						}
						else
							currentToken = createToken(ASSIGN, "=", currentToken,line);
						break;
					case '!':
						currentToken = checksToken(word, currentToken,line);
						memset(word, 0, sizeof(word));
						j = 0;
						if(buf[i+1] == '='){
							currentToken = createToken(COMPARE_OP, "!=", currentToken,line);
							//i++;
						}
						else
							currentToken = checksToken("!", currentToken,line);
						break;
					case '+':
						currentToken = checksToken(word, currentToken,line);
						memset(word, 0, sizeof(word));
						j = 0;
						if(buf[i+1] == '+'){
							currentToken = createToken(INCREMENT, "++", currentToken,line);
							i++;
						}
						else
							currentToken = createToken(ARITMETIC_OP, "+", currentToken,line);
						break;
					case '-':
						currentToken = checksToken(word, currentToken,line);
						memset(word, 0, sizeof(word));
						j = 0;
						if(buf[i+1] == '-'){
							currentToken = createToken(DECREMENT, "--", currentToken,line);
							i++;
						}
						else
							currentToken = createToken(ARITMETIC_OP, "-", currentToken,line);
						break;
					case '*':
						currentToken = checksToken(word, currentToken,line);
						memset(word, 0, sizeof(word));
						j = 0;
						currentToken = createToken(ARITMETIC_OP, "*", currentToken,line);
						break;
					case '/':
						currentToken = checksToken(word, currentToken,line);
						memset(word, 0, sizeof(word));
						j = 0;
						currentToken = createToken(ARITMETIC_OP, "/", currentToken,line);
						break;
					case '%':
						currentToken = checksToken(word, currentToken,line);
						memset(word, 0, sizeof(word));
						j = 0;
						currentToken = createToken(ARITMETIC_OP, "%", currentToken, line);
				}

				if(!isspace(buf[i]) && buf[i] != '(' && buf[i] != ')' 
				&& buf[i] != '{' && buf[i] != '}' && buf[i] != '[' 
				&& buf[i] != ']' && buf[i] != ';' && buf[i] != ','
				&& buf[i] != '>' && buf[i] != '<' && buf[i] != '='
				&& buf[i] != '!' && buf[i] != '-' && buf[i] != '+'
				&& buf[i] != '/' && buf[i] != '*'){
					word[j] = buf[i];
					j++;
				}
			}
			else{
				word[j] = buf[i];
				j++;
				if(isString == 1 && buf[i] == '"'){
					currentToken = createToken(STRING, word, currentToken,line);
					memset(word, 0, sizeof(word));
					j = 0;
					isString = 0;
				}
				else if(isString == 2 && buf[i] == '\''){
					if(strlen(word) == 3){
						currentToken = createToken(KCHAR, word, currentToken,line);
						memset(word, 0, sizeof(word));
						j = 0;
						isString = 0;
					}
					else{
						currentToken = createToken(-1, word, currentToken,line);
						memset(word, 0, sizeof(word));
						j = 0;
						isString = 0;
					}
				}
			}		
		}
		line++;
	}

	printf("LIST:\n");
    while(head){
    	printf("ID: %i, CONTENT: %s\n", head->id, head->content);
    	head = head->next;
    }
    return lists;
}

int main(int argc, char *args[]){
	if(!args[1]){
		printf("Needs more arguments\n");
		return 1;
	}

	FILE *fp = fopen(args[1], "r");

	if(!fp){
		printf("Could not open file: %s\n", args[1]);
		return 1;
	}

	struct tokenList *tl = lex(fp);
	syntax(tl);
	//printTable(t);
	//struct symbol *s = t->start;
	//printf("Start-> nombre: %s, tipo: %i, value: %i\n",s->name,s->type,s->valueI);
}