#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

struct student {
    char name[20];
    char mobile[10];
    int rollno;
    char course[20];
    char branch[20];
};

struct student students[MAX_STUDENTS];
int student_count = 0;

void menu();
void add();
void view();
void search();
void modify();
void delete_record();

void load_records();
void save_records();

int main() {
    printf("\n\n\n\n\n<--:Student Record Management System:-->\n\n\n\n\n\n");
    printf("Press any key to continue.");
    getchar();
    load_records();
    menu();
    return 0;
}

void menu() {
    int choice;
    system("cls");
    printf("<--:MENU:-->\n");
    printf("Enter appropriate number to perform the following task.\n");
    printf("1 : Add Record.\n");
    printf("2 : View Record.\n");
    printf("3 : Search Record.\n");
    printf("4 : Modify Record.\n");
    printf("5 : Delete Record.\n");
    printf("6 : Exit.\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            add();
            break;
        case 2:
            view();
            break;
        case 3:
            search();
            break;
        case 4:
            modify();
            break;
        case 5:
            delete_record();
            break;
        case 6:
            save_records();
            exit(0);
        default:
            printf("Invalid Choice.");
            menu();
    }
}

void load_records() {
    FILE *fp = fopen("record.dat", "rb");
    if (fp == NULL) {
        return;
    }
    while (fread(&students[student_count], sizeof(struct student), 1, fp) == 1) {
        student_count++;
    }
    fclose(fp);
}

void save_records() {
    FILE *fp = fopen("record.dat", "wb");
    if (fp == NULL) {
        printf("Error opening file for saving records.");
        exit(1);
    }
    for (int i = 0; i < student_count; i++) {
        fwrite(&students[i], sizeof(struct student), 1, fp);
    }
    fclose(fp);
}

void add() {
    if (student_count >= MAX_STUDENTS) {
        printf("Student record limit reached.\n");
        printf("Press any key to continue.");
        getchar();
        getchar();
        menu();
        return;
    }

    struct student std;
    system("cls");
    fflush(stdin);
    printf("<--:ADD RECORD:-->\n\n");
    printf("Enter details of student.\n\n");
    printf("Enter Name: ");
    fgets(std.name, sizeof(std.name), stdin);
    std.name[strcspn(std.name, "\n")] = 0;  // Remove newline character

    printf("Enter Mobile Number: ");
    fgets(std.mobile, sizeof(std.mobile), stdin);
    std.mobile[strcspn(std.mobile, "\n")] = 0;

    printf("Enter Roll No: ");
    scanf("%d", &std.rollno);
    getchar();  // consume the newline character

    printf("Enter Course: ");
    fgets(std.course, sizeof(std.course), stdin);
    std.course[strcspn(std.course, "\n")] = 0;

    printf("Enter Branch: ");
    fgets(std.branch, sizeof(std.branch), stdin);
    std.branch[strcspn(std.branch, "\n")] = 0;

    students[student_count] = std;
    student_count++;

    printf("Record added successfully.\n");
    printf("Press any key to continue.");
    getchar();
    menu();
}

void view() {
    system("cls");
    printf("<--:VIEW RECORD:-->\n");
    printf("S.No   Name of Student      Mobile No    Roll No   Course     Branch\n");
    printf("-------------------------------------------------------------------\n");
    for (int i = 0; i < student_count; i++) {
        struct student std = students[i];
        printf("%-7d%-22s%-12s%-9d%-12s%-12s\n", i + 1, std.name, std.mobile, std.rollno, std.course, std.branch);
    }
    printf("\nPress any key to continue.");
    getchar();
    getchar();
    menu();
}

void search() {
    char stname[20];
    system("cls");
    fflush(stdin);
    printf("<--:SEARCH RECORD:-->\n");
    printf("Enter name of student: ");
    fgets(stname, sizeof(stname), stdin);
    stname[strcspn(stname, "\n")] = 0;

    for (int i = 0; i < student_count; i++) {
        if (strcmp(stname, students[i].name) == 0) {
            struct student std = students[i];
            printf("Name: %s\n", std.name);
            printf("Mobile Number: %s\n", std.mobile);
            printf("Roll No: %d\n", std.rollno);
            printf("Course: %s\n", std.course);
            printf("Branch: %s\n", std.branch);
            break;
        }
    }
    printf("\nPress any key to continue.");
    getchar();
    menu();
}

void modify() {
    char stname[20];
    system("cls");
    fflush(stdin);
    printf("<--:MODIFY RECORD:-->\n");
    printf("Enter name of student to modify: ");
    fgets(stname, sizeof(stname), stdin);
    stname[strcspn(stname, "\n")] = 0;

    for (int i = 0; i < student_count; i++) {
        if (strcmp(stname, students[i].name) == 0) {
            struct student *std = &students[i];
            printf("Enter new name: ");
            fgets(std->name, sizeof(std->name), stdin);
            std->name[strcspn(std->name, "\n")] = 0;

            printf("Enter new mobile number: ");
            fgets(std->mobile, sizeof(std->mobile), stdin);
            std->mobile[strcspn(std->mobile, "\n")] = 0;

            printf("Enter new roll no: ");
            scanf("%d", &std->rollno);
            getchar();  // consume the newline character

            printf("Enter new course: ");
            fgets(std->course, sizeof(std->course), stdin);
            std->course[strcspn(std->course, "\n")] = 0;

            printf("Enter new branch: ");
            fgets(std->branch, sizeof(std->branch), stdin);
            std->branch[strcspn(std->branch, "\n")] = 0;

            printf("Record modified successfully.\n");
            break;
        }
    }
    printf("Press any key to continue.");
    getchar();
    menu();
}

void delete_record() {
    char stname[20];
    system("cls");
    fflush(stdin);
    printf("<--:DELETE RECORD:-->\n");
    printf("Enter name of student to delete record: ");
    fgets(stname, sizeof(stname), stdin);
    stname[strcspn(stname, "\n")] = 0;

    int found = 0;
    for (int i = 0; i < student_count; i++) {
        if (strcmp(stname, students[i].name) == 0) {
            for (int j = i; j < student_count - 1; j++) {
                students[j] = students[j + 1];
            }
            student_count--;
            found = 1;
            printf("Record deleted successfully.\n");
            break;
        }
    }
    if (!found) {
        printf("Record not found.\n");
    }
    printf("Press any key to continue.");
    getchar();
    menu();
}
