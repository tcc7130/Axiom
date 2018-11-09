#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LENGTH 255

struct Token {
	char *name;
	char *value;
};

struct Token check (char c){
	struct Token t;
	t.name = (char *) malloc (20);
	t.value = (char *) malloc (20);
	switch(c){
		case ';':
			strcpy(t.name, "Semicolon");
			strcpy(t.value, ";");
			break;
		case '"':
			strcpy(t.name, "Comilla_Dob");
			strcpy(t.value, "\"");
			break;
		case '\'':
			strcpy(t.name, "Comilla_Sin");
			strcpy(t.value, "'");
			break;
		case ',':
			strcpy(t.name, "Coma");
			strcpy(t.value, ",");
			break;
		case '(':
			strcpy(t.name, "Paren_L");
			strcpy(t.value, "(");
			break;
		case ')':
			strcpy(t.name, "Paren_R");
			strcpy(t.value, ")");
			break;
		case '[':
			strcpy(t.name, "Corchete_L");
			strcpy(t.value, "[");
			break;
		case ']':
			strcpy(t.name, "Corchete_R");
			strcpy(t.value, "]");
			break;
		case '{':
			strcpy(t.name, "Llave_L");
			strcpy(t.value, "{");
			break;	
		case '}':
			strcpy(t.name, "LLave_R");
			strcpy(t.value, "}");
	}
	
	return t;
}

void lex(FILE *fp){
	struct Token *tokens;
	tokens = (struct Token *) malloc (MAX_LENGTH);
	char *token;
	int c;
	size_t n = 0;
        token = (char *) malloc (MAX_LENGTH);
		
   	if(fp!=NULL){
		while((c = fgetc(fp)) != EOF){
			if(isspace(c)==0){
				tokens[n] = (struct Token) check(c);
				printf("%s\t\t%s\n", tokens[n].name, tokens[n].value);
				n++;
			}	
		}
		token[n] = 0;
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
