#include <stdio.h>
#include <ctype.h>
#include <string.h>

int can_print_it(char ch);
void print_letters(char arg[],int len);

void print_arguments(int argc, char *argv[]){
	for(int i = 0; i < argc; ++i){
		print_letters(argv[i],strlen(argv[i]));
	}
}

void print_letters(char arg[], int len){
	for(int i = 0;i<len; ++i){
		char ch = arg[i];
		if(isalpha(ch) || isblank(ch)){
			printf("'%c'==%d ",ch,ch);
		}
	}
	printf("\n");
}


int main(int argc, char **argv){
	print_arguments(argc, argv);
	return 0;
}
