#include <stdio.h>

int main(int argc, char *argv[])
{
    char *states[] = {
        "California", NULL,
        "Washington", "Texas"
    };
    int num_states = 4;

	states[3] = argv[3];
	argv[1] = states[0];
	argv[2] = "lit";
	// argv[1][0] = 'h';
	// argv[2][0] = 'n';
	argv[3][0] = 'y';

    for(int i = 0; i < argc; i++) {
        printf("arg %d: %s\n", i, argv[i]);
    }

    for(int i = 0; i < num_states; i++) {
        printf("state %d: %s\n", i, states[i]);
    }

    return 0;
}
