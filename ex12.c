#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;
	printf("Here %d arguments\n",argc-1);
    if(argc == 2) {
        printf("You only have one argument. You suck.\n");
    } else if(argc > 2 && argc < 4) {
        printf("Here's your arguments:\n");

        for(i = 1; i < argc; i++) {
            printf("%s ", argv[i]);
        }
        printf("\n");
    } else {
        printf("You have too many arguments. You suck.\n");
    }

    return 0;
}
