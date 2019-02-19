#ifndef DEFS_H_
#define DEFS_H_

/*
 * Basic definitions
 */
typedef void * Element;
typedef Element (*CopyFunction)(Element);
typedef void (*FreeFunction)(Element);
typedef void (*PrintFunction)(Element);
typedef Element (*EvolveFunction)(Element);


/*
 * Structs and enums
 */
typedef enum e_state{
	DEAD, P1, P2, BLANK
}State;

struct t_cell{
	State cellState;
	State neighbors[8];
};
typedef struct t_cell * Cell;

struct t_array{
	int size;
	Element* elements;
	CopyFunction copyElement;
	FreeFunction freeElement;
	PrintFunction printElement;
	EvolveFunction evolveElement;
};
typedef struct t_array * Array;


/*
 * Zero player Functions Declaration
 * File: zeroPlayer.c
 */
void beginLifeForZero(Array arr, int size ,int generations, char file_name[]);


/*
 * Two player Functions Declaration
 * File: twoPlayer.c
 */
void beginLifeForTwo(Array arr, int size ,int generations, char file_name[]);

/*
 * IO Functions Declaration
 * File: gameIO.c
 */
void generationChange(Array arr, int size ,int generations);
void saveNeighbors(Array arr, int size);
void UpdateNeighbors(Array arr, int size, int i, int j);
int NeighborType(Array arr, int size, int i, int j);
void inputFromUser(int players, int board_size , char file_name [], int gen_num);
void readFile(Array arr, int size, char file_name[]);
void writeFile(Array arr, int size, char file_name[]);

/*
 * Function Declaration
 */
Array createArray(int _size, CopyFunction _copy, FreeFunction _free, PrintFunction _print, EvolveFunction _evolve);
void destroyArray(Array array);
void set(Array array, int i, Element element);		//assigns array[i]=element;
Element get(Array array, int i);					//returns array[i]

void setFunc(Array array,CopyFunction Copy_Func, FreeFunction Free_Func, PrintFunction Print_Func, EvolveFunction Evolve_Func);

Element		CopyFunctionArray		(Element arr);
void		FreeFunctionArray		(Element arr);
void		PrintFunctionArray		(Element arr);
Element		EvolveFunctionArray		(Element arr);

Element		CopyFunctionZPC		(Element zpc);
void		FreeFunctionZPC		(Element zpc);
void		PrintFunctionZPC		(Element zpc);
Element		EvolveFunctionZPC		(Element zpc);

Element		CopyFunctionTPC		(Element tpc);
void		FreeFunctionTPC		(Element tpc);
void		PrintFunctionTPC		(Element tpc);
Element		EvolveFunctionTPC		(Element tpc);

#endif /* DEFS_H_ */
