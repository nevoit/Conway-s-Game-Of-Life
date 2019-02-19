/*
 * zeroPlayer.c
 *
 *  Created on: Dec 8, 2016
 *      Author: Nevo & Tomer
 */

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"


/**************************************************
 ********** Function Declaration ******************
 **************************************************/
static void preparationZeroCells(Array arr, int size);

/**************************************************
 ********** Function implementation ***************
 **************************************************/

/* Manage the zero player game - main function */
void beginLifeForZero(Array arr, int size ,int generations, char file_name[])
{
	//create the board game
	preparationZeroCells(arr, size);

	//put the file on the board
	readFile(arr, size, file_name);

	//Do all the generations
	generationChange(arr, size, generations);
}


/* Sets the board with zero player cells - receives the 2D board and its' size */
static void preparationZeroCells(Array arr, int size)
{
	int i=0;
	for (i = 0; i < size; i++)
	{
		Array row = NULL;
		row = (Array) arr->elements[i]; //1D array that will be filled with 0 player cells
		setFunc(row,CopyFunctionZPC,FreeFunctionZPC,PrintFunctionZPC,EvolveFunctionZPC);
	}
	return;
}
