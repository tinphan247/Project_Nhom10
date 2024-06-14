#ifndef function_h
#define function_h
#include "raylib.h"
#include <iostream>
#include <cstring>
#include<fstream>
#include <string>
using namespace std;

//// Hàm kiểm tra nếu chuỗi rỗng
//bool IsEmpty(const char* str);
//
//// Hàm kiểm tra thông tin đăng nhập
//bool CheckLogin(const char* username, const char* password);
struct Date {
	int year;
	int month;
	int day;
	string wDay;
};
struct Course
{
	string id;
	string courseName;
	string teacherName;
	string ClassName;
	int Credits;
	int maxStudents;
	int academicYear;
	string wDay;
	string session;
	Course* next;
};
struct 	ListCourses

{
	Course* head;
	Course* tail;
	int size;
};
struct SinhVien
{
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
struct ListSV
{
	SinhVien* phead;
	SinhVien* ptail;
};
struct Class
{
	ListSV* ds;
	string ClassName;
	Class* next;
};
struct ListClass
{
	Class* head;
};
struct Semester
{
	int thutu;
	string Ngaybatdau;
	string Ngayketthuc;
	Semester* next;
	ListCourses* lc;
};
struct NamHoc
{
	string ngaybatdau;
	Semester* Hocky;
	NamHoc* next;
};
struct ListNamHoc
{
	NamHoc* phead;
};
struct User
{
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
struct ListUser
{
	User* phead;
	User* ptail;
};
struct Grade {
	string subject;
	float score;
	Grade* next;
};
struct StudentGrades {
	string mssv;
	Grade* grades;
	StudentGrades* next;
};
bool IsEmpty(const char* str);
ListUser* addListUser(const string& path);
bool CheckLogin(const char* username, const char* password, bool& checkstaff, ListUser*& LU);
void DrawButton(Rectangle button, const char* text, bool mouseOverButton);
bool kiemtrangaysinh(int ngay, int thang, int nam);
void taosv(string& MSSV, string& ten, string& ho, string& gender, int& ngay, int& thang, int& nam, string& cccd);
void themsvvaolop(Class*& lop, string& MSSV, string& ten, string& ho, string& gender, int& ngay, int& thang, int& nam, string& cccd);
void taonamhoc(ListNamHoc& L, NamHoc*& N, const char* thoigiannamhoc);
void taohocky(Semester*& H, ListNamHoc& L);
void themlopmoivaodanhsachcaclop(Class*& CTT, ListClass*& DS);
void xemdanhsachcaclop(ListClass*& DS);
void xemdanhsachkhoahoc(ListCourses*& LC);
void xoasvkhoikhoahoc(ListCourses*& LC);
void DrawNumbers(NamHoc*& H, ListNamHoc& L);
void InitList(ListCourses& list);
void AddCourse(ListCourses& List, Course* newCourse);
void DrawCourseTable(const Course* courses, int numRows);
Course* InputCourse(string id, string CourseName, string ClassName, string GVName, int AcademicYear, int Credits, string wDay, string Session);
void ImportCourseFile(ListCourses& List, string path);
void ShowInputCoursePage(string& id, string& CourseName, string& ClassName, string& GVName, int& AcademicYear, int& Credits, string& wDay, string& Session);
ListSV* addListSV(string path);
void saveListUser(ListUser* LUR, const string& path);
void ChangePassword(ListUser* userList, const char* username, const char* password);
void DrawSVTable(const SinhVien* sv, int numRows);
void ShowStudentListWindow(ListSV* svList);
void DrawStudentListFromData(ListSV* studentList, int numRows);
//void DrawStudentListFromData(ListSV* studentList, int numRows, StudentGrades* studentGradesList);
void DrawStudentGrades(const StudentGrades* studentGrades);

void InputCourseScreen(ListCourses& LC);
void ImportCourse(const char* fileName);
void DrawCourseDashBoard(ListCourses& LC);
#endif // FUNCTION_H
