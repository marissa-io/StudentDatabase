#include "StudentGradeSystem.h"
//implement functions

void loadStudents(Student students[], int& count) {
	//read student data from file
	ifstream inFile("students.txt");

	bool endOfFile = false;
	//load up to MAX_STUDENTS 
	while (count < MAX_STUDENTS && !endOfFile) { //before when i used !eof(), it was giving me an extra row
		inFile >> students[count].firstName;	//with random long numbers, so I had to find a way to fix that.
		inFile >> students[count].lastName;
		inFile >> students[count].id;
		inFile >> students[count].grade;

		//update count
		count++;

		//I was trying to find a way to control the loop without using break
		if (inFile.eof()) {
			endOfFile = true;
		}
	}
	inFile.close();
	//file format: FirstName LastName ID 0
}

void generateGrades(double grades[][NUM_ASSIGNMENTS], int count) {

	for (int i = 0; i < count; i++) {	//loop for every student
		for (int j = 0; j < NUM_ASSIGNMENTS; j++) { //loop for each assignment
			grades[i][j] = rand() % 41 + 60; //assign random grades 60-100 to each student.
		}
	}
}
void calculateAverages(double grades[][NUM_ASSIGNMENTS], Student students[], int count) {
	//sum 5 assignment grades

	for (int i = 0; i < count; i++) {
		double sum = 0;

		for (int j = 0; j < NUM_ASSIGNMENTS; j++) {
			sum += grades[i][j];
		}
		//compute average and store in struct
		students[i].grade = sum / NUM_ASSIGNMENTS;
	}
}


void displayAllStudentInfo(double grades[][NUM_ASSIGNMENTS], Student students[], int count) {
	//display one table
	cout << "\n===== ALL STUDENT RECORDS =====\n";
	cout << "\033[31mID\tFname     \tLname     \tA1\tA2\tA3\tA4\tA5\tAVG\n\033[0m";
	//include ID Fname Lname A1 A2 A3 A4 A5 AVG
	for (int i = 0; i < count; i++) {
		cout << students[i].id << "\t"
			<< students[i].firstName << "     \t"
			<< students[i].lastName << "     \t";
		for (int j = 0; j < NUM_ASSIGNMENTS; j++) {
			cout << grades[i][j] << "\t";
		}
		cout << students[i].grade << endl;
	}

	cout << count << " students loaded.\n\n";
}

void updateAssignment(double grades[][NUM_ASSIGNMENTS], Student students[], int count) {
	//ask for student ID
	int studentID;
	int assignment;
	double newGrade;

	cout << "Enter student ID: ";
	cin >> studentID;
	//ask for assignment number
	cout << "Enter assignment (1-5): ";
	cin >> assignment;
	//ask for new grade
	cout << "Enter new grade: ";
	cin >> newGrade;

	for (int i = 0; i < count; i++) {
		if (students[i].id == studentID) {
			grades[i][assignment - 1] = newGrade;
		}

	}
	//recalculate average
	calculateAverages(grades, students, count);
	//display all student info to verify change
	displayAllStudentInfo(grades, students, count);
}

void addStudent(Student students[], int& count, double grades[][NUM_ASSIGNMENTS]) {
	if (count < MAX_STUDENTS) {

		cout << "Enter First Name: ";
		cin >> students[count].firstName;

		cout << "Enter Last Name: ";
		cin >> students[count].lastName;

		cout << "Enter ID: ";
		cin >> students[count].id;
	}

	for (int i = 0; i < NUM_ASSIGNMENTS; i++) {
		grades[count][i] = rand() % 41 + 60;
	}
	count++;
	cout << "Student added!\n";

	calculateAverages(grades, students, count);
	displayAllStudentInfo(grades, students, count);

}

void saveStudents(Student students[], int count) {

	ofstream outFile("students.txt");
	for (int i = 0; i < count; i++) {
		outFile << students[i].firstName << " "
			<< students[i].lastName << " "
			<< students[i].id << " "
			<< students[i].grade << endl;
	}
	outFile.close();
	cout << "Data saved.\n";
}

void highlightSearch(double grades[][NUM_ASSIGNMENTS], Student students[], int count) {
	int choice;
	int studentID;
	int assignment;

	cout << "\nHighlights Options:\n";
	cout << "1. Highlight Student (Row)\n";
	cout << "2. Highlight Assignment (Column)\n";
	cout << "Enter choice: ";
	cin >> choice;

	if (choice == 1) {
		cout << "Enter student ID to highlight: ";
		cin >> studentID;
	}
	else if (choice == 2) {
		cout << "Enter assignment number to highlight (1-5): ";
		cin >> assignment;
	}
		cout << "\n===== ALL STUDENT RECORDS =====\n";
		cout << "\033[31mID\tFname     \tLname     \tA1\tA2\tA3\tA4\tA5\tAVG\n\033[0m";
		//include ID Fname Lname A1 A2 A3 A4 A5 AVG
		for (int i = 0; i < count; i++) {

			bool highlightedRow = false;

			if (choice == 1 && students[i].id == studentID) {
				highlightedRow = true;
			}
			if (highlightedRow) {
				cout << "\033[33m";
			}
			cout << students[i].id << "\t"
				<< students[i].firstName << "     \t"
				<< students[i].lastName << "     \t";


			for (int j = 0; j < NUM_ASSIGNMENTS; j++)
			{
				if (choice == 2 && j == assignment - 1) {

					cout << "\033[33m" << grades[i][j] << "\033[0m\t";
				}
				else {
					cout << grades[i][j] << "\t";
				}
			}
			cout << students[i].grade << endl;

			if (highlightedRow) {
				cout << "\033[0m";
			}
			cout << endl;
		}

}