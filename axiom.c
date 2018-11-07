#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LENGTH 255

void lex(FILE *fp){
	char *token;
	int c;
	size_t n = 0;
        token = (char *) malloc (MAX_LENGTH);
		
   	if(fgets(token, MAX_LENGTH, fp)!=NULL){
		
		while((c = fgetc(fp)) != EOF)
		{
			token[n++] = (char) c;
		}
		token[n] = 0;
		printf("%s", token);
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
