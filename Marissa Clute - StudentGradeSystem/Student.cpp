#include "Student.h"
#include <fstream>
#include <iostream>

// ================= DISPLAY =================
void displayStudents(Student students[], int count)
{
    cout << "\nID\tLName\t\tFName\t\t";

    for (int j = 0; j < NUM_ASSIGNMENTS; j++)
        cout << "A" << j + 1 << "\t";

    cout << "AVG\tC1\tC2\tC3\n";

    for (int i = 0; i < count; i++)
    {
        cout << students[i].id << "\t"
            << students[i].lastName << "      \t"
            << students[i].firstName << "      \t";

        for (int j = 0; j < NUM_ASSIGNMENTS; j++)
            cout << students[i].assignments[j] << "\t";

        cout << students[i].average << "\t";

        for (int j = 0; j < NUM_COURSES; j++)
            cout << students[i].courses[j] << "\t";

        cout << endl;
    }
}

void loadStudents(Student students[], int& count) {
    ifstream inFile("Students90.txt");


    while (!inFile.eof() && count < STUDENT_MAX) {
        inFile >> students[count].firstName;
        inFile >> students[count].lastName;
        inFile >> students[count].id;

        for (int i = 0; i < NUM_ASSIGNMENTS; i++) {
            inFile >> students[count].assignments[i];
        }
        inFile >> students[count].average;

        for (int i = 0; i < NUM_COURSES; i++) {
            inFile >> students[count].courses[i];
        }

        count++;
    }
    inFile.close();
}

void calculateAverage(Student* s) {
    double total = 0;
    for (int i = 0; i < NUM_ASSIGNMENTS; i++) {
        total += s->assignments[i];
    }

    s->average = total / NUM_ASSIGNMENTS;
}

void calculateAllAverages(Student students[], int count) {
    for (int i = 0; i < count; i++) {
        calculateAverage(students);
    }

}


void searchByCourse(Student students[], int count) {
    string course;

    cout << "Enter Course: ";
    cin >> course;

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < NUM_COURSES; j++) {

            if (students[i].courses[j] == course) {
                cout << students[i].id << " "
                    << students[i].firstName << " "
                    << students[i].lastName << endl;
            }

        }
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

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < NUM_ASSIGNMENTS; j++) {
            calculateAllAverages(students, count);
            if (students[i].average < lowestAverage) {
                hardestAssignment = j + 1;
                lowestAverage = students[i].average;
            }
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
    if (count < STUDENT_MAX) {

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
            cout << students[i].id << students[i].firstName << students[i].lastName << endl;
        }
    }
}