#include <stdio.h>

    // char name[4] ={'a','a','a','a'};
int main(int argc, char *argv[])
{
    int numbers[4] = {1};
	// name[3] = 'A';
	char * name = "QWE";
    // first, print them out raw
    printf("numbers: %d %d %d %d\n",
            numbers[0], numbers[1],
            numbers[2], numbers[3]);

    printf("name each: %c %c %c %c\n",
            name[0], name[1],
            name[2], name[3]);

    printf("name: %s\n", name);

    // setup the numbers
    numbers[0] = 1;
    numbers[1] = 2;
    numbers[2] = 3;
    numbers[3] = 4;

    // setup the name
    //  name[0] = 'Z';
    // name[1] = 'e';
    // name[2] = 'd';
    // name[3] = '\0';

    // then print them out initialized
    printf("numbers: %d %d %d %d\n",
            numbers[0], numbers[1],
            numbers[2], numbers[3]);

    printf("name each: %c %c %c %c\n",
            name[0], name[1],
            name[2], name[3]);

    // print the name like a string
    printf("name: %s\n", name);

    // another way to use name
    char *another = "Zed";

    printf("another: %s\n", another);

    printf("another each: %c %c %c %c\n",
            another[0], another[1],
            another[2], another[3]);
	numbers[2] = 'b';
	printf("charnumber %d %c\n",numbers[2],numbers[2]);
	// name[2] = 97;
	printf("numberchar %d %c\n",name[2],name[2]);

	char *litnum = "abcd";
	printf("0x%08x\n",*(int *)litnum);
    char *litnum2 = "abc";
	printf("0x%08x\n",*(int *)litnum2);
    return 0;
}
