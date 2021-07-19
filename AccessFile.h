#pragma once
#include <iostream>
#include <fstream>

//------------------------ Load files --------------------------------
int LoadFileTheDocGia(Tree &Root) {
	std::ifstream FileIn;
	FileIn.open("DocGia.txt", ios::in);
	if(FileIn.fail()) {
		return -1;
	}
	string tmp;
	int readers = 0, count = 0;
	FileIn >> readers;
	while(!FileIn.eof() && count<readers) {
		DocGia x;
		count++;
		FileIn >> x.MATHE;
		FileIn.ignore();
		getline(FileIn, x.ho);
		getline(FileIn, x.ten);
		FileIn >> x.phai;
		FileIn >> x.trangthai;
		x.listMT=CreateListMT();
		x.lichsumuon=0;
		NodeBST *p=CreateNode(x);
		InsertNode(Root, p);
	}
	FileIn.close();
	std::cout<<"\ncheck load file doc gia";
	return (count == readers ? readers : 1);
}

int LoadFileDauSach(ArrPointerDauSach &ArrDauSach) {
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
		std::cout<<"\ncheck luot muon:"<<dausach->luotMuon;
		i+=InsertDauSach(ArrDauSach, dausach);
	}
	FileIn.close();
	std::cout<<"\ncheck load file dau sach";
	return (i==len ? len : 0);
}

int LoadFileDanhMucSach(ArrPointerDauSach &ArrDauSach) {
	std::ifstream FileIn;
	FileIn.open("DanhMucSach.txt", ios::in);
	if(FileIn.fail()) {
		return -1;
	}
	int i=0, n, lenDms, trangthai;
	danhMucSach *dms;
	ListDMS* listDMS;
	n=ArrDauSach.n;
	while(!FileIn.eof() && i<n) {
		listDMS=new ListDMS;
		InitListDMS(listDMS);
		lenDms=ArrDauSach.dsDauSach[i]->soLuong;
//		if(i==0)
//			FileIn.ignore();
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
	std::cout<<"\ncheck load file danh muc";
	return i==n?i:1;
}

int LoadFileMuonTra(Tree &root) {
	std::ifstream FileIn;
	std::cout<<"\ncheck";
	FileIn.open("DanhSachMuonTra.txt", ios::in);
	if(FileIn.fail()) {
		return -1;
	}
	std::cout<<"\ncheck";
	string tmp;
	int readers = 0, count = 0;
	FileIn >> readers;
	string masach;
	int maDocGia, lichsumuon, ngay, thang, nam;
	MuonTra mt;
	NodeBST *pNode;
	ListMT *listMuonTra;
	std::cout<<"\ncheck 1";
	while(!FileIn.eof() && count<readers) {
		FileIn >> maDocGia;
		FileIn >> lichsumuon;
//		listMuonTra = new ListMT;
//		listMuonTra->pFirst = NULL;
		std::cout<<"\ncheck 1.1";
		if(pNode->data.listMT==NULL) {
			std::cout<<"\nchua tao list mt";
		}
		
		pNode=FindNodeBSTById(root, maDocGia);
		for(int i=0; i<lichsumuon; i++) {
			FileIn.ignore();
			getline(FileIn, mt.maSach);
			FileIn >> mt.ngayMuon.ngay >> mt.ngayMuon.thang >> mt.ngayMuon.nam;
			FileIn >> mt.ngayTra.ngay >> mt.ngayTra.thang >> mt.ngayTra.nam;
			FileIn >> mt.trangThai;
			InsertLastListMuonTra(pNode->data.listMT, mt);
		}
		std::cout<<"\ncheck 2";
//		pNode->data.listMT=listMuonTra;
		pNode->data.lichsumuon=lichsumuon;
		count++;
	}
	FileIn.close();
	std::cout<<"\ncheck load file muon tra";
	return (count == readers ? readers : 1);
}


int getIdDocGia(Tree root, int reader) {
	std::ifstream FileIn;
	FileIn.open("FileMaDocGia.txt", ios::in);
	if(FileIn.fail()) {
		return -1;
	}
	int id;
	FileIn.seekg(6*(reader-1), ios::beg);
	FileIn >> id;
	while(IdDocGiaIsUsed(root, id)) {
		FileIn >> id;
	}
	FileIn.close();
	return id;
}

//------------------------ Save files --------------------------------
void SaveFileDauSach(ArrPointerDauSach ArrDauSach) {
	ofstream file;
	file.open("DauSach.txt", ios_base::out);
	file << ArrDauSach.n << endl;
	for(int i = 0; i < ArrDauSach.n; i++) {
		file << ArrDauSach.dsDauSach[i]->ISBN << endl
			 << ArrDauSach.dsDauSach[i]->tenSach << endl
			 << ArrDauSach.dsDauSach[i]->soTrang << endl
			 << ArrDauSach.dsDauSach[i]->tacGia << endl
			 << ArrDauSach.dsDauSach[i]->namXuatBan << endl
			 << ArrDauSach.dsDauSach[i]->theLoai << endl
			 << ArrDauSach.dsDauSach[i]->soLuong << endl
			 << ArrDauSach.dsDauSach[i]->luotMuon << endl;
	}
	file.close();
	std::cout<<"\ncheck luu file ddau sach";
}
void DemDocGia(Tree root, int &k) {
	if(root != NULL) {
		DemDocGia(root->pLeft, k);
		k++;
		DemDocGia(root->pRight, k);
	}
}
void SaveFileDocGia(Tree root) {
	int k = 0;
	ofstream file;
	file.open("DocGia.txt", ios_base::out);
	DemDocGia(root, k);
	file << k << endl;
	const int STACKSIZE = 500;
	NodeBST* Stack[STACKSIZE];
	NodeBST* p = root;
	int sp = -1;
	do {
		while(p!= NULL) {
		Stack[++sp] = p;
		p = p->pLeft;
		}
		if(sp != -1) {
			p = Stack[sp--];
			
			file <<p->data.MATHE << endl 
				<<p->data.ho << endl 
				<<p->data.ten << endl 
				<<p->data.phai << endl 
				<<p->data.trangthai << endl;
			p = p->pRight;
		}
		else break;
	}while(1);
	file.close();
	std::cout<<"\ncheck luu file doc gia";
}

void SaveFileDanhSachMuonTra(Tree root, int nMT) {
	ofstream file;
	file.open("DanhSachMuonTra.txt", ios_base::out);
	file << nMT << endl;
	int sp = -1, lichsumuon;
	const int STACKSIZE = 500;
	NodeBST *Stack[STACKSIZE];
	NodeBST *pNode = root;
	NodeMuonTra *r;
	do {
		while(pNode!=NULL) {
			Stack[++sp] = pNode;
			pNode = pNode->pLeft;
		}
		if(sp != -1){
			pNode = Stack[sp--];
			if(pNode==NULL) {
				std::cout<<"\ndoc gia ko ton tai";
			}
			if(pNode->data.listMT!=NULL && pNode->data.listMT->pFirst!=NULL) {
				file << pNode->data.MATHE << endl 
					<< pNode->data.lichsumuon << endl;
				for(r = pNode->data.listMT->pFirst; r != NULL; r = r->next) {
					file << r->data.maSach << endl
						<< r->data.ngayMuon.ngay <<" " << r->data.ngayMuon.thang <<" " << r->data.ngayMuon.nam << endl
						<< r->data.ngayTra.ngay <<" "<< r->data.ngayTra.thang <<" "<< r->data.ngayTra.nam << endl
						<< r->data.trangThai << endl;
				}
			}
			
			pNode = pNode->pRight;
		}
		else break;
 	} while(1);
	file.close();
	std::cout<<"\ncheck luu file muon tra";
}

void SaveFileDanhMucSach(ArrPointerDauSach ArrDauSach){
	ofstream file;
	file.open("DanhMucSach.txt", ios_base::out);
	int n = ArrDauSach.n;
	ListDMS *listDMS;
	NodeDMS *pNode;
	for(int i = 0; i < ArrDauSach.n; i++) {
		listDMS = ArrDauSach.dsDauSach[i]->listDMS;
		for(pNode=listDMS->pFirst; pNode != NULL; pNode = pNode->next) {
			file <<pNode->data.MaSach << endl
				 <<pNode->data.TrangThai << endl
				 <<pNode->data.ViTri << endl;
		}
	}
	file.close();
	std::cout<<"\ncheck luu file danh muc sach";
}
