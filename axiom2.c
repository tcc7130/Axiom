#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "axiom.h"

int endsToken(char c){
	if(c == ' ' || c == ';' || c == '(' || c == ')' || c == '{' || c == '}'){
		printf("Si es final del token\n");
		return 1;
	}
	return (c == ' ' || c == ';' || c == '(' || c == ')' || c == '{' || c == '}');
}

struct token *checksToken(char *word, struct token *tok){
	//printf("%s\n",word);
	int decimal = 0;
	if(!strcmp(word, "int") || !strcmp(word, "double") || !strcmp(word, "char") || !strcmp(word, "str")){
		
		return createToken(VARIABLE_TYPE, word, tok);
	}
	else if (isdigit(word[0])) {
		
		
		for (int i = 1; i < strlen(word); i++)
		{
			if (!(isdigit(word[i]) || word[i] == 46)) {
				tok->next = malloc(sizeof(struct token));
					tok = tok->next;
					tok->id = -1;
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
			tok->next = malloc(sizeof(struct token));
			tok = tok->next;
			tok->id = 3;
			tok->content = malloc(sizeof(word));
			strcpy(tok->content, word);
			tok->next = NULL;
			printf("Found token: %s\n", tok->content);
			return tok;
		}
		else if (decimal == 1) {
			if (word[strlen(word) - 1] == 46) {
				tok->next = malloc(sizeof(struct token));
				tok = tok->next;
				tok->id = -1;
				tok->content = malloc(sizeof(word));
				strcpy(tok->content, word);
				tok->next = NULL;
				printf("Undefined token: %s\n", tok->content);
				return tok;
			}
			tok->next = malloc(sizeof(struct token));
			tok = tok->next;
			tok->id = -1;
			tok->content = malloc(sizeof(word));
			strcpy(tok->content, word);
			tok->next = NULL;
			printf("Undefined token: %s\n", tok->content);
			return tok; 
		}
		else {
			tok->next = malloc(sizeof(struct token));
			tok = tok->next;
			tok->id = 3;
			tok->content = malloc(sizeof(word));
			strcpy(tok->content, word);
			tok->next = NULL;
			printf("Found token: %s\n", tok->content);
			return tok;
		}
	}
	else if(!strcmp(word, ";")){
		return createToken(22, word, tok);
	}
	else if(!strcmp(word, "(")){
		tok->next = malloc(sizeof(struct token));
		tok = tok->next;
		tok->id = 3;
		tok->content = malloc(sizeof(word));
		strcpy(tok->content, word);
		tok->next = NULL;
		printf("Found token: %s\n", tok->content);			
		return tok;
	}
	else if(!strcmp(word, ")")){
		tok->next = malloc(sizeof(struct token));
		tok = tok->next;
		tok->id = 3;
		tok->content = malloc(sizeof(word));
		strcpy(tok->content, word);
		tok->next = NULL;
		printf("Found token: %s\n", tok->content);			
		return tok;
	}
	else if(!strcmp(word, "{")){
		tok->next = malloc(sizeof(struct token));
		tok = tok->next;
		tok->id = 3;
		tok->content = malloc(sizeof(word));
		strcpy(tok->content, word);
		tok->next = NULL;
		printf("Found token: %s\n", tok->content);			
		return tok;
	}
	else if(!strcmp(word, "}")){
		tok->next = malloc(sizeof(struct token));
		tok = tok->next;
		tok->id = 3;
		tok->content = malloc(sizeof(word));
		strcpy(tok->content, word);
		tok->next = NULL;
		printf("Found token: %s\n", tok->content);			
		return tok;
	}
	else if(!strcmp(word, "[")){
		tok->next = malloc(sizeof(struct token));
		tok = tok->next;
		tok->id = 3;
		tok->content = malloc(sizeof(word));
		strcpy(tok->content, word);
		tok->next = NULL;
		printf("Found token: %s\n", tok->content);			
		return tok;
	}
	else if(!strcmp(word, "]")){
		tok->next = malloc(sizeof(struct token));
		tok = tok->next;
		tok->id = 3;
		tok->content = malloc(sizeof(word));
		strcpy(tok->content, word);
		tok->next = NULL;
		printf("Found token: %s\n", tok->content);			
		return tok;
	}
	else{
		if(strlen(word) > 0){
			tok->next = malloc(sizeof(struct token));
			tok = tok->next;
			tok->id = -1;
			tok->content = malloc(sizeof(word));
			strcpy(tok->content, word);
			tok->next = NULL;
			printf("Undefined token: %s\n", tok->content);
			return tok;
		}
		else
			return tok;
	}
	return NULL;
}

struct token *createToken(int id, char *word, struct token *tok){
	tok->next = malloc(sizeof(struct token));
	tok = tok->next;
	tok->id = id;
	tok->content = malloc(sizeof(word));
	strcpy(tok->content, word);
	tok->next = NULL;
	printf("Found token: %s\n", tok->content);
	return tok;
}

void lex(FILE *fp) {
	struct tokenList *lists = NULL;
	lists = malloc(sizeof(struct tokenList));

	struct token *head;
	head = malloc(sizeof(struct token));
	head->id = 0;
	head->content = "START";
	head->next = NULL;

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
	while (fgets(buf, 255, fp)) {
		//printf("\nbuf: %s\n", buf);
		memset(word, 0, sizeof(word));
		j = 0;
		for (int i = 0; buf[i] != 0; i++) {
			
			switch (buf[i]) {
			case ' ':
				currentToken = checksToken(word, currentToken);
				memset(word, 0, sizeof(word));
				j = 0;
				break;
			case ';':
				currentToken = checksToken(word, currentToken);
				memset(word, 0, sizeof(word));
				j = 0;
				currentToken = checksToken(";", currentToken);
				break;
			case '(':
				currentToken = checksToken(word, currentToken);
				memset(word, 0, sizeof(word));
				j = 0;
				currentToken = checksToken("(", currentToken);
				break;
			case ')':
				currentToken = checksToken(word, currentToken);
				memset(word, 0, sizeof(word));
				j = 0;
				currentToken = checksToken(")", currentToken);
				break;
			case '{':
				currentToken = checksToken(word, currentToken);
				memset(word, 0, sizeof(word));
				j = 0;
				currentToken = checksToken("{", currentToken);
				break;
			case '}':
				currentToken = checksToken(word, currentToken);
				memset(word, 0, sizeof(word));
				j = 0;
				currentToken = checksToken("}", currentToken);
				break;
			case '[':
				currentToken = checksToken(word, currentToken);
				memset(word, 0, sizeof(word));
				j = 0;
				currentToken = checksToken("[", currentToken);
				break;
			case ']':
				currentToken = checksToken(word, currentToken);
				memset(word, 0, sizeof(word));
				j = 0;
				currentToken = checksToken("]", currentToken);
				break;
			case '"':
				break;
			}

			if (!isspace(buf[i]) && buf[i] != '(' && buf[i] != ')'
				&& buf[i] != '{' && buf[i] != '}' && buf[i] != '['
				&& buf[i] != ']' && buf[i] != ';' && buf[i] != ',') {
				word[j] = buf[i];
				j++;
			}
		}
	}

	printf("LIST:\n");
	while (head) {
		printf("FINAL: %s\n", head->content);
		head = head->next;
	}
}

int main(int argc, char *args[]) {
	if (!args[1]) {
		printf("Needs more arguments\n");
		return 1;
	}

	FILE *fp = fopen(args[1], "r");

	if (!fp) {
		printf("Could not open file: %s\n", args[1]);
		return 1;
	}

	lex(fp);
}