#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void lex(FILE *fp){
	char *buf;
	char *token;
        token = (char *) malloc (15);	
   	if(fgets(token, 255, fp)!=NULL){
		char* i = token;
		char* j = token;
		while(*j != 0)
		{
			*i = *j++;
			if(*i != ' ')
				i++;
		}
		*i = 0;
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
