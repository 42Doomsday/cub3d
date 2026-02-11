#include <stdio.h>
#include <stddef.h>
#include <string.h>


//typedef struct test
//{
//	char earth;
//	char wind;
//	char fire;
//} t_elem;
//
//int main(void)
//{
//	t_elem el;
//	
//	el.earth = 'e';
//	el.wind = 'w';
//	el.fire = 'f';
//
//	printf("the first element is %c\n", el.earth);
//	printf("the first element bytes are %zu\n", offsetof(t_elem, earth));
//	printf("the second element is %c\n", el.wind);
//	printf("the second element bytes are %zu\n", offsetof(t_elem, wind));
//	printf("the third element is %c\n", el.fire);
//	printf("the third element bytes are %zu\n", offsetof(t_elem, fire));
//	return (0);
//
//}

typedef struct person
{
	int age;
	float height;
	char grade;
} t_person;


/*
 * (char *) here is char = 1 byte 
 * (int *) would be 4 bytes etc
 * we want to go byte by byte here so (char *) 
*/
void set_field(void *struct_ptr, size_t offset, void *value, size_t size)
{
	char *base = (char *)struct_ptr;
	memcpy(base + offset, value, size);
}

int main(void)
{
	t_person p;
	int age = 25;
	float height = 5.9;
	char grade = 'A';

	set_field(&p, offsetof(t_person, age), &age, sizeof(int));
	set_field(&p, offsetof(t_person, height), &height, sizeof(float));
	set_field(&p, offsetof(t_person, grade), &grade, sizeof(char));

	printf("Age: %d\n", p.age);
	printf("Height: %.1f\n", p.height);
	printf("Grade: %c\n", p.grade);
	return (0);
}
