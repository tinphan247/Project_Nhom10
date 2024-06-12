#ifndef function_h
#define function_h
#include "raylib.h"
#include <iostream>
#include <cstring>
#include<fstream>
#include <string>
using namespace std;

// Hàm kiểm tra nếu chuỗi rỗng
bool IsEmpty(const char* str);

// Hàm kiểm tra thông tin đăng nhập
bool CheckLogin(const char* username, const char* password);
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
	int maxStudents = 50;
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
void ShowInputCoursePage(string& id, string& CourseName, string& ClassName, string& GVName, int& AcademicYear, int& Credits, string& wDay, string& Session);
ListSV* addListSV(string path);
void DrawSVTable(const SinhVien* sv, int numRows);
void ShowStudentListWindow(ListSV* svList);
void DrawStudentListFromData( ListSV* studentList, int numRows);
#endif // FUNCTION_H
