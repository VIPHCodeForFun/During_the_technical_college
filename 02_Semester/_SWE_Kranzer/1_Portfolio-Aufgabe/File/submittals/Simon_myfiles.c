/*
 ============================================================================
 Name        : myfiles.c
 Author      : Simon
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		printf("USAGE: %s srcfile\n", argv[0]);
		return 0;
	}

	FILE *src;
	src = fopen(argv[1], "rt");
	if (NULL == src)
	{
		printf("ERROR: Connot open file %s!\n", argv[1]);
		return 0;
	}

	char buffer[32000];
	while (NULL != (fgets(buffer, 32000, src))) //char *fgets( char *str, int n, FILE *stream );
	{
		printf("%s", buffer);
	}
	fclose(src);
	return 0;
}
