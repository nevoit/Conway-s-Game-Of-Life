/*
 * gameIO.c
 *
 *  Created on: Dec 8, 2016
 *      Author: Nevo & Tomer
 */

#include "defs.h"
#include <stdio.h>
#include <stdlib.h>


Array createArray(int _size, CopyFunction _copy, FreeFunction _free, PrintFunction _print, EvolveFunction _evolve)
{
	Array arr = NULL;
	arr = (Array)malloc(sizeof(struct t_array));
	if (arr == NULL)
	{
		printf("Failed to allocate memory for a Array\n");
		exit(1);
	}

		arr->size = _size;
		arr->copyElement =_copy;
		arr->freeElement = _free;
		arr->printElement= _print;
		arr->evolveElement= _evolve;

	return arr;
}

void destroyArray(Array array)
{
	if(array == NULL)
		return;

	int i;
	for (i = 0; i < array->size; i++)
	{
		Element tmp_elm = array->elements[i];
		array->freeElement(tmp_elm);
	}
	free(array->elements);
	free(array);
}

void set(Array array, int i, Element element)	//assigns array[i]=element;
{
	array->elements[i] = NULL;
	array->elements[i] = element;
}


void setFunc(Array array ,CopyFunction Copy_Func, FreeFunction Free_Func, PrintFunction Print_Func, EvolveFunction Evolve_Func)
{
	array->copyElement = Copy_Func;
	array->freeElement = Free_Func;
	array->printElement = Print_Func;
	array->evolveElement = Evolve_Func;
}

Element get(Array array, int i) //returns array[i]
{
	Element elm = (Element) array->elements[i];
	return elm;
} // We need to think how to return the value of the get: pointer or copy?


/*
 * ADT - Array
 *
 *
 */

Element	CopyFunctionArray(Element elm)
{
	int size=((Array)elm)->size;
	Array copy = createArray(size, CopyFunctionArray,FreeFunctionArray,PrintFunctionArray,EvolveFunctionArray);

	int i;
	for (i = 0; i < size; i++)
	{
		Element tmp_elm = (Element) (((Array)elm)->elements[i]);
		copy->elements[i] = ((Array)elm)->copyElement(tmp_elm);
	}

	return copy;
}

void FreeFunctionArray(Element elm){
	destroyArray((Array)elm);
}

void PrintFunctionArray(Element elm){
	int i;
	Array arr = (Array) elm;
	for (i = 0; i < (arr->size); i++)
	{
		Element tmp_elm = arr->elements[i];
		arr->printElement(tmp_elm);

		if((i == (arr->size)-1))
			printf("\n");
	}
}

Element	EvolveFunctionArray(Element elm){ //Receives a 2D array and evolves all of its' rows and cells.

	int size=((Array)elm)->size;
	Array arr = (Array) elm;

	int i;
	for (i = 0; i < size; i++)
	{
		Element temp_elm = arr->elements[i];
		arr->evolveElement(temp_elm);
	}

	return arr;
}

/*
 * ADT - Zero Cells
 */

Element CopyFunctionZPC(Element zpc)
{
	Cell zpc_elm=NULL;
	zpc_elm =(Cell) malloc(sizeof(struct t_cell));
	zpc_elm->cellState=((Cell)zpc)->cellState;

	int var;
	for (var = 0; var < 8; var++)
		zpc_elm->neighbors[var]=((Cell)zpc)->neighbors[var];

	return zpc_elm;
}

void FreeFunctionZPC(Element zpc)
{
	if(zpc==NULL)
		return;

	free(zpc);
}

void PrintFunctionZPC(Element zpc)
{
	//printf("Im in the print cell func \n");
	switch (((Cell)zpc)->cellState)
	{
	case 0:
		printf(".");
		break;
	case 1:
		printf("X");
		break;
	case 3:
		printf(" ");
		break;
	default :
		printf("Error!");
		break;
	}
}

Element EvolveFunctionZPC(Element zpc)
{
	int neighbor_count=0;
	Cell zero = (Cell)zpc;

	int i;
	for (i = 0; i < 8; i++)
		if (zero->neighbors[i] == 1)
			neighbor_count++;

	if( (neighbor_count==2 || neighbor_count==3) && zero->cellState == 1)
		return (Element)zero;

	if(zero->cellState==1) //if cell is alive
	{
		if(neighbor_count<2 || neighbor_count>3)
			zero->cellState=0;
	}

	if(zero->cellState==0)
	{
		if(neighbor_count==3)
			zero->cellState=1;
	}

	return (Element)zero;
}


/*
 * ADT - Two Players
 */

Element CopyFunctionTPC(Element tpc)
{
	Cell tpc_elm=NULL;
	tpc_elm =(Cell) malloc(sizeof(struct t_cell));
	tpc_elm->cellState=((Cell)tpc)->cellState;

	int var;
	for (var = 0; var < 8; var++)
		tpc_elm->neighbors[var]=((Cell)tpc)->neighbors[var];

	return tpc_elm;
}

void FreeFunctionTPC(Element tpc)
{
	if(tpc==NULL)
		return;

	free(tpc);
}

void PrintFunctionTPC(Element tpc)
{
	switch (((Cell)tpc)->cellState)
	{
	case 0:
		printf(".");
		break;
	case 1:
		printf("X");
		break;
	case 2:
		printf("Y");
		break;
	case 3:
		printf(" ");
		break;
	default :
		printf("Error!");
		break;
	}
}

Element EvolveFunctionTPC(Element tpc)
{
	int neighborX_count=0, neighborY_count=0, sumOfNeighbors=0;
	Cell two = (Cell) tpc;

	/***Count the numbers of neighbors, X neighbors and Y neighbors***/
	int i;
	for (i = 0; i < 8; i++)
	{
		if ( two->neighbors[i] == 1) //count neighbors X
			neighborX_count++;
		else if (two->neighbors[i] == 2) //count neighbors Y
			neighborY_count++;
	}

	sumOfNeighbors=neighborX_count+neighborY_count;

	//if((sumOfNeighbors==2 || sumOfNeighbors==3) && ((two->cellState==1|| two->cellState==2)))
	//	return ((Element)tpc);

	/***Cell is alive***/
	if(two->cellState==1 || two->cellState==2)
	{
		if(sumOfNeighbors<2 || sumOfNeighbors>3)
			two->cellState=0;
		else //the cell is alive and has 2 or 3 neighbors
		{
			if( (two->cellState==1) && (neighborY_count==2 ||neighborY_count==3))
				two->cellState=2;
			else if ( (two->cellState==2) && (neighborX_count==2 ||neighborX_count==3))
				two->cellState=1;
		}
	}
	else /***Cell is DEAD***/
	{
		if(sumOfNeighbors==3)
		{
			if(neighborX_count>neighborY_count) //the cell will be a X type.
				two->cellState=1;
			else //the cell will be a Y type.
				two->cellState=2;
		}
	}

	return tpc;
}
