#pragma once
#include <iostream>
#include <ctime>
#include "define.h"
#include "local.h"
#include "model.h"
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

//void CreateTree(Tree &Root) {
//    Root = NULL;
//}

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
	std::cout<<"\ncheck so doc gia qua han:"<<list.n;
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
