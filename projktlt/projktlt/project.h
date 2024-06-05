#ifndef _PROJECT_H
#define _PROJECT_H
#include <filesystem>
#include <iostream>
#include <cstring>
#include <string>
using namespace std;
namespace fs = std::filesystem;
struct Date {
	int year;
	int month;
	int day;
	string wDay;
};
struct SinhVien
{
	string mssv;
	string ten;
	string ho;
	string gender;
	int ngay, thang, nam;
	string cccd;
	SinhVien* next;
};
struct Listsv
{
	SinhVien* phead;
	SinhVien* ptail;
};
struct Lop
{
	Listsv* ds;
	char tenlop[20];
	Lop* next;
};
struct danhsachcaclop 
{
	Lop* head;
};
struct Course
{
	string id;
	char courseName[50];
	string teacherName;
	int credits;
	int maxStudents = 50;
	int numberRegistered = 0;
	int academicYear;
	string wDay;
	string session[2];
	Course* prev;
	Course* next;
	Listsv* dssv;
};
struct ListCourses
{
	Course* head;
	Course* tail;
	Date startDate, endDate;
	int size;
};
struct hocky
{
	int thutu;
	char ngaybatdau[11];
	char ngayketthuc[11];
	char chonhocky[30];
	hocky* next;
	ListCourses* lc;
};

struct namhoc
{
	char thoigiannamhoc[30];
	hocky* Hocky;
	namhoc* next;
};
struct listnamhoc
{
	namhoc* phead;
};


bool kiemtrangaysinh(int ngay, int thang, int nam);
void taosv(string &MSSV, string& ten, string& ho, string& gender, int& ngay, int& thang, int& nam, string &cccd);
void themsvvaolop(Lop*& lop, string &MSSV, string& ten, string &ho, string& gender, int& ngay, int& thang, int& nam, string& cccd);
void taonamhoc(listnamhoc& L, namhoc*& N);
void taohocky(hocky*& H, listnamhoc& L);
void themlopmoivaodanhsachcaclop(Lop*& CTT, danhsachcaclop*& DS);
void xemdanhsachcaclop(danhsachcaclop*& DS);
void xemdanhsachkhoahoc(ListCourses*& LC);
void xoasvkhoikhoahoc(ListCourses*& LC);
//void xembangdiemcua1khoahoc(Student*& st, Course*& c, ListStudent*& lst);
//void xemdanhsachhocvientrongkhoa(Course*& c);
#endif
