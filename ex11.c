#include <stdio.h>

int main(int argc, char *argv[])
{
    // go through each string in argv

    int i = argc-1;
    while(i>0) {
        printf("arg %d: %s\n", i, argv[i]);
        i--;
    }

    // let's make our own array of strings
    char *states[] = {
        "California", "Oregon",
        "Washington", "Texas"
    };

	i = 1;
	while(i < argc){
		if(i>5){
			break;
		}
		states[i-1] = argv[i];
		i++;
	}
    int num_states = 4;
    i = 0;  // watch for this
    while(i < num_states) {
        printf("state %d: %s\n", i, states[i]);
        i++;
    }

    return 0;
}
