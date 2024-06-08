#ifndef _PROJECT_H
#define _PROJECT_H
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include<fstream>
using namespace std;

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


bool kiemtrangaysinh(int ngay, int thang, int nam);
int dayofweek(int day, int month, int year);
void taosv(string &MSSV, string& ten, string& ho, string& gender, int& ngay, int& thang, int& nam, string &cccd);
void themsvvaolop(Class*& lop, string &MSSV, string& ten, string &ho, string& gender, int& ngay, int& thang, int& nam, string& cccd);
void taonamhoc(ListNamHoc& L, NamHoc*& N);
void taohocky(Semester*& H, ListNamHoc& L);
void themlopmoivaodanhsachcaclop(Class*& CTT,ListClass*& DS);
void xemdanhsachcaclop(ListClass*& DS);
void xemdanhsachkhoahoc(ListCourses*& LC);
void xoasvkhoikhoahoc(ListCourses*& LC);
//void xembangdiemcua1khoahoc(Student*& st, Course*& c, ListStudent*& lst);
//void xemdanhsachhocvientrongkhoa(Course*& c);
//7
void InitList(ListCourses &list);
Course* InputCourse(string id,string CourseName,string ClassName,string GVName,int AcademicYear,int Credits,string wDay,string Session);
void AddCourse(ListCourses& List,Course* newCourse);
void OutputListCourses(ListCourses List);
//yeu cau8 
ListSV* addListSV(string path);
#endif
