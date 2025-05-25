#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h> 

// Structure to hold student information
struct info
{
    char name[100];
    int age;
    int id;
    float grade[3];
};

// Functions
void add(); // Adds new student information
void delete(); // Deletes students informatio
bool check(char name[100]); // Check if a name already exists
void search(); // Search fstudents information
void edit(); // Edits student information
void list(); // Show list of all student name
void initializing(); // Checks or Create file
float average(float *flptr); // Calculates average of 3 grades

int main()
{
    int choice;
    bool run = true;

    printf("Initializing...\n");
    initializing(); // Initialize the data file
    sleep(2); // Pause for a second
    system("cls");

    while(run)
    {   
        printf("\n--- Student Management System ---\n");
        printf("[1] List All Students\n");
        printf("[2] Add New Student\n");
        printf("[3] Delete Student\n");
        printf("[4] Edit Student Information\n");
        printf("[5] Search Student\n");
        printf("[6] Exit\n");
        printf("Enter your choice: ");
        scanf(" %d", &choice); // Read user's choice
        getchar(); // Remove the newline character left by scanf

        // Validate user input
        if (choice <= 0 || choice >= 7)
        {
            printf("Invalid Action! Please enter a number between 1 and 6.\n");
        }
        else
        {
            system("cls");
            // Perform action based on user's choice
            if (choice == 1)
            {
                list();
                printf("\nReturning...");
                sleep(3);
                system("cls");
            }
            else if (choice == 2)
            {
                add();
                printf("\nReturning...");
                sleep(3);
                system("cls");
            }
            else if (choice == 3)
            {
                delete();
                printf("\nReturning...");
                sleep(3);
                system("cls");
            }
            else if (choice == 4)
            {
                edit();
                printf("\nReturning...");
                sleep(3);
                system("cls");
            }
            else if (choice == 5)
            {
                search();
                printf("\nReturning...");
                sleep(3);
                system("cls");
            }
            else if (choice == 6)
            {
                run = false; // Exit the loop
                printf("Exiting program. Goodbye!\n");
            }
        }
    }

    return 0;
}

// Function to list all student records
void list()
{
    char line[200]; // Buffer 
    char returninput[100];
    FILE *fptr = fopen("myname.txt", "r"); // Open file in read mode

    if (!fptr) // Check if file was opened successfully
    {
        printf("Error: Could not open 'myname.txt' for reading.\n");
        return;
    }

    printf("\n--- All Student Records ---\n");
    bool checkfound = false; 

    while(fgets(line, sizeof(line), fptr) != NULL)
    {
        checkfound = true;
        printf("%s", line);
    }
    fclose(fptr); // Close the file

    if (!checkfound) {
        printf("No records found.\n");

    }
    else // Wait for user input to return
    {
        printf("Press any key then enter to return.");
        scanf(" %s", &returninput);
    }
    printf("---------------------------\n");
}

// Function to initialize or create the data file
void initializing()
{
    // Open file in append mode
    FILE *file = fopen("myname.txt", "a"); 

    if (file != NULL) // Check if file was successfully opened/created
    {
        printf("File 'myname.txt' opened successfully or created!\n");
        fclose(file);
    }
    else
    {
        printf("Error: Could not open or create 'myname.txt'. Check file permissions.\n");
    }
}

// Function to calculate the average of three grades
float average(float *flptr)
{
    float avg = 0;
    for (int i = 0; i < 3; i++)
    {
        avg += flptr[i]; 
    }
    return avg / 3.00;
}

// Function to edit student record
void edit()
{
    char editinfo[100], line[200]; // Buffers for name to edit and file lines
    bool found = false; 
    struct info student;

    printf("\nEnter Complete Name Of Student To Edit: ");
    fgets(editinfo, 100, stdin); // Read the linr for the name
    editinfo[strcspn(editinfo, "\n")] = 0; // Remove newline from input name

    FILE *original = fopen("myname.txt", "r"); // original file for reading
    FILE *temp = fopen("temp.txt", "w"); // temporary file for writing

    // Check if both file succesfully opened
    if (!original)
    {
        printf("Error: Could not open 'myname.txt' for reading.\n");
        return;
    }
    if (!temp)
    {
        printf("Error: Could not open 'temp.txt' for writing.\n");
        fclose(original); // Close original file if temp fails
        return;
    }

    bool target = false; 

    // Read the original file line by line
    while (fgets(line, sizeof(line), original) != NULL)
    {
        // Check if the current line starts as a block
        if (strstr(line, "Name: ") == line) // Check to see if the line was the students name
        {
            char storedName[100];
            // Extract the name without "Name: "
            sscanf(line, "Name: %[^\n]", storedName);

            // Check if both names are correct
            if (strcmp(storedName, editinfo) == 0)
            {
                found = true;
                target = true;
                printf("\n--- Editing record for %s ---\n", editinfo);

                // Ask user for the new student information
                printf("Enter new name: ");
                fgets(student.name, 100, stdin);
                student.name[strcspn(student.name, "\n")] = 0; // Remove newline

                printf("Enter new age: ");
                scanf(" %d", &student.age);
                getchar(); // Remove newline

                printf("Enter new ID number: ");
                scanf(" %d", &student.id);
                getchar(); // Remove newline

                for (int i = 0; i < 3; i++)
                {
                    printf("Enter Subject #%d Grade: ", i + 1);
                    scanf(" %f", &student.grade[i]);
                }
                getchar(); // Remove newline

                // Write the new student's data in the temporary file
                fprintf(temp, "Name: %s\n", student.name);
                fprintf(temp, "ID: %d\n", student.id);
                fprintf(temp, "Age: %d\n", student.age);
                for (int i = 0; i < 3; i++)
                {
                    fprintf(temp, "Subject #%d Grade: %.2f\n", i + 1, student.grade[i]);
                }
                fprintf(temp, "Average Grade: %.2f\n\n", average(student.grade));
            }
            else
            {
                target = false; 
                fputs(line, temp); // Write the "Name:" in line variable
            }
        }
        else if (!target) // If its not in the target record, just copy the line
        {
            fputs(line, temp);
        }
    }

    fclose(original); // Close both files
    fclose(temp);

    if (found) // If the student was found and edited
    {
        remove("myname.txt"); // Delete the original file
        rename("temp.txt", "myname.txt"); // Rename the temporary file to the original name
        printf("Entry edited successfully!\n");
    }
    else // If the student was not found
    {
        remove("temp.txt"); // Delete the temporary file as it's not needed
        printf("Name not found!\n");
    }
}

// Function to delete a student record
void delete()
{
    char infodelete[100], line[200];
    bool found = false;

    printf("\nEnter Complete Name Of Student To Delete: ");
    fgets(infodelete, 100, stdin);
    infodelete[strcspn(infodelete, "\n")] = 0; // Remove newline

    FILE *original = fopen("myname.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!original)
    {
        printf("Error: Could not open 'myname.txt' for reading.\n");
        return;
    }
    if (!temp)
    {
        printf("Error: Could not open 'temp.txt' for writing.\n");
        fclose(original);
        return;
    }

    bool target = false; 

    while (fgets(line, sizeof(line), original) != NULL)
    {
        if (strstr(line, "Name: ") == line) // Check if this line starts a new record
        {
            char storedName[100];
            sscanf(line, "Name: %[^\n]", storedName);

            if (strcmp(storedName, infodelete) == 0)
            {
                found = true;
                target = true; 
                continue; // Skip writing the "Name:" line of the target record
            }
            else
            {
                target = false; 
                fputs(line, temp);
            }
        }
        else if (!target) 
        {
            // If we are not in the target record, just copy the line
            fputs(line, temp);
        }
        // If target is true, skip writing
    }

    fclose(original);
    fclose(temp);

    if (found)
    {
        remove("myname.txt"); // Delete the original file
        rename("temp.txt", "myname.txt"); // Rename the temporary file to the original name
        printf("Entry deleted successfully!\n");
    }
    else
    {
        remove("temp.txt"); // Delete temporary file if no match was found
        printf("Name not found!\n");
    }
}

// Function to check if a student name already exists in the file
bool check(char name[100])
{
    char relay[200]; // Buffer 
    bool exists = false; 
    FILE *ptr = fopen("myname.txt", "r"); // Open file in read mode

    // Loop through the file until end or name is found
    while (fgets(relay, sizeof(relay), ptr) != NULL && !exists)
    {
        if (strstr(relay, "Name: ") == relay) // Check if line starts with "Name: "
        {
            char storedName[100];
            sscanf(relay, "Name: %[^\n]", storedName); // Extract name

            if (strcmp(storedName, name) == 0) // Compare with the name being checked
            {
                exists = true; // Name found
            }
        }
    }

    fclose(ptr); // Close the file
    return exists;
}

// Function to add a new student record
void add()
{
    int age, id;
    float grade[3], avg;
    char name[100];

    printf("Enter student's name: ");
    fgets(name, 100, stdin); // Read name
    name[strcspn(name, "\n")] = 0; // Remove newline from name

    if (check(name)) // Check if name already exists
    {
        printf("Name already exists. Entry not added.\n");
    }
    else
    {
        printf("Enter student's age: ");
        scanf("%d", &age);
        getchar(); // Consume newline after scanf

        printf("Enter student's ID: ");
        scanf("%d", &id);
        getchar(); // Consume newline after scanf

        for (int i = 0; i < 3; i++)
        {
            printf("Enter Subject #%d Grade: ", i + 1);
            scanf(" %f", &grade[i]);
        }
        getchar(); // Consume newline after the last scanf for grades

        FILE *ptr = fopen("myname.txt", "a"); // Open file in append mode
        if (!ptr) // Check if file opened successfully
        {
            printf("Error opening file for adding!\n");
            return;
        }

        // Write student data to file
        fprintf(ptr, "Name: %s\n", name);
        fprintf(ptr, "ID: %d\n", id);
        fprintf(ptr, "Age: %d\n", age);

        for (int i = 0; i < 3; i++)
        {
            fprintf(ptr, "Subject #%d Grade: %.2f\n", i + 1, grade[i]);
        }
        avg = average(grade); // Calculate average grade
        fprintf(ptr, "Average Grade: %.2f\n\n", avg);

        fclose(ptr); // Close the file
        printf("\nEntry added successfully!\n");
    }
}

// Function to search for a student record by name
void search()
{
    char nameToSearch[100], line[200];
    bool found = false;
    FILE *ptr = fopen("myname.txt", "r"); // Open file in read mode

    if (!ptr) // Check if file opened successfully
    {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Name of Student to Search: ");
    fgets(nameToSearch, 100, stdin);
    nameToSearch[strcspn(nameToSearch, "\n")] = 0;

    bool target = false;
    char returninput[100];

    while (fgets(line, sizeof(line), ptr) != NULL) // Read file line by line
    {
        if (strstr(line, "Name: ") == line) // Check line break
        {
            char storedName[100];
            sscanf(line, "Name: %[^\n]", storedName); // Extract name from line

            if (strcmp(storedName, nameToSearch) == 0) // If names match proceed with the code block
            {
                found = true;
                target = true; // Start printing this record
                printf("\n--- Found Record for %s ---\n", nameToSearch);
                printf("%s", line);
            }
            else
            {
                target = false; 
            }
        }
        else if (target) 
        {
            printf("%s", line);
            // Check for an empty line
            if (strlen(line) <= 1 && line[0] == '\n') {
                target = false; // End of current record block
            }
        }
    }

    fclose(ptr); // Close the file

    if (!found) // If student not found
    {
        printf("Name not found!\n");
    }
    else
    {
        printf("Press any key then enter to return.");
        scanf(" %s", &returninput);
    }
}