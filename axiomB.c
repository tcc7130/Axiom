#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LENGTH 255
#define NELEMS(x) (sizeof(x) / sizeof((x)[0]))

const char *keywords[] = {"while","for","int","char","str","double","if","else","elif","read","print","println"};
int isKeyword(char *w);

struct Token {
	char *name;
	char *value;
};

struct Token caseD (char c){
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
	char sim_esp[]={';',',','\'','"','{','}','[',']','(',')'};
	struct Token *tokens;
	tokens = (struct Token *) malloc (MAX_LENGTH);
	char *token, *word;
	int c;
	size_t n = 0, w = 0;
        token = (char *) malloc (MAX_LENGTH);
		
   	if(fp!=NULL){
		while((c = fgetc(fp)) != EOF){
			if(isspace(c)==0){
				//tokens[n] = (struct Token) caseD(c);
				//printf("%s\t\t%s\n", tokens[n].name, tokens[n].value);
				//n++;
			}
			word[w++]=c;
			//printf("%s\n",word);
			if(isKeyword(word)==1){
				size_t i=w;
				//if(word[i++]
				printf("%s\n",word);	
			}
		}
		token[n] = 0;
    	}	
}
int isCharInArray(char c, char *a, int size){
	for(int i=0; i<size; i++){
		if(a[i] == c)
		       return 1;	
	}
	return 0;
}	
int isKeyword(char *w){
	size_t n = NELEMS(keywords);
	for(int i=0; i<n; i++){
		if(strncmp(w, keywords[i], strlen(keywords[i]))==0)
			return 1;
		//printf("%li\n", n);
	}

	return 0;
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
