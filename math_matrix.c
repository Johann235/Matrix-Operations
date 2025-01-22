// CODE: include necessary library(s)
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "functions.h"
#include "functions.c"

int main(int argc, char *argv[]) {
    srand(time(NULL));

    // Check if the number of arguments is correct
    if (argc < 6 || argc > 7) {
        printf("Usage: %s nrows_A ncols_A nrows_B ncols_B <operation> [print]\n", argv[0]);
        return 1;
    }

    // CODE: Generate random matrices A with size N1*M1 and B with size N2*M2

    // Setting up all the variables
    int N1 = atoi(argv[1]); 
    int M1 = atoi(argv[2]);
    int N2 = atoi(argv[3]);
    int M2 = atoi(argv[4]);
    char operation [14];
    strcpy(operation, argv[5]);
    char print [10];
    strcpy(print,argv[6]);

    double **A;
    A = (double**)malloc(sizeof(double*)*N1);
    for (int i = 0; i < N1; i ++)
    {
        A[i] = (double*)malloc(sizeof(double)*M1);
    }
    
    double **B;
    B = (double**)malloc(sizeof(double*)*N1);
    for (int i = 0; i < N1; i ++)
    {
        B[i] = (double*)malloc(sizeof(double)*M1);
    }
    double **result;
    
    

    //Generate random matrices A and B
    generateMatrix(N1,M1,A);
    generateMatrix(N2,M2,B);
    

    //Print out matrices A and B
    
    printf("A = \n");
    printMatrix(N1,M1,A);
    printf("\nB = \n");
    printMatrix(N2,M2,B);
    

    clock_t start, end;
    double time;
    //If the operation is add/subtract, call the respective function
    if(strcmp(operation, "add") == 0 || strcmp(operation, "subtract") == 0)
    {
        result = (double**)malloc(sizeof(double*)*N1);
        for (int i = 0; i < N1; i ++)
        {
            result[i] = (double*)malloc(sizeof(double)*M1);
        }
        if(strcmp(operation, "add") == 0)
            {
                start = clock();
                addMatrices(N1,M1,A,N2,M2,B,result);
                end = clock();

                time = ( (double) end-start) / CLOCKS_PER_SEC;
                printf("Time taken = %f\n", time);

                if(strcmp(print, "print") == 0)
                {
                    printf("\nResult = \n");
                    printMatrix(N1,M1,result);
                }
            }

        if(strcmp(operation, "subtract") == 0)
            {
                subtractMatrices(N1,M1,A,N2,M2,B,result);
                if(strcmp(print, "print") == 0)
                {
                    printf("\nResult = \n");
                    printMatrix(N1,M1,result);
                }
            }
    }

    //If operation is multiply, call AxB
    if(strcmp(operation, "multiply") == 0)
    {
        result = (double**)malloc(sizeof(double*)*N1);
        for (int i = 0; i < N1; i ++)
        {
            result[i] = (double*)malloc(sizeof(double)*M2);
        }
        multiplyMatrices(N1,M1,A,N2,M2,B,result);
        if(strcmp(print, "print") == 0)
                {
                    printf("\nResult = \n");
                    printMatrix(N1,M2,result);
                }
    }

    //If operation is solve, call Ax=B
    if(strcmp(operation, "solve") == 0)
    {
        result = (double**)malloc(sizeof(double*)*N1);
        for (int i = 0; i < N1; i ++)
        {
            result[i] = (double*)malloc(sizeof(double)*M2);
        }
        solveLinearSystem(N1,M1,A,N2,M2,B,result);
        if(strcmp(print, "print") == 0)
                {
                    printf("\nResult of x=B/A \n");
                    printMatrix(N1,M2,result);
                    printf("\nAx = \n");

                    //Check the results
                    multiplyMatrices(N1,M1,A,N2,M2,result,B);
                    printMatrix(N2,M2,B);

                }
    }

    deallocateMatrix(A, N1);
    deallocateMatrix(B, N2);
    deallocateMatrix(result, N1);

    return 0;

}