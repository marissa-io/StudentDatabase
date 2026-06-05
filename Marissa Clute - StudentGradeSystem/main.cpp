#include "StudentGradeSystem.h"

int main()
{
	srand(time(0));

	//array of 20-23 student structs
	Student students[MAX_STUDENTS];

	//2D array of student w/ random assigned marks for assignments
	double grades[MAX_STUDENTS][NUM_ASSIGNMENTS];

	int count = 0; //keeps track of num of current students in system

	loadStudents(students, count); //initial load of students

	generateGrades(grades, count); //initializes grades for existing students

	calculateAverages(grades, students, count);

	int choice;

	do {

		//menu
		cout << "\n===== STUDENT SYSTEM =====\n";
		cout << "1. Display All Student Info\n";
		cout << "2. Update Assignment\n";
		cout << "3. Add Student\n";
		cout << "4. Save to File\n";
		cout << "5. Highlight Student/Assignment\n";
		cout << "6. Exit\n";
		cout << "Enter a choice: ";
		cin >> choice;

		//switch statement
		switch (choice) {
		case 1:
			displayAllStudentInfo(grades, students, count);
			break;
		case 2:
			updateAssignment(grades, students, count);
			break;
		case 3:
			addStudent(students, count, grades);
			break;
		case 4:
			saveStudents(students, count);
			break;
		case 5:
			highlightSearch(grades, students, count);
			break;
		case 6:
			cout << "Goodbye!\n";
			break;
		}
	} while (choice != 6);

	return 0;
}