#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "axiom2.h"

int endsToken(char c){
	if(c == ' ' || c == ';' || c == '(' || c == ')' || c == '{' || c == '}'){
		printf("Si es final del token\n");
		return 1;
	}
	return (c == ' ' || c == ';' || c == '(' || c == ')' || c == '{' || c == '}');
}

struct token *checksToken(char *word, struct token *tok){
	//printf("%s\n",word);
	if(!strcmp(word, "int")){
		tok->next = malloc(sizeof(struct token));
		tok = tok->next;
		tok->id = 1;
		tok->content = malloc(sizeof(word));
		strcpy(tok->content, word);
		tok->next = NULL;
		printf("Found token: %s\n", tok->content);
		return tok;
	}
	else if(!strcmp(word, "x[]")){
		tok->next = malloc(sizeof(struct token));
		tok = tok->next;
		tok->id = 2;
		tok->content = malloc(sizeof(word));
		strcpy(tok->content, word);
		tok->next = NULL;
		printf("Found token: %s\n", tok->content);			
		return tok;
	}
	else if(!strcmp(word, ";")){
		tok->next = malloc(sizeof(struct token));
		tok = tok->next;
		tok->id = 3;
		tok->content = malloc(sizeof(word));
		strcpy(tok->content, word);
		tok->next = NULL;
		printf("Found token: %s\n", tok->content);			
		return tok;
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
	else{
		tok->next = malloc(sizeof(struct token));
		tok = tok->next;
		tok->id = -1;
		tok->content = malloc(sizeof(word));
		strcpy(tok->content, word);
		tok->next = NULL;
		printf("Undefined token: %s\n", tok->content);
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
	printf("Undefined token: %s\n", tok->content);
	return tok;
}

void lex(FILE *fp){
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
   	while(fgets(buf, 255, fp)){
   		//printf("\nbuf: %s\n", buf);
		memset(word, 0, sizeof(word));
		j = 0;
		for(int i = 0; buf[i] != 0; i++){
			if(buf[i] == ' '){
				currentToken = checksToken(word, currentToken);
				memset(word, 0, sizeof(word));
				j = 0;
			}
			if(buf[i] == ';'){
				currentToken = checksToken(word, currentToken);
				memset(word, 0, sizeof(word));
				j = 0;
				checksToken(";", currentToken);
				printf("HOLA\n");
			}

			if(buf[i] != ' ' && buf[i] != '\t'){
				word[j] = buf[i];
				j++;
			}
			// if(!strcmp(word,"int")){
			// }
			//printf("%s\n", word);
		}
	}

	printf("LIST:\n");
    while(head){
    	printf("FINAL: %s\n", head->content);
    	head = head->next;
    }
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

	lex(fp);
}