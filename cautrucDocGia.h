#pragma once
#include <iostream>
#include "define.h"
#include "local.h"
#include "model.h"
#include <string>
using namespace std;

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
	NodeDMS *first;
};

struct DauSach{
	char ISBN[6];
	int soTrang;
	int namXuatBan;
	string tenSach;
	string tacGia;
	string theLoai;
//	ListDMS *listDMS = NULL;
	int soLuong; //so luong sach trong danh muc sach
	int luotMuon;	// //so luot muon cho tung dau sach
}; 
struct DanhSachDauSach{
	int n;
	DauSach *dsDauSach[MAXDAUSACH];
};

DanhSachDauSach ArrDauSach;
//// ---------- Muon Tra ------------
//struct Date {
//	int ngay;
//	int thang;
//	int nam;
//};
//struct MuonTra{
//	string maSach;
//	Date ngayMuon;
//	Date ngayTra;
//	TrangThai trangThai;
//};
//struct NodeMuonTra{
//	MuonTra info;
//	NodeMuonTra *next;
//}

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
//	DS_MuonTra mt;
	
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
	if (Root)
    {
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
Tree CayDocGia=NULL;

