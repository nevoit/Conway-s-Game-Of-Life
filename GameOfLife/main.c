/*
 * main.c
 *
 *  Created on: Dec 8, 2016
 *      Author: Nevo & Tomer
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"

int main(int argc, char* argv[])
{

	if(argc>4)
	{
		char *pchar= (char*) malloc((strlen(argv[3])+1)*sizeof(char));
		strcpy(pchar,argv[3]);

		//The C library function int atoi(const char *str) converts the string argument str to an integer (type int).
		int player=atoi(argv[1]), size=atoi(argv[2]), gen_num=atoi(argv[4]);
		inputFromUser(player,size,pchar,gen_num);

		free(pchar);
		pchar=NULL;
	}
	else
	{
		printf("Invalid input! \n");
	}

	return 0;
}
