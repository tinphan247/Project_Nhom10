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
void DrawButton(Rectangle button, const char* text, bool mouseOverButton);
bool kiemtrangaysinh(int ngay, int thang, int nam);
void taosv(string& MSSV, string& ten, string& ho, string& gender, int& ngay, int& thang, int& nam, string& cccd);
void themsvvaolop(Class*& lop, string& MSSV, string& ten, string& ho, string& gender, int& ngay, int& thang, int& nam, string& cccd);
bool IsValidSchoolYearFormat(const char* input);
void taonamhoc(ListNamHoc& L, NamHoc*& N, const char* thoigiannamhoc);
Semester* taohocky(Semester*& H, ListNamHoc& L);
void themlopmoivaodanhsachcaclop(Class*& CTT, ListClass*& DS);
void xemdanhsachcaclop(ListClass*& DS);
void xemdanhsachkhoahoc(ListCourses*& LC);
void xoasvkhoikhoahoc(ListCourses*& LC);
void DrawNumbers(NamHoc*& H, ListNamHoc& L);
void InitList(ListCourses* list);
void AddCourse(ListCourses& List, Course* newCourse);
void viewcourse(ListCourses*& List, Course*& courses, int& numRows);
Course* InputCourse(string id, string CourseName, string ClassName, string GVName, int AcademicYear, int Credits, string wDay, string Session);
void ShowInputCoursePage(string& id, string& CourseName, string& ClassName, string& GVName, int &AcademicYear, int& Credits, string& wDay, string& Session);
ListSV* addListSV(string path);
void DrawSVTable(const SinhVien* sv, int numRows);
void ShowStudentListWindow(ListSV* svList);
void DrawStudentListFromData(ListSV* studentList, int numRows);
ListUser* addListUser(const string& path);
bool IsEmpty(const char* str);
bool CheckLogin(const char* username, const char* password, bool& checkstaff, ListUser*& LU);
void ChangePassword(ListUser* userList, const char* username, const char* password);
void saveListUser(ListUser* LUR, const string& path);
bool Login(ListUser* LUR, char* username, char* password, bool& checkstaff);
void CreateNewSchoolYeabutton(bool& createNewSchoolYearActive, bool& schoolYearInputBoxActive, char* schoolYearInput, ListNamHoc& LNH, NamHoc*& N, Vector2 mousePoint, bool& showError);
void AddStudentsbutton(char* AddsvInput, Rectangle AddsvInputBox, bool& AddsvInputBoxActive, ListCourses*& LC, int screenWidth, int screenHeight);
User* timnodeuser(ListUser* LUR, string username, string password);
void DisplayProfileInfo(User* user);
void ShowImportCoursePage(string& pathC);
void ImportCourseFile(ListCourses*& List, string path);
void CourseDashboard(int screenWidth, int screenHeight, ListCourses*& LC);
void AddstudentDashboard(int screenWidth, int screenHeight, ListCourses*& LC, Course* cour);
void add1StudentCourse(Course*& cour, SinhVien*& sv);
void createnewstudent(Course* cour);
void createnewstudent(Course* cour, bool& studentSaved);
void showCourseDetails(ListCourses& List, Course& course);
void RemoveCourse(ListCourses*& List, Course* course);
Course* Find_ID(ListCourses*& List, string id);
void ViewAvailableSignCourses(ListCourses* List, Course* courses, int numRows, ListCourses*& SV);
void DisplayCourseDetails(Course* course, ListCourses*& List_Courses_SV);
void ViewSignCourses(ListCourses* List, Course* courses, int numRows, ListCourses*& SV);
void ShowSignCoursesDetails(ListCourses*& List, Course& course, ListCourses*& SV);
void ViewCourses_SV(Course* courses, int numRows,ListCourses*& SV);
#endif 
