#ifndef _PROJECT_H
#define _PROJECT_H

#include <iostream>
#include <cstring>
using namespace std;
struct Date {
	int year;
	int month;
	int day;
	string wDay;
};
struct SinhVien
{
	int stt;
	int mssv;
	char* ten;
	char* ho;
	char* gender;
	int ngay, thang, nam;
	long int cccd;
	SinhVien* next;
};
struct danhsachsv
{
	SinhVien* phead;
	SinhVien* ptail;
};
struct Lop
{
	danhsachsv* ds;
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
	danhsachsv* dssv;
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
void taosv(int& STT, int& MSSV, char ten[], char ho[], char gender[], int& ngay, int& thang, int& nam, long int& cccd);
void themsvvaolop(Lop*& lop, int& STT, int& MSSV, char ten[], char ho[], char gender[], int& ngay, int& thang, int& nam, long int& cccd);
void taonamhoc(listnamhoc& L, namhoc*& N);
void taohocky(hocky*& H, listnamhoc& L);
void themlopmoivaodanhsachcaclop(Lop*& CTT, danhsachcaclop*& DS);
void xemdanhsachcaclop(danhsachcaclop*& DS);
void xemdanhsachkhoahoc(ListCourses*& LC);
void xoasvkhoikhoahoc(ListCourses*& LC);
void xembangdiemcua1khoahoc(Student*& st, Course*& c, ListStudent*& lst);
void xemdanhsachhocvientrongkhoa(Course*& c);
#endif
