#pragma once
#include "model.h"
#include "local.h"
#include "define.h"
#include "layoutDauSach.h"
#include "cautrucDocGia.h"

int MuonTraController(int **MapId, int &x, int &y) {
	refreshMainLayout(MapId);
	drawHeader(MapId, 3);
	std::cout<<"\ncheck load file dau sach "<<LoadFileDauSach(ArrDauSach);
	std::cout<<"\ncheck load file danh muc"<<LoadFileDanhMucSach(ArrDauSach);
	int lenDG=0, currentID=-1, currentPos=-1;
	char buffer[30];
	DauSach *currentDS;
	DocGia ListDG[MAXDOCGIA], currentDG;
	CreateDocGiaArr(CayDocGia, ListDG, lenDG);
	std::cout<<"\ncheck lenDG:"<<lenDG;
	std::cout<<LoadFileMuonTra(ListDG);
	
	Button btnMuonSach(MG, UNIT*3+MG*2, BLOCK*4, BLOCK, "Muon Sach", 301);
	Button btnTraSach(ACTICLE-BLOCK*4, UNIT*3+MG*2, BLOCK*4, BLOCK, "Tra sach", 302);
	Button btnTopTen(w-BLOCK*10-MG, UNIT*3+MG*2, BLOCK*9, BLOCK, "Top 10 sach muon nhieu", 303);
	Button btnSearchDocGia(ACTICLE-BLOCK-MG*3, YDS[0], BLOCK+MG*2, BLOCK, "Tim", 304);
	Button btnRefreash(ACTICLE-BLOCK-MG*3, YDS[0], BLOCK+MG*2, BLOCK, "Xoa", 305);
	Button btnSearchDauSach(ACTICLE-BLOCK-MG*3, YDS[5], BLOCK+MG*2, BLOCK, "Tim", 306);
	Button btnConfirm(BLOCK*4, h-BLOCK*2+MG, BLOCK*4, BLOCK, "Xac Nhan", 307);
	
	EditText edSearchDocGia(MG*2, YDS[0], BLOCK*6, BLOCK, "Nhap ma the :", "", "Nhap vao 4 so", 310);
	EditText edNameDocGia(BLOCK, YDS[1], BLOCK*7-MG, BLOCK, "Doc gia :", "", "", 311);
	EditText edMaTheDocGia(BLOCK, YDS[2], BLOCK*7-MG, BLOCK, "Ma the :", "", "", 312);
	EditText edGioiTinhDocGia(BLOCK, YDS[3], BLOCK*7-MG, BLOCK, "Gioi tinh :", "", "", 313);
	EditText edTrangThaiTheDocGia(BLOCK, YDS[4], BLOCK*7-MG, BLOCK, "Trang thai the :", "", "", 314);
	EditText edSearchISBN(MG*2, YDS[5], BLOCK*6, BLOCK, "ISBN sach muon :","","Nhap vao 5 so", 315);
	
	btnBackMenu.draw(MapId);
	btnExit.draw(MapId);
	
	btnMuonSach.isChoose=true;
	btnMuonSach.draw(MapId);
	btnTraSach.draw(MapId);
	btnTopTen.draw(MapId);
	btnSearchDocGia.draw(MapId);
	btnSearchDauSach.draw(MapId);
	
	edSearchDocGia.draw(MapId);
	edNameDocGia.draw(MapId);
	edMaTheDocGia.draw(MapId);
	edGioiTinhDocGia.draw(MapId);
	edTrangThaiTheDocGia.draw(MapId);
	edSearchISBN.draw(MapId);
	
	drawTable(MapId, tableTitleDanhMuc, tableTitleWidthDanhMuc, 3);
	while(1) {
		delay(0.0001);
        if (ismouseclick(WM_LBUTTONDOWN)){
            getmouseclick(WM_LBUTTONDOWN, x, y);
            std::cout<<"\nleft click:"<<x<<" "<<y<<"="<<MapId[y][x];
            switch(MapId[y][x]) {
            	case -1:
            		return 0;
            	case -2:
            		exit(1);
            	case 100:
            		return 1;
            	case 200:
            		return 2;
            	case 301:
            		btnMuonSach.toggle(btnTraSach, MapId);
            		edSearchISBN.draw(MapId);
            		drawTable(MapId, tableTitleDanhMuc, tableTitleWidthDanhMuc, 3);
            		break;
            	case 302:
            		edSearchISBN.deleteEdText(MAIN_COLOR, MapId);
            		btnSearchDauSach.deleteBtn(MAIN_COLOR, MapId);
					edMaTheDocGia.draw(MapId);
            		edNameDocGia.draw(MapId);
					edGioiTinhDocGia.draw(MapId);
					edTrangThaiTheDocGia.draw(MapId);
					
					btnSearchDocGia.draw(MapId);
            		btnTraSach.toggle(btnMuonSach, MapId);
            		drawTable(MapId, tableTitleMuonTra, tableTitleWidthMuonTra, 4);
            		break;
            	case 303:
//            		btnTraSach.toggle(btnTraSach, MapId);
					if(btnMuonSach.isChoose) {
						btnTopTen.isChoose=true;
						btnTopTen.draw(MapId);
					}
            		break;
            	case 304:// tim thong tin theo ma doc gia nhap vao
            		btnSearchDocGia.deleteBtn(MAIN_COLOR, MapId);
            		btnRefreash.draw(MapId);
            		currentID=atoi(edSearchDocGia.content);
            		currentPos=FindIndexDocGiaInArr(ListDG, currentID);
            		currentDG=ListDG[currentPos];
            		std::cout<<"\ncheck docgia:"<<currentDG.ten<<", ID:"<<currentID<<", vitri:"<<currentPos;
            		std::cout<<"\nsach dau tien la:"<<currentDG.listMT->pFirst->data.maSach
							<<", trang thai:"<<currentDG.listMT->pFirst->data.trangThai;
            		itoa(currentPos, buffer, 10);
            		strcpy(edNameDocGia.content, (ListDG[currentPos].ho + " " + ListDG[currentPos].ten).c_str());
            		std::cout<<"\n check 0";
            		strcpy(edMaTheDocGia.content, buffer);
            		strcpy(edGioiTinhDocGia.content, PhaiDocGia[ListDG[currentPos].phai]);
            		strcpy(edTrangThaiTheDocGia.content, TTTDocGia[ListDG[currentPos].trangthai]);
            		std::cout<<"\n check 1";
					edGioiTinhDocGia.draw(MapId);
					edTrangThaiTheDocGia.draw(MapId);
            		edNameDocGia.draw(MapId);
					edMaTheDocGia.draw(MapId);
            		std::cout<<"\n check 2";
            		if(btnTraSach.isChoose) {
            			PrintSachMuonTable(currentPos, ListDG, MapId);
					}
            		
            		std::cout<<"\n check 3";
            		break;
            	case 305:// xoa noi dung tim kiem
            		edSearchISBN.clear();
            		edNameDocGia.clear();
            		edMaTheDocGia.clear();
            		edSearchDocGia.clear();
					edGioiTinhDocGia.clear();
					edTrangThaiTheDocGia.clear();
					
					if(btnMuonSach.isChoose) {
						edSearchISBN.draw(MapId);
						drawTable(MapId, tableTitleDanhMuc, tableTitleWidthDanhMuc, 3);
					} else {
						drawTable(MapId, tableTitleMuonTra, tableTitleWidthMuonTra, 4);
					}
            		edNameDocGia.draw(MapId);
            		edMaTheDocGia.draw(MapId);
            		edSearchDocGia.draw(MapId);
					edGioiTinhDocGia.draw(MapId);
					edTrangThaiTheDocGia.draw(MapId);
					
            		break;
            	case 306://Tim dau sach theo ISBN da nhap
            		if(edSearchISBN.content[0] == '\0') {
            			drawNotification(ThongTinKhongDuocDeTrong);
            			break;
					}
					currentDS=SearchDauSachByIsbn(ArrDauSach, edSearchISBN.content);
					if(currentDS==NULL) {
						drawNotification(KhongTimThaySach);
						break;
					}
//					int tmp1=0;
//					int tmp2=10;
					std::cout<<"\nCheck so luong khi in: "<<currentDS->soLuong;
					PrintDMTable(currentDS->listDMS, 0, 10,MapId);
            		break;
            	case 307:
            		break;
            	case 310:
            		btnRefreash.deleteBtn(MAIN_COLOR, MapId);
            		btnSearchDocGia.draw(MapId);
            		ScanNumber(edSearchDocGia, 4, MapId);
            		break;
            	case 311:
            		break;
            	case 312:
            		break;
            	case 313:
					break;
				case 314:
					break;
				case 315://nhap isbn sach can tim
					ScanNumber(edSearchISBN, 5, MapId);
					
//					btnConfirm.draw(MapId);
					break; 
			}
			
        }
	}
	delay(10);
	std::cout << "Check5\n";
}

