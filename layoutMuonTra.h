#pragma once
#include "model.h"
#include "local.h"
#include "define.h"
#include "layoutDauSach.h"
#include "cautrucDocGia.h"

int MuonTraController(int **MapId, int &x, int &y) {
	std::cout<<"\ncheck muon tra";
	int lenDG=0, 
	currentID=-1, 
	currentPos=-1, 
	sachMuon;
	char buffer[30];
	DocGia ArrDG[MAXDOCGIA], *currentDG;
	DauSach *currentDS, *ArrTopTen[10];
	NodeMuonTra *currentNodeMT;
	NodeDMS *currentNodeDMS;
	MuonTra mt;
	GetTopTenDauSach(ArrDauSach, ArrTopTen);
	CreateDocGiaArr(CayDocGia, ArrDG, lenDG);
	
	Button 		btnMuonSach		(MG, UNIT*3+MG*2, BLOCK*4, BLOCK, "Muon Sach", 							301);
	Button 		btnTraSach		(ACTICLE-BLOCK*4, UNIT*3+MG*2, BLOCK*4, BLOCK, "Tra sach", 				302);
	Button 		btnTopTen		(w-BLOCK*10-MG, UNIT*3+MG*2, BLOCK*9, BLOCK, "Top 10 sach muon nhieu", 	303);
	Button 		btnSearchDocGia	(ACTICLE-BLOCK-MG*3, YDS[0], BLOCK+MG*2, BLOCK, "Tim", 					304);
	Button 		btnRefreash		(ACTICLE-BLOCK-MG*3, YDS[0], BLOCK+MG*2, BLOCK, "Xoa", 					305);
	Button 		btnSearchDauSach(ACTICLE-BLOCK-MG*3, YDS[5], BLOCK+MG*2, BLOCK, "Tim", 					306);
	Button 		btnXacNhanMuon	(BLOCK*4, h-BLOCK*2+MG, BLOCK*4, BLOCK, "Xac Nhan", 					307);
	Button 		btnChangeDS		(ACTICLE-BLOCK-MG*3, YDS[5], BLOCK+MG*2, BLOCK, "Xoa", 					308);
	Button 		btnXacNhanTra	(BLOCK, h-BLOCK*2+MG, BLOCK*4, BLOCK, "Tra sach", 						320);
	Button 		btnLamMat		(BLOCK*7, h-BLOCK*2+MG, BLOCK*4, BLOCK, "Lam mat", 						321);
	
	EditText 	edSearchDocGia			(MG*2, YDS[0], BLOCK*6, BLOCK, "Nhap ma the :", "", "Nhap vao 4 so", 	310);
	EditText 	edNameDocGia			(BLOCK, YDS[1], BLOCK*7-MG, BLOCK, "Doc gia :", "", "", 				311);
	EditText 	edMaTheDocGia			(BLOCK, YDS[2], BLOCK*7-MG, BLOCK, "Ma the :", "", "", 					312);
	EditText 	edTrangThaiTheDocGia	(BLOCK, YDS[3], BLOCK*7-MG, BLOCK, "Trang thai the :", "", "", 			313);
	EditText 	edGioiTinhDocGia		(BLOCK, YDS[4], BLOCK*7-MG, BLOCK, "Gioi tinh :", "", "", 				314);
	EditText 	edSearchISBN			(MG*2, YDS[5], BLOCK*6, BLOCK, "ISBN sach muon :","","Nhap vao 5 so", 	315);
	EditText 	edTenSachMuon			(BLOCK, YDS[4], BLOCK*7-MG, BLOCK, "Sach muon :", "", "", 				316);
	EditText 	edMaSachMuon			(MG*2, YDS[5], BLOCK*6, BLOCK, "Ma sach :", "", "", 					317);	
	
	refreshMainLayout(MapId);
	drawHeader(MapId, 3);
	drawTable(MapId, tableTitleDanhMuc, tableTitleWidthDanhMuc, 3);
	
	btnMuonSach.isChoose=true;
	btnSearchDauSach.draw(MapId);
	btnSearchDocGia.draw(MapId);
	btnBackMenu.draw(MapId);
	btnMuonSach.draw(MapId);
	btnTraSach.draw(MapId);
	btnTopTen.draw(MapId);
	btnExit.draw(MapId);
	
	edTrangThaiTheDocGia.draw(MapId);
	edGioiTinhDocGia.draw(MapId);
	edSearchDocGia.draw(MapId);
	edMaTheDocGia.draw(MapId);
	edNameDocGia.draw(MapId);
	edSearchISBN.draw(MapId);
	
	while(1) {
		delay(0.0001);
        if (ismouseclick(WM_LBUTTONDOWN)){
            getmouseclick(WM_LBUTTONDOWN, x, y);
            std::cout<<"\nleft click:"<<x<<" "<<y<<"="<<MapId[y][x];
            switch(MapId[y][x]) {
            	case -1://Quay ve menu
            		return 0;
            	case -2://Luu data va thoat chuong trinh
            		return 5;
            	case 100://Chuyen sang layout dau sach
            		return 1;
            	case 140:
            	case 141:
            	case 142:
            	case 143:
            	case 144:
            	case 145:
            	case 146://ckick vao cac sach trong table danh muc sach
            	case 147:
            	case 148:
            	case 149:
            	case 150:
            	case 151:
            	case 152:
            		currentNodeDMS=GetNodeDmsInDauSach(currentDS, MapId[y][x]-140);
            		edGioiTinhDocGia.deleteEdText(MAIN_COLOR, MapId);
            		edSearchISBN.deleteEdText(MAIN_COLOR, MapId);
            		btnSearchDauSach.deleteBtn(MAIN_COLOR, MapId);
            		
            		strcpy(edTenSachMuon.content, currentDS->tenSach.c_str());
            		strcpy(edMaSachMuon.content, currentNodeDMS->data.MaSach);
            		
            		drawNotification();
            		edTenSachMuon.draw(MapId);
            		edMaSachMuon.draw(MapId);
            		btnChangeDS.draw(MapId);
            		
            		sachMuon = GetSoSachMuonDG(currentDG);
            		if(sachMuon>=3 
					|| currentDG->trangthai==KHOA 
					|| currentNodeDMS->data.TrangThai!=CHOMUONDUOC) {
            			btnXacNhanMuon.isLock=true;
					} else {
						btnXacNhanMuon.isLock=false;
					}
            		btnXacNhanMuon.draw(MapId);
            		break;
            	case 200://chuyen sang layoutDocGia
            		return 2;
            	case 301://Che do Muon sach
            		drawNotification();
            		btnTopTen.draw(MapId);
            		btnMuonSach.toggle(btnTraSach, MapId);
            		edSearchISBN.draw(MapId);
            		btnSearchDauSach.draw(MapId);
            		drawTable(MapId, tableTitleDanhMuc, tableTitleWidthDanhMuc, 3);
            		break;
            	case 302://Che do Tra Sach
            		drawNotification();
            		edSearchISBN.deleteEdText(MAIN_COLOR, MapId);
            		btnSearchDauSach.deleteBtn(MAIN_COLOR, MapId);
            		btnTopTen.deleteBtn(BG_COLOR, MapId);
					edMaTheDocGia.draw(MapId);
            		edNameDocGia.draw(MapId);
					edGioiTinhDocGia.draw(MapId);
					edTrangThaiTheDocGia.draw(MapId);
					
					btnSearchDocGia.draw(MapId);
            		btnTraSach.toggle(btnMuonSach, MapId);
            		drawTable(MapId, tableTitleMuonTra, tableTitleWidthMuonTra, 4);
            		break;
            	case 303:// In top10 sach muon nhieu
					if(btnMuonSach.isChoose) {
						btnTopTen.isChoose=true;
						btnTopTen.draw(MapId);
						ViewTopTenDauSachTable(ArrTopTen, MapId);
					}
            		break;
            	case 304:// tim thong tin theo ma doc gia nhap vao
            		if(edSearchDocGia.content[3]=='\0') {//khong nhap du ma sach thi nhap lai
            			drawNotification(VuiLongNhapLai);
            			break;
					}
					drawNotification();
            		btnSearchDocGia.deleteBtn(MAIN_COLOR, MapId);
            		btnRefreash.draw(MapId);
            		currentID=atoi(edSearchDocGia.content);
            		currentPos=FindIndexDocGiaInArr(ArrDG, currentID);
            		currentDG=&ArrDG[currentPos];
            		itoa(currentPos, buffer, 10);
            		strcpy(edNameDocGia.content, (ArrDG[currentPos].ho + " " + ArrDG[currentPos].ten).c_str());
            		strcpy(edMaTheDocGia.content, buffer);
            		strcpy(edGioiTinhDocGia.content, PhaiDocGia[ArrDG[currentPos].phai]);
            		strcpy(edTrangThaiTheDocGia.content, TTTDocGia[ArrDG[currentPos].trangthai]);
					edGioiTinhDocGia.draw(MapId);
					edTrangThaiTheDocGia.draw(MapId);
            		edNameDocGia.draw(MapId);
					edMaTheDocGia.draw(MapId);
            		if(btnTraSach.isChoose) {
            			ViewSachMuonTable(ArrDG[currentPos], MapId);
					}
            		break;
            	case 305:// xoa noi dung tim kiem
            		edSearchISBN.clear();
            		edNameDocGia.clear();
            		edMaTheDocGia.clear();
            		edSearchDocGia.clear();
					edGioiTinhDocGia.clear();
					edTrangThaiTheDocGia.clear();
					btnChangeDS.deleteBtn(MAIN_COLOR, MapId);
					
					if(btnMuonSach.isChoose) {
						edSearchISBN.draw(MapId);
						btnSearchDauSach.draw(MapId);
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
					ViewDanhMucTable(currentDS->listDMS, 0, currentDS->soLuong,MapId);
					if(GetChuaMuon(currentDS)==0) {
						drawNotification(SachDaDuocMuonHet);
					}
            		break;
            	case 307://btn xac nhan
            		if(btnXacNhanMuon.isLock) {
            			break;
					}
            		btnXacNhanMuon.deleteBtn(BG_COLOR, MapId);
            		if(btnMuonSach.isChoose) {
            			if(btnXacNhanMuon.isLock) {
            				drawNotification(KhongDuocMuonSachNay);
            				break;
						}
						drawNotification(MuonSachThanhCong);
						currentNodeDMS->data.TrangThai=DAMUON;
						currentDS->luotMuon++;
						mt.maSach=currentNodeDMS->data.MaSach;
						mt.ngayMuon=GetDate();
						mt.trangThai=0;
						mt.ngayTra.ngay=0;
						mt.ngayTra.thang=0;
						mt.ngayTra.nam=0;
						InsertLastListMuonTra(currentDG->listMT, mt);
						if(currentDG->lichsumuon<MAXLICHSUMUON) {
							currentDG->lichsumuon;
						} else {
							DeleteFirstListMuonTra(currentDG->listMT);
						}
					}
					ViewDanhMucTable(currentDS->listDMS, 0, currentDS->soLuong,MapId);
            		break;
            	case 310:// Nhap ma the
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
					if(edSearchISBN.content[0] == '\0') {
	            			drawNotification(VuiLongNhapMaThe);
	            			break;
					}
					ScanNumber(edSearchISBN, 5, MapId);
					break;
				case 316:
					break;
				case 317:
					break;
				case 320://Tra sach: trang thai sach->cho muon duoc, trang thai muon tra -> da tra
					currentNodeDMS->data.TrangThai=CHOMUONDUOC;
					currentNodeMT->data.trangThai=DATRA;
					currentNodeMT->data.ngayTra=GetDate();
					
					ViewSachMuonTable(ArrDG[currentPos], MapId);
					btnXacNhanTra.deleteBtn(BG_COLOR, MapId);
					btnLamMat.deleteBtn(BG_COLOR, MapId);
					drawNotification(TraSachThanhCong);
					break;
				case 321://Lam mat sach: trang  thai the-> khoa, trang thai sach -> da thanh ly
					currentNodeDMS->data.TrangThai=DATHANHLY;
					currentNodeMT->data.trangThai=LAMMATSACH;
					currentNodeMT->data.ngayTra=GetDate();
					currentDG->trangthai=KHOA;
					
					ViewSachMuonTable(ArrDG[currentPos], MapId);
					btnXacNhanTra.deleteBtn(BG_COLOR, MapId);
					btnLamMat.deleteBtn(BG_COLOR, MapId);
					drawNotification();
					break;
				case 330:
				case 331:
				case 332:
				case 333:
				case 334:
				case 335:
				case 336:
				case 337://click vao lich su muon tra cua doc gia
				case 338:
				case 339:
				case 340:
				case 341:
				case 342:
					if(edSearchDocGia.content[3]=='\0') {//neu chua nhap doc gia thi ko cho muon
						break;
					}
					currentNodeMT=GetNodeMTById(currentDG->listMT, MapId[y][x]-330);
					drawNotification();
					if(currentNodeMT->data.trangThai!=0) {//neu sach dang muon/da thanh ly thi ko cho muon
						break;
					}
					strcpy(edMaSachMuon.content, currentNodeMT->data.maSach.c_str());
					edMaSachMuon.draw(MapId);
					btnXacNhanTra.draw(MapId);
					btnLamMat.draw(MapId);
					break;
				case 350:
				case 351:
				case 352:
				case 353:
				case 354:// click sach trong top10, cho muon sach trong top10
				case 355:
				case 356:
				case 357:
				case 358:
				case 359:
					currentDS=ArrTopTen[MapId[y][x]-350];
					ViewDanhMucTable(currentDS->listDMS, 0, 10, MapId);
					break;
			}
			
        }
	}
	delay(10);
}

