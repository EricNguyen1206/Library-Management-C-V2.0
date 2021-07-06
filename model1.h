//#pragma once
//#include <time.h>
//#include "cautrucDocGia.h"
//#include <iostream>
//#include <fstream>
//#include "local.h"
//#include "define.h"
//#include "string"
//using namespace std;
//// ---------- Handle DanhMucSach's structure function ------------
//void InitListDMS(ListDMS *&listDMS) {
//	listDMS = new ListDMS;
//	listDMS->pFirst = NULL;
//}
//
//NodeDMS *CreateNodeDMS(danhMucSach *dms) {
//    NodeDMS *pNode=new NodeDMS;
//	pNode->data=*dms;
//    pNode->next=NULL;
//    return pNode;
//}
//
//void InsertLastDMS(ListDMS *&listDMS, danhMucSach *dms) {
//    NodeDMS *pNode=CreateNodeDMS(dms);
//    if(listDMS->pFirst==NULL) {
//        listDMS->pFirst=pNode;
//    } else {
//        NodeDMS *pTmp=listDMS->pFirst;
//         
//        while(pTmp->next!=NULL) {
//            pTmp=pTmp->next;
//        }
//        pTmp->next=pNode;
//    }
//}
//
//NodeDMS *GetNodeDmsById(ListDMS *listDMS, int Id) {
//	NodeDMS *pNode=listDMS->pFirst;
//	for(int i=140; i<=Id; i++) {
//		if(i==Id) {
//			return pNode;
//		}
//		pNode=pNode->next;
//	}
//}
//
//ListDMS* CreateListDMS(char ISBN[], string vitri, int n) {
//	ListDMS *listDMS;
//	InitListDMS(listDMS);
//	danhMucSach *dms;
//	char buffer[30];
//	char MaSach[10];
//	int index;
//	for(int i=1; i<=n; i++) {
//		dms = new danhMucSach;
//		dms->ViTri=vitri;
//		itoa(i, buffer, 10);
//		strcpy(MaSach, ISBN);
//		strcat(MaSach, "_");
//		strcat(MaSach, buffer);
//		strcpy(dms->MaSach, MaSach);
//		dms->TrangThai=0;
//		InsertLastDMS(listDMS, dms);
//	}
//	return listDMS;
//}
//
//int deleteNodeDMS(DauSach *dauSach, NodeDMS *pDel) {
//	if(dauSach->listDMS->pFirst==NULL) {
//		return -1;
//	}
//	if(strcmp(pDel->data.MaSach, dauSach->listDMS->pFirst->data.MaSach)==0) {
//		dauSach->listDMS->pFirst=dauSach->listDMS->pFirst->next;
//		delete pDel;
//		return 0;
//	}
//	NodeDMS *pNode=dauSach->listDMS->pFirst;
//	while(strcmp(pDel->data.MaSach, pNode->next->data.MaSach)!=0) {
//		pNode=pNode->next;
//	}
//	pNode->next=pDel->next;
//	delete pDel;
//	dauSach->soLuong--;
//	return 0;
//	
//}
//
//NodeDMS *GetNodeDmsInDauSach(DauSach *dausach, int index) {
//	NodeDMS *pNode=dausach->listDMS->pFirst;
//	for(int i=0; i<index; i++) {
//		pNode=pNode->next;
//	}
//	return pNode;
//}
//
//int GetChuaMuon(DauSach *dausach) {
//	int count =0;
//	NodeDMS *pNode=dausach->listDMS->pFirst;
//	while(pNode) {
//		if(pNode->data.TrangThai==0) {
//			count++;
//		}
//	}
//	return count;
//}
//
//int GetLuotMuon(DauSach *dausach) {
//	int count =0;
//	NodeDMS *pNode=dausach->listDMS->pFirst;
//	while(pNode) {
//		if(pNode->data.TrangThai==1) {
//			count++;
//		}
//	}
//	return count;
//}
//// ---------- Handle DauSach's structure function ------------
//int CompareDS(DauSach *a, DauSach *b, int mode) {//mode=0: so sanh theo the loai; else: so sanh theo ten
//	if(mode == 0) {
//		return strcmp(a->theLoai.c_str(), b->theLoai.c_str());
//	}
//	return strcmp(a->tenSach.c_str(), b->tenSach.c_str());
//}
//
//void SortDS(ArrPointerDauSach &dsds) {
//	DauSach* temp;
//	int mode;
//	mode=0;//sort theo the loai
//	for (int i = 0; i < dsds.n - 1; i++) {
//		for (int j = i + 1; j < dsds.n; j++) {
//			if (CompareDS(dsds.dsDauSach[i], dsds.dsDauSach[j], mode)>0) {
//				temp = dsds.dsDauSach[i];
//				dsds.dsDauSach[i] = dsds.dsDauSach[j];
//				dsds.dsDauSach[j] = temp;
//			} else if(CompareDS(dsds.dsDauSach[i], dsds.dsDauSach[j], mode)==0) {
//				mode=1;
//				if (CompareDS(dsds.dsDauSach[i], dsds.dsDauSach[j], mode)>0) {
//					temp = dsds.dsDauSach[i];
//					dsds.dsDauSach[i] = dsds.dsDauSach[j];
//					dsds.dsDauSach[j] = temp;
//				}
//			}
//			mode=0;
//		}
//	}
//}
//
//int InsertDauSach(ArrPointerDauSach &dsds, DauSach *ds) {
//	if(dsds.n+1<=MAXDAUSACH) {
//		dsds.n++;
//		dsds.dsDauSach[dsds.n-1]=ds;
//		return 1;
//	}
//	return 0;
//}
//
//bool CheckISBN(ArrPointerDauSach dsds, DauSach *ds) {//kiem tra isbn cua dau sach da co tron he thong chua
//	for(int i=0; i<dsds.n; i++) {
//		if(strcmp(dsds.dsDauSach[i]->ISBN, ds->ISBN)==0) {
//			return false;
//		}
//	}
//	return true;
//}
//
//void  XoaDauSach(ArrPointerDauSach &dsds, int pos) {
//	DauSach *pNode=dsds.dsDauSach[pos];
//	NodeDMS *pList;
//	while(pNode->listDMS->pFirst!=NULL) {
//		pList=pNode->listDMS->pFirst;
//		pNode->listDMS->pFirst=pNode->listDMS->pFirst->next;
//		free(pList);
//	}
//	free(pNode);
////	delete  (dsds.dsDauSach[pos]);
//	for(int i = pos; i <dsds.n; i++) {
//		dsds.dsDauSach[i] = dsds.dsDauSach[i + 1];
//	}
//	dsds.n--;
//	return;
//}
//
//void FreeDSArr(ArrPointerDauSach &dsds) {
//	while(dsds.n>0) {
//		XoaDauSach(dsds, dsds.n-1);
//	}
//	delete [] dsds.dsDauSach;
//}
//
//ArrPointerDauSach SearchDauSach(ArrPointerDauSach dsds, string input) {
//	int i, j=-1;
//	ArrPointerDauSach temp;
//	temp.n=0;
//	input.erase(input.length()-1);
//	for(i=0; i<dsds.n; i++) {
//		int search = dsds.dsDauSach[i]->tenSach.find(input);
//		if(search != -1) {
//			temp.dsDauSach[++j] = dsds.dsDauSach[i];
//			temp.n++;
//		} else {
//			std::cout<<"\nKhong tim thay "<<input<<" trong chuoi "<<dsds.dsDauSach[i]->tenSach;
//		}
//	}
//	return temp;
//}
//
//DauSach *SearchDauSachByIsbn(ArrPointerDauSach dsds, char ISBN[]) {
//	int n=dsds.n;
//	for(int i=0; i<n;i++) {
//		if(strcmp(dsds.dsDauSach[i]->ISBN, ISBN)==0) {
//			return dsds.dsDauSach[i];
//		}
//	}
//	return NULL;
//}
//
//DauSach *SearchIsbn(ArrPointerDauSach dsds, char ISBN[]) {
//	int n=dsds.n;
//	for(int i=0; i<n ;i++) {
//		if(strcmp(dsds.dsDauSach[i]->ISBN, ISBN)==0) {
//			return dsds.dsDauSach[i];
//		}
//	}
//}
//
//bool CheckTrungMax(DauSach *ArrDS[], int lenArr, char isbn[]) {
//	for(int i=0; i<lenArr; i++) {
//		if(strcmp(ArrDS[i]->ISBN, isbn)==0) {
//			return false;
//		}
//	}
//	return true;
//}
//
//void GetTopTenDauSach(ArrPointerDauSach dsds, DauSach *ArrDS[]) {
//	int i, j, n=dsds.n;
//	for(i=0; i<10; i++) {
//		DauSach *max = dsds.dsDauSach[0];
//		for(j=0; j<n; j++) {
//			if(max->luotMuon<dsds.dsDauSach[j]->luotMuon && CheckTrungMax(ArrDS, i, dsds.dsDauSach[j]->ISBN)) {
//				max=dsds.dsDauSach[j];
//			}
//		}
//		ArrDS[i]=max;
//	}
//	std::cout<<"\n check top 10";
//}
//
//
//// ---------- Handle MuonTra's structure function ------------
//int GetSoSachMuonDG(DocGia *docgia) {
//	int count=0;
//	NodeMuonTra *pNode=docgia->listMT->pFirst;
//	while(pNode) {
//		if(pNode->data.trangThai==0) {
//			count ++;
//		}
//		pNode=pNode->next;
//	}
//	return count;
//}
//
//NodeMuonTra *CreateNodeMT(MuonTra mt) {
//	NodeMuonTra *pNode = new NodeMuonTra;
//	pNode->data=mt;
//	pNode->next = NULL;
//	return pNode;
//}
//void InsertLastListMuonTra(ListMT *&listMT, MuonTra mt) {
//	NodeMuonTra *pInsert = CreateNodeMT(mt);
//	NodeMuonTra *pNode = listMT->pFirst;
//	if(listMT->pFirst == NULL) {
//		listMT->pFirst = pInsert;
//		return;
//	}
//	while(pNode->next != NULL) {
//		pNode = pNode->next;
//	}
//	pNode->next = pInsert;
//}
//
//int FindIndexDocGiaInArr(DocGia ListDG[], int mathe) {
//	for(int i=0; i<MAXDOCGIA; i++) {
//		if(ListDG[i].MATHE==mathe) {
//			return i;
//		}
//	}
//}
//
//NodeBST *FindNodeBSTById(Tree root, int IdDocGia) {
//	const int STACKSIZE = 500;
//	NodeBST *Stack[STACKSIZE];
//	NodeBST *pNode;
//	pNode=root;
//	int sp = -1; // khoi tao Stack rong
//	do {
//		while (pNode != NULL) {
//			Stack[++sp] = pNode;
//			pNode = pNode->pLeft;
//		}
//		if(sp != -1) {
//			pNode = Stack[sp--];//Pop stack
//			if(pNode->data.MATHE==IdDocGia) {
//				return pNode;
//				break;
//			}
//			pNode = pNode->pRight;
//		} else {
//			std::cout<<"\nko tim thay doc gia:" << IdDocGia;
//			break;
//		}//sp=-1: Stack rong thi dung
//	}while (1);
//}
//
//NodeMuonTra *GetNodeMTById(ListMT *listMT, int index) {
//	NodeMuonTra *pNode=listMT->pFirst;
//	for(int i=0; i<index; i++) {
//		pNode=pNode->next;
//	}
//	return pNode;
//}
//
//void DeleteFirstListMuonTra(ListMT *&listMT) {
//	NodeMuonTra *pNode = listMT->pFirst;
//	listMT->pFirst = listMT->pFirst->next;
//	free(pNode);
//}
//
//void DeleteListMuonTra(ListMT *&listMT) {
//	while(listMT->pFirst!=NULL) {
//		DeleteFirstListMuonTra(listMT);
//	}
//}
//
//
//// ---------- Handle DocGia's structure function ------------
//bool IdDocGiaIsUsed(Tree root, int id) {
//	const int STACKSIZE = 500;
//	NodeBST *Stack[STACKSIZE];
//	NodeBST *pNode;
//	pNode=root;
//	int sp = -1;//Khoi tao Stack rong
//	do {
//		while (pNode != NULL) {
//			Stack[++sp] = pNode;
//			pNode = pNode->pLeft;
//		}
//		if(sp != -1) {
//			pNode = Stack[sp--];//Pop stack
//			if(pNode->data.MATHE==id) {
//				return true;
//			}
//			pNode = pNode->pRight;
//		} else {
//			return false;
//			break;
//		}//sp=-1: Stack rong thi dung
//	}while (1);
//}
//
//int getIdDocGia(Tree root, int reader) {
//	std::ifstream FileIn;
//	FileIn.open("FileMaDocGia.txt", ios::in);
//	if(FileIn.fail()) {
//		return -1;
//	}
//	int id;
//	FileIn.seekg(6*(reader-1), ios::beg);
//	FileIn >> id;
//	while(IdDocGiaIsUsed(root, id)) {
//		FileIn >> id;
//	}
//	FileIn.close();
//	return id;
//}
//
//int CompareDG(DocGia a, DocGia b, int mode) {//mode=0: sap xep theo ma the, else: sap xep theo ten
//	if(mode == 0) {
//		return a.MATHE>b.MATHE ? 1 : 0;
//	}
//	if(strcmp(a.ten.c_str(), b.ten.c_str()) == 0) {
//		return strcmp(a.ho.c_str(), b.ho.c_str());
//	} else {
//		return strcmp(a.ten.c_str(), b.ten.c_str());
//	}
//	return 0;
//}
//
////Tao mang chua doc gia de sap xep
//void CreateDocGiaArr(Tree t, DocGia arr[], int &lenDocGia) {
//	if (t == NULL) {
//		return;
//	} else {
//		CreateDocGiaArr(t->pLeft, arr, lenDocGia);
//		arr[lenDocGia++] = t->data;
//		CreateDocGiaArr(t->pRight, arr, lenDocGia);
//	}
//}
//
////Selection-sort doc gia theo ten
//void SortDG(DocGia arr[], int lenDocGia, int mode) {
//	DocGia temp;
//	for (int i = 0; i < lenDocGia - 1; i++) {
//		for (int j = i + 1; j < lenDocGia; j++) {
//			if (CompareDG(arr[i], arr[j], mode)>0) {
//				temp = arr[i];
//				arr[i] = arr[j];
//				arr[j] = temp;
//			}
//		}
//	}
//}
//
//void SortDGByIndex(DocGia arr[]) {
//	DocGia temp;
//	int dem=0;
//	for(int i=0; i<MAXDOCGIA-1; i++) {
//		for(int j=0; j<MAXDOCGIA; j++) {
//			if(arr[j].MATHE-1000==i) {
//				temp=arr[i];
//				arr[i]=arr[j];
//				arr[j]=temp;
//				std::cout<<"\ndocgia "<<i<<" co ma the la:"<<arr[i].MATHE;
//				dem++;
//				break;
//			}
//		}
//		std::cout<<"||doc gia rac"<<i<<" co ma the rac la:"<<arr[i].MATHE;
//	}
//	std::cout<<"\ncheck sort "<<dem<<" doc gia";
//}
//
//void FreeMemoryBST(Tree root) {
//	if(root!=NULL) {
//		FreeMemoryBST(root->pLeft);
//		DeleteListMuonTra(root->data.listMT);
//		FreeMemoryBST(root->pRight);
//		free(root);
//	}
//}
//
////------------------------ Load files --------------------------------
//int LoadFileTheDocGia(Tree &Root) {
//	std::ifstream FileIn;
//	FileIn.open("DocGia.txt", ios::in);
//	if(FileIn.fail()) {
//		return -1;
//	}
//	string tmp;
//	int readers = 0, count = 0;
//	FileIn >> readers;
//
//	while(!FileIn.eof() && count<readers) {
//		DocGia x;
//		count++;
//		FileIn >> x.MATHE;
//		FileIn.ignore();
//		getline(FileIn, x.ho);
//		getline(FileIn, x.ten);
//		FileIn >> x.phai;
//		FileIn >> x.trangthai;
//		NodeBST *p=CreateNode(x);
//		InsertNode(Root, p);
//	}
//	FileIn.close();
//	std::cout<<"\ncheck load file doc gia";
//	return (count == readers ? readers : 1);
//}
//
//int LoadFileDauSach(ArrPointerDauSach &ArrDauSach) {
//	std::ifstream FileIn;
//	FileIn.open("DauSach.txt", ios::in);
//	if(FileIn.fail()) {
//		return -1;
//	}
//	int len, i=0;
//	string temp;
//	FileIn >> len;
//	DauSach *dausach;
//	while(i<len) {
//		dausach = new DauSach;
//		FileIn.ignore();
//		getline(FileIn, temp);//1
//		strcpy(dausach->ISBN, temp.c_str());
//		getline(FileIn, dausach->tenSach);//2
//		FileIn >> dausach->soTrang;//3
//		FileIn.ignore();
//		getline(FileIn, dausach->tacGia);//4
//		FileIn >> dausach->namXuatBan;//5
//		FileIn.ignore();
//		getline(FileIn, dausach->theLoai);//6
//		FileIn >> dausach->soLuong;//7
//		FileIn >> dausach->luotMuon;//8
//		i+=InsertDauSach(ArrDauSach, dausach);
//	}
//	FileIn.close();
//	std::cout<<"\ncheck load file dau sach";
//	return (i==len ? len : 0);
//}
//
//int LoadFileDanhMucSach(ArrPointerDauSach &ArrDauSach) {
//	std::ifstream FileIn;
//	FileIn.open("DanhMucSach.txt", ios::in);
//	if(FileIn.fail()) {
//		return -1;
//	}
//	int i=0, n, lenDms, trangthai;
//	danhMucSach *dms;
//	ListDMS* listDMS;
//	n=ArrDauSach.n;
//	while(!FileIn.eof() && i<n) {
//		listDMS=new ListDMS;
//		InitListDMS(listDMS);
//		lenDms=ArrDauSach.dsDauSach[i]->soLuong;
//		if(i==0)
//			FileIn.ignore();
//		for(int j=0; j<lenDms; j++) {
//			string vitri, masach;
//			dms = new danhMucSach;
//			getline(FileIn, masach);
//			FileIn >> trangthai;
//			FileIn.ignore();
//			getline(FileIn, vitri);
//			strcpy(dms->MaSach, masach.c_str());
//			dms->TrangThai=trangthai;
//			dms->ViTri=vitri;
//			InsertLastDMS(listDMS, dms);
//		}
//		ArrDauSach.dsDauSach[i]->listDMS=listDMS;
////		ArrDauSach.dsDauSach[i]->luotMuon=GetLuotMuon(ArrDauSach.dsDauSach[i]);
//		i++;
//	}
//	FileIn.close();
//	std::cout<<"\ncheck load file danh muc";
//	return i==n?i:1;
//}
//
//int LoadFileMuonTra(Tree &root) {
//	std::ifstream FileIn;
//	FileIn.open("DanhSachMuonTra.txt", ios::in);
//	if(FileIn.fail()) {
//		return -1;
//	}
//	string tmp;
//	int readers = 0, count = 0;
//	FileIn >> readers;
//	string masach;
//	int maDocGia, lichsumuon, ngay, thang, nam;
//	MuonTra mt;
//	NodeBST *pNode;
//	ListMT *listMuonTra;
//	while(!FileIn.eof() && count<readers) {
//		FileIn >> maDocGia;
//		FileIn >> lichsumuon;
//		listMuonTra = new ListMT;
//		listMuonTra->pFirst = NULL;
//		for(int i=0; i<lichsumuon; i++) {
//			FileIn.ignore();
//			getline(FileIn, mt.maSach);
//			FileIn >> mt.ngayMuon.ngay >> mt.ngayMuon.thang >> mt.ngayMuon.nam;
//			FileIn >> mt.ngayTra.ngay >> mt.ngayTra.thang >> mt.ngayTra.nam;
//			FileIn >> mt.trangThai;
//			InsertLastListMuonTra(listMuonTra, mt);
//		}
//		pNode=FindNodeBSTById(root, maDocGia);
//		pNode->data.listMT=listMuonTra;
//		pNode->data.lichsumuon=lichsumuon;
//		count++;
//	}
//	FileIn.close();
//	std::cout<<"\ncheck load file muon tra";
//	return (count == readers ? readers : 1);
//}
//
////
//////------------------------ Save files --------------------------------
////void SaveFileDauSach(ArrPointerDauSach ArrDauSach) {
////	ofstream file;
////	file.open("DauSach.txt", ios_base::out);
////	file << ArrDauSach.n << endl;
////	for(int i = 0; i < ArrDauSach.n; i++) {
////		file << ArrDauSach.dsDauSach[i]->ISBN << endl
////			 << ArrDauSach.dsDauSach[i]->tenSach << endl
////			 << ArrDauSach.dsDauSach[i]->soTrang << endl
////			 << ArrDauSach.dsDauSach[i]->tacGia << endl
////			 << ArrDauSach.dsDauSach[i]->namXuatBan << endl
////			 << ArrDauSach.dsDauSach[i]->theLoai << endl
////			 << ArrDauSach.dsDauSach[i]->soLuong << endl
////			 << ArrDauSach.dsDauSach[i]->luotMuon << endl;
////	}
////	file.close();
////	std::cout<<"\ncheck luu file ddau sach";
////}
////void DemDocGia(Tree root, int &k) {
////	if(root != NULL) {
////		DemDocGia(root->pLeft, k);
////		k++;
////		DemDocGia(root->pRight, k);
////	}
////}
////void SaveFileDocGia(Tree root) {
////	int k = 0;
////	ofstream file;
////	file.open("DocGia.txt", ios_base::out);
////	DemDocGia(root, k);
////	file << k << endl;
////	const int STACKSIZE = 500;
////	NodeBST* Stack[STACKSIZE];
////	NodeBST* p = root;
////	int sp = -1;
////	do {
////		while(p!= NULL) {
////		Stack[++sp] = p;
////		p = p->pLeft;
////		}
////		if(sp != -1) {
////			p = Stack[sp--];
////			
////			file <<p->data.MATHE << endl 
////				<<p->data.ho << endl 
////				<<p->data.ten << endl 
////				<<p->data.phai << endl 
////				<<p->data.trangthai << endl;
////			p = p->pRight;
////		}
////		else break;
////	}while(1);
////	file.close();
////	std::cout<<"\ncheck luu file doc gia";
////}
////
////void SaveFileDanhSachMuonTra(Tree root, int nMT) {
////	ofstream file;
////	file.open("DanhSachMuonTra.txt", ios_base::out);
////	file << nMT << endl;
////	int sp = -1, lichsumuon;
////	const int STACKSIZE = 500;
////	NodeBST *Stack[STACKSIZE];
////	NodeBST *pNode = root;
////	NodeMuonTra *r;
////	do {
////		while(pNode!=NULL) {
////			Stack[++sp] = pNode;
////			pNode = pNode->pLeft;
////		}
////		if(sp != -1){
////			pNode = Stack[sp--];
////			if(pNode==NULL) {
////				std::cout<<"\ndoc gia ko ton tai";
////			}
////			if(pNode->data.listMT!=NULL && pNode->data.listMT->pFirst!=NULL) {
////				file << pNode->data.MATHE << endl 
////					<< pNode->data.lichsumuon << endl;
////				for(r = pNode->data.listMT->pFirst; r != NULL; r = r->next) {
////					file << r->data.maSach << endl
////						<< r->data.ngayMuon.ngay <<" " << r->data.ngayMuon.thang <<" " << r->data.ngayMuon.nam << endl
////						<< r->data.ngayTra.ngay <<" "<< r->data.ngayTra.thang <<" "<< r->data.ngayTra.nam << endl
////						<< r->data.trangThai << endl;
////				}
////			}
////			
////			pNode = pNode->pRight;
////		}
////		else break;
//// 	} while(1);
////	file.close();
////	std::cout<<"\ncheck luu file muon tra";
////}
////
////void SaveFileDanhMucSach(ArrPointerDauSach ArrDauSach){
////	ofstream file;
////	file.open("DanhMucSach.txt", ios_base::out);
////	int n = ArrDauSach.n;
////	ListDMS *listDMS;
////	NodeDMS *pNode;
////	for(int i = 0; i < ArrDauSach.n; i++) {
////		listDMS = ArrDauSach.dsDauSach[i]->listDMS;
////		for(pNode=listDMS->pFirst; pNode != NULL; pNode = pNode->next) {
////			file <<pNode->data.MaSach << endl
////				 <<pNode->data.TrangThai << endl
////				 <<pNode->data.ViTri << endl;
////		}
////	}
////	file.close();
////	std::cout<<"\ncheck luu file danh muc sach";
////}

