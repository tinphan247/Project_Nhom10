#include "project.h"
bool kiemtrangaysinh(int ngay, int thang, int nam)
{
	if (ngay < 1 || ngay > 31 || thang < 1 || thang >12 || nam < 1)
	{
		return false;
	}
	if (thang == 2)
	{
		if ((nam % 4 == 0 && nam % 100 != 0) || nam % 400 == 0)
		{
			if (ngay > 29)
			{
				return false;
			}
		}
		else
		{
			if (ngay > 28)
			{
				return false;
			}
		}
	}
	else if (thang == 4 || thang == 6 || thang == 9 || thang == 11)
	{
		if (ngay > 30)
		{
			return false;
		}
	}
	else
	{
		if (ngay > 31)
		{
			return false;
		}
	}
	return true;
}
void taosv(int &STT, int &MSSV, char ten[], char ho[], char gender[], int &ngay, int &thang, int &nam,long int &cccd)
{
    cout << "Nhap vao so thu tu:";
    cin >> STT;
	cin.ignore();
    cout << "Nhap vao ho cua sinh vien:";
	cin.getline(ho, 10);
    cout << "Nhap vao ten cua sinh vien:";
    cin.getline(ten,30);
    cout << "Nhap vao mssv:";
    cin >> MSSV;
    do
    {
		cin.ignore();
        cout << "Nhap vao gioi tinh sinh vien (Nam/Nu):";
        cin.getline(gender,5);
    } while (strcmp(gender,"Nam")!=0 && strcmp(gender, "Nu") != 0&&strcmp(gender, "nam") != 0 && strcmp(gender, "nu") != 0);
	do
	{
		cout << "Nhap vao ngay thang nam sinh cua sinh vien:" << endl;
		cout << "Nhap vao ngay:";
		cin >> ngay;
		cout << "Nhap vao thang:";
		cin >> thang;
		cout << "Nhap vao nam:";
		cin >> nam;
		if (kiemtrangaysinh(ngay, thang, nam) == false)
		{
			cout << "Ngay sinh khong hop le,vui long nhap lai" << endl;
		}
	} while (kiemtrangaysinh(ngay, thang, nam) == false);
    cout << "Nhap vao so cccd cua sinh vien:";
    cin >> cccd;
}
void themsvvaolop(Lop*& lop, int& STT, int& MSSV, char ten[], char ho[], char gender[], int& ngay, int& thang, int& nam,long int& cccd)
{
	SinhVien* temp = lop->danhsachsv;
	if (temp == nullptr)
	{
		lop->danhsachsv = new SinhVien;
		temp = lop->danhsachsv;
	}
	else
	{
		while (temp->next != nullptr) 
		{
			temp = temp->next;
		}
		temp->next = new SinhVien;
		temp = temp->next;
	}
	temp->cccd = cccd;
	temp->gender = new char[strlen(gender) + 1];
	strcpy_s(temp->gender, strlen(gender) + 1, gender);
	temp->ho = new char[strlen(ho) + 1];
	strcpy_s(temp->ho, strlen(ho) + 1, ho);
	temp->ten = new char[strlen(ten) + 1];
	strcpy_s(temp->ten, strlen(ten) + 1, ten);
	temp->ngay = ngay;
	temp->thang = thang;
	temp->nam = nam;
	temp->next = nullptr;
	temp->stt = STT;
	temp->mssv = MSSV;
}
void taonamhoc( listnamhoc& L,namhoc*& N)
{
	N = new namhoc();
	cout << "Nhap vao thoi gian hoc(VD:2020-2021):";
		cin>>N->thoigiannamhoc;
		if (L.phead == NULL)
		{
			L.phead = N;
		}
		else 
		{
			namhoc* temp = L.phead;
			while (temp->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = N;
		}
		N->next = NULL;
		N->Hocky = NULL;
}
void taohocky(hocky*& H, listnamhoc& L)
{
	H = new hocky();
	cout << "Chon nam hoc:" << endl;
	namhoc* temp = L.phead;
	while (temp != NULL)
	{
		cout << temp->thoigiannamhoc << endl;
		temp = temp->next;
	}
	cin.ignore(); 
	cin.getline(H->chonhocky, 30);
	cout << "Chon thu tu cua hoc ki(1-3):";
	do
	{
		cin >> H->thutu;
		if (H->thutu < 1 || H->thutu>3)
		{
			cout << "Hoc ky khong hop le,vui long nhap lai" << endl;
		}
	} while (H->thutu < 1 || H->thutu>3);
	cout << "Nhap vao ngay bat dau(VD 01/01/2024):";
	cin >> H->ngaybatdau;
	cout << "Nhap vao ngay ket thuc(VD 01/01/2024):";
	cin >> H->ngayketthuc;
	H->next = NULL;
	temp = L.phead;
	while (temp != NULL)
	{
		if (strcmp(temp->thoigiannamhoc, H->chonhocky) == 0)
		{
			if (temp->Hocky == NULL)
			{
				temp->Hocky = H;
			}
			else
			{
				hocky* temphocky = temp->Hocky;
				while (temphocky != NULL)
				{
					temphocky = temphocky->next;
				}
				temphocky->next = H;
			}
			cout << "Da them 1 hoc ky vao nam hoc " << temp->thoigiannamhoc << endl;
			break;
		}
		temp = temp->next;
	}
}
//Yêu cầu số 9
void themlopmoivaodanhsachcaclop(Lop*& CTT,danhsachlop& DS)
{
	CTT = new Lop();
	cout << "Nhap vao ten lop: ";
	cin >> CTT->tenlop;
	CTT->next = NULL;
	if (DS.head == NULL)
	{
		DS.head = CTT;
	}
	else 
	{
		Lop* temp = DS.head;
		while (temp->next != NULL) 
		{
			temp = temp->next;
		}
		temp->next = CTT;
	}

	cout << "Da them 1 lop moi vao danh sach cac lop" << endl;
}
void xemdanhsachcaclop(danhsachlop& DS)
{
	cout << "Danh sach cac lop:" << endl;
	Lop* temp = DS.head;
	while (temp != NULL)
	{
		cout << temp->tenlop << endl;
		temp = temp->next;
	}
}
void xemdanhsachkhoahoc(ListCourses*& LC)
{
	cout << "Danh sach cac khoa hoc hien tai:" << endl;
	Course* temp = LC->head;
	while (temp != NULL)
	{
		cout << temp->courseName << endl;
		temp = temp->next;
	}
}
//Yeu cau 12
void xoasvkhoikhoahoc(ListCourses*& LC)
{
	char arr[50];
	cout << "Chon khoa hoc muon xoa hoc sinh:" << endl;
	Course* temp = LC->head;
	while (temp != NULL)
	{
		cout << temp->courseName << endl;
	}
	cin.getline(arr, 50);
	temp = LC->head;
	while (temp != NULL)
	{
		if (strcmp(temp->courseName, arr) == 0)
		{
			break;
		}
		temp = temp->next;
	}
	cout << "Chon ten sinh vien muon xoa:" << endl;
	SinhVien* phu = temp->dssv->phead;
	while (phu != NULL)
	{
		cout << phu->ten << endl;
		phu = phu->next;
	}
	char ten[50];
	cin.getline(ten, 50);
	phu = temp->dssv->phead;
	SinhVien* prephu = NULL;
	while (phu != NULL)
	{
		if (strcmp(phu->ten, ten) == 0)
		{
			if (phu == temp->dssv->phead)
			{
				temp->dssv->phead = temp->dssv->phead->next;
				delete phu;
			}
			else
			{
				prephu->next = phu->next;
				delete phu;
			}
			break;
		}
		prephu = phu;
		phu = phu->next;
	}
}
