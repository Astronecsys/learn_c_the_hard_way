#include <stdio.h>

int main()
{
    int age = 10;
    int height = 72;

    printf("I am %2$*1$d years old.\n", age, height);
    printf("I am %d inches tall.\n", height);

    return 0;
}
