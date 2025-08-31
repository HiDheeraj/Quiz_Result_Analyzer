#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100

struct Student {
    int rollNo;
    char name[50];
    int score;
    char result[10];
};

// Function to swap two students
void swap(struct Student *a, struct Student *b) {
    struct Student temp = *a;
    *a = *b;
    *b = temp;
}

// Sort by Roll Number (ascending)
void sortByRollNo(struct Student students[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (students[j].rollNo > students[j + 1].rollNo) {
                swap(&students[j], &students[j + 1]);
            }
        }
    }
}

// Sort by Score (descending)
void sortByScore(struct Student students[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (students[j].score < students[j + 1].score) {
                swap(&students[j], &students[j + 1]);
            }
        }
    }
}

int main() {
    struct Student students[MAX_STUDENTS];
    int n, i, j, choice;
    int totalPassed = 0, totalFailed = 0;
    float sum = 0.0; // Use 0.0 for float
    int highest = -1, lowest = 101;

    printf("=========== QUIZ RESULT ANALYZER ===========\n");

    // Input number of students
    do {
        printf("\nEnter number of students (max 100): ");
        scanf("%d", &n);
        while (getchar() != '\n'); // Clear input buffer
        if (n <= 0 || n > MAX_STUDENTS) {
            printf("Invalid number! Please enter between 1 and %d.\n", MAX_STUDENTS);
        }
    } while (n <= 0 || n > MAX_STUDENTS);

    // Input student details
    for (i = 0; i < n; i++) {
        printf("\nEnter details for student %d\n", i + 1);

        // Roll number validation + check duplicates
        int validRoll;
        do {
            validRoll = 1;
            printf("Roll Number: ");
            scanf("%d", &students[i].rollNo);
            while (getchar() != '\n'); // Clear input buffer

            if (students[i].rollNo <= 0) {
                printf("Invalid Roll Number! Must be positive.\n");
                validRoll = 0;
                continue;
            }

            // Check duplicate
            for (j = 0; j < i; j++) {
                if (students[i].rollNo == students[j].rollNo) {
                    printf("Duplicate Roll Number! Enter a unique one.\n");
                    validRoll = 0;
                    break;
                }
            }
        } while (!validRoll);

        // Name input
        printf("Name: ");
        // scanf("%s", students[i].name);
        fgets(students[i].name, sizeof(students[i].name), stdin);
        students[i].name[strcspn(students[i].name, "\n")] = '\0'; // Remove trailing newline

        // Score validation
        do {
            printf("Score (0-100): ");
            scanf("%d", &students[i].score);
            while (getchar() != '\n'); // Clear input buffer
            if (students[i].score < 0 || students[i].score > 100) {
                printf("Invalid Score! Must be between 0 and 100.\n");
            }
        } while (students[i].score < 0 || students[i].score > 100);

        // Pass/Fail
        if (students[i].score >= 40) {
            strcpy(students[i].result, "PASS");
            totalPassed++;
        } else {
            strcpy(students[i].result, "FAIL");
            totalFailed++;
        }

        // Update highest/lowest
        if (students[i].score > highest) highest = students[i].score;
        if (students[i].score < lowest) lowest = students[i].score;

        // Corrected for precision
        sum += (float)students[i].score;
    }

    // Results summary
    printf("\n=========== QUIZ ANALYSIS RESULT ===========\n");
    printf("Total Students: %d\n", n);
    // Corrected for precision
    printf("Class Average: %.2f\n", sum / n);
    printf("Highest Score: %d\n", highest);
    printf("Lowest Score: %d\n", lowest);
    printf("Passed Students: %d\n", totalPassed);
    printf("Failed Students: %d\n", totalFailed);

    // Ask user how to sort
    printf("\nHow would you like to see the report?\n");
    printf("1. Sort by Roll Number \n");
    printf("2. Sort by Score \n");
    printf("Enter choice (1 or 2): ");
    scanf("%d", &choice);
    while (getchar() != '\n'); // Clear input buffer

    if (choice == 1) {
        sortByRollNo(students, n);
        printf("\nReport sorted by Roll Number :\n");
    } else if (choice == 2) {
        sortByScore(students, n);
        printf("\nReport sorted by Score :\n");
    } else {
        printf("\nInvalid choice! Showing unsorted report.\n");
    }

    // Detailed Report
    printf("\n----------- Detailed Report -----------\n");
    printf("RollNo\tName\t\tScore\tResult\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%-10s\t%d\t%s\n", students[i].rollNo, students[i].name, students[i].score, students[i].result);
    }

    return 0;
}
