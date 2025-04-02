#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for student data  using LinkedList
typedef struct Student {
    int id;
    char name[50];
    float marks;
    struct Student* next;
} Student;

// Function to create a new student node
Student* createStudent(int id, char name[], float marks) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    if (newStudent == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    newStudent->id = id;
    strcpy(newStudent->name, name);
    newStudent->marks = marks;
    newStudent->next = NULL;
    return newStudent;
}

// Function to insert a student at the end of the list
void insertStudent(Student** head, int id, char name[], float marks) {
    Student* newStudent = createStudent(id, name, marks);
    if (*head == NULL) {
        *head = newStudent;
        return;
    }
    Student* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newStudent;
}

// Function to display all student records
void displayStudents(Student* head) {
    if (head == NULL) {
        printf("No student records found!\n");
        return;
    }
    printf("\nStudent Records:\n");
    printf("-------------------------\n");
    while (head != NULL) {
        printf("ID: %d | Name: %s | Marks: %.2f\n", head->id, head->name, head->marks);
        head = head->next;
    }
}

// Function to delete a student by ID
void deleteStudent(Student** head, int id) {
    Student* temp = *head;
    Student* prev = NULL;

    if (temp != NULL && temp->id == id) {
        *head = temp->next;
        free(temp);
        printf("Student with ID %d deleted successfully.\n", id);
        return;
    }

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Student with ID %d not found!\n", id);
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("Student with ID %d deleted successfully.\n", id);
}

// Function to free the entire linked list
void freeMemory(Student** head) {
    Student* temp = *head;
    while (temp != NULL) {
        Student* next = temp->next;
        free(temp);
        temp = next;
    }
    *head = NULL;
}

int main() {
    Student* head = NULL;

    insertStudent(&head, 101, "Alice", 85.5);
    insertStudent(&head, 102, "Bob", 78.0);
    insertStudent(&head, 103, "Charlie", 92.3);
    insertStudent(&head, 104,"Bently",75.4);
    insertStudent(&head, 105,"kawasaki",75.5);
    insertStudent(&head, 106,"mbane",75.6);
    insertStudent(&head, 107,"Ben",75.7);

    displayStudents(head);

    printf("\nDeleting student with ID 102...\n");
    deleteStudent(&head, 102);
    deleteStudent(&head, 103);

    displayStudents(head);

    freeMemory(&head);  // Free allocated memory before exiting
    return 0;
}
