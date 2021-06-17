#include <ctime>
#include "cautrucDocGia.h"
#include <iostream>
#include <fstream>
#include "local.h"
#include "define.h"
// ---------- Handle DauSach's structure function ------------
int CompareDS(DauSach *a, DauSach *b, int mode) {//mode=0: so sanh theo the loai; else: so sanh theo ten
	if(mode == 0) {
		return strcmp(a->theLoai.c_str(), b->theLoai.c_str());
	}
	return strcmp(a->tenSach.c_str(), b->tenSach.c_str());
}

void SortDS(DanhSachDauSach &dsds) {
	DauSach* temp;
	int mode;
//	mode=0: sort Dau Sach theo the alphabe the loai; else: sort theo alphabe ten sach
	mode=1;//sort theo ten sach truoc
	for (int i = 0; i < dsds.n - 1; i++) {
		for (int j = i + 1; j < dsds.n; j++) {
			if (CompareDS(dsds.dsDauSach[i], dsds.dsDauSach[j], mode)>0) {
				temp = dsds.dsDauSach[i];
				dsds.dsDauSach[i] = dsds.dsDauSach[j];
				dsds.dsDauSach[j] = temp;
			}
		}
	}
	mode=0;//sort theo the loai
	for (int i = 0; i < dsds.n - 1; i++) {
		for (int j = i + 1; j < dsds.n; j++) {
			if (CompareDS(dsds.dsDauSach[i], dsds.dsDauSach[j], mode)>0) {
				temp = dsds.dsDauSach[i];
				dsds.dsDauSach[i] = dsds.dsDauSach[j];
				dsds.dsDauSach[j] = temp;
			}
		}
	}
}

int InsertDauSach(DanhSachDauSach &dsds, DauSach *ds) {
	dsds.n++;
	std::cout<<"\ncheck insert dau sach 1";
	dsds.dsDauSach[dsds.n-1]=ds;
//	SortDS(dsds);//sap xep lai theo thu tu
	std::cout<<"\ncheck insert dau sach 2";
	return 1;
}

int LoadFileDauSach(DanhSachDauSach &ArrDauSach) {
	std::ifstream FileIn;
	FileIn.open("DauSach.txt", ios::in);
	if(FileIn.fail()) {
		return -1;
	}
	int len, i=0;
	string temp;
	FileIn >> len;
	std::cout<<"\ncheck doc du lieu n: "<<len;
	DauSach *dausach;
	while(i<len) {
		dausach = new DauSach;
		FileIn.ignore();
		getline(FileIn, temp);//1
		strcpy(dausach->ISBN, temp.c_str());
		getline(FileIn, dausach->tenSach);//2
		FileIn >> dausach->soTrang;//3
		FileIn.ignore();
		getline(FileIn, dausach->tacGia);//4
		FileIn >> dausach->namXuatBan;//5
		FileIn.ignore();
		getline(FileIn, dausach->theLoai);//6
		FileIn >> dausach->soLuong;//7
		FileIn >> dausach->luotMuon;//8
		std::cout<<"\ncheck dau sach "<<i<<" :"<<dausach->tenSach;
		i+=InsertDauSach(ArrDauSach, dausach);
		std::cout<<"\ncheck insert dau sach 3; i="<<i;
	}
	i-=2;
	std::cout<<"\ncheck doc du lieu i cuoi: "<<i<<" len cuoi="<<len;
	std::cout<<"\ncheck n:"<<ArrDauSach.n;
//	for(int i=0; i<len; i++) {
//		std::cout<<"\ncheck dau sach "<<i<<" :"<<ArrDauSach.dsDauSach[i]->tenSach;
//	}
	FileIn.close();
	return (i==len ? len : 0);
}



bool CheckISBN(DanhSachDauSach dsds, DauSach *ds) {//kiem tra isbn cua dau sach da co tron he thong chua
	for(int i=0; i<dsds.n; i++) {
		if(strcmp(dsds.dsDauSach[i]->ISBN, ds->ISBN)==0) {
			return false;
		}
	}
	return true;
}


void  XoaDauSach(DanhSachDauSach &dsds, int pos) {
//	if(dsds.dsDauSach[l]->luotMuon > 0) 
//		cout <<"Sach da co nguoi muon nen khong the xoa";
//	else {

			// xoa dms cua sach do
//			NodeDanhMucSach *r = dsds.dsDauSach[l]->dms;
//			NodeDanhMucSach *k;
//			while(r != NULL) {
//				k = r->next;
//				delete r;
//				r = k;
//			}
			// cap nhat so sach trong dms
	delete  (dsds.dsDauSach[pos]);
	for(int i = pos; i <dsds.n; i++) 
		dsds.dsDauSach[i] = dsds.dsDauSach[i + 1];
	dsds.n--;
	// thong bao 
	std::cout <<"Da xoa thanh cong. ";
	return;
}

void FreeDSArr(DanhSachDauSach &dsds) {
	while(dsds.n>0) {
		XoaDauSach(dsds, dsds.n-1);
	}
}
int SoLuongDocGia = 0;
// ---------- Nhap Xuat file ------------
int LoadFileTheDocGia(Tree &Root) {
	std::ifstream FileIn;
	FileIn.open("inputDocGia.txt", ios::in);
	if(FileIn.fail()) {
		return -1;
	}
	string tmp;
	int readers = 0, count = 0;
	std::string gender;
	FileIn >> readers;
	std::cout<< "\nreader: "<<readers;

	while(!FileIn.eof() && count<readers) {
		//FileIn.seekg(1, ios::cur);
		DocGia x;
		count++;
		FileIn >> x.MATHE;
		FileIn.ignore();
		getline(FileIn, x.ho);
		getline(FileIn, x.ten);
		getline(FileIn, gender);
		x.phai = (gender == "Nam" ? 0 : 1);
		FileIn >> x.trangthai;
		NodeBST *p=CreateNode(x);
		InsertNode(Root, p);
	}
	FileIn.close();
	return (count == readers ? readers : 1);
}
int readers = LoadFileTheDocGia(CayDocGia);

int getIdDocGia(int reader) {
	std::ifstream FileIn;
	FileIn.open("FileMaDocGia.txt", ios::in);
	if(FileIn.fail()) {
		return -1;
	}
	int id;
	FileIn.seekg(6*(reader-1), ios::beg);
	FileIn >> id;
	FileIn.close();
	return id;
}


int IdCurrentDocGia[13]={0};


int CompareDG(DocGia a, DocGia b, int mode) {//mode=0: sap xep theo ma the, else: sap xep theo ten
	if(mode == 0) {
		return a.MATHE>b.MATHE ? 1 : 0;
	}
	if(strcmp(a.ten.c_str(), b.ten.c_str()) == 0) {
		return strcmp(a.ho.c_str(), b.ho.c_str());
	} else {
		return strcmp(a.ten.c_str(), b.ten.c_str());
	}
	return 0;
}
//Tao mang chua doc gia de sap xep
void CreateDocGiaArr(Tree t, DocGia arr[], int& lenDocGia) {
	if (t == NULL) {
		return;
	} else {
		CreateDocGiaArr(t->pLeft, arr, lenDocGia);
		arr[lenDocGia++] = t->data;
		CreateDocGiaArr(t->pRight, arr, lenDocGia);
	}
}

//Selection-sort doc gia theo ten
void SortDG(DocGia arr[], int lenDocGia, int mode) {
	DocGia temp;
	for (int i = 0; i < lenDocGia - 1; i++) {
		for (int j = i + 1; j < lenDocGia; j++) {
			if (CompareDG(arr[i], arr[j], mode)>0) {
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

