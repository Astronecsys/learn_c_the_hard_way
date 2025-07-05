#include <stdio.h>

void print_int_arr(int *prt,int len){
	while(len--){
		printf("%d, ",*prt++);
	}
	printf("\n");
}
void print_str_arr(char **prt,int len){
	while(len--){
		printf("%s at %p\n", *prt, prt );
		prt++;
	}
}

int main(int argc, char *argv[]){

	int ages[] = {23, 43, 12, 89, 2};
    char *names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };

	int count = sizeof(ages) / sizeof(int);
    int i = 0;
	print_int_arr(ages, count);
	print_str_arr(names,count);
	for(i = 0; i < count; i++) {
        printf("%s has %d years alive.\n",
                names[i], ages[i]);
    }
	for(int i = count-1; i>=0; --i){
		printf("%s %d\n",names[i],ages[i]);
	}
	printf("---\n");

	int *cur_age = ages;
    char **cur_name = names;
	for(i = 0; i < count; i++) {
        printf("%s is %d years old.\n",
                *(cur_name+i), *(cur_age+i));
    }
	for(int i=count-1; i>=0; --i){
		printf("%s %d\n", *(cur_name+i), *(cur_age+i));
	}
    printf("---\n");

	for(i = 0; i < count; i++) {
        printf("%s is %d years old again.\n",
                cur_name[i], cur_age[i]);
    }
	for(int i = count-1; i>=0; --i){
		printf("%s %d\n", cur_name[i], cur_age[i]);
	}

    printf("---\n");
	for(cur_name = names, cur_age = ages;
			(cur_age - ages) < count;
            cur_name++, cur_age++)
    {
        printf("%s lived %d years so far.\n",
                *cur_name, *cur_age);
    }
	for(--cur_age, --cur_name;cur_age>=ages;--cur_age, --cur_name){
		printf("%s %d\n",*cur_name, *cur_age);
	}
	printf("---\n");
	printf("%p\n",names);
	printf("%p\n",&names);
	printf("%p\n",&(names[0]));
	printf("%p\n",names[0]);
	printf("%c\n",*(names[0]));
	printf("%p\n",names[1]);
	printf("%c\n",*(names[1]));
	printf("---\n");
	printf("%p\n",cur_age);
	printf("%p\n",&cur_age);
	cur_age = (int *)names;
	printf("%p\n",cur_age);
	printf("%p\n",&cur_age);
	printf("%#x%x\n",*(cur_age+1),*(cur_age+0));
	printf("%c\n",*(((char **)cur_age)[0]));
	printf("%#x%x\n",*(cur_age+3),*(cur_age+2));
	return 0;
}
