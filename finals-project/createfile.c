#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void takeinput(FILE *ptr)
{
    int age;
    char name[100];

    printf("Enter your name: ");
    fgets(name, 100, stdin);
    printf("Enter your age: ");
    scanf("%d", &age);
    getchar();

    fprintf(ptr, "Name: %s", name);
    fprintf(ptr, "Age: %d\n", age);
}

void search(FILE *ptr)
{
    char name[100], relay[100];
    bool found = false;
    
    printf("Enter Name to Search: ");
    fgets(name, 100, stdin);

    while (fgets(relay, 100, ptr) != NULL)
    {
        if (strstr(relay, "Name:") != NULL && strstr(relay, name) != NULL && !found)
        {
            printf("%s", relay);
            if (fgets(relay, 100, ptr) != NULL)
            {
                printf("%s", relay);
                found = true;
            }
        }
    }

}

int main()
{
    FILE *fptr = fopen("myname.txt", "a");

    takeinput(fptr);
    fclose(fptr);

    fptr = fopen("myname.txt", "r");

    search(fptr);
    fclose(fptr);

    printf("\nCode executed.\n");
    return 0;
}