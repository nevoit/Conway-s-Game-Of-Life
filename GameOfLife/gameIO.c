/*
 * gameIO.c
 *
 *  Created on: Dec 8, 2016
 *      Author: Nevo & Tomer
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"


static Array gamePreparation(int board_size);
static void checkInputValid(int players, int board_size , char file_name[], int gen_num);
static void printNeighbors(Array arr, int size);

/*
 * The Functions
 */
void inputFromUser(int players, int board_size , char file_name[], int gen_num)
{
	/***Checking if the input is valid***/
	checkInputValid(players, board_size, file_name, gen_num); //Checked


	/***Creating the game board***/
	Array arr = NULL;
	arr = gamePreparation(board_size);

	/***Create the cells For 0 OR 2 players***/
	if(players==0)
		beginLifeForZero(arr, board_size ,gen_num, file_name);
	else
		beginLifeForTwo(arr, board_size ,gen_num, file_name);

	/***Here we Printing the game board***/
	writeFile(arr,board_size,file_name);

	/***We need to free from the Heap***/
	destroyArray(arr);
}

static Array gamePreparation(int board_size)
{
	Array c_arr = NULL;
	c_arr = createArray(board_size, CopyFunctionArray,FreeFunctionArray,PrintFunctionArray,EvolveFunctionArray);

	c_arr->elements = (Element*) malloc(board_size*sizeof(Array));

	int i=0;
	for (i = 0; i < board_size; i++)
	{
		Array row = NULL;
		row = createArray(board_size, CopyFunctionArray,FreeFunctionArray,PrintFunctionArray,EvolveFunctionArray);

		set(c_arr,i,((Element)row));


		row->elements = (Element*) malloc(board_size*sizeof(Cell));
		int j=0;
		for (j = 0; j < board_size; j++)
		{
			Cell c_temp = NULL;
			c_temp=(Cell)malloc(sizeof(struct t_cell)); //creates a cell that will be put in row[j]

			if (c_temp == NULL)
			{
				printf("Failed to allocate memory for a cell\n");
				exit(1);
			}

			set(row,j,c_temp);
		}
	}

	return c_arr;
}

static void checkInputValid(int players, int board_size , char file_name[], int gen_num)
{
	if(players!=0 && players!=2)
	{
		printf("Error: %d is an invalid player number. \n",players);
		exit(1);
	}
    if (board_size<1)
	{
		printf("Error: %d is an invalid size. \n",board_size);
		exit(1);
	}
	if (gen_num<0)
	{
		printf("Error: %d is an invalid generation number. \n",gen_num);
		exit(1);
	}
	return;
}

void readFile(Array arr, int size, char file_name[])
{
	FILE *first_Generation;
	first_Generation = fopen(file_name, "r");


	int i=0;
	for (i = 0; i < size; i++)
	{
			Array row = (Array) arr->elements[i]; //1D array that will be filled with 0 player cells

			int j=0;
			while(j < size)
			{
				char state;
				fscanf(first_Generation, "%c" , &state);
				switch (state)
				{
					case '.':
						((Cell)(row->elements[j]))->cellState = DEAD;
						j++;
						break;
					case 'X':
						((Cell)(row->elements[j]))->cellState = P1;
						j++;
						break;
					case 'Y':
						((Cell)(row->elements[j]))->cellState = P2;
						j++;
						break;
					default:
						break;
				}
			}
		}

	fclose (first_Generation);
	return;
}


void writeFile(Array arr, int size, char file_name[])
{
	PrintFunctionArray(arr);
	return;
}



/* Return the type of the zero cell: 0-DEAD,1-P1,3-BLANK */
int NeighborType(Array arr, int size, int i, int j)
{

	if( (i>=0 && i<size) && (j>=0 && j<size))
	{
		Array row = ((Array) get(arr,i));
		Cell neighbor_cell = ((Cell) get(row,j));
		return neighbor_cell->cellState;
	}
	else return 3;

}

/* Update all the neighbors array of the cell you choose */
void UpdateNeighbors(Array arr, int size, int i, int j) //i = row number, j = column number
{
	Array row = ((Array) get(arr,i));
	Cell neighbor_cell = ((Cell) get(row,j));

	neighbor_cell->neighbors[0] = NeighborType(arr,size,i-1,j-1);
	neighbor_cell->neighbors[1] = NeighborType(arr,size,i-1,j);
	neighbor_cell->neighbors[2] = NeighborType(arr,size,i-1,j+1);
	neighbor_cell->neighbors[3] = NeighborType(arr,size,i,j-1);
	neighbor_cell->neighbors[4] = NeighborType(arr,size,i,j+1);
	neighbor_cell->neighbors[5] = NeighborType(arr,size,i+1,j-1);
	neighbor_cell->neighbors[6] = NeighborType(arr,size,i+1,j);
	neighbor_cell->neighbors[7] = NeighborType(arr,size,i+1,j+1);

	return;
}

/* Find all the cells on the array and update them */
void saveNeighbors(Array arr, int size)
{

	int i=0, j=0;
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			UpdateNeighbors(arr,size,i,j);

	return;
}

/* Do all the generations: save the neighbors and after that evolve the array */
void generationChange(Array arr, int size ,int generations)
{
	int i;
	for (i = 0; i < generations; i++)
	{
		saveNeighbors(arr,size);
		arr=EvolveFunctionArray(arr);
	}

	return;
}

static void printNeighbors(Array arr, int size)
{
	int i=0, j=0;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			Array row = ((Array) get(arr,i));
			Cell neighbor_cell = ((Cell) get(row,j));
			int var=0;
			for (var = 0; var < 8; var++)
			{
				printf("%d  |  " ,neighbor_cell->neighbors[var]);
			}
			printf("\n");
		}
		printf("\n");
	}
}
