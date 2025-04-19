#include <stdio.h>
#include <stdlib.h>

#define GRADE 5

struct studentinfo 
{
    char name[20];
    int id;
    int grades[GRADE];
}

void newinfo (struct studentinfo studentsdate, FILE *file);

void avg()

int main()
{
    struct studentinfo studentsdata [25];
    FILE *file = NULL;

    newinfo(studentsdate, *file);
}

void newinfo (struct studentinfo studentsdate, FILE *file)
{
    file = fopen("studentsinfo.txt", "w");
    printf("Enter Students Name: ");
    scanf("%s", &studentsdate->name);
    fprintf(file, "Name: %s",*studentsdate->name);

    printf("Enter Students Id Number: ");
    scanf("%d", &studentsdate->id);
    fprintf(file, "ID: %s",*studentsdate->id);

    for (int i = 0; i < GRADE; i++)
    {
        printf("Enter the Grade of Subject #%d", i);
        scanf("%d", &studentsdate->grade[i]);
        fprintf(file, "Subject #%d: %s",*studentsdate->grade[i], i);
    }
}
