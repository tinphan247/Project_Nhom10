#include "project.h"
int main()
{
	{
		string  MSSV;
		int ngay, thang, nam;
		string ten, ho, gender,cccd;
		Class* CTT = NULL;
		int menu;
		NamHoc* N;
		Semester* H;
		ListNamHoc L;
		L.phead = NULL;
		ListClass* DS=new ListClass();
		DS->head =NULL;
		do
		{
			cout << "Nhap vao yeu cau muon lam:" << endl;
			cout << "(1):khoi tao 1 nam hoc moi" << endl;
			cout << "(2):Chon 1 nam hoc roi tao 1 hco ki moi trong nam hoc do" << endl;
			cout << "(3):Them 1 lop moi vao danh sach cac lop" << endl;
			cout << "(4):Xem danh sach cac lop" << endl;
			cout << "(5):Them 1 sinh vien vao lop" << endl;
			cin >> menu;
			if (menu == 1)
			{
				taonamhoc(L, N);
			}
			else if (menu == 2)
			{
				taohocky(H, L);
			}
			else if (menu == 3)
			{
				themlopmoivaodanhsachcaclop(CTT, DS);
			}
			else if (menu == 4)
			{
				xemdanhsachcaclop(DS);
			}
			else if (menu == 5)
			{
				if (DS->head != NULL)
				{
					taosv( MSSV, ten, ho, gender, ngay, thang, nam, cccd);
					themsvvaolop(CTT, MSSV, ten, ho, gender, ngay, thang, nam, cccd);
					cout << "Thong tin hoc sinh trong lop " << CTT->ClassName << ":" << endl;
					cout << "Ho va ten:" << CTT->ds->phead->ho << " " << CTT->ds->phead->ten << endl;
					cout << "So can cuoc cong dan:" << CTT->ds->phead->cccd << endl;
					cout << "Ngay sinh:" << CTT->ds->phead->birth.day << "/" << CTT->ds->phead->birth.month << "/" << CTT->ds->phead->birth.year << endl;
				}
				else
				{
					cout << "Khong co lop de them sinh vien" << endl;
				}
			}
		} while (menu != 0);
	}
}
