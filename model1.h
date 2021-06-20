#pragma once
#include <ctime>
#include "cautrucDocGia.h"
#include <iostream>
#include <fstream>
#include "local.h"
#include "define.h"
using namespace std;
// ---------- Handle DanhMucSach's structure function ------------
void InitListDMS(ListDMS *&listDMS) {
	listDMS = new ListDMS;
	listDMS->pFirst = NULL;
}

NodeDMS *CreateNodeDMS(danhMucSach *dms) {
    NodeDMS *pNode=new NodeDMS;
	pNode->data=*dms;
    pNode->next=NULL;
    return pNode;
}

void InsertLastDMS(ListDMS *&listDMS, danhMucSach *dms) {
    NodeDMS *pNode=CreateNodeDMS(dms);
    if(listDMS->pFirst==NULL) {
        listDMS->pFirst=pNode;
    } else {
        NodeDMS *pTmp=listDMS->pFirst;
         
        while(pTmp->next!=NULL) {
            pTmp=pTmp->next;
        }
        pTmp->next=pNode;
//	cout<<"\ncheck insert du lieu danh muc :"<<pNode->data.MaSach<<" tt:"<<pNode->data.TrangThai<<" vitri:"<<pNode->data.ViTri;
    }
}

int LoadFileDanhMucSach(DanhSachDauSach &ArrDauSach) {
	std::ifstream FileIn;
	FileIn.open("DanhMucSach.txt", ios::in);
	if(FileIn.fail()) {
		return -1;
	}
	int temp=0, i=0, n, lenDms, trangthai;
	danhMucSach *dms;
	ListDMS* listDMS;
	FileIn >> temp;
	n=ArrDauSach.n;
	while(!FileIn.eof() && i<n) {
		listDMS=new ListDMS;
		InitListDMS(listDMS);
		lenDms=ArrDauSach.dsDauSach[i]->soLuong;
		if(i==0)
			FileIn.ignore();
		for(int j=0; j<lenDms; j++) {
			string vitri, masach;
			dms = new danhMucSach;
			getline(FileIn, masach);
			FileIn >> trangthai;
			FileIn.ignore();
			getline(FileIn, vitri);
			strcpy(dms->MaSach, masach.c_str());
			dms->TrangThai=trangthai;
			dms->ViTri=vitri;
			InsertLastDMS(listDMS, dms);
		}
		ArrDauSach.dsDauSach[i]->listDMS=listDMS;
		i++;
	}
	FileIn.close();
	return i==n?i:1;
}

NodeDMS *GetNodeDmsById(ListDMS *listDMS, int Id) {
	NodeDMS *pNode=listDMS->pFirst;
	for(int i=140; i<=Id; i++) {
		if(i==Id) {
			return pNode;
		}
		pNode=pNode->next;
	}
}
ListDMS* CreateListDMS(char ISBN[], string vitri, int n) {
	ListDMS *listDMS;
	InitListDMS(listDMS);
	std::cout<<"\ncheck init listdms";
	danhMucSach *dms;
	std::cout<<"\ncheck dms";
	char buffer[33];
	char MaSach[10];
	int index;
	std::cout<<"\ncheck n: "<<n;
	std::cout<<"\ncheck khoi tao creat dms";
	for(int i=1; i<=n; i++) {
		std::cout<<"\ncheck 1.0";
		dms = new danhMucSach;
		dms->ViTri=vitri;
		std::cout<<"\ncheck 1.1";
		itoa(i, buffer, 10);
		strcpy(MaSach, ISBN);
		strcat(MaSach, "_");
		std::cout<<"\ncheck 1.2";
		strcat(MaSach, buffer);
		strcpy(dms->MaSach, MaSach);
		std::cout<<"\ncheck 1.3";
		dms->TrangThai=0;
		std::cout<<"\ncheck tao data dms; ma sach: "<<MaSach;
		InsertLastDMS(listDMS, dms);
	}
	std::cout<<"\ncheck 2";
	return listDMS;
}

int deleteNodeDMS(DauSach *dauSach, NodeDMS *pDel) {
	if(dauSach->listDMS->pFirst==NULL) {
		return -1;
	}
	if(strcmp(pDel->data.MaSach, dauSach->listDMS->pFirst->data.MaSach)==0) {
		dauSach->listDMS->pFirst=dauSach->listDMS->pFirst->next;
		delete pDel;
		return 0;
	}
	NodeDMS *pNode=dauSach->listDMS->pFirst;
	while(strcmp(pDel->data.MaSach, pNode->next->data.MaSach)!=0) {
		pNode=pNode->next;
	}
	pNode->next=pDel->next;
	delete pDel;
	dauSach->soLuong--;
	std::cout<<"\ncheck xoa node dms; So Luong sau xoa: "<<dauSach->soLuong;
	return 0;
	
}
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
	dsds.dsDauSach[dsds.n-1]=ds;
//	SortDS(dsds);//sap xep lai theo thu tu
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
		i+=InsertDauSach(ArrDauSach, dausach);
	}
	i-=2;
	std::cout<<"\ncheck doc du lieu i cuoi: "<<i<<" len cuoi="<<len;
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

