#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person {
	char *name;
	int age;
	int height;
	int weight;
};

struct Person Person_create(char *name, int age, int height, int weight){
	struct Person who  ;
	//assert(who != NULL);

	who.name = strdup(name);
	who.age = age;
	who.height = height;
	who.weight = weight;

	return who;
}

void Person_destroy(struct Person who){
	//assert(who != NULL);

	free(who.name);
}

void Person_print(struct Person who){
	printf("Name: %s\n", who.name);
	printf("\tAge: %d\n", who.age);
	printf("\tHeight: %d\n", who.height);
	printf("\tWeight: %d\n", who.weight);
}

int main(int argc, char *argv[]){
	struct Person fukura = Person_create("Fukura", 32, 64, 140);
	struct Person he2 = Person_create("He2", 20, 72, 180);

	printf("fukura is at memory location %p:\n",&fukura);
	Person_print(fukura);

	printf("he2 is at memory location %p:\n",&he2);
	Person_print(he2);

	fukura.age += 20;
	fukura.height -= 2;
	fukura.weight +=40;
	Person_print(fukura);

	he2.age += 20;
	he2.weight += 20;
	Person_print(he2);

	Person_destroy(fukura);
	Person_destroy(he2);
	
	return 0;
}

