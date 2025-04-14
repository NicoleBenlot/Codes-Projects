#include <stdio.h>

#define GRADE 5

struct studentinfo 
{
    char name[20];
    int id = 0;
    int grades[GRADE];
}

void newinfo (struct studentinfo *structptr);

int main()
{
    struct studentinfo studentsdata [25];
    int *structptr = studentsdata;
    FILE *file = NULL;

    file = fopen("myname.txt", "w");
    fprintf(file,"Name: %s", name);
}

void newinfo (struct studentinfo *structptr)
{
    printf("Enter Students Name: ");
    fgets(*structptr->name, 20, stdin);

    printf("Enter Students Id Number: ");
    fgets(*structptr->id, sizeof(int), stdin);

    for (int i = 0; i < GRADE; i++)
    {
        printf("Enter the Grade of Subject #%d", i);
        fgets(*structptr->grades[i], sizeof(int), stdin);
    }
}