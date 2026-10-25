Student Grade Book Management System

A menu-driven, console-based application written in C for managing student academic records. It supports multi-semester tracking, automatic grading, report generation, and class analytics, all without external dependencies.

Features

Student Management

Add new students with roll number, name, and subject marks
View all students or look up detailed records by roll number
Add marks for additional semesters (up to 8 per student)
Update a student’s name or edit marks for any semester

Reports Generation (exported to .txt files)

Complete student report (report.txt)
Topper report with top 3 students and class pass/fail summary (topper.txt)
Failure analysis report (failure_report.txt)
Grade distribution report (grade_distribution.txt)
Semester-wise report (semester_wise_report.txt)
One-click export of all reports

Analytics & Statistics

Top rankers (user-selected count)
Failed students and average performers (Grades B/C)
Class statistics: average, highest, lowest, pass/fail percentages
Semester-wise analysis and subject-wise performance (average, highest, lowest)
Grade distribution with a text bar chart

Search & Query

Search by roll number
Search by name (case-insensitive, partial match)
Search by grade
Filter by pass/fail status
Semester-wise progress tracker

Other

Context-sensitive help menus and a grading system guide
Cross-platform screen clearing (Windows/Linux/macOS)
Input validation on menu choices
Grading System
Grade	Average Range	Remark
S	91 – 100	Outstanding
A	75 – 90	Excellent
B	50 – 74	Good
C	40 – 49	Average
D	35 – 39	Below Average
F	0 – 34	Fail

Passing criteria: average ≥ 35

Data Input

On startup, the program loads initial records from grades.txt (if present). Each line has the format:

<roll_no> <name> <marks1> <marks2> <marks3>

Example:

101 Rahul 85 90 78
102 Priya 92 88 95

If the file is missing, the program starts with an empty database.

Build & Run
bash
gcc main.c -o gradebook
./gradebook

On Windows:

bash
gcc main.c -o gradebook.exe
gradebook.exe
Technical Details
Language: C (C99 or later)
Concepts used: structs, nested structs, arrays, file I/O, string handling, modular functions, menu-driven design
Limits: 60 students, 8 semesters per student, 5 subjects per semester
Project Structure
├── main.c                       # Source code
├── grades.txt                   # Input data (optional)
├── report.txt                   # Generated reports
├── topper.txt
├── failure_report.txt
├── grade_distribution.txt
└── semester_wise_report.txt
Known Limitations
Data added during a session is not saved back to grades.txt
Names must be a single word (no spaces)
Initial file loading supports only 3 subjects in semester 1
