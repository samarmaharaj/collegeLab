#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 100
#define MAX_BRANCH_LEN 100

typedef struct {
    char name[MAX_NAME_LEN];
    int roll;
    float CGPI;
    int semesters;
    char branch[MAX_BRANCH_LEN];
} Student;

void getDetails(Student *student) {
    printf("Enter name: ");
    // Use fgets to read the whole line including spaces
    fgets(student->name, MAX_NAME_LEN, stdin);
    student->name[strcspn(student->name, "\n")] = '\0'; // Remove the newline character if present

    printf("Enter roll: ");
    scanf("%d", &student->roll);
    printf("Enter CGPI: ");
    scanf("%f", &student->CGPI);
    printf("Enter semesters: ");
    scanf("%d", &student->semesters);
    printf("Enter branch: ");
    scanf("%s", student->branch);
    getchar(); // To consume the newline character left by scanf
}

void displayDetails(const Student *student) {
    printf("Name: %s\n", student->name);
    printf("Roll: %d\n", student->roll);
    printf("CGPI: %.2f\n", student->CGPI);
    printf("Semesters: %d\n", student->semesters);
    printf("Branch: %s\n", student->branch);
}

void CGPIFilter(const Student *student, float k) {
    if (student->CGPI > k) {
        printf("Name: %s\n", student->name);
        printf("Roll: %d\n", student->roll);
        printf("CGPI: %.2f\n", student->CGPI);
        printf("Semesters: %d\n", student->semesters);
        printf("Branch: %s\n", student->branch);
    }
}

void insertRecord(Student *student) {
    printf("Enter name: ");
    // Use fgets to read the whole line including spaces
    fgets(student->name, MAX_NAME_LEN, stdin);
    student->name[strcspn(student->name, "\n")] = '\0'; // Remove the newline character if present

    printf("Enter roll: ");
    scanf("%d", &student->roll);
    printf("Enter CGPI: ");
    scanf("%f", &student->CGPI);
    printf("Enter semesters: ");
    scanf("%d", &student->semesters);
    printf("Enter branch: ");
    scanf("%s", student->branch);
    getchar(); // To consume the newline character left by scanf

    printf("Record inserted successfully!\n");
}

int main() {
    printf("Welcome to Student Management System\n");
    int choice = 1;
    int n = 0;
    Student *students = NULL;

    while (1) {
        printf("\nChoose from the following options:\n");
        printf("1. Get details of student\n");
        printf("2. Display record of all students\n");
        printf("3. Insert record\n");
        printf("4. CGPI Filter record\n");
        printf("5. Enter to exit.\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // To consume the newline character left by scanf

        if (choice == 1) {
            printf("Enter number of students: ");
            scanf("%d", &n);
            getchar(); // To consume the newline character left by scanf
            free(students); // Clean up previously allocated memory
            students = (Student *)malloc(n * sizeof(Student));
            for (int i = 0; i < n; i++) {
                printf("\n\nEnter details of student %d\n", i + 1);
                getDetails(&students[i]);
            }
        } else if (choice == 2) {
            for (int i = 0; i < n; i++) {
                printf("\n\nDetails of student %d\n", i + 1);
                displayDetails(&students[i]);
            }
        } else if (choice == 3) {
            int k;
            printf("Enter the position at which you want to add a record: ");
            scanf("%d", &k);
            getchar(); // To consume the newline character left by scanf
            if (k < 1 || k > n + 1) {
                printf("Invalid position!\n");
                continue;
            }
            Student *new_students = (Student *)malloc((n + 1) * sizeof(Student));
            for (int i = 0, j = 0; i < n + 1; i++) {
                if (i == k - 1) {
                    printf("Enter details for the new student:\n");
                    getDetails(&new_students[i]);
                } else {
                    new_students[i] = students[j++];
                }
            }
            free(students);
            students = new_students;
            n++;
        } else if (choice == 4) {
            float k;
            printf("Enter CGPI filter: ");
            scanf("%f", &k);
            for (int i = 0; i < n; i++) {
                CGPIFilter(&students[i], k);
            }
        } else {
            break;
        }
    }

    free(students); // Clean up allocated memory
    return 0;
}
