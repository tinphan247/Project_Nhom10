#ifndef _PROJECT_H
#define _PROJECT_H

#include <raylib.h>
#include <iostream>
#include <cstring>
using namespace std;

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
struct Lop
{
	SinhVien* danhsachsv;
	char tenlop[20];
    Lop* next;
};
struct danhsachlop{
    Lop* head;
};
struct hocky
{
	int thutu;
	char ngaybatdau[11];
	char ngayketthuc[11];
	char chonhocky[30];
	hocky* next;
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
void taosv(int &STT, int &MSSV, char ten[], char ho[], char gender[], int &ngay, int &thang, int &nam,long int &cccd);
void themsvvaolop(Lop*& lop, int& STT, int& MSSV, char ten[], char ho[], char gender[], int& ngay, int& thang, int& nam,long int& cccd);
void taonamhoc( listnamhoc& L,namhoc*& N);
void taohocky(hocky*& H, listnamhoc& L);
void themlopmoivaodanhsachcaclop(Lop*& CTT,danhsachlop& DS);
void xemdanhsachcaclop(danhsachlop& DS);

#endif