#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>

void displaygridcells(int *grid, int size, char *charptr);
int inputsize();
void inputvalues(int *grid, int size);
int checkneighborscount(int *grid, int x, int y, int size);
int userinput(int *grid, int size);
void copygrid(int *grid1, int *grid2, int size);
void simulationrule(int *grid, int size, bool *changes);
void takechardisplay(char *charptr);
void commencing(char *charptr);
void inputval(int *grid, int size, char *charptr);

int main()
{
    int size = inputsize();
    int gridcells[size][size];
    int *matrixptr = &gridcells[0][0];
    char displaychar[2];
    char *charptr = &displaychar[0];
    takechardisplay(charptr);
    inputval(matrixptr, size, charptr);
    int speed = userinput(matrixptr, size);
    bool gridchanges = true;
    bool *boolptr = &gridchanges;
    
    commencing(charptr);
    while (gridchanges)
    {
        gridchanges = false;
        displaygridcells(matrixptr, size, charptr);
        simulationrule(matrixptr, size, boolptr);
        Sleep(speed);
    }
    printf("\nSimulation Complete!");
    
    return 0;
}

int inputsize()
{
    int z;
    while (true)
    {
        printf("\nEnter Grid Size (LIMIT: 1 - 40): ");
        scanf(" %d", &z);

        if (z < 41 && z > 0)
        {
            return z;
        }
        else 
        {
            printf("Input Number Within the Limit!");
        }
    }
}

void displaygridcells(int *grid, int size, char *charptr)
{
    printf("\033[H");
    for (int i = 0; i < size ; i++)
    {
        for (int o = 0; o < size ; o++)
        {
            if (*(grid + i * size + o) == 1)
            {
                
                printf(" %c ", *charptr);
            }
            else if (*(grid + i * size + o) == 2)
            {
                printf(" %c ", *(charptr + 1));
            }            
        }
        printf("\n");
    }
}

void inputvalues(int *grid, int size)
{
    //srand(time(NULL));
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
           *(grid + i * size + j) = (rand() % 2) + 1;
        }
    }
}

int checkneighborscount(int *grid, int x, int y, int size)
{
    int count = 0;

    for (int upperborder = -1; upperborder <= 1; upperborder++)
    {
        for (int lowerborder = -1; lowerborder <= 1; lowerborder++)
        {
            if (upperborder == 0 && lowerborder == 0) continue;

            int row = (x + upperborder + size) % size;
            int col = (y + lowerborder + size) % size; 

            if (*(grid + row * size + col) == 1)
            {
                count++;
            }
        }
    }

    return count;
}

int userinput(int *grid, int size)
{
    int upperborder, col, speedcontrol;
    bool con = true;

    while (con)
    {
        printf("\nInput Simulation Speed: 1 for FAST, 2 for MODERATE, 3 for SLOW \nINPUT HERE: ");
        scanf(" %d", &speedcontrol);

        if (speedcontrol > 0 && speedcontrol < 4)
        {
            con = false;
        }
    }
    
    if (speedcontrol == 1)
    {
        return 200;
    }
    else if (speedcontrol == 2)
    {
        return 1000;
    }
    else if (speedcontrol == 3)
    {
        return 3000;
    }
}

void copygrid(int *grid1, int *grid2, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            *(grid1 + i * size + j) = *(grid2 + i * size + j);
        }
    }
}

void simulationrule(int *grid, int size, bool *changes)
{
    int virussim[size][size];
    int *matrixptr = &virussim[0][0];
    copygrid(matrixptr, grid, size);

    for (int i = 0; i < size; i++)
    {
        for (int o = 0; o < size ; o++)
        {
            if (*(grid + i * size + o) == 1)
            {
                int neighborcount = checkneighborscount(matrixptr, i, o, size);
                if (neighborcount < 2 || neighborcount > 3)
                {
                    *(matrixptr + i * size + o) = 2;
                    *changes = true;
                }
                else if (neighborcount > 1 && neighborcount < 4)
                {
                    *(matrixptr + i * size + o) = 1;
                }
            }
            else if (*(grid + i * size + o) == 2)
            {
                int neighborcount = checkneighborscount(matrixptr, i, o, size);
                if (neighborcount == 3)
                {
                    *(matrixptr + i * size + o) = 1;
                    *changes = true;
                }
            }
        }
    }
    copygrid(grid, matrixptr, size);
}

void takechardisplay(char *charptr)
{
    int choice;
    bool correct = true;

    printf("\n            |Defualt|Custom|");
    printf("\nLive Cell   |   O   |   ?  |");
    printf("\nDead Cell   |   .   |   ?  |");
    while (correct)
    {
        printf("\n\nCHANGING ICON....\n\n1 for default, 2 for Custom.\nInput Here: ");
        scanf(" %d", &choice);
        
        if (choice > 0 && choice < 3)
        {
            correct = false;
        }
        else 
        {
            printf("\nInvalide Input!.");
        }
    }
    
    if (choice == 1)
    {
        *charptr = 'O';
        *(charptr + 1) = '.';
    }
    else if (choice == 2)
    {
        char input;
        printf("Input Character for Live Cell: ");
        scanf(" %c", &input);
        *charptr = input;
        
        
        printf("Input Character for Dead Cell: ");
        scanf(" %c", &input);
        *(charptr + 1) = input;
    }
}

void commencing(char *charptr)
{
    printf("\n\n\nLive Cell = %c\nDead Cell = %c\n\n\n", *charptr, *(charptr + 1));
    printf("Simulation Starting in...");

    for (int i = 1; i < 6; i++)
    {
        Sleep(1000);
        printf("\n%d!", 6 - i);
    }
    system("cls");
}

void inputval(int *grid, int size, char *charptr)
{
    int inputchoice;
    bool con = true;
    printf("\nINPUTING VALUES....\n\n");
    printf("Default = All grid cells are randomly generated.\n");
    printf("Custom  = Requires user to input values in the grid.\n");

    while (con)
    {
        printf("\n1 for Default, 2 for Custom.\nInput Here: ");
        scanf(" %d", &inputchoice);
        if (inputchoice > 0 && inputchoice < 3) 
        {
            con = false;
        } 
        else
        {
            printf("Invalid Input");
        }
    }

    if (inputchoice == 1)
    {
        inputvalues(grid, size);
    }

    if (inputchoice == 2)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
               *(grid + i * size + j) = 2;
            }
        }

        int cells, row, col;
        bool proceed = true;
        printf("\nHow many live cells you wanna place (LIMIT: %d): ", size * size);
        scanf(" %d", &cells);

        int p = 1;
        printf("\nInput Row and Column for each cell. (Ex. Row: 12 Col: 12 (Input: 12 12))\n");
        while (proceed)
        {
            printf("\nInput Row and Column for #%d cell from (1 - %d): ", p , size);
            scanf(" %d %d", &row, &col);

            if ((row > 0 && row < size) && (col > 0 && col < size))
            {
                if (*(grid + (row - 1) * size + (col - 1)) == 2)
                {
                    *(grid + (row - 1) * size + (col - 1)) = 1;
                    system("cls");
                    displaygridcells(grid, size, charptr);
                    proceed = true;
                    p++;
                }
                else
                {
                    printf("\nThe grid cell is already occupied with a live cell!");
                }
            }
            else 
            {
                printf("\nInvalid Input. Try Again.");
            }

            if (p == cells + 1)
            {
                proceed = false;
            }
            
        }
    }
}