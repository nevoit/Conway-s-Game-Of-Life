/*
 * twoPlayer.c
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
static void preparationTwoCells(Array arr, int size);
static void inputFromPlayers(Array arr, int size, int gen_num);
static void changeTurns(Array arr, int size, int gen_num);

/**************************************************
 ********** Function implementation ***************
 **************************************************/

/* Manage the zero player game - main function */
void beginLifeForTwo(Array arr, int size ,int generations, char file_name[])
{
	//create the board game
	preparationTwoCells(arr, size);

	//put the file on the board
	readFile(arr, size, file_name);

	//Do all the generations
	changeTurns(arr, size, generations);
}

static void changeTurns(Array arr, int size, int gen_num)
{
	generationChange(arr, size, 1);
	saveNeighbors(arr,size);
	PrintFunctionArray(arr);
	int turn=2;

		while(turn<=gen_num)
		{
			inputFromPlayers(arr,size,turn);
			EvolveFunctionArray(arr);

			turn++;
		}

}

static void inputFromPlayers(Array arr, int size, int gen_num)
{
	int row=0, col=0;
	int playerNum = (gen_num%2)+1;
	printf("Player %d: Please enter row number to kill:", playerNum);
	scanf("%d", &row);
	printf("Player %d: Please enter column number to kill:", playerNum);
	scanf("%d", &col);

	printf("Your row: %d Your Col: %d \n", row,col);

	Array row_array = arr->elements[row];
	Cell cell = row_array->elements[col];
	cell->cellState = 0;

	row=0, col=0;
	printf("Player %d: Please enter row number to control:", playerNum);
	scanf("%d", &row);
	printf("Player %d: Please enter column number to control:", playerNum);
	scanf("%d", &col);

	printf("Your row: %d Your Col: %d \n", row,col);

	row_array = arr->elements[row];
	cell = row_array->elements[col];
	cell->cellState = playerNum;

	saveNeighbors(arr,size);
}


/* Sets the board with zero player cells - receives the 2D board and its' size */
static void preparationTwoCells(Array arr, int size)
{
	int i=0;
	for (i = 0; i < size; i++)
	{
		Array row = NULL;
		row = (Array) arr->elements[i]; //1D array that will be filled with 0 player cells
		setFunc(row,CopyFunctionTPC,FreeFunctionTPC,PrintFunctionTPC,EvolveFunctionTPC);
	}
	return;
}
