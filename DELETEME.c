#include <stdio.h>


int main(void)
{
	char *s = "hello "" world";
	printf("%s\n", s);
}

// printf ignores double quotes inside the string if theres nothing between them