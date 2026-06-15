#include "Student.h"
#include <fstream>
#include <iostream>
#include <iomanip>

// ================= DISPLAY =================
void displayStudents(StudentNode* head)
{
    cout << "\n"
        << setw(8) << "ID"
        << setw(15) << "LName"
        << setw(15) << "FName";

    for (int j = 0; j < NUM_ASSIGNMENTS; j++) {
        cout << setw(6) << ("A" + to_string(j + 1));
    }
    cout << setw(8) << "AVG"
        << setw(10) << "C1"
        << setw(10) << "C2"
        << setw(10) << "C3"
        << endl;

    StudentNode* current = head;
    while (current != nullptr) {
        cout << setw(8) << current->data.id
            << setw(15) << current->data.lastName
            << setw(15) << current->data.firstName;

        for (int j = 0; j < NUM_ASSIGNMENTS; j++) {
            cout << setw(6) << current->data.assignments[j];
        }
        cout << setw(8) << current->data.average;

        for (int j = 0; j < NUM_COURSES; j++) {
            cout << setw(10) << current->data.courses[j];
        }
        cout << endl;

        current = current->next; //move to next node
    }
}

void loadStudents(StudentNode*& head) {
    ifstream file("Students90.txt");
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    Student tempStudent;

    while (file >> tempStudent.firstName >> tempStudent.lastName >> tempStudent.id) {
        for (int j = 0; j < NUM_ASSIGNMENTS; j++) {
            file >> tempStudent.assignments[j];
        }
        file >> tempStudent.average;

        for (int j = 0; j < NUM_COURSES; j++) {
            file >> tempStudent.courses[j];
        }
        StudentNode* newNode = new StudentNode();
        newNode->data = tempStudent;

        newNode->next = head;
        head = newNode;
    }
    file.close();
}

void calculateAverage(Student* s) {
    double total = 0;
    for (int i = 0; i < NUM_ASSIGNMENTS; i++) {
        total += s->assignments[i];
    }

    s->average = total / NUM_ASSIGNMENTS;
}

void calculateAllAverages(StudentNode* head) {

    StudentNode* current = head;
    while (current != nullptr) {
        calculateAverage(&current->data);

        current = current->next;
    }
}


void searchByCourse(StudentNode* head) {
    string course;
    StudentNode* current = head;

    cout << "Enter Course: ";
    cin >> course;

    while (current != nullptr) {

        for (int j = 0; j < NUM_COURSES; j++) {

            if (current->data.courses[j] == course) {
                cout << current->data.id << " "
                    << current->data.firstName << " "
                    << current->data.lastName << endl;
            }
        }
        current = current->next;

    }
}


void showAssignmentAverage(Student students[], int count) {
    for (int i = 0; i < NUM_ASSIGNMENTS; i++) {
        double sum = 0;

        for (int j = 0; j < count; j++) {
            sum += students[j].assignments[i];
        }

        cout << "A" << i + 1 << ": " << sum / count << endl;
    }
}

void showHardestAssignment(Student students[], int count) {
    double lowestAverage = 100;
    int hardestAssignment = 0;

    for (int i = 0; i < NUM_ASSIGNMENTS; i++) {
        double sum = 0;

        for (int j = 0; j < count; j++) {
            sum += students[j].assignments[i];
        }

        double avg = sum / count;

        if (avg < lowestAverage) {
            lowestAverage = avg;
            hardestAssignment = i + 1;
        }
    }
    cout << "Hardest Assignment: A" << hardestAssignment << " (" << lowestAverage << ")\n";

}

void courseEnrollment(Student students[], int count) {
    int comp = 0, math = 0,
        stat = 0, engl = 0, hist = 0,
        biol = 0, csci = 0;

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < NUM_COURSES; j++) {
            if (students[i].courses[j] == "COMP220") {
                comp += 1;
            }
            if (students[i].courses[j] == "MATH102") {
                math += 1;
            }
            if (students[i].courses[j] == "STAT110") {
                stat += 1;
            }
            if (students[i].courses[j] == "ENGL150") {
                engl += 1;
            }
            if (students[i].courses[j] == "HIST210") {
                hist += 1;
            }
            if (students[i].courses[j] == "BIOL120") {
                biol += 1;
            }
            if (students[i].courses[j] == "CSCI101") {
                csci += 1;
            }
        }
    }

    cout << "COMP220: " << comp << endl
        << "MATH102: " << math << endl
        << "STAT110: " << stat << endl
        << "ENGL150: " << engl << endl
        << "HIST210: " << hist << endl
        << "BIOL120: " << biol << endl
        << "CSCI101: " << csci << endl;

}

void sortByAverage(Student students[], int count) {

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (students[j].average > students[i].average) {
                swap(students[i], students[j]);
            }
        }
    }
    displayStudents(students, count);
}


void addStudent(Student students[], int& count) {
    if (count >= STUDENT_MAX) {
        cout << "Student list has reached maximum capacity!\n";
        return;
    }
    cout << "Enter First Name: ";
    cin >> students[count].firstName;

    cout << "Enter Last Name: ";
    cin >> students[count].lastName;

    cout << "Enter ID: ";
    cin >> students[count].id;

    for (int i = 0; i < NUM_ASSIGNMENTS; i++) {
        cout << "Enter A" << i + 1 << " mark: ";
        cin >> students[count].assignments[i];
    }
    for (int i = 0; i < NUM_COURSES; i++) {
        cout << "Enter Course" << i + 1 << ": ";
        cin >> students[count].courses[i];
    }


    calculateAverage(&students[count]);
    count++;
}

void atRiskStudents(Student students[], int count) {
    for (int i = 0; i < count; i++) {

        bool isAtRisk = false;
        for (int j = 0; j < NUM_ASSIGNMENTS; j++) {
            if (students[i].average > 50 && students[i].average < 59 || students[i].assignments[j] <= 50) {
                isAtRisk = true;
            }
        }

        if (isAtRisk) {
            cout << students[i].id << " " << students[i].firstName << " " << students[i].lastName << endl;
        }
    }
}

void saveStudents(Student students[], int count) {
    ofstream outFile("Students90.txt");
    for (int i = 0; i < count; i++) {
        outFile << students[i].firstName << " "
            << students[i].lastName << " "
            << students[i].id << " ";

        for (int j = 0; j < NUM_ASSIGNMENTS; j++) {
            outFile << students[i].assignments[j] << " ";
        }
        outFile << students[i].average << " ";

        for (int j = 0; j < NUM_COURSES; j++) {
            outFile << students[i].courses[j] << " ";
        }
        outFile << endl;
    }
    outFile.close();
    cout << "Data saved.\n";
}