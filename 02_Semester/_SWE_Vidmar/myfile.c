/*
 * myfile.c
 *
 *  Created on: 09.03.2021
 *      Author: Simon
 */

#include <stdio.h>
#include <stdlib.h>

#include "myfile.h"

void catTextFile(char * path)
{
	if(NULL == path)
	{
		printf("Invalid path!\n");
		return;
	}
	FILE * datei;
	datei = fopen(path, "rt");
	if(NULL == datei)
	{
		fprintf(stdout, "File %s does not exist or is locked!\n", path);
		return;
	}
	int c;
	while( (c = fgetc(datei)) != EOF)
	{
		//printf("%c", c);
		putchar(c);
	}
	fclose(datei);
}

void catTextFile_(char * path) //Zeilenweise!
{
	if(NULL == path)
	{
		printf("Invalid path!\n");
		return;
	}
	FILE * datei;
	datei = fopen(path, "rt");
	if(NULL == datei)
	{
		fprintf(stdout, "File %s does not exist or is locked!\n", path);
		return;
	}
	char buffer[4096];

	while(NULL != (fgets(buffer, 4096, datei)))
	{
		printf("%s", buffer);
	}

	fclose(datei);
}

void copyTextFile(char * src, char * dst)
{
	    if(NULL == src)
		{
			printf("Invalid source path!\n");
			return;
		}
	    if(NULL == dst)
	    {
	    	printf("Invalid destination path!\n");
	    	return;
	    }
		FILE * dateis, * dateid;
		dateis = fopen(src, "rt");
		if(NULL == dateis)
		{
			fprintf(stdout, "File %s does not exist or is locked!\n", src);
			return;
		}
		dateid = fopen(dst, "rt");
		if(NULL != dateid)
		{
			printf("%s already exists!\n", dst);
			fclose(dateis);
			fclose(dateid);
			return;
		}
		dateid = fopen(dst, "wt");
		if(NULL == dateid)
		{
			printf("Unable to write to %s!\n", dst);
			fclose(dateis);
			return;
		}

		int c;
		while( (c = fgetc(dateis)) != EOF)
		{
			int r = fputc(c, dateid);
			if(r == EOF)
			{
				printf("Error writing to file  %s\n", dst);
				break;
			}
		}
		fclose(dateis);
		fclose(dateid);
}

