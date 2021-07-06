#pragma once
#include <iostream>
#include <ctime>
#include "define.h"
#include "local.h"
#include <string>
using namespace std;
// ---------- Dates & times ------------
struct Date {
	int ngay;
	int thang;
	int nam;
};

Date GetDate() {//lay ngay-thang-nam hien tai
	Date resDate;
	time_t now = time(0);
	tm *ltm = localtime(&now);
	resDate.nam=1900 + ltm->tm_year;
	resDate.thang=1 + ltm->tm_mon;
	resDate.ngay=ltm->tm_mday;
	return resDate;
}

int countLeapYears(Date d) {
    int years = d.nam;
 
    // Check if the current year needs to be
    //  considered for the count of leap years
    // or not
    if (d.thang <= 2)
        years--;
 
    // An year is a leap year if it
    // is a multiple of 4,
    // multiple of 400 and not a
     // multiple of 100.
    return years / 4
           - years / 100
           + years / 400;
}

int getDifference(Date dt1, Date dt2) {
    
    long int n1 = dt1.nam * 365 + dt1.ngay;
    for (int i = 0; i < dt1.thang - 1; i++) {
    	n1 += monthDays[i];
	}
    n1 += countLeapYears(dt1);
    
    long int n2 = dt2.nam * 365 + dt2.ngay;
    for (int i = 0; i < dt2.thang - 1; i++) {
    	n2 += monthDays[i];
	}
    n2 += countLeapYears(dt2);
	
    // tra ve so ngay dt1 ke tu ngay dt2
    return (n1 - n2);
}

// ---------- Dau sach va danh muc sach ------------
struct danhMucSach {
	char MaSach[10];
	int TrangThai;
	string ViTri;
};

struct NodeDMS {
	danhMucSach data;
	NodeDMS *next;
};

struct ListDMS {
	NodeDMS *pFirst;
};

struct DauSach{
	char ISBN[10];
	int soTrang;
	int namXuatBan;
	string tenSach;
	string tacGia;
	string theLoai;
	ListDMS *listDMS = NULL;
	int soLuong; //so luong sach trong danh muc sach
	int luotMuon;//so luot muon cho tung dau sach
};

struct ArrPointerDauSach{
	int n;
	DauSach *dsDauSach[MAXDAUSACH];
};
ArrPointerDauSach ArrDauSach;

// ---------- Muon Tra ------------
struct MuonTra {
	string maSach;
	Date ngayMuon;
	Date ngayTra;
	int trangThai;
};

struct NodeMuonTra {
	MuonTra data;
	NodeMuonTra *next;
};

struct ListMT {
	NodeMuonTra *pFirst;
};

// ---------- The Doc Gia ------------
struct DocGia{
	//so nguyen sinh tu dong co 4 chu so tu 1000-9999
	int MATHE;
	string ho;
	string ten;
	int phai;
//	0: Nam
//	1: Nu
	 
	int trangthai;
//	0: Khoa
//	1: Hoat dong

//	dslk don luu cac sach ma doc gia da va dang muon
	ListMT *listMT = NULL;
	int lichsumuon;// do dai lich su muon tra cua doc gia
	DocGia(){
	}
	DocGia(int MT, string Ho, string Ten, int Phai, int TT){
		MATHE = MT;
		ho = Ho;
		ten = Ten;
		phai = Phai;
		trangthai = TT;
	}
};

struct NodeBST {
    DocGia data;
//	int BF;
    NodeBST *pLeft;
    NodeBST *pRight;
};

typedef NodeBST *Tree;

NodeBST *CreateNode(DocGia init) {
    NodeBST *p = new NodeBST;
    
    p->data = init;
//    p->BF = EH;
    p->pLeft = NULL;
    p->pRight = NULL;
    return p;
}

void DestroyTree(Tree &Root) {
    if (Root) {
        DestroyTree(Root->pLeft);
        DestroyTree(Root->pRight);
        delete Root;
    }
}

int InsertNode(Tree &Root, NodeBST *x) {
	if(Root) {
		if(Root->data.MATHE == x->data.MATHE) 
			return 0;
		if(Root->data.MATHE > x->data.MATHE)
			return InsertNode(Root->pLeft, x);
		return InsertNode(Root->pRight, x);
	}
	Root=x;
	return 1;
}

NodeBST *FindNode(Tree Root, NodeBST *x){
	if (Root) {
        if (Root->data.MATHE == x->data.MATHE)
            return Root;
        if (x->data.MATHE < Root->data.MATHE)
            return FindNode(Root->pLeft, x);
        return FindNode(Root->pRight, x);
    }
    return NULL;
}

NodeBST *FindNodeById(Tree Root, int ID) {
	if(Root) {
		if (Root->data.MATHE == ID)
			return Root;
		if(Root->data.MATHE > ID)
			return FindNodeById(Root->pLeft, ID);
		return FindNodeById(Root->pRight, ID);
	}
	return NULL;
}
// print tree using LNR
void PrintTree(Tree Root) {
    if (Root) {
        PrintTree(Root->pLeft);
        std::cout << Root->data.MATHE << ' ';
        PrintTree(Root->pRight);
    }
}

NodeBST *MostLeftNode(NodeBST *node){
	NodeBST *p = node;
	while(p->pLeft!=NULL){
		p = p->pLeft;
	}
	return p;
}

int DeleteNodeBST(Tree &Root, NodeBST *x) {
	if(Root) {
		if (Root->data.MATHE == x->data.MATHE) {
			NodeBST *p = Root;
            if (!Root->pLeft)
                Root = Root->pRight;
            else if(!Root->pRight)
            	Root = Root->pLeft;
            else {
            	NodeBST *replace = MostLeftNode(Root->pRight);
            	Root->data = replace->data;
            	Root = replace;
            	replace = replace->pRight;
			}
            delete p;
            return 1;
		}
        if (x->data.MATHE < Root->data.MATHE)
            return DeleteNodeBST(Root->pLeft, x);
        return DeleteNodeBST(Root->pRight, x);
	}
	return 0;
}

void IncayDocGia(Tree root) {
	if(root!=NULL) {
		IncayDocGia(root->pLeft);
		std::cout<<"\ndoc gia"<<root->data.MATHE;
		IncayDocGia(root->pRight);
	}
}
Tree CayDocGia=NULL;
int readers;

// ---------- Doc Gia quan han ------------
struct NodeDGQuaHan {
	DocGia data;
	int soNgayQuaHan;
	NodeDGQuaHan *next;
};

struct ListDGQuaHan {
	int n;
	NodeDGQuaHan *pFirst;
};

NodeDGQuaHan *CreateNodeDGQuaHan(DocGia docgia, int soNgayQuaHan) {
	NodeDGQuaHan *pNode = new NodeDGQuaHan;
	pNode->data=docgia;
	pNode->soNgayQuaHan=soNgayQuaHan;
	pNode->next=NULL;
	return pNode;
}

void InsertNodeDGQuaHan(ListDGQuaHan &list, NodeDGQuaHan *pInsert) {
	NodeDGQuaHan *pNode=list.pFirst;//Neu Node Insert co so ngay muon la lon nhat: them vao dau list
	if(pNode==NULL) {
		list.pFirst=pInsert;
	} else {//Them Node Insert vao truoc node co so ngay muon be hon
		while(pNode->next!=NULL) {
			pNode=pNode->next;
		}
		pNode->next=pInsert;
	}
}

// Loc cac doc gia muon sach qua han trong BST thu tu LNR bang thuat toan khu de quy voi Stack
int GetListDGQuaHan(Tree root, ListDGQuaHan &list) {
	list.pFirst=NULL;
	list.n=0;
	const int STACKSIZE = 500;
	NodeBST *Stack[STACKSIZE];
	NodeBST *pNode;
	pNode=root;
	Date today=GetDate();
	int sp = -1, count =0; // khoi tao Stack rong
	do {
		while (pNode != NULL) {
		Stack[++sp] = pNode;
		pNode = pNode->pLeft;
		}
		if(sp != -1) {
			pNode = Stack[sp--];//Pop stack
			if(pNode->data.listMT!=NULL) {//Neu doc gia tung muon sach trong thu vien
				NodeMuonTra *pCheck;
				
				pCheck=pNode->data.listMT->pFirst;//kiem tra tung sach trong list Muon tra
				int NgayMuon=0;
				while(pCheck!=NULL) {//Neu Doc gia chua tra sach thi tinh so ngay da muon
					if(pCheck->data.ngayTra.nam==0 && getDifference(today, pCheck->data.ngayMuon)>NgayMuon) {
						NgayMuon=getDifference(today, pCheck->data.ngayMuon);
					}
					pCheck=pCheck->next;
				}
				if(NgayMuon>NGAYQUAHAN) {//Neu So ngay muon lon hon 7 thi them vao ListDGQuaHan
					InsertNodeDGQuaHan(list, CreateNodeDGQuaHan(pNode->data, NgayMuon-NGAYQUAHAN));
					list.n++;
					count++;
				}
			}
			pNode = pNode->pRight;
		} else {//sp=-1: Stack rong thi dung
			break;
		}
	}while (1);
	return count;
}

void SwapNodeQuaHan(NodeDGQuaHan *p1, NodeDGQuaHan *p2) {
	DocGia temp=p1->data;
	int tmp=p1->soNgayQuaHan;
	p1->data=p2->data;
	p1->soNgayQuaHan=p2->soNgayQuaHan;
	p2->data=temp;
	p2->soNgayQuaHan=tmp;
}

void SortListDFQuaHan(ListDGQuaHan ListDGQH) {//sap xep danh sach doc gia qua han theo thu tu ngay qua han giam dan
	int n=ListDGQH.n;
	bool isSwap;
	NodeDGQuaHan *pNode, *pCheck=NULL;
	if(pNode==NULL) {
		return;
	}
	
	do {
        isSwap=false;
		pNode=ListDGQH.pFirst;
  
        while (pNode->next != pCheck) {
            if (pNode->soNgayQuaHan < pNode->next->soNgayQuaHan) {
                SwapNodeQuaHan(pNode, pNode->next);
                isSwap=true;
            }
            pNode = pNode->next;
        }
        pCheck = pNode;
    } while (isSwap);
}

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
    }
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
	danhMucSach *dms;
	char buffer[30];
	char MaSach[10];
	int index;
	for(int i=1; i<=n; i++) {
		dms = new danhMucSach;
		dms->ViTri=vitri;
		itoa(i, buffer, 10);
		strcpy(MaSach, ISBN);
		strcat(MaSach, "_");
		strcat(MaSach, buffer);
		strcpy(dms->MaSach, MaSach);
		dms->TrangThai=0;
		InsertLastDMS(listDMS, dms);
	}
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
	return 0;
	
}

NodeDMS *GetNodeDmsInDauSach(DauSach *dausach, int index) {
	NodeDMS *pNode=dausach->listDMS->pFirst;
	for(int i=0; i<index; i++) {
		pNode=pNode->next;
	}
	return pNode;
}

int GetChuaMuon(DauSach *dausach) {
	int count =0;
	NodeDMS *pNode=dausach->listDMS->pFirst;
	while(pNode) {
		if(pNode->data.TrangThai==0) {
			count++;
		}
		pNode=pNode->next;
	}
	return count;
}

int GetLuotMuon(DauSach *dausach) {
	int count =0;
	NodeDMS *pNode=dausach->listDMS->pFirst;
	while(pNode) {
		if(pNode->data.TrangThai==1) {
			count++;
		}
	}
	return count;
}
// ---------- Handle DauSach's structure function ------------
int CompareDS(DauSach *a, DauSach *b, int mode) {//mode=0: so sanh theo the loai; else: so sanh theo ten
	if(mode == 0) {
		return strcmp(a->theLoai.c_str(), b->theLoai.c_str());
	}
	return strcmp(a->tenSach.c_str(), b->tenSach.c_str());
}

void SortDS(ArrPointerDauSach &dsds) {
	DauSach* temp;
	int mode;
	mode=0;//sort theo the loai
	for (int i = 0; i < dsds.n - 1; i++) {
		for (int j = i + 1; j < dsds.n; j++) {
			if (CompareDS(dsds.dsDauSach[i], dsds.dsDauSach[j], mode)>0) {
				temp = dsds.dsDauSach[i];
				dsds.dsDauSach[i] = dsds.dsDauSach[j];
				dsds.dsDauSach[j] = temp;
			} else if(CompareDS(dsds.dsDauSach[i], dsds.dsDauSach[j], mode)==0) {
				mode=1;
				if (CompareDS(dsds.dsDauSach[i], dsds.dsDauSach[j], mode)>0) {
					temp = dsds.dsDauSach[i];
					dsds.dsDauSach[i] = dsds.dsDauSach[j];
					dsds.dsDauSach[j] = temp;
				}
			}
			mode=0;
		}
	}
}

int InsertDauSach(ArrPointerDauSach &dsds, DauSach *ds) {
	if(dsds.n+1<=MAXDAUSACH) {
		dsds.n++;
		dsds.dsDauSach[dsds.n-1]=ds;
		return 1;
	}
	return 0;
}

bool CheckISBN(ArrPointerDauSach dsds, DauSach *ds) {//kiem tra isbn cua dau sach da co tron he thong chua
	for(int i=0; i<dsds.n; i++) {
		if(strcmp(dsds.dsDauSach[i]->ISBN, ds->ISBN)==0) {
			return false;
		}
	}
	return true;
}

void  XoaDauSach(ArrPointerDauSach &dsds, int pos) {
	DauSach *pNode=dsds.dsDauSach[pos];
	NodeDMS *pList;
	while(pNode->listDMS->pFirst!=NULL) {
		pList=pNode->listDMS->pFirst;
		pNode->listDMS->pFirst=pNode->listDMS->pFirst->next;
		free(pList);
	}
	free(pNode);
//	delete  (dsds.dsDauSach[pos]);
	for(int i = pos; i <dsds.n; i++) {
		dsds.dsDauSach[i] = dsds.dsDauSach[i + 1];
	}
	dsds.n--;
	return;
}

void FreeDSArr(ArrPointerDauSach &dsds) {
	while(dsds.n>0) {
		XoaDauSach(dsds, dsds.n-1);
	}
	delete [] dsds.dsDauSach;
}

ArrPointerDauSach SearchDauSach(ArrPointerDauSach dsds, string input) {
	int i, j=-1;
	ArrPointerDauSach temp;
	temp.n=0;
	input.erase(input.length()-1);
	for(i=0; i<dsds.n; i++) {
		int search = dsds.dsDauSach[i]->tenSach.find(input);
		if(search != -1) {
			temp.dsDauSach[++j] = dsds.dsDauSach[i];
			temp.n++;
		} else {
			std::cout<<"\nKhong tim thay "<<input<<" trong chuoi "<<dsds.dsDauSach[i]->tenSach;
		}
	}
	return temp;
}

DauSach *SearchDauSachByIsbn(ArrPointerDauSach dsds, char ISBN[]) {
	int n=dsds.n;
	for(int i=0; i<n;i++) {
		if(strcmp(dsds.dsDauSach[i]->ISBN, ISBN)==0) {
			return dsds.dsDauSach[i];
		}
	}
	return NULL;
}

DauSach *SearchIsbn(ArrPointerDauSach dsds, char ISBN[]) {
	int n=dsds.n;
	for(int i=0; i<n ;i++) {
		if(strcmp(dsds.dsDauSach[i]->ISBN, ISBN)==0) {
			return dsds.dsDauSach[i];
		}
	}
}

bool CheckTrungMax(DauSach *ArrDS[], int lenArr, char isbn[]) {
	for(int i=0; i<lenArr; i++) {
		if(strcmp(ArrDS[i]->ISBN, isbn)==0) {
			return false;
		}
	}
	return true;
}

void GetTopTenDauSach(ArrPointerDauSach dsds, DauSach *ArrDS[]) {
	int i, j, n=dsds.n;
	for(i=0; i<10; i++) {
		DauSach *max = dsds.dsDauSach[0];
		for(j=0; j<n; j++) {
			if(max->luotMuon<dsds.dsDauSach[j]->luotMuon && CheckTrungMax(ArrDS, i, dsds.dsDauSach[j]->ISBN)) {
				max=dsds.dsDauSach[j];
			}
		}
		ArrDS[i]=max;
	}
}


// ---------- Handle MuonTra's structure function ------------
int GetSoSachMuonDG(DocGia *docgia) {
	int count=0;
	NodeMuonTra *pNode=docgia->listMT->pFirst;
	while(pNode) {
		if(pNode->data.trangThai==0) {
			count ++;
		}
		pNode=pNode->next;
	}
	return count;
}

NodeMuonTra *CreateNodeMT(MuonTra mt) {
	NodeMuonTra *pNode = new NodeMuonTra;
	pNode->data=mt;
	pNode->next = NULL;
	return pNode;
}
void InsertLastListMuonTra(ListMT *&listMT, MuonTra mt) {
	NodeMuonTra *pInsert = CreateNodeMT(mt);
	NodeMuonTra *pNode = listMT->pFirst;
	if(listMT->pFirst == NULL) {
		listMT->pFirst = pInsert;
		return;
	}
	while(pNode->next != NULL) {
		pNode = pNode->next;
	}
	pNode->next = pInsert;
}

int FindIndexDocGiaInArr(DocGia ListDG[], int mathe) {
	for(int i=0; i<MAXDOCGIA; i++) {
		if(ListDG[i].MATHE==mathe) {
			return i;
		}
	}
}

NodeBST *FindNodeBSTById(Tree root, int IdDocGia) {
	const int STACKSIZE = 500;
	NodeBST *Stack[STACKSIZE];
	NodeBST *pNode;
	pNode=root;
	int sp = -1; // khoi tao Stack rong
	do {
		while (pNode != NULL) {
			Stack[++sp] = pNode;
			pNode = pNode->pLeft;
		}
		if(sp != -1) {
			pNode = Stack[sp--];//Pop stack
			if(pNode->data.MATHE==IdDocGia) {
				return pNode;
				break;
			}
			pNode = pNode->pRight;
		} else {
			std::cout<<"\nko tim thay doc gia:" << IdDocGia;
			break;
		}//sp=-1: Stack rong thi dung
	}while (1);
}

NodeMuonTra *GetNodeMTById(ListMT *listMT, int index) {
	NodeMuonTra *pNode=listMT->pFirst;
	for(int i=0; i<index; i++) {
		pNode=pNode->next;
	}
	return pNode;
}

NodeDMS *GetNodeDmsInListMT(NodeMuonTra *mt, ArrPointerDauSach dsds) {
	char isbn[10];
//	std::cout<<"\ncheck 1";
	for(int i=0; i<5; i++) {
		isbn[i]=mt->data.maSach[i];
	}
//	std::cout<<"\ncheck 2";
	dsds.dsDauSach;
	DauSach *resDS;
	resDS = SearchDauSachByIsbn(dsds, isbn);
	NodeDMS *nodeRes=resDS->listDMS->pFirst;
//	std::cout<<"\ncheck 3";
	while(nodeRes!=NULL) {
		if(strcmp(nodeRes->data.MaSach, mt->data.maSach.c_str())) {
//			std::cout<<"\ncheck get node dms";
			return nodeRes;
		}
		nodeRes=nodeRes->next;
	}
	return NULL;
}

void DeleteFirstListMuonTra(ListMT *&listMT) {
	NodeMuonTra *pNode = listMT->pFirst;
	listMT->pFirst = listMT->pFirst->next;
	free(pNode);
}

void DeleteListMuonTra(ListMT *&listMT) {
	while(listMT->pFirst!=NULL) {
		DeleteFirstListMuonTra(listMT);
	}
}


// ---------- Handle DocGia's structure function ------------
bool IdDocGiaIsUsed(Tree root, int id) {
	const int STACKSIZE = 500;
	NodeBST *Stack[STACKSIZE];
	NodeBST *pNode;
	pNode=root;
	int sp = -1;//Khoi tao Stack rong
	do {
		while (pNode != NULL) {
			Stack[++sp] = pNode;
			pNode = pNode->pLeft;
		}
		if(sp != -1) {
			pNode = Stack[sp--];//Pop stack
			if(pNode->data.MATHE==id) {
				return true;
			}
			pNode = pNode->pRight;
		} else {
			return false;
			break;
		}//sp=-1: Stack rong thi dung
	}while (1);
}


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
void CreateDocGiaArr(Tree t, DocGia arr[], int &lenDocGia) {
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

void SortDGByIndex(DocGia arr[]) {
	DocGia temp;
	int dem=0;
	for(int i=0; i<MAXDOCGIA-1; i++) {
		for(int j=0; j<MAXDOCGIA; j++) {
			if(arr[j].MATHE-1000==i) {
				temp=arr[i];
				arr[i]=arr[j];
				arr[j]=temp;
				std::cout<<"\ndocgia "<<i<<" co ma the la:"<<arr[i].MATHE;
				dem++;
				break;
			}
		}
		std::cout<<"||doc gia rac"<<i<<" co ma the rac la:"<<arr[i].MATHE;
	}
	std::cout<<"\ncheck sort "<<dem<<" doc gia";
}

void FreeMemoryBST(Tree root) {
	if(root!=NULL) {
		FreeMemoryBST(root->pLeft);
		DeleteListMuonTra(root->data.listMT);
		FreeMemoryBST(root->pRight);
		free(root);
	}
}

