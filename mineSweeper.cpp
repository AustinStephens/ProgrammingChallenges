/*
Test file for setUpMineSweeper.
Generates and prints a random minesweeper field of a given size, and a given amount of bombs in it.
9 indicates a mine since there cannot be a tile with 9 bombs surrounding it.
*/

#include <iostream>
#include <cmath>
#include <time.h>
#include <stdlib.h>

using std::cout;
using std::endl;

void setUpMineSweeper(int,int,int);

int main()
{
	setUpMineSweeper(10,10,10);	
}

void setUpMineSweeper(int rows, int cols, int mines) // number of rows, number of columns, number of mines in the field.
{
	if(rows * cols < mines) return;//could end up in an infinite loop if there are more mines than spaces in matrix
	
	int matrix[rows][cols];
	bool flag;
	int i, j;
	
	time_t timer;																			    
	srand(time(&timer));
	
	for (i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			matrix[i][j] = 0;
		}
	}
	
		
	for (int k = 0; k < mines; ++k)
	{	
		do 
		{											  
			i = rand() % (rows); // i wrote the whole thing using i and j instead of num1 and num2 so i guess this is how it has to be
			j = rand() % (cols);
			
			if(matrix[i][j] == 9) flag = true;
			else
			{
				bool plusRows = i + 1 < rows; // makes sure there is space next to the mine so we dont get a array out of bounds error
				bool minusRows = i - 1 >= 0;
				bool plusCols = j + 1 < cols;
				bool minusCols = j - 1 >= 0;
				matrix[i][j] = 9;
				if (plusRows && matrix[i + 1][j] != 9) matrix[i + 1][j]++; // if there isn't another mine next to it, increment that space.
				if (minusRows && matrix[i - 1][j] != 9) matrix[i - 1][j]++;
				if (plusCols && matrix[i][j + 1] != 9) matrix[i][j + 1]++;
				if (minusCols && matrix[i][j - 1] != 9) matrix[i][j - 1]++;
				if (plusRows && plusCols && matrix[i + 1][j + 1] != 9) matrix[i + 1][j + 1]++;
				if (plusRows && minusCols && matrix[i + 1][j - 1] != 9) matrix[i + 1][j - 1]++;
				if (minusRows && plusCols && matrix[i - 1][j + 1] != 9) matrix[i - 1][j + 1]++;
				if (minusRows && minusCols && matrix[i - 1][j - 1] != 9) matrix[i - 1][j - 1]++;
				flag = false;
			}
		}while(flag);
		
	}
	
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	
}
