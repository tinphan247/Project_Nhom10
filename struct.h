struct Date {
	int year;
	int month;
	int day;
	string wDay;
};
struct User {
	string id;
	string password;
	string lastName;
	string firstName;
	string className;
	string gender;
	int academicYear;
	bool isStaff;
	Date dateOfBirth;
	User* next;
};
struct Course {
	string id;
	string courseName;
	string teacherName;
	int credits;
	int maxStudents = 50;
	int numberRegistered = 0;
	int academicYear;
	string wDay;
	string session[2];
	Course* next;
};
struct ListCourses {
	Course* head;
	Course* tail;
	Date startDate, endDate;
	int size;
};
struct ListUser {
	User* head;
	User* tail;
	int size;
};
struct CourseMark {
	float otherMark = 0;
	float midtermMark = 0;
	float finalMark = 0;
	float totalMark = 0;
};
struct SemesterMark {
	float GPA = 0;
	float overallGPA = 0;
};
struct Student {
	string studentID;
	string lastName;
	string firstName;
	string gender;
	string socialID;
	Date dateOfBirth;
	int academicYear;
	ListCourses enrolledCourses;
	CourseMark courseMark;
	SemesterMark semesterMark;
	Student* next;
};
struct ListStudent {
	Student* head;
	Student* tail;
	string program;
	string className;
	string year;
	int academicYear;
	int size;
};
struct Semester {
	int semester;
	Date startDate, endDate;
};
struct Class {
	string className;
	fs::path path;
	Class* next;
};
struct ListClasses {
	Class* head;
	Class* tail;
	int size;
};

