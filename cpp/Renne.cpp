#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100
#define LINE  "─────────────────────────────────────────────────────────────\n"
#define LINE2 "┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄\n"

struct Student {
    char  regNo[20];
    char  name[30];
    int   age;
    float marks;
};


void addStudent         (struct Student s[], int *count);
void displayStudents    (struct Student s[], int  count);
void searchStudent      (struct Student s[], int  count);
void saveToFile         (struct Student s[], int  count);
void loadFromFile       (struct Student s[], int *count);
void displayAboveAverage(struct Student s[], int  count);

static void printHeader(void) {
    printf("\n  SRMS  ·  Student Record Management System\n");
    printf("  " LINE2);
    printf("  1  Add Student\n");
    printf("  2  Display All Records\n");
    printf("  3  Search by Reg No.\n");
    printf("  4  Save to File\n");
    printf("  5  Load from File\n");
    printf("  6  Average & Above-Average Students\n");
    printf("  7  Exit\n");
    printf("  " LINE2);
    printf("  >> ");
}

static void ok (const char *msg) { printf("  [OK]  %s\n", msg); }
static void err(const char *msg) { printf("  [!!]  %s\n", msg); }

int main(void) {
    struct Student students[MAX_STUDENTS];
    int count = 0, choice;

    for (;;) {
        printHeader();
        if (scanf("%d", &choice) != 1) { getchar(); continue; }

        if      (choice == 1) addStudent(students, &count);
        else if (choice == 2) displayStudents(students, count);
        else if (choice == 3) searchStudent(students, count);
        else if (choice == 4) saveToFile(students, count);
        else if (choice == 5) loadFromFile(students, &count);
        else if (choice == 6) displayAboveAverage(students, count);
        else if (choice == 7) { printf("\n  Goodbye.\n\n"); break; }
        else                    err("Invalid choice. Enter 1-7.");
    }
    return 0;
}

void addStudent(struct Student s[], int *count) {
    if (*count >= MAX_STUDENTS) { err("Student limit reached."); return; }

    printf("\n  -- Add Student (%d / %d) --\n", *count + 1, MAX_STUDENTS);

    printf("  Reg No  : "); scanf("%19s",  s[*count].regNo);
    getchar();
    printf("  Name    : "); fgets(s[*count].name, 30, stdin);
    s[*count].name[strcspn(s[*count].name, "\n")] = '\0';
    printf("  Age     : "); scanf("%d",   &s[*count].age);
    printf("  Marks   : "); scanf("%f",   &s[*count].marks);

    (*count)++;
    printf("\n");
    ok("Record saved.");
}


void displayStudents(struct Student s[], int count) {
    int i;
    if (count == 0) { err("No records found."); return; }

    printf("\n  %-16s  %-22s  %-5s  %s\n", "Reg No", "Name", "Age", "Marks");
    printf("  " LINE);
    for (i = 0; i < count; i++)
        printf("  %-16s  %-22s  %-5d  %.2f\n",
               s[i].regNo, s[i].name, s[i].age, s[i].marks);
    printf("  " LINE);
    printf("  Total: %d student(s)\n", count);
}

void searchStudent(struct Student s[], int count) {
    int i;
    if (count == 0) { err("No records to search."); return; }

    char q[20];
    printf("\n  Reg No to search: "); scanf("%19s", q);

    for (i = 0; i < count; i++) {
        if (strcmp(s[i].regNo, q) == 0) {
            printf("\n  %-16s  %-22s  %-5s  %s\n", "Reg No", "Name", "Age", "Marks");
            printf("  " LINE);
            printf("  %-16s  %-22s  %-5d  %.2f\n",
                   s[i].regNo, s[i].name, s[i].age, s[i].marks);
            printf("  " LINE);
            return;
        }
    }
    err("No student found with that registration number.");
}

void saveToFile(struct Student s[], int count) {
    int i;
    if (count == 0) { err("Nothing to save."); return; }

    FILE *fp = fopen("students.txt", "w");
    if (!fp) { err("Could not open students.txt for writing."); return; }

    for (i = 0; i < count; i++)
        fprintf(fp, "%s %s %d %.2f\n",
                s[i].regNo, s[i].name, s[i].age, s[i].marks);
    fclose(fp);
    ok("Saved to students.txt");  
}

void loadFromFile(struct Student s[], int *count) {
    FILE *fp = fopen("students.txt", "r");
    if (!fp) { err("students.txt not found."); return; }

    *count = 0;
    while (*count < MAX_STUDENTS &&
           fscanf(fp, "%19s %29s %d %f",
                  s[*count].regNo, s[*count].name,
                  &s[*count].age, &s[*count].marks) == 4)
        (*count)++;

    fclose(fp);
    char buf[60];
    sprintf(buf, "Loaded %d record(s) from students.txt.", *count);
    ok(buf);
}

void displayAboveAverage(struct Student s[], int count) {
    int i, found = 0;
    float total = 0.0f, avg;

    if (count == 0) { err("No records available."); return; }

    for (i = 0; i < count; i++) total += s[i].marks;
    avg = total / count;

    printf("\n  Total students : %d\n", count);
    printf("  Total marks    : %.2f\n", total);
    printf("  Average marks  : %.2f\n\n", avg);

    printf("  Students above average (> %.2f)\n", avg);
    printf("  %-16s  %-22s  %-5s  %s\n", "Reg No", "Name", "Age", "Marks");
    printf("  " LINE);

    for (i = 0; i < count; i++) {
        if (s[i].marks > avg) {
            printf("  %-16s  %-22s  %-5d  %.2f\n",
                   s[i].regNo, s[i].name, s[i].age, s[i].marks);
            found++;
        }
    }

    if (found == 0) printf("  (none)\n");
    printf("  " LINE);
    printf("  Above average: %d / %d student(s)\n", found, count);
}