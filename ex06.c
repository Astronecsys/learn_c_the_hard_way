#include <stdio.h>

int main(int argc, char *argv[]){
	int distance = 100;
	float power = 2.345f;
	double super_power = 56789.4532;
	char initial = 'A';
	char first_name[] = "Zed";
	char last_name[] = "Shaw";

	printf("You are %d miles away.\n", distance);
    printf("You have %.3f levels of power.\n", power);
    printf("You have %ef awesome super powers.\n", super_power);
    printf("I have an initial %c.\n", initial);
    printf("I have a first name %s.\n", first_name);
    printf("I have a last name %s.\n", last_name);
    printf("My whole name is %s %c. %s.\n",
            first_name, initial, last_name);
	printf("3");
	printf("3\n");
	printf("%+i\n",distance);
	printf("%o\n",distance);
	printf("%u\n",distance);
	printf("%x\n",distance);
    return 0;
}
