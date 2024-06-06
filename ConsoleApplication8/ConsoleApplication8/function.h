#ifndef function_h
#define function_h
#include "raylib.h"
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

// Hàm kiểm tra nếu chuỗi rỗng
bool IsEmpty(const char* str);

// Hàm kiểm tra thông tin đăng nhập
bool CheckLogin(const char* username, const char* password);


#include <string>
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
	char courseName[50];
	string teacherName;
	int credits;
	int maxStudents = 50;
	int numberRegistered = 0;
	int academicYear;
	string wDay;
	string session[2];
	Course* next;
	Date startDate, endDate;
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
void taosv(string& MSSV, string& ten, string& ho, string& gender, int& ngay, int& thang, int& nam, string& cccd);
void themsvvaolop(Class*& lop, string& MSSV, string& ten, string& ho, string& gender, int& ngay, int& thang, int& nam, string& cccd);
void taonamhoc(ListNamHoc& L, NamHoc*& N, const char* thoigiannamhoc);
void taohocky(Semester*& H, ListNamHoc& L);
void themlopmoivaodanhsachcaclop(Class*& CTT, ListClass*& DS);
void xemdanhsachcaclop(ListClass*& DS);
void xemdanhsachkhoahoc(ListCourses*& LC);
void xoasvkhoikhoahoc(ListCourses*& LC);
void DrawNumbers(NamHoc*& H, ListNamHoc& L);
#endif // FUNCTION_H
