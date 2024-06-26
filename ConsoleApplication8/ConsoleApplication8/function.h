#ifndef FUNCTION_H
#define FUNCTION_H
#include "raylib.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
using namespace std;
struct Date {
    int year;
    int month;
    int day;
    string wDay;
};

struct ListCourses;

struct SinhVien {
    string mssv;
    string ten;
    string ho;
    string gender;
    Date birth;
    string cccd;
    SinhVien* next;
    ListCourses* Lc;
    string ClassName;
};

struct ListSV {
    SinhVien* phead;
    SinhVien* ptail;
};

struct Course {
    string id;
    string courseName;
    string teacherName;
    string ClassName;
    int Credits;
    int maxStudents = 50;
    int academicYear;
    string wDay;
    string session;
    Course* next;
    ListSV* lsv;
};

struct ListCourses {
    Course* head;
    Course* tail;
    int size;
};

struct Class {
    ListSV* ds;
    string ClassName;
    Class* next;
};

struct ListClass {
    Class* head;
};

struct Semester {
    int thutu;
    string Ngaybatdau;
    string Ngayketthuc;
    Semester* next;
    ListCourses* lc;
    string namhoc;
    bool showsemester = false;
};

struct NamHoc {
    string ngaybatdau;
    Semester* Hocky;
    NamHoc* next;
};

struct ListNamHoc {
    NamHoc* phead;
};

struct User {
    string id;
    string pass;
    string ten;
    string ho;
    string gender;
    Date birth;
    string ClassName;
    string academicYear;
    bool staff;
    User* next;
};

struct ListUser {
    User* phead;
    User* ptail;
};
struct docDiem
{
    int No;
    string id;
    string ho;
    string ten;
    double other;
    double midterm;
    double final;
    double total;
};
void DrawButton(Rectangle button, const char* text, bool mouseOverButton);
bool IsValidSchoolYearFormat(const char* input);
void taonamhoc(ListNamHoc& L, NamHoc*& N, const char* thoigiannamhoc);
Semester* taohocky(Semester*& H, ListNamHoc& L);
void InitList(ListCourses* list);
void viewcourse(ListCourses*& List, Course*& courses, int& numRows);
Course* InputCourse(string id, string CourseName, string ClassName, string GVName, int AcademicYear, int Credits, string wDay, string Session);
void ShowInputCoursePage(string& id, string& CourseName, string& ClassName, string& GVName, int& AcademicYear, int& Credits, string& wDay, string& Session);
ListSV* addListSV(string path);
void RemoveStudent(ListSV* studentList, int index);
void DisplayStudentDetails(SinhVien* student, ListSV* studentList, int studentIndex);
void DrawStudentListFromData(ListSV* studentList, int numRows);
ListUser* addListUser(const string& path);
bool IsEmpty(const char* str);
bool CheckLogin(const char* username, const char* password, bool& checkstaff, ListUser*& LU);
void ChangePassword(ListUser* userList, const char* username, const char* password);
void saveListUser(ListUser* LUR, const string& path);
bool Login(ListUser* LUR, char* username, char* password, bool& checkstaff);
void CreateNewSchoolYeabutton(bool& createNewSchoolYearActive, bool& schoolYearInputBoxActive, char* schoolYearInput, ListNamHoc& LNH, NamHoc*& N, Vector2 mousePoint, bool& showError);
void AddStudentsbutton(char* AddsvInput, Rectangle& AddsvInputBox, bool& AddsvInputBoxActive, ListCourses*& LC, float screenWidth, float screenHeight);
User* timnodeuser(ListUser* LUR, string username, string password);
void DisplayProfileInfo(User* user);
void ShowImportCoursePage(string& pathC);
void ImportCourseFile(ListCourses*& List, string path);
void CourseDashboard(int screenWidth, int screenHeight, ListCourses*& LC);
void AddstudentDashboard(int screenWidth, int screenHeight, ListCourses*& LC, Course* cour);
void add1StudentCourse(Course*& cour, SinhVien*& sv);
void createnewstudent(Course* cour, bool& studentSaved);
void RemoveCourse(ListCourses*& List, Course* course);
Course* Find_ID(ListCourses*& List, string id);
void ViewAvailableSignCourses(ListCourses* List, Course* courses, int numRows, ListCourses*& SV);
void DisplayCourseDetails(Course* course, ListCourses*& List_Courses_SV);
void ViewSignCourses(ListCourses* List, Course* courses, int numRows, ListCourses*& SV);
void ShowSignCoursesDetails(ListCourses*& List, Course& course, ListCourses*& SV);
void ViewCourses_SV(Course* courses, int numRows, ListCourses*& SV);
void DrawClassNameInputBox(Rectangle& classNameInputBox, char* classNameInput, Vector2 mousePoint, bool& mouseOnText, bool& classNameBoxActive, float screenWidth, float screenHeight, ListClass*& DS, bool& createClassActive);
void AddNewClassToList(const char* className, ListClass*& DS);
void saveClassesToCSV(ListClass* classList, const char* filename);
void loadClassesFromCSV(ListClass* classList, const char* filename);
void clearClassList(ListClass* classList);
void viewClasses(ListClass* classList, ListCourses*& List);
void showClassFunctions(ListCourses*& List, ListClass* classList, Class& selectedClass, bool& deletepress);
void viewListStudent(const Class& selectedClass, int screenWidth, int screenHeight, bool& viewlistsvActive);
void importListStudent(Class& selectedClass, int screenWidth, int screenHeight, bool& importlistsvActive);
void deleteClass(ListClass* classList, const Class& selectedClass);
docDiem* docDiemTuFile(string path, int& count, string& title);
void viewGrade(docDiem* diem, int& numRows, string title);
void deletesemester(Semester*& sm);
void deletelistnamhoc(ListNamHoc& LNH);
void viewcoursescore(ListCourses*& List, Course*& courses, int& numRows, Class& selectedClass);
void deleteListUser(ListUser* list);
void deleteListSV(ListSV* list);
void deleteListCourses(ListCourses* list);
void viewGrade_SV(docDiem* diem, int& numRows, string title, const char* username);
void viewcoursescore_SV(ListCourses*& List, Course*& courses, int& numRows, const char* username);
#endif 
