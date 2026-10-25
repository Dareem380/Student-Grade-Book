#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 200
#define MAX_NAME 50
#define MAX_STUDENTS 60
#define MAX_SUBJECTS 5
#define MAX_SEMESTERS 8

struct semester_record {
    int subjects[MAX_SUBJECTS];
    int subject_count;
    int total;
    float average;
    char grade[5];
    char status[10];
};

struct student {
    int id;
    char name[MAX_NAME];
    struct semester_record semesters[MAX_SEMESTERS];
    int semester_count;
    float overall_average;
    char overall_grade[5];
};

// Global variables
struct student students[MAX_STUDENTS];
int student_count = 0;

// Function prototypes
void mainMenu();
void studentManagementMenu();
void reportsMenu();
void analyticsMenu();
void searchMenu();
void helpMenu();
void displayHelp(const char *menuType);
void loadStudentData();
void addStudent();
void viewAllStudents();
void viewStudentDetails();
void searchByRollNo();
void viewStudentProgress();
void generateFullReport();
void generateTopperReport();
void generateFailureReport();
void showTopRankers();
void showAveragePerformers();
void showFailedStudents();
void showClassStatistics();
void showSemesterWiseAnalysis();
void calculateGrade(float avg, char *grade);
void calculateStatus(float avg, char *status);
void addSemesterData();
void updateStudentInfo();
void clearScreen();
void pressEnterToContinue();
int getValidChoice(int min, int max);

// Main function
int main() {
    loadStudentData();
    mainMenu();
    return 0;
}

// Clear screen function
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Press enter to continue
void pressEnterToContinue() {
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}

// Get valid choice from user
int getValidChoice(int min, int max) {
    int choice;
    while (1) {
        printf("Enter your choice: ");
        if (scanf("%d", &choice) == 1 && choice >= min && choice <= max) {
            return choice;
        }
        printf("Invalid choice! Please enter a number between %d and %d.\n", min, max);
        while (getchar() != '\n');
    }
}

// Calculate grade based on average
void calculateGrade(float avg, char *grade) {
    if (avg >= 91) strcpy(grade, "S");
    else if (avg >= 75) strcpy(grade, "A");
    else if (avg >= 50) strcpy(grade, "B");
    else if (avg >= 40) strcpy(grade, "C");
    else if (avg >= 35) strcpy(grade, "D");
    else strcpy(grade, "F");
}

// Calculate status (PASS/FAIL)
void calculateStatus(float avg, char *status) {
    if (avg >= 35) strcpy(status, "PASS");
    else strcpy(status, "FAIL");
}

// Load student data from file
void loadStudentData() {
    FILE *fp = fopen("grades.txt", "r");
    if (fp == NULL) {
        printf("Note: grades.txt not found. Starting with empty database.\n");
        return;
    }

    char line[MAX_LINE];
    student_count = 0;

    while (fgets(line, sizeof(line), fp) && student_count < MAX_STUDENTS) {
        int id, s1, s2, s3;
        char name[MAX_NAME];

        if (sscanf(line, "%d %s %d %d %d", &id, name, &s1, &s2, &s3) == 5) {
            students[student_count].id = id;
            strcpy(students[student_count].name, name);
            students[student_count].semester_count = 1;

            // Store first semester data
            students[student_count].semesters[0].subjects[0] = s1;
            students[student_count].semesters[0].subjects[1] = s2;
            students[student_count].semesters[0].subjects[2] = s3;
            students[student_count].semesters[0].subject_count = 3;
            students[student_count].semesters[0].total = s1 + s2 + s3;
            students[student_count].semesters[0].average = students[student_count].semesters[0].total / 3.0;

            calculateGrade(students[student_count].semesters[0].average, students[student_count].semesters[0].grade);
            calculateStatus(students[student_count].semesters[0].average, students[student_count].semesters[0].status);

            students[student_count].overall_average = students[student_count].semesters[0].average;
            strcpy(students[student_count].overall_grade, students[student_count].semesters[0].grade);

            student_count++;
        }
    }
    fclose(fp);
    printf("Loaded %d students successfully.\n", student_count);
}

// Main Menu
void mainMenu() {
    int choice;
    while (1) {
        clearScreen();
        printf("\n==================================================\n");
        printf("     STUDENT GRADE BOOK MANAGEMENT SYSTEM      \n");
        printf("==================================================\n\n");
        printf("  1. Student Management\n");
        printf("  2. Reports Generation\n");
        printf("  3. Analytics & Statistics\n");
        printf("  4. Search & Query\n");
        printf("  5. Help\n");
        printf("  0. Exit\n");
        printf("\n==================================================\n");

        choice = getValidChoice(0, 5);

        switch (choice) {
            case 1: studentManagementMenu(); break;
            case 2: reportsMenu(); break;
            case 3: analyticsMenu(); break;
            case 4: searchMenu(); break;
            case 5: helpMenu(); break;
            case 0:
                printf("\nThank you for using Student Grade Book System!\n");
                printf("Exiting...\n");
                exit(0);
        }
    }
}

// Student Management Menu
void studentManagementMenu() {
    int choice;
    while (1) {
        clearScreen();
        printf("\n==================================================\n");
        printf("          STUDENT MANAGEMENT MENU              \n");
        printf("==================================================\n\n");
        printf("  1. Add New Student\n");
        printf("  2. View All Students\n");
        printf("  3. View Student Details\n");
        printf("  4. Add Semester Data for Existing Student\n");
        printf("  5. Update Student Information\n");
        printf("  9. Help\n");
        printf("  0. Back to Main Menu\n");
        printf("\n==================================================\n");

        choice = getValidChoice(0, 9);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewAllStudents(); break;
            case 3: viewStudentDetails(); break;
            case 4: addSemesterData(); break;
            case 5: updateStudentInfo(); break;
            case 9: displayHelp("Student Management"); pressEnterToContinue(); break;
            case 0: return;
        }
    }
}

// Reports Menu
void reportsMenu() {
    int choice;
    while (1) {
        clearScreen();
        printf("\n==================================================\n");
        printf("             REPORTS GENERATION MENU           \n");
        printf("==================================================\n\n");
        printf("  1. Generate Complete Student Report\n");
        printf("  2. Generate Topper Report\n");
        printf("  3. Generate Failure Analysis Report\n");
        printf("  4. Generate Grade Distribution Report\n");
        printf("  5. Generate Semester-wise Report\n");
        printf("  6. Export All Reports\n");
        printf("  9. Help\n");
        printf("  0. Back to Main Menu\n");
        printf("\n==================================================\n");

        choice = getValidChoice(0, 9);

        switch (choice) {
            case 1: generateFullReport(); break;
            case 2: generateTopperReport(); break;
            case 3: generateFailureReport(); break;
            case 4: generateGradeDistributionReport(); break;
            case 5: generateSemesterWiseReport(); break;
            case 6: 
                generateFullReport();
                generateTopperReport();
                generateFailureReport();
                generateGradeDistributionReport();
                generateSemesterWiseReport();
                printf("\nAll reports exported successfully!\n");
                pressEnterToContinue();
                break;
            case 9: displayHelp("Reports"); pressEnterToContinue(); break;
            case 0: return;
        }
    }
}

// Analytics Menu
void analyticsMenu() {
    int choice;
    while (1) {
        clearScreen();
        printf("\n==================================================\n");
        printf("          ANALYTICS & STATISTICS MENU          \n");
        printf("==================================================\n\n");
        printf("  1. Show Top Rankers\n");
        printf("  2. Show Failed Students\n");
        printf("  3. Show Average Performers\n");
        printf("  4. Class Statistics Overview\n");
        printf("  5. Semester-wise Analysis\n");
        printf("  6. Subject-wise Performance\n");
        printf("  7. Grade Distribution\n");
        printf("  9. Help\n");
        printf("  0. Back to Main Menu\n");
        printf("\n==================================================\n");

        choice = getValidChoice(0, 9);

        switch (choice) {
            case 1: showTopRankers(); break;
            case 2: showFailedStudents(); break;
            case 3: showAveragePerformers(); break;
            case 4: showClassStatistics(); break;
            case 5: showSemesterWiseAnalysis(); break;
            case 6: showSubjectWisePerformance(); break;
            case 7: showGradeDistribution(); break;
            case 9: displayHelp("Analytics"); pressEnterToContinue(); break;
            case 0: return;
        }
    }
}

// Search Menu
void searchMenu() {
    int choice;
    while (1) {
        clearScreen();
        printf("\n==================================================\n");
        printf("             SEARCH & QUERY MENU               \n");
        printf("==================================================\n\n");
        printf("  1. Search by Roll Number\n");
        printf("  2. View Student Progress (Semester-wise)\n");
        printf("  3. Search by Name\n");
        printf("  4. Search by Grade\n");
        printf("  5. Find Students by Status (Pass/Fail)\n");
        printf("  9. Help\n");
        printf("  0. Back to Main Menu\n");
        printf("\n==================================================\n");

        choice = getValidChoice(0, 9);

        switch (choice) {
            case 1: searchByRollNo(); break;
            case 2: viewStudentProgress(); break;
            case 3: searchByName(); break;
            case 4: searchByGrade(); break;
            case 5: searchByStatus(); break;
            case 9: displayHelp("Search"); pressEnterToContinue(); break;
            case 0: return;
        }
    }
}

// Help Menu
void helpMenu() {
    int choice;
    while (1) {
        clearScreen();
        printf("\n==================================================\n");
        printf("                  HELP MENU                    \n");
        printf("==================================================\n\n");
        printf("  1. General Help\n");
        printf("  2. Student Management Help\n");
        printf("  3. Reports Help\n");
        printf("  4. Analytics Help\n");
        printf("  5. Search Help\n");
        printf("  6. About Grading System\n");
        printf("  0. Back to Main Menu\n");
        printf("\n==================================================\n");

        choice = getValidChoice(0, 6);

        switch (choice) {
            case 1: displayHelp("General"); pressEnterToContinue(); break;
            case 2: displayHelp("Student Management"); pressEnterToContinue(); break;
            case 3: displayHelp("Reports"); pressEnterToContinue(); break;
            case 4: displayHelp("Analytics"); pressEnterToContinue(); break;
            case 5: displayHelp("Search"); pressEnterToContinue(); break;
            case 6: displayHelp("Grading"); pressEnterToContinue(); break;
            case 0: return;
        }
    }
}

// Display contextual help
void displayHelp(const char *menuType) {
    clearScreen();
    printf("\n==================================================\n");
    printf("                    HELP                       \n");
    printf("==================================================\n\n");

    if (strcmp(menuType, "General") == 0) {
        printf("GENERAL HELP:\n");
        printf("--------------------------------------------------\n");
        printf("This Student Grade Book System helps you manage\n");
        printf("student records, generate reports, and analyze\n");
        printf("academic performance.\n\n");
        printf("Navigation:\n");
        printf("* Use number keys to select menu options\n");
        printf("* Press 0 to go back to previous menu\n");
        printf("* Press 9 for help in any submenu\n");
    } 
    else if (strcmp(menuType, "Student Management") == 0) {
        printf("STUDENT MANAGEMENT HELP:\n");
        printf("--------------------------------------------------\n");
        printf("* Add New Student: Register a new student\n");
        printf("* View All Students: Display all records\n");
        printf("* View Details: See complete student information\n");
        printf("* Add Semester: Add marks for new semester\n");
    }
    else if (strcmp(menuType, "Reports") == 0) {
        printf("REPORTS HELP:\n");
        printf("--------------------------------------------------\n");
        printf("* Complete Report: All students with grades\n");
        printf("* Topper Report: Top 3 performers\n");
        printf("* Failure Report: Students who failed\n");
        printf("* Export All: Generate all reports at once\n");
    }
    else if (strcmp(menuType, "Analytics") == 0) {
        printf("ANALYTICS HELP:\n");
        printf("--------------------------------------------------\n");
        printf("* Top Rankers: View top performers\n");
        printf("* Failed Students: List of failed students\n");
        printf("* Average Performers: Students with grades B/C\n");
        printf("* Class Statistics: Overall class performance\n");
    }
    else if (strcmp(menuType, "Search") == 0) {
        printf("SEARCH HELP:\n");
        printf("--------------------------------------------------\n");
        printf("* Search by Roll No: Find specific student\n");
        printf("* View Progress: Semester-wise performance\n");
        printf("* Advanced search options available\n");
    }
    else if (strcmp(menuType, "Grading") == 0) {
        printf("GRADING SYSTEM:\n");
        printf("--------------------------------------------------\n");
        printf("Grade S: 91-100  (Outstanding)\n");
        printf("Grade A: 75-90   (Excellent)\n");
        printf("Grade B: 50-74   (Good)\n");
        printf("Grade C: 40-49   (Average)\n");
        printf("Grade D: 35-39   (Below Average)\n");
        printf("Grade F: 0-34    (Fail)\n\n");
        printf("Passing Criteria: Average >= 35\n");
    }
}

// Add new student
void addStudent() {
    clearScreen();
    if (student_count >= MAX_STUDENTS) {
        printf("\nError: Maximum student limit reached!\n");
        pressEnterToContinue();
        return;
    }

    printf("\n==================================================\n");
    printf("              ADD NEW STUDENT                  \n");
    printf("==================================================\n\n");

    int id;
    char name[MAX_NAME];
    int s1, s2, s3;

    printf("Enter Roll Number: ");
    scanf("%d", &id);
    printf("Enter Name: ");
    scanf("%s", name);
    printf("Enter Subject 1 Marks: ");
    scanf("%d", &s1);
    printf("Enter Subject 2 Marks: ");
    scanf("%d", &s2);
    printf("Enter Subject 3 Marks: ");
    scanf("%d", &s3);

    students[student_count].id = id;
    strcpy(students[student_count].name, name);
    students[student_count].semester_count = 1;

    students[student_count].semesters[0].subjects[0] = s1;
    students[student_count].semesters[0].subjects[1] = s2;
    students[student_count].semesters[0].subjects[2] = s3;
    students[student_count].semesters[0].subject_count = 3;
    students[student_count].semesters[0].total = s1 + s2 + s3;
    students[student_count].semesters[0].average = students[student_count].semesters[0].total / 3.0;

    calculateGrade(students[student_count].semesters[0].average, students[student_count].semesters[0].grade);
    calculateStatus(students[student_count].semesters[0].average, students[student_count].semesters[0].status);

    students[student_count].overall_average = students[student_count].semesters[0].average;
    strcpy(students[student_count].overall_grade, students[student_count].semesters[0].grade);

    student_count++;

    printf("\n✓ Student added successfully!\n");
    pressEnterToContinue();
}

// Generate grade distribution report
void generateGradeDistributionReport() {
    FILE *gradeFile = fopen("grade_distribution.txt", "w");
    if (gradeFile == NULL) {
        printf("\nError: Cannot create grade_distribution.txt\n");
        return;
    }

    int gradeCount[6] = {0}; // S, A, B, C, D, F

    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].overall_grade, "S") == 0) gradeCount[0]++;
        else if (strcmp(students[i].overall_grade, "A") == 0) gradeCount[1]++;
        else if (strcmp(students[i].overall_grade, "B") == 0) gradeCount[2]++;
        else if (strcmp(students[i].overall_grade, "C") == 0) gradeCount[3]++;
        else if (strcmp(students[i].overall_grade, "D") == 0) gradeCount[4]++;
        else if (strcmp(students[i].overall_grade, "F") == 0) gradeCount[5]++;
    }

    fprintf(gradeFile, "===================================================\n");
    fprintf(gradeFile, "            GRADE DISTRIBUTION REPORT              \n");
    fprintf(gradeFile, "===================================================\n\n");

    fprintf(gradeFile, "Total Students: %d\n\n", student_count);

    fprintf(gradeFile, "GRADE BREAKDOWN:\n");
    fprintf(gradeFile, "---------------------------------------------------\n");
    fprintf(gradeFile, "Grade S (91-100)  : %d students (%.2f%%)\n", gradeCount[0], (gradeCount[0] * 100.0) / student_count);
    fprintf(gradeFile, "Grade A (75-90)   : %d students (%.2f%%)\n", gradeCount[1], (gradeCount[1] * 100.0) / student_count);
    fprintf(gradeFile, "Grade B (50-74)   : %d students (%.2f%%)\n", gradeCount[2], (gradeCount[2] * 100.0) / student_count);
    fprintf(gradeFile, "Grade C (40-49)   : %d students (%.2f%%)\n", gradeCount[3], (gradeCount[3] * 100.0) / student_count);
    fprintf(gradeFile, "Grade D (35-39)   : %d students (%.2f%%)\n", gradeCount[4], (gradeCount[4] * 100.0) / student_count);
    fprintf(gradeFile, "Grade F (<35)     : %d students (%.2f%%)\n\n", gradeCount[5], (gradeCount[5] * 100.0) / student_count);

    // List students by grade
    const char *grades[] = {"S", "A", "B", "C", "D", "F"};
    for (int g = 0; g < 6; g++) {
        if (gradeCount[g] > 0) {
            fprintf(gradeFile, "\nGrade %s Students:\n", grades[g]);
            fprintf(gradeFile, "---------------------------------------------------\n");
            for (int i = 0; i < student_count; i++) {
                if (strcmp(students[i].overall_grade, grades[g]) == 0) {
                    fprintf(gradeFile, "  %d - %s (Average: %.2f)\n", 
                            students[i].id, students[i].name, students[i].overall_average);
                }
            }
        }
    }

    fclose(gradeFile);
    printf("\n✓ Grade distribution report generated in grade_distribution.txt\n");
    pressEnterToContinue();
}

// Generate semester-wise report
void generateSemesterWiseReport() {
    FILE *semFile = fopen("semester_wise_report.txt", "w");
    if (semFile == NULL) {
        printf("\nError: Cannot create semester_wise_report.txt\n");
        return;
    }

    fprintf(semFile, "===================================================\n");
    fprintf(semFile, "            SEMESTER-WISE REPORT                   \n");
    fprintf(semFile, "===================================================\n\n");

    for (int i = 0; i < student_count; i++) {
        fprintf(semFile, "\nStudent: %s (Roll No: %d)\n", students[i].name, students[i].id);
        fprintf(semFile, "---------------------------------------------------\n");
        fprintf(semFile, "Total Semesters: %d\n", students[i].semester_count);
        fprintf(semFile, "Overall Average: %.2f (Grade: %s)\n\n", 
                students[i].overall_average, students[i].overall_grade);

        for (int sem = 0; sem < students[i].semester_count; sem++) {
            fprintf(semFile, "  Semester %d:\n", sem + 1);
            fprintf(semFile, "    Subjects: ");
            for (int j = 0; j < students[i].semesters[sem].subject_count; j++) {
                fprintf(semFile, "%d ", students[i].semesters[sem].subjects[j]);
            }
            fprintf(semFile, "\n");
            fprintf(semFile, "    Total   : %d\n", students[i].semesters[sem].total);
            fprintf(semFile, "    Average : %.2f\n", students[i].semesters[sem].average);
            fprintf(semFile, "    Grade   : %s\n", students[i].semesters[sem].grade);
            fprintf(semFile, "    Status  : %s\n\n", students[i].semesters[sem].status);
        }
    }

    fclose(semFile);
    printf("\n✓ Semester-wise report generated in semester_wise_report.txt\n");
    pressEnterToContinue();
}

// Show subject-wise performance
void showSubjectWisePerformance() {
    clearScreen();
    printf("\n==================================================\n");
    printf("        SUBJECT-WISE PERFORMANCE ANALYSIS      \n");
    printf("==================================================\n\n");

    if (student_count == 0) {
        printf("No students available for analysis!\n");
        pressEnterToContinue();
        return;
    }

    printf("Semester 1 Subject-wise Performance:\n");
    printf("==================================================\n\n");

    // Assuming 3 subjects in first semester
    int max_subjects = 3;
    float subject_totals[MAX_SUBJECTS] = {0};
    int subject_counts[MAX_SUBJECTS] = {0};

    for (int i = 0; i < student_count; i++) {
        for (int j = 0; j < students[i].semesters[0].subject_count && j < max_subjects; j++) {
            subject_totals[j] += students[i].semesters[0].subjects[j];
            subject_counts[j]++;
        }
    }

    printf("Subject   Average   Highest   Lowest\n");
    printf("--------------------------------------------------\n");

    for (int j = 0; j < max_subjects; j++) {
        if (subject_counts[j] > 0) {
            float avg = subject_totals[j] / subject_counts[j];
            
            // Find highest and lowest
            int highest = 0, lowest = 100;
            for (int i = 0; i < student_count; i++) {
                if (j < students[i].semesters[0].subject_count) {
                    if (students[i].semesters[0].subjects[j] > highest)
                        highest = students[i].semesters[0].subjects[j];
                    if (students[i].semesters[0].subjects[j] < lowest)
                        lowest = students[i].semesters[0].subjects[j];
                }
            }

            printf("Sub %d     %.2f      %d         %d\n", j + 1, avg, highest, lowest);
        }
    }

    printf("\n==================================================\n");
    printf("\nNote: Analysis is based on Semester 1 data.\n");
    printf("      More detailed analysis available with\n");
    printf("      multiple semester data.\n");

    pressEnterToContinue();
}

// Show grade distribution
void showGradeDistribution() {
    clearScreen();
    printf("\n==================================================\n");
    printf("           GRADE DISTRIBUTION                  \n");
    printf("==================================================\n\n");

    if (student_count == 0) {
        printf("No students available!\n");
        pressEnterToContinue();
        return;
    }

    int gradeCount[6] = {0}; // S, A, B, C, D, F

    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].overall_grade, "S") == 0) gradeCount[0]++;
        else if (strcmp(students[i].overall_grade, "A") == 0) gradeCount[1]++;
        else if (strcmp(students[i].overall_grade, "B") == 0) gradeCount[2]++;
        else if (strcmp(students[i].overall_grade, "C") == 0) gradeCount[3]++;
        else if (strcmp(students[i].overall_grade, "D") == 0) gradeCount[4]++;
        else if (strcmp(students[i].overall_grade, "F") == 0) gradeCount[5]++;
    }

    printf("Grade    Count    Percentage    Bar Chart\n");
    printf("==================================================\n");

    const char *grades[] = {"S", "A", "B", "C", "D", "F"};
    const char *ranges[] = {"(91-100)", "(75-90)", "(50-74)", "(40-49)", "(35-39)", "(<35)"};

    for (int i = 0; i < 6; i++) {
        float percentage = (gradeCount[i] * 100.0) / student_count;
        printf("%-5s %8s %5d     %6.2f%%    ", 
               grades[i], ranges[i], gradeCount[i], percentage);
        
        // Simple bar chart
        int bars = (int)(percentage / 2); // Scale to fit screen
        for (int j = 0; j < bars; j++) {
            printf("*");
        }
        printf("\n");
    }

    printf("==================================================\n");
    printf("Total Students: %d\n", student_count);

    pressEnterToContinue();
}

// Search by name
void searchByName() {
    clearScreen();
    printf("\n==================================================\n");
    printf("             SEARCH BY NAME                    \n");
    printf("==================================================\n\n");

    if (student_count == 0) {
        printf("No students in the system!\n");
        pressEnterToContinue();
        return;
    }

    char search_name[MAX_NAME];
    printf("Enter student name (or part of name): ");
    scanf("%s", search_name);

    // Convert search term to lowercase for case-insensitive search
    for (int i = 0; search_name[i]; i++) {
        search_name[i] = tolower(search_name[i]);
    }

    printf("\nSearch Results:\n");
    printf("==================================================\n");

    int found_count = 0;
    for (int i = 0; i < student_count; i++) {
        char temp_name[MAX_NAME];
        strcpy(temp_name, students[i].name);
        
        // Convert to lowercase for comparison
        for (int j = 0; temp_name[j]; j++) {
            temp_name[j] = tolower(temp_name[j]);
        }

        if (strstr(temp_name, search_name) != NULL) {
            found_count++;
            printf("\n%d. Roll No: %d\n", found_count, students[i].id);
            printf("   Name    : %s\n", students[i].name);
            printf("   Average : %.2f\n", students[i].overall_average);
            printf("   Grade   : %s\n", students[i].overall_grade);
            printf("   Status  : %s\n", students[i].semesters[0].status);
        }
    }

    if (found_count == 0) {
        printf("\nNo students found matching '%s'\n", search_name);
    } else {
        printf("\n==================================================\n");
        printf("Total matches found: %d\n", found_count);
    }

    pressEnterToContinue();
}

// Search by grade
void searchByGrade() {
    clearScreen();
    printf("\n==================================================\n");
    printf("             SEARCH BY GRADE                   \n");
    printf("==================================================\n\n");

    if (student_count == 0) {
        printf("No students in the system!\n");
        pressEnterToContinue();
        return;
    }

    char grade[5];
    printf("Available Grades: S, A, B, C, D, F\n");
    printf("Enter grade to search: ");
    scanf("%s", grade);

    // Convert to uppercase
    for (int i = 0; grade[i]; i++) {
        grade[i] = toupper(grade[i]);
    }

    printf("\nStudents with Grade %s:\n", grade);
    printf("==================================================\n");

    int found_count = 0;
    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].overall_grade, grade) == 0) {
            found_count++;
            printf("\n%d. Roll No: %d\n", found_count, students[i].id);
            printf("   Name    : %s\n", students[i].name);
            printf("   Average : %.2f\n", students[i].overall_average);
            printf("   Status  : %s\n", students[i].semesters[0].status);
        }
    }

    if (found_count == 0) {
        printf("\nNo students found with grade '%s'\n", grade);
    } else {
        printf("\n==================================================\n");
        printf("Total students with grade %s: %d (%.2f%%)\n", 
               grade, found_count, (found_count * 100.0) / student_count);
    }

    pressEnterToContinue();
}

// Search by status (Pass/Fail)
void searchByStatus() {
    clearScreen();
    printf("\n==================================================\n");
    printf("          SEARCH BY STATUS (PASS/FAIL)         \n");
    printf("==================================================\n\n");

    if (student_count == 0) {
        printf("No students in the system!\n");
        pressEnterToContinue();
        return;
    }

    int choice;
    printf("Select Status:\n");
    printf("  1. PASS\n");
    printf("  2. FAIL\n");
    printf("  0. Cancel\n\n");

    choice = getValidChoice(0, 2);

    if (choice == 0) {
        return;
    }

    const char *status = (choice == 1) ? "PASS" : "FAIL";

    printf("\nStudents with Status: %s\n", status);
    printf("==================================================\n");

    int found_count = 0;
    printf("ID\tName\t\tAverage\tGrade\n");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].semesters[0].status, status) == 0) {
            found_count++;
            printf("%d\t%-12s\t%.2f\t%s\n",
                   students[i].id,
                   students[i].name,
                   students[i].overall_average,
                   students[i].overall_grade);
        }
    }

    if (found_count == 0) {
        printf("\nNo students found with status '%s'\n", status);
    } else {
        printf("\n==================================================\n");
        printf("Total students with status %s: %d (%.2f%%)\n", 
               status, found_count, (found_count * 100.0) / student_count);
    }

    pressEnterToContinue();
}

// View all students
void viewAllStudents() {
    clearScreen();
    printf("\n======================================================================\n");
    printf("                        ALL STUDENTS LIST                              \n");
    printf("======================================================================\n\n");

    if (student_count == 0) {
        printf("No students found!\n");
        pressEnterToContinue();
        return;
    }

    printf("ID\tName\t\tAverage\tGrade\tStatus\n");
    printf("----------------------------------------------------------------------\n");

    for (int i = 0; i < student_count; i++) {
        printf("%d\t%-12s\t%.2f\t%s\t%s\n",
               students[i].id,
               students[i].name,
               students[i].overall_average,
               students[i].overall_grade,
               students[i].semesters[0].status);
    }

    pressEnterToContinue();
}

// View student details
void viewStudentDetails() {
    int id, found = -1;
    clearScreen();
    printf("\n==================================================\n");
    printf("           VIEW STUDENT DETAILS                \n");
    printf("==================================================\n\n");

    printf("Enter Roll Number: ");
    scanf("%d", &id);

    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("\nStudent with Roll Number %d not found!\n", id);
        pressEnterToContinue();
        return;
    }

    printf("\n=============== STUDENT DETAILS ===============\n");
    printf("Roll Number : %d\n", students[found].id);
    printf("Name        : %s\n", students[found].name);
    printf("Semesters   : %d\n", students[found].semester_count);
    printf("Overall Avg : %.2f\n", students[found].overall_average);
    printf("Overall Grade: %s\n", students[found].overall_grade);
    printf("\nLatest Semester Performance:\n");
    printf("Total       : %d\n", students[found].semesters[0].total);
    printf("Average     : %.2f\n", students[found].semesters[0].average);
    printf("Grade       : %s\n", students[found].semesters[0].grade);
    printf("Status      : %s\n", students[found].semesters[0].status);

    pressEnterToContinue();
}

// Search by roll number
void searchByRollNo() {
    int id, found = -1;
    clearScreen();
    printf("\n==================================================\n");
    printf("          SEARCH STUDENT BY ROLL NO            \n");
    printf("==================================================\n\n");

    printf("Enter Roll Number to search: ");
    scanf("%d", &id);

    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("\n✗ Student with Roll Number %d not found!\n", id);
    } else {
        printf("\n✓ Student Found!\n");
        printf("==============================================\n");
        printf("Roll Number : %d\n", students[found].id);
        printf("Name        : %s\n", students[found].name);
        printf("Average     : %.2f\n", students[found].overall_average);
        printf("Grade       : %s\n", students[found].overall_grade);
        printf("Status      : %s\n", students[found].semesters[0].status);
    }

    pressEnterToContinue();
}

// View student progress semester-wise
void viewStudentProgress() {
    int id, found = -1;
    clearScreen();
    printf("\n==================================================\n");
    printf("         STUDENT PROGRESS TRACKER              \n");
    printf("==================================================\n\n");

    printf("Enter Roll Number: ");
    scanf("%d", &id);

    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("\nStudent not found!\n");
        pressEnterToContinue();
        return;
    }

    printf("\n=========== PROGRESS REPORT ===========\n");
    printf("Roll Number: %d\n", students[found].id);
    printf("Name       : %s\n\n", students[found].name);

    for (int sem = 0; sem < students[found].semester_count; sem++) {
        printf("Semester %d:\n", sem + 1);
        printf("  Subjects: ");
        for (int j = 0; j < students[found].semesters[sem].subject_count; j++) {
            printf("%d ", students[found].semesters[sem].subjects[j]);
        }
        printf("\n  Total   : %d\n", students[found].semesters[sem].total);
        printf("  Average : %.2f\n", students[found].semesters[sem].average);
        printf("  Grade   : %s\n", students[found].semesters[sem].grade);
        printf("  Status  : %s\n\n", students[found].semesters[sem].status);
    }

    printf("Overall Average: %.2f\n", students[found].overall_average);
    printf("Overall Grade  : %s\n", students[found].overall_grade);

    pressEnterToContinue();
}

// Generate full report
void generateFullReport() {
    FILE *report = fopen("report.txt", "w");
    if (report == NULL) {
        printf("\nError: Cannot create report.txt\n");
        return;
    }

    fprintf(report, "=======================================================================\n");
    fprintf(report, "                    STUDENT GRADE BOOK REPORT                          \n");
    fprintf(report, "=======================================================================\n\n");

    fprintf(report, "ID\tName\t\tScores\t\tTotal\tAverage\tGrade\tStatus\n");
    fprintf(report, "-----------------------------------------------------------------------\n");

    for (int i = 0; i < student_count; i++) {
        fprintf(report, "%d\t%-12s\t", students[i].id, students[i].name);
        for (int j = 0; j < students[i].semesters[0].subject_count; j++)
            fprintf(report, "%d ", students[i].semesters[0].subjects[j]);
        fprintf(report, "\t%d\t%.2f\t%s\t%s\n",
                students[i].semesters[0].total,
                students[i].semesters[0].average,
                students[i].overall_grade,
                students[i].semesters[0].status);
    }

    fclose(report);
    printf("\n✓ Report generated successfully in report.txt\n");
    pressEnterToContinue();
}

// Generate topper report
void generateTopperReport() {
    if (student_count == 0) {
        printf("\nNo students available for report generation!\n");
        pressEnterToContinue();
        return;
    }

    // Sort students by average
    int indices[MAX_STUDENTS];
    for (int i = 0; i < student_count; i++)
        indices[i] = i;

    for (int i = 0; i < student_count - 1; i++) {
        for (int j = i + 1; j < student_count; j++) {
            if (students[indices[j]].overall_average > students[indices[i]].overall_average) {
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }

    FILE *topperFile = fopen("topper.txt", "w");
    if (topperFile == NULL) {
        printf("\nError: Cannot create topper.txt\n");
        return;
    }

    int passCount = 0, failCount = 0;
    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].semesters[0].status, "PASS") == 0)
            passCount++;
        else
            failCount++;
    }

    float passPercentage = (passCount * 100.0) / student_count;
    float failPercentage = (failCount * 100.0) / student_count;

    fprintf(topperFile, "===================================================\n");
    fprintf(topperFile, "            CLASS PERFORMANCE SUMMARY              \n");
    fprintf(topperFile, "===================================================\n\n");

    fprintf(topperFile, "Total Students  : %d\n", student_count);
    fprintf(topperFile, "Pass Count      : %d\n", passCount);
    fprintf(topperFile, "Fail Count      : %d\n", failCount);
    fprintf(topperFile, "Pass Percentage : %.2f%%\n", passPercentage);
    fprintf(topperFile, "Fail Percentage : %.2f%%\n\n", failPercentage);

    fprintf(topperFile, "=============== TOP 3 STUDENTS ===============\n");

    for (int i = 0; i < 3 && i < student_count; i++) {
        int x = indices[i];
        fprintf(topperFile, "\nRank %d:\n", i + 1);
        fprintf(topperFile, "  ID      : %d\n", students[x].id);
        fprintf(topperFile, "  Name    : %s\n", students[x].name);
        fprintf(topperFile, "  Average : %.2f\n", students[x].overall_average);
        fprintf(topperFile, "  Grade   : %s\n", students[x].overall_grade);
        fprintf(topperFile, "  Status  : %s\n", students[x].semesters[0].status);
    }

    fclose(topperFile);
    printf("\n✓ Topper report generated successfully in topper.txt\n");
    pressEnterToContinue();
}

// Generate failure report
void generateFailureReport() {
    FILE *failFile = fopen("failure_report.txt", "w");
    if (failFile == NULL) {
        printf("\nError: Cannot create failure_report.txt\n");
        return;
    }

    fprintf(failFile, "===================================================\n");
    fprintf(failFile, "            FAILURE ANALYSIS REPORT                \n");
    fprintf(failFile, "===================================================\n\n");

    int failCount = 0;
    fprintf(failFile, "Failed Students:\n");
    fprintf(failFile, "---------------------------------------------------\n");

    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].semesters[0].status, "FAIL") == 0) {
            failCount++;
            fprintf(failFile, "\n%d. Roll No: %d\n", failCount, students[i].id);
            fprintf(failFile, "   Name    : %s\n", students[i].name);
            fprintf(failFile, "   Average : %.2f\n", students[i].overall_average);
            fprintf(failFile, "   Grade   : %s\n", students[i].overall_grade);
        }
    }

    if (failCount == 0) {
        fprintf(failFile, "\nNo students failed. Excellent class performance!\n");
    } else {
        fprintf(failFile, "\n---------------------------------------------------\n");
        fprintf(failFile, "Total Failed Students: %d\n", failCount);
        fprintf(failFile, "Failure Rate: %.2f%%\n", (failCount * 100.0) / student_count);
    }

    fclose(failFile);
    printf("\n✓ Failure report generated successfully in failure_report.txt\n");
    pressEnterToContinue();
}

// Show top rankers
void showTopRankers() {
    clearScreen();
    printf("\n==================================================\n");
    printf("              TOP RANKERS                      \n");
    printf("==================================================\n\n");

    if (student_count == 0) {
        printf("No students available!\n");
        pressEnterToContinue();
        return;
    }

    // Sort students by average
    int indices[MAX_STUDENTS];
    for (int i = 0; i < student_count; i++)
        indices[i] = i;

    for (int i = 0; i < student_count - 1; i++) {
        for (int j = i + 1; j < student_count; j++) {
            if (students[indices[j]].overall_average > students[indices[i]].overall_average) {
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }

    printf("Enter number of top rankers to display (1-%d): ", student_count);
    int n;
    scanf("%d", &n);
    if (n > student_count) n = student_count;

    printf("\n");
    printf("Rank\tID\tName\t\tAverage\tGrade\tStatus\n");
    printf("----------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        int x = indices[i];
        printf("%d\t%d\t%-12s\t%.2f\t%s\t%s\n",
               i + 1,
               students[x].id,
               students[x].name,
               students[x].overall_average,
               students[x].overall_grade,
               students[x].semesters[0].status);
    }

    pressEnterToContinue();
}

// Show failed students
void showFailedStudents() {
    clearScreen();
    printf("\n==================================================\n");
    printf("           FAILED STUDENTS LIST                \n");
    printf("==================================================\n\n");

    int failCount = 0;
    printf("ID\tName\t\tAverage\tGrade\n");
    printf("--------------------------------------------------------\n");

    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].semesters[0].status, "FAIL") == 0) {
            failCount++;
            printf("%d\t%-12s\t%.2f\t%s\n",
                   students[i].id,
                   students[i].name,
                   students[i].overall_average,
                   students[i].overall_grade);
        }
    }

    if (failCount == 0) {
        printf("\n✓ No students failed. Great performance!\n");
    } else {
        printf("\n--------------------------------------------------------\n");
        printf("Total Failed Students: %d\n", failCount);
        printf("Failure Rate: %.2f%%\n", (failCount * 100.0) / student_count);
    }

    pressEnterToContinue();
}

// Show average performers
void showAveragePerformers() {
    clearScreen();
    printf("\n==================================================\n");
    printf("         AVERAGE PERFORMERS (Grade B/C)        \n");
    printf("==================================================\n\n");

    int avgCount = 0;
    printf("ID\tName\t\tAverage\tGrade\tStatus\n");
    printf("----------------------------------------------------------------\n");

    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].overall_grade, "B") == 0 || 
            strcmp(students[i].overall_grade, "C") == 0) {
            avgCount++;
            printf("%d\t%-12s\t%.2f\t%s\t%s\n",
                   students[i].id,
                   students[i].name,
                   students[i].overall_average,
                   students[i].overall_grade,
                   students[i].semesters[0].status);
        }
    }

    if (avgCount == 0) {
        printf("\nNo students in average performance category.\n");
    } else {
        printf("\n----------------------------------------------------------------\n");
        printf("Total Average Performers: %d\n", avgCount);
        printf("Percentage: %.2f%%\n", (avgCount * 100.0) / student_count);
    }

    pressEnterToContinue();
}

// Show class statistics
void showClassStatistics() {
    clearScreen();
    printf("\n==================================================\n");
    printf("          CLASS STATISTICS OVERVIEW           \n");
    printf("==================================================\n\n");

    if (student_count == 0) {
        printf("No students available for statistics!\n");
        pressEnterToContinue();
        return;
    }

    int gradeCount[6] = {0}; // S, A, B, C, D, F
    int passCount = 0, failCount = 0;
    float totalAvg = 0, maxAvg = 0, minAvg = 100;

    for (int i = 0; i < student_count; i++) {
        totalAvg += students[i].overall_average;

        if (students[i].overall_average > maxAvg)
            maxAvg = students[i].overall_average;
        if (students[i].overall_average < minAvg)
            minAvg = students[i].overall_average;

        if (strcmp(students[i].semesters[0].status, "PASS") == 0)
            passCount++;
        else
            failCount++;

        // Count grades
        if (strcmp(students[i].overall_grade, "S") == 0) gradeCount[0]++;
        else if (strcmp(students[i].overall_grade, "A") == 0) gradeCount[1]++;
        else if (strcmp(students[i].overall_grade, "B") == 0) gradeCount[2]++;
        else if (strcmp(students[i].overall_grade, "C") == 0) gradeCount[3]++;
        else if (strcmp(students[i].overall_grade, "D") == 0) gradeCount[4]++;
        else if (strcmp(students[i].overall_grade, "F") == 0) gradeCount[5]++;
    }

    float classAvg = totalAvg / student_count;

    printf("=============== OVERALL STATISTICS ===============\n\n");
    printf("Total Students      : %d\n", student_count);
    printf("Class Average       : %.2f\n", classAvg);
    printf("Highest Average     : %.2f\n", maxAvg);
    printf("Lowest Average      : %.2f\n\n", minAvg);

    printf("=============== PASS/FAIL ANALYSIS ===============\n\n");
    printf("Passed Students     : %d (%.2f%%)\n", passCount, (passCount * 100.0) / student_count);
    printf("Failed Students     : %d (%.2f%%)\n\n", failCount, (failCount * 100.0) / student_count);

    printf("=============== GRADE DISTRIBUTION ===============\n\n");
    printf("Grade S (91-100)    : %d students (%.2f%%)\n", gradeCount[0], (gradeCount[0] * 100.0) / student_count);
    printf("Grade A (75-90)     : %d students (%.2f%%)\n", gradeCount[1], (gradeCount[1] * 100.0) / student_count);
    printf("Grade B (50-74)     : %d students (%.2f%%)\n", gradeCount[2], (gradeCount[2] * 100.0) / student_count);
    printf("Grade C (40-49)     : %d students (%.2f%%)\n", gradeCount[3], (gradeCount[3] * 100.0) / student_count);
    printf("Grade D (35-39)     : %d students (%.2f%%)\n", gradeCount[4], (gradeCount[4] * 100.0) / student_count);
    printf("Grade F (<35)       : %d students (%.2f%%)\n", gradeCount[5], (gradeCount[5] * 100.0) / student_count);

    pressEnterToContinue();
}

// Show semester-wise analysis
void showSemesterWiseAnalysis() {
    clearScreen();
    printf("\n==================================================\n");
    printf("        SEMESTER-WISE ANALYSIS                 \n");
    printf("==================================================\n\n");

    if (student_count == 0) {
        printf("No students available for analysis!\n");
        pressEnterToContinue();
        return;
    }

    printf("Semester 1 Statistics:\n");
    printf("==================================================\n");

    float totalAvg = 0;
    int passCount = 0;

    for (int i = 0; i < student_count; i++) {
        totalAvg += students[i].semesters[0].average;
        if (strcmp(students[i].semesters[0].status, "PASS") == 0)
            passCount++;
    }

    printf("Average Score       : %.2f\n", totalAvg / student_count);
    printf("Pass Rate           : %.2f%%\n", (passCount * 100.0) / student_count);
    printf("Fail Rate           : %.2f%%\n", ((student_count - passCount) * 100.0) / student_count);

    printf("\nNote: Multi-semester analysis will be available\n");
    printf("      when more semester data is added.\n");

    pressEnterToContinue();
}

// Add semester data for existing student
void addSemesterData() {
    clearScreen();
    printf("\n==================================================\n");
    printf("         ADD SEMESTER DATA FOR STUDENT         \n");
    printf("==================================================\n\n");

    if (student_count == 0) {
        printf("No students in the system!\n");
        pressEnterToContinue();
        return;
    }

    int id, found = -1;
    printf("Enter Roll Number: ");
    scanf("%d", &id);

    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("\nStudent with Roll Number %d not found!\n", id);
        pressEnterToContinue();
        return;
    }

    if (students[found].semester_count >= MAX_SEMESTERS) {
        printf("\nMaximum semester limit reached for this student!\n");
        pressEnterToContinue();
        return;
    }

    printf("\nStudent: %s (Roll No: %d)\n", students[found].name, students[found].id);
    printf("Current Semesters: %d\n", students[found].semester_count);
    printf("\nAdding Semester %d data:\n", students[found].semester_count + 1);
    printf("--------------------------------------------------\n");

    int num_subjects;
    printf("Enter number of subjects (1-%d): ", MAX_SUBJECTS);
    scanf("%d", &num_subjects);

    if (num_subjects < 1 || num_subjects > MAX_SUBJECTS) {
        printf("\nInvalid number of subjects!\n");
        pressEnterToContinue();
        return;
    }

    int sem_index = students[found].semester_count;
    students[found].semesters[sem_index].subject_count = num_subjects;
    students[found].semesters[sem_index].total = 0;

    for (int i = 0; i < num_subjects; i++) {
        printf("Enter marks for Subject %d: ", i + 1);
        scanf("%d", &students[found].semesters[sem_index].subjects[i]);
        students[found].semesters[sem_index].total += students[found].semesters[sem_index].subjects[i];
    }

    students[found].semesters[sem_index].average = 
        students[found].semesters[sem_index].total / (float)num_subjects;

    calculateGrade(students[found].semesters[sem_index].average, 
                   students[found].semesters[sem_index].grade);
    calculateStatus(students[found].semesters[sem_index].average, 
                    students[found].semesters[sem_index].status);

    students[found].semester_count++;

    // Recalculate overall average
    float total_avg = 0;
    for (int i = 0; i < students[found].semester_count; i++) {
        total_avg += students[found].semesters[i].average;
    }
    students[found].overall_average = total_avg / students[found].semester_count;
    calculateGrade(students[found].overall_average, students[found].overall_grade);

    printf("\n✓ Semester %d data added successfully!\n", sem_index + 1);
    printf("\nSemester %d Summary:\n", sem_index + 1);
    printf("  Total     : %d\n", students[found].semesters[sem_index].total);
    printf("  Average   : %.2f\n", students[found].semesters[sem_index].average);
    printf("  Grade     : %s\n", students[found].semesters[sem_index].grade);
    printf("  Status    : %s\n", students[found].semesters[sem_index].status);
    printf("\nUpdated Overall Average: %.2f (Grade: %s)\n", 
           students[found].overall_average, students[found].overall_grade);

    pressEnterToContinue();
}

// Update student information
void updateStudentInfo() {
    clearScreen();
    printf("\n==================================================\n");
    printf("          UPDATE STUDENT INFORMATION           \n");
    printf("==================================================\n\n");

    if (student_count == 0) {
        printf("No students in the system!\n");
        pressEnterToContinue();
        return;
    }

    int id, found = -1;
    printf("Enter Roll Number: ");
    scanf("%d", &id);

    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("\nStudent with Roll Number %d not found!\n", id);
        pressEnterToContinue();
        return;
    }

    printf("\nCurrent Information:\n");
    printf("--------------------------------------------------\n");
    printf("Roll Number : %d\n", students[found].id);
    printf("Name        : %s\n\n", students[found].name);

    int choice;
    printf("What would you like to update?\n");
    printf("  1. Name\n");
    printf("  2. Marks for a specific semester\n");
    printf("  0. Cancel\n\n");

    choice = getValidChoice(0, 2);

    if (choice == 0) {
        printf("\nUpdate cancelled.\n");
        pressEnterToContinue();
        return;
    }

    if (choice == 1) {
        char new_name[MAX_NAME];
        printf("\nEnter new name: ");
        scanf("%s", new_name);
        strcpy(students[found].name, new_name);
        printf("\n✓ Name updated successfully!\n");
    }
    else if (choice == 2) {
        if (students[found].semester_count == 0) {
            printf("\nNo semester data available!\n");
            pressEnterToContinue();
            return;
        }

        printf("\nAvailable semesters: 1 to %d\n", students[found].semester_count);
        printf("Enter semester number to update: ");
        int sem_num;
        scanf("%d", &sem_num);

        if (sem_num < 1 || sem_num > students[found].semester_count) {
            printf("\nInvalid semester number!\n");
            pressEnterToContinue();
            return;
        }

        int sem_idx = sem_num - 1;
        printf("\nCurrent marks for Semester %d:\n", sem_num);
        for (int i = 0; i < students[found].semesters[sem_idx].subject_count; i++) {
            printf("  Subject %d: %d\n", i + 1, students[found].semesters[sem_idx].subjects[i]);
        }

        printf("\nEnter new marks:\n");
        students[found].semesters[sem_idx].total = 0;
        for (int i = 0; i < students[found].semesters[sem_idx].subject_count; i++) {
            printf("Subject %d: ", i + 1);
            scanf("%d", &students[found].semesters[sem_idx].subjects[i]);
            students[found].semesters[sem_idx].total += students[found].semesters[sem_idx].subjects[i];
        }

        students[found].semesters[sem_idx].average = 
            students[found].semesters[sem_idx].total / (float)students[found].semesters[sem_idx].subject_count;

        calculateGrade(students[found].semesters[sem_idx].average, 
                       students[found].semesters[sem_idx].grade);
        calculateStatus(students[found].semesters[sem_idx].average, 
                        students[found].semesters[sem_idx].status);

        // Recalculate overall average
        float total_avg = 0;
        for (int i = 0; i < students[found].semester_count; i++) {
            total_avg += students[found].semesters[i].average;
        }
        students[found].overall_average = total_avg / students[found].semester_count;
        calculateGrade(students[found].overall_average, students[found].overall_grade);

        printf("\n✓ Semester %d marks updated successfully!\n", sem_num);
        printf("\nNew Semester %d Summary:\n", sem_num);
        printf("  Total     : %d\n", students[found].semesters[sem_idx].total);
        printf("  Average   : %.2f\n", students[found].semesters[sem_idx].average);
        printf("  Grade     : %s\n", students[found].semesters[sem_idx].grade);
        printf("  Status    : %s\n", students[found].semesters[sem_idx].status);
        printf("\nUpdated Overall Average: %.2f (Grade: %s)\n", 
               students[found].overall_average, students[found].overall_grade);
    }

    pressEnterToContinue();
}