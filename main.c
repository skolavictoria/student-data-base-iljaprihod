#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100
#define FILENAME "database.txt"

// Student Structure
struct Student {
    char name[50];
    char surname[50];
    char group[10];
    char course[10];
    int id;
    char additionalInfo[100];
};

// Function prototypes
void writeDatabaseToFile(struct Student database[], int numStudents);
void readDatabaseFromFile(struct Student database[], int* numStudents);
void addStudent(struct Student database[], int* numStudents);
void removeStudent(struct Student database[], int* numStudents, int studentId);
void editStudent(struct Student database[], int numStudents, int studentId);
void searchStudents(struct Student database[], int numStudents, const char* query);

int main() {
    struct Student studentDatabase[MAX_STUDENTS];
    int numStudents = 0;
    int choice;
    
    // Load data from file when the program starts
    readDatabaseFromFile(studentDatabase, &numStudents);

    do {
        printf("\nStudent Database Management System\n");
        printf("1. Add Student\n");
        printf("2. Remove Student\n");
        printf("3. Edit Student\n");
        printf("4. Search Students\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(studentDatabase, &numStudents);
                break;
            case 2: {
                int studentId;
                printf("Enter the ID of the student to remove: ");
                scanf("%d", &studentId);
                removeStudent(studentDatabase, &numStudents, studentId);
                break;
            }
            case 3: {
                int studentId;
                printf("Enter the ID of the student to edit: ");
                scanf("%d", &studentId);
                editStudent(studentDatabase, numStudents, studentId);
                break;
            }
            case 4: {
                char searchQuery[50];
                printf("Enter search query: ");
                scanf("%s", searchQuery);
                searchStudents(studentDatabase, numStudents, searchQuery);
                break;
            }
            case 5:
                // Save data to file before exiting the program
                writeDatabaseToFile(studentDatabase, numStudents);
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    } while (choice != 5);

    return 0;
}

// write the  database to 
void writeDatabaseToFile(struct Student database[], int numStudents) {
    FILE* file = fopen(FILENAME, "w");

    if (file != NULL) {
        for (int i = 0; i < numStudents; i++) {
            fprintf(file, "%s,%s,%s,%s,%d,%s\n",
                    database[i].name,
                    database[i].surname,
                    database[i].group,
                    database[i].course,
                    database[i].id,
                    database[i].additionalInfo);
        }

        fclose(file);
        printf("Data written to %s successfully.\n", FILENAME);
    } else {
        printf("Error: Unable to open %s for writing.\n", FILENAME);
    }
}

// Fuck the police undeground database 
void readDatabaseFromFile(struct Student database[], int* numStudents) {
    FILE* file = fopen(FILENAME, "r");

    if (file != NULL) {
        while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%d,%[^\n]\n",
                      database[*numStudents].name,
                      database[*numStudents].surname,
                      database[*numStudents].group,
                      database[*numStudents].course,
                      &database[*numStudents].id,
                      database[*numStudents].additionalInfo) == 6) {
            (*numStudents)++;
        }

        fclose(file);
        printf("Data read from %s successfully.\n", FILENAME);
    } else {
        printf("Creating a new %s since it doesn't exist.\n", FILENAME);
    }
}

// add 
void addStudent(struct Student database[], int* numStudents) {
    if (*numStudents < MAX_STUDENTS) {
        printf("\nEnter details for the new student:\n");
        printf("Name: ");
        scanf("%s", database[*numStudents].name);
        printf("Surname: ");
        scanf("%s", database[*numStudents].surname);
        printf("Group: ");
        scanf("%s", database[*numStudents].group);
        printf("Course: ");
        scanf("%s", database[*numStudents].course);
        printf("ID: ");
        scanf("%d", &database[*numStudents].id);
        printf("Additional Info: ");
        scanf("%s", database[*numStudents].additionalInfo);

        (*numStudents)++;
        printf("Student added successfully.\n");

        // Save data to file after adding a new student
        writeDatabaseToFile(database, *numStudents);
    } else {
        printf("Error: Database is full. Cannot add more students.\n");
    }
}

// vikinutj studenta cerez id
void removeStudent(struct Student database[], int* numStudents, int studentId) {
    int foundIndex = -1;

    for (int i = 0; i < *numStudents; i++) {
        if (database[i].id == studentId) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        for (int i = foundIndex; i < *numStudents - 1; i++) {
            database[i] = database[i + 1];
        }

        (*numStudents)--;
        printf("Student with ID %d removed successfully.\n", studentId);

        // Save that etot student visvernut
        writeDatabaseToFile(database, *numStudents);
    } else {
        printf("Error: Student with ID %d not found.\n", studentId);
    }
}

// cerez ID izmenitj studenta
void editStudent(struct Student database[], int numStudents, int studentId) {
    int foundIndex = -1;

    for (int i = 0; i < numStudents; i++) {
        if (database[i].id == studentId) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        printf("Enter new details for the student with ID %d:\n", studentId);
        printf("Name: ");
        scanf("%s", database[foundIndex].name);
        printf("Surname: ");
        scanf("%s", database[foundIndex].surname);
        printf("Group: ");
        scanf("%s", database[foundIndex].group);
        printf("Course: ");
        scanf("%s", database[foundIndex].course);
        printf("ID: ");
        scanf("%d", &database[foundIndex].id);
        printf("Additional Info: ");
        scanf("%s", database[foundIndex].additionalInfo);

        printf("Student edited successfully.\n");

        // Save data 
        writeDatabaseToFile(database, numStudents);
    } else {
        printf("Error: Student with ID %d not found.\n", studentId);
    }
}

// naiti etogo uslepka
void searchStudents(struct Student database[], int numStudents, const char* query) {
    printf("\nSearch Results:\n");

    for (int i = 0; i < numStudents; i++) {
        if (strstr(database[i].name, query) != NULL ||
            strstr(database[i].surname, query) != NULL ||
            strstr(database[i].group, query) != NULL ||
            strstr(database[i].course, query) != NULL ||
            database[i].id == atoi(query)) {
            printf("Name: %s\n", database[i].name);
            printf("Surname: %s\n", database[i].surname);
            printf("Group: %s\n", database[i].group);
            printf("Course: %s\n", database[i].course);
            printf("ID: %d\n", database[i].id);
            printf("Additional Info: %s\n", database[i].additionalInfo);
            printf("--------------------\n");
        }
    }
}