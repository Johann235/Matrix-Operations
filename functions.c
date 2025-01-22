// CODE: include necessary library(s)
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "functions.h"

// Function to generate a random matrix
void generateMatrix(int rows, int cols, double **matrix) {
    // CODE: Generate random numbers between -10 and 10
    for (int i = 0; i < rows; i ++)
    {
        for (int j = 0; j < cols; j ++)
        {
            matrix[i][j] = ((float)rand() / (RAND_MAX/20)) - 10; //random number between -10 and 10
            //rand() / (RAND_MAX/10); tesing with integer only 
        }
    }
}

// Function to print a matrix
void printMatrix(int rows, int cols, double **matrix) {
    // CODE: to print the matrix 
    for (int i = 0; i < rows; i ++) //go through each row
    {
        for(int j = 0; j < cols; j ++) // go through each col 
        {
            printf("%f ",matrix[i][j]); // print the value at [row][col]
        }
        printf("\n"); //go to next line once we have finished that row
    }
}

// Function to add two matrices
void addMatrices(int N1, int M1, double **A , int N2, int M2, double **B, double **result) {
    // CODE: check for the condition (matrices are same size)
    if (N1 == N2 && M1 == M2) 
    {
        for (int i = 0; i < N1; i ++) //for each row
        {
            for (int j = 0; j < M1; j ++) // for each col
            {
                result[i][j] = A[i][j] + B[i][j]; //result at row col, should be the sum of A and B at that index
            }
        }

    }

    else
    {
        printf("Wrong Size\n");
    }
}


// CODE: do the same for subtractMatrices, multiplyMatrices, and solveLinearSystem functions

//sub matrices
void subtractMatrices(int N1, int M1,double **A , int N2, int M2, double **B, double **result) {
    // CODE: check for the condition 
    if (N1 == N2 && M1 == M2) 
    {
        for (int i = 0; i < N1; i ++) //go through rows
        {
            for (int j = 0; j < M1; j ++) // go through cols
            {
                result[i][j] = A[i][j] - B[i][j]; //new matrix at index row col is A at index row col minus B at index row Col
            }
        }
    }

    else
    {
        printf("Wrong Size\n");
    }
}

void multiplyMatrices(int N1, int M1,double **A , int N2, int M2, double **B, double **result) {
    // CODE: check for the condition 
    if (M1 == N2) 
    {
        for (int i = 0; i < N1; i ++) //go through rows
        {
            for (int j = 0; j < M2; j ++) // go through cols
            {
                result[i][j] = 0;
                for (int k = 0; k < M1; k ++) 
                //Goes through a row of A, and multiplies each element by the corresponding positiion on
                //in the column of B. These are totaled up and the value is the result at that the row of A and col of B
                {
                    result[i][j] += A[i][k] * B[k][j];
                }
            }
        }
    }

    else
    {
        printf("Wrong Size\n");
    }
}


//Helper function for solve linear systems
void rowOperation(int N3, int M3, double AB[N3][M3], int row1, int row2, int startCol)
{
    double mult1 = AB[row2][startCol]; //Gets the coefficients we are mu
    double mult2 = AB[row1][startCol];

    for (int j = startCol; j < (M3); j++) 
    //Does row operation row1 - row2, so that the value at AB[row1][startCol] is 0
    {
        AB[row1][j] = AB[row1][j] * mult1 - AB[row2][j] * mult2;
    }
}


void solveLinearSystem(int N1, int M1,double **A , int N2, int M2, double **B, double **x)
{
    if(M1 == N2)
    {

    int M3 = M1+M2;
    double AB[N1][M3]; //Makes the augmented matrix AB
    for (int i = 0; i < N1; i ++) //copies A into AB
    {
        for (int j = 0; j < M1; j ++)
        {
            AB[i][j] = A[i][j];
        }
    }

    for (int l = 0; l < M2; l ++) //copies B into AB
    {
        for (int k = 0; k < N2; k ++)
        {
            AB[k][M3-1] = B[k][l];
        }
    }

    if(AB[0][0] == 0 && AB[1][0] != 0) 
    //If the first element of the matrix is 0, swap row 0 and row 1
    {
        for (int k = 0; k < N1; k++)
        {
            double holder = AB[0][k];
            AB[0][k] = AB[1][k];
            AB[1][k] = holder;
        }
    }

    

    for (int n = 0; n < M3-1; n ++) //loop that does gaussian elimination until AB is in REF
        {
            for (int m = 1 + n; m < N1; m++)
            {
                if(AB[m][n] != 0)
                {
                rowOperation(N1,M3, AB,m,n,n);
                }
            }
        }


    for(int i = 0; i < N1; i ++) //goes up the matrix and solves for each variable, and add it to the x vector
    {
        x[N1-1-i][0] = AB[N1-1-i][M3-1] / AB[N1-1-i][M3-2-i];
        for(int j = 0; j < N1-i; j ++)
        {
            AB[j][M3-1] -= AB[j][M3-2-i]* x[N1-1-i][0];
            
        }
    }
    }

    else
    {
        printf("Wrong Size\n");
    }
}

void deallocateMatrix(double **matrix, int rows)
{
    for(int i = 0; i < rows; i ++)
    {
        free(matrix[i]);
    }
    free(matrix);
}
