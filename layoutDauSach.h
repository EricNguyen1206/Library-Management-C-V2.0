#pragma once
#include <iostream>
#include "define.h"
#include "model.h"
#include "model1.h"
#include "local.h"
#include "cautrucDocGia.h"
	
int DauSachController(int **MapId, int &x, int &y) {
	std::cout<<"\ncheck dau sach";
	char buffer[30];
	int mode=0, /*mode = 0: mac dinh,mode = 1: tim kiem*/
	begin=0, 
	end, 
	pos;
	NodeDMS *pNode;
	DauSach *currentDS;
	ArrPointerDauSach searchDS;
	std::cout<<"\ncheck 1";
	Button 	btnThemmoi			(MG+BLOCK*4, UNIT*3+MG*2, BLOCK*4, BLOCK, "Them moi", 			101);
	Button 	btnDieuchinh		(ACTICLE-BLOCK*4, UNIT*3+MG*2, BLOCK*4, BLOCK, "Dieu chinh", 	102);
	Button 	btnTimkiem			(w-BLOCK*3-MG,  UNIT*3+MG*2, BLOCK*3, BLOCK, "Tim", 			103);
	Button 	btnBackTable		(ACTICLE+MG, h-BLOCK*2+MG, BLOCK*3, BLOCK, "<Back", 			104);
	Button 	btnNextTable		(w-BLOCK*3-MG*2, h-BLOCK*2+MG, BLOCK*3, BLOCK, "Next>", 		105);
	Button 	btnConfirmThemmoi	(BLOCK*4, h-BLOCK*2+MG, BLOCK*4, BLOCK, "Xac nhan", 			106);
	Button 	btnDanhMucSach		(MG+1, HEADER+1, BLOCK-2, BLOCK-2, "...", 						107);
	Button 	btnDeleteDauSach	(MG, UNIT*3+MG*2, BLOCK*4, BLOCK, "Xoa", 						108);
	Button 	btnEscapeActicle	(ACTICLE-BLOCK+1, HEADER+1, BLOCK-2, BLOCK-2, "x", 				109);
	
	EditText edTimDauSach	(ACTICLE+MG, UNIT*3+MG*2, BLOCK*16, BLOCK, "", "", "Nhap ten sach vao day", 		110);
	EditText edThemISBN		(BLOCK, YDS[0]-UNIT, BLOCK*7-MG, BLOCK, "ISBN :","","Nhap du 5 so", 				111);
	EditText edThemTenSach	(BLOCK, YDS[1]-UNIT, BLOCK*7-MG, BLOCK, "Ten sach :","","Toi da 25 so va ky tu", 	112);
	EditText edThemSoTrang	(BLOCK, YDS[2]-UNIT, BLOCK*7-MG, BLOCK, "So trang :","","Toi da 5 so", 				113);
	EditText edThemTacGia	(BLOCK, YDS[3]-UNIT, BLOCK*7-MG, BLOCK, "Tac gia :","", "Toi da 20 ky tu", 			114);
	EditText edThemNXB		(BLOCK, YDS[4], BLOCK*7-MG, BLOCK, "Nam xuat ban :","","Nhap du 4 so", 				115);
	EditText edThemTheLoai	(BLOCK, YDS[5]-UNIT, BLOCK*7-MG, BLOCK, "The loai :","","Toi da 20 ky tu", 			116);
	EditText edThongBao		(MG*2, h-BLOCK*2, BLOCK*8-MG*3, BLOCK, "Thong bao :", "", "", 						117);
	EditText edSoLuong		(BLOCK, YDS[4]-BLOCK-MG, BLOCK*7-MG, BLOCK, "So luong :","","Tu 1-999", 			118);
	EditText edViTri		(BLOCK, YDS[5]+MG*2, BLOCK*7-MG, BLOCK, "Vi tri :","","Toi da 25 so va ky tu", 		119);
	EditText edMaSach		(BLOCK, YDS[1], BLOCK*7-MG, BLOCK, "Ma sach:", "", "", 								163);
	std::cout<<"\ncheck 2";
	refreshMainLayout(MapId);
	drawHeader(MapId, 1);
	edTimDauSach.draw(MapId);
	btnBackTable.draw(MapId);
	btnNextTable.draw(MapId);
	btnBackMenu.draw(MapId);
	btnThemmoi.draw(MapId);
	btnTimkiem.draw(MapId);
	btnExit.draw(MapId);
	std::cout<<"\ncheck 2.1";
	SortDS(ArrDauSach);
	end=13;
	std::cout<<"\ncheck 2.2";
	ViewDSTable(ArrDauSach, begin, end, MapId);
	std::cout<<"\ncheck 3";
	while(1) {
		delay(0.0001);
        if (ismouseclick(WM_LBUTTONDOWN)){
            getmouseclick(WM_LBUTTONDOWN, x, y);
            std::cout<<"\nleft click:"<<x<<" "<<y<<"="<<MapId[y][x];
            switch(MapId[y][x]) {
            	case -1://Quay ve menu
            		return 0;
            	case -2://Luu data va thoat chuong trinh
            		exit(1);
            	case 101://Che do them moi
					if(btnThemmoi.isChoose) {
						break;
					}
					drawNotification();
	            	btnThemmoi.isChoose=true;
	            	btnThemmoi.draw(MapId);
            		btnEscapeActicle.draw(MapId);
					
					edThemISBN.clear();
					edThemTenSach.clear();
					edThemSoTrang.clear();
					edThemTacGia.clear();
					edThemNXB.clear();
					edThemTheLoai.clear();
					edSoLuong.clear();
					edViTri.clear();
					
            		edThemISBN.draw(MapId);
					edThemTenSach.draw(MapId);
					edThemSoTrang.draw(MapId);
					edThemTacGia.draw(MapId);
					edThemNXB.draw(MapId);
					edThemTheLoai.draw(MapId);
					edSoLuong.draw(MapId);
					edViTri.draw(MapId);
					
					break;
            	case 102://Che do dieu chinh
            		if(!(btnDieuchinh.isLock)) {
						if(atoi(edSoLuong.content)<currentDS->soLuong) {
							drawNotification(ChiDuocTangSoLuong);
							goto ChinhSoLuong;//case 118
						} else {
							int loopstep=atoi(edSoLuong.content)-currentDS->soLuong;
							char MaSach[10];
							danhMucSach *dms;
							for(int i=1; i<=loopstep; i++) {
								itoa(++(currentDS->soLuong), buffer, 10);
								strcpy(MaSach, currentDS->ISBN);
								strcat(MaSach, "_");
								strcat(MaSach, buffer);
								dms = new danhMucSach;
								strcpy(dms->MaSach, MaSach);
								dms->TrangThai=0;
								dms->ViTri=currentDS->listDMS->pFirst->data.ViTri;
								InsertLastDMS(currentDS->listDMS, dms);
								std::cout<<"\ncheck chinh sua so luong: "<<dms->MaSach;
							}
						}
						drawActicle();
	            		
	            		strcpy(currentDS->ISBN, edThemISBN.content);
						currentDS->tenSach=edThemTenSach.content;
						currentDS->soTrang=atoi(edThemSoTrang.content);
						currentDS->tacGia=edThemTacGia.content;
						currentDS->namXuatBan=atoi(edThemNXB.content);
						currentDS->theLoai=edThemTheLoai.content;
	            		
	            		ViewDSTable(ArrDauSach, begin, end, MapId);
	            		
	            		edThemISBN.deleteEdText(MAIN_COLOR, MapId);
						edThemTenSach.deleteEdText(MAIN_COLOR, MapId);
						edThemSoTrang.deleteEdText(MAIN_COLOR, MapId);
						edThemTacGia.deleteEdText(MAIN_COLOR, MapId);
						edThemNXB.deleteEdText(MAIN_COLOR, MapId);
						edThemTheLoai.deleteEdText(MAIN_COLOR, MapId);
						
						drawNotification(HieuChinhSachThanhCong);
						btnDanhMucSach.isLock=false;
						btnDieuchinh.deleteBtn(BG_COLOR, MapId);
						btnDeleteDauSach.deleteBtn(BG_COLOR, MapId);
						btnThemmoi.draw(MapId);
						break;
					}
            	case 103://Tim kiem dau sach
            		searchDS = SearchDauSach(ArrDauSach, edTimDauSach.content);
            		edTimDauSach.clear();
            		edTimDauSach.draw(MapId);
            		ViewDSTable(searchDS, 0, searchDS.n>=13?13:searchDS.n, MapId);
            		mode=1;//mode = 0: mac dinh,mode = 1: tim kiem
            		break;
            	case 104://Quay ve trang truoc
            		if(begin>0 && !btnBackTable.isLock) {
						begin-=13;
						end -= end%13==0 ? 13 : ArrDauSach.n%13;
						if(begin==0) {
							btnBackTable.isLock = true;
							btnBackTable.draw(MapId);
						}
						ViewDSTable(ArrDauSach, begin, end, MapId);
						btnNextTable.isLock = false;
						btnNextTable.draw(MapId);
					} 
            		break;
            	case 105://Trang ke tiep
            		if(end < ArrDauSach.n && !btnNextTable.isLock) {
						begin+=13;
						if(ArrDauSach.n-end<13) {
							end+=ArrDauSach.n-end;
							btnNextTable.isLock = true;
							btnNextTable.draw(MapId);
						} 
						else end+=13;
						ViewDSTable(ArrDauSach, begin, end, MapId);
						btnBackTable.isLock = false;
						btnBackTable.draw(MapId);
					} else {
						btnNextTable.isLock = true;
						btnNextTable.draw(MapId);
					}
            		break;
            	case 106://btn xac nhan them dau sach
            		if(edThemISBN.content[0]=='\0' 
					|| edThemTenSach.content[0]=='\0' 
					|| edThemSoTrang.content[0]=='\0' 
					|| edThemTacGia.content[0]=='\0' 
					|| edThemNXB.content[0]=='\0' 
					|| edThemTheLoai.content[0]=='\0' 
					|| edSoLuong.content[0]=='\0' 
					|| edViTri.content[0]=='\0' ) {
            			btnConfirmThemmoi.deleteBtn(BG_COLOR, MapId);
						drawNotification(ThongTinKhongDuocDeTrong);
					} else {
						currentDS = new DauSach;
						strcpy(currentDS->ISBN, edThemISBN.content);
						currentDS->tenSach=edThemTenSach.content;
						currentDS->soTrang=atoi(edThemSoTrang.content);
						currentDS->tacGia=edThemTacGia.content;
						currentDS->namXuatBan=atoi(edThemNXB.content);
						currentDS->theLoai=edThemTheLoai.content;
						currentDS->soLuong=atoi(edSoLuong.content);
						if(!CheckISBN(ArrDauSach, currentDS)) {
							btnConfirmThemmoi.deleteBtn(BG_COLOR, MapId);
							drawNotification(IsbnDaTonTai);
							goto labelThemDauSach;
						}
						if(currentDS->namXuatBan>2021) {
							btnConfirmThemmoi.deleteBtn(BG_COLOR, MapId);
							drawNotification(NamXuatBanKhongHopLe);
							goto labelNhapNXB;
						}
						
						currentDS->listDMS=CreateListDMS(currentDS->ISBN, edViTri.content, currentDS->soLuong);
						std::cout << InsertDauSach(ArrDauSach, currentDS);
						SortDS(ArrDauSach);
						
						if(end%13!=0) {
							end++;
						}
						ViewDSTable(ArrDauSach, begin, end, MapId);
						edThemISBN.clear();
						edThemTenSach.clear();
						edThemSoTrang.clear();
						edThemTacGia.clear();
						edThemNXB.clear();
						edThemTheLoai.clear();
						
						edThemISBN.deleteEdText(MAIN_COLOR, MapId);
						edThemTenSach.deleteEdText(MAIN_COLOR, MapId);
						edThemSoTrang.deleteEdText(MAIN_COLOR, MapId);
						edThemTacGia.deleteEdText(MAIN_COLOR, MapId);
						edThemNXB.deleteEdText(MAIN_COLOR, MapId);
						edThemTheLoai.deleteEdText(MAIN_COLOR, MapId);
						
						drawActicle();
						
						btnThemmoi.isChoose=false;
	            		btnThemmoi.draw(MapId);
	            		
	            		btnConfirmThemmoi.deleteBtn(BG_COLOR, MapId);
						drawNotification(ThemSachThanhCong);
					}
            		break;
				case 107://in danh muc sach
					{	PrintDMS:
						int tmp1=0, tmp2=(currentDS->soLuong<=13?currentDS->soLuong:13);
						btnDanhMucSach.isLock=true;
						btnDanhMucSach.draw(MapId);
						ViewDanhMucTable(currentDS->listDMS, tmp1, tmp2,MapId);
						btnNextTable.deleteBtn(BG_COLOR, MapId);
						btnBackTable.deleteBtn(BG_COLOR, MapId);
					}
            		break;
				case 108://xoa dau sach
					if(currentDS->luotMuon!=0) {
						drawNotification(KhongDuocXoaSachNay);
					}
					edThemISBN.clear();
					edThemTenSach.clear();
					edThemSoTrang.clear();
					edThemTacGia.clear();
					edThemNXB.clear();
					edThemTheLoai.clear();
					edSoLuong.clear();
					edViTri.clear();
					
					edThemISBN.deleteEdText(MAIN_COLOR, MapId);
					edThemTenSach.deleteEdText(MAIN_COLOR, MapId);
					edThemSoTrang.deleteEdText(MAIN_COLOR, MapId);
					edThemTacGia.deleteEdText(MAIN_COLOR, MapId);
					edThemNXB.deleteEdText(MAIN_COLOR, MapId);
					edThemTheLoai.deleteEdText(MAIN_COLOR, MapId);
					edSoLuong.deleteEdText(MAIN_COLOR, MapId);
					edViTri.deleteEdText(MAIN_COLOR, MapId);
					XoaDauSach(ArrDauSach, pos);
					drawNotification(XoaDauSachThanhCong);
					if(end%13!=0 || end > ArrDauSach.n) end--;
					ViewDSTable(ArrDauSach, begin, end, MapId);
					btnDieuchinh.deleteBtn(BG_COLOR, MapId);
					btnDeleteDauSach.deleteBtn(BG_COLOR, MapId);
					btnThemmoi.draw(MapId);
					break;
				case 109://nut x tren Acticle
					if(btnDanhMucSach.isLock) {
						btnDanhMucSach.isLock=false;
						btnDanhMucSach.draw(MapId);
	            		
	            		edMaSach.deleteEdText(MAIN_COLOR, MapId);
	            		edViTri.deleteEdText(MAIN_COLOR, MapId);
	            		
	            		edThemISBN.draw(MapId);
						edThemTenSach.draw(MapId);
						edThemSoTrang.draw(MapId);
						edThemTacGia.draw(MapId);
						itoa(currentDS->soLuong, buffer, 10);
						strcpy(edSoLuong.content, buffer);
						edSoLuong.draw(MapId);
						edThemNXB.draw(MapId);
						edThemTheLoai.draw(MapId);
						drawNotification();
						ViewDSTable(ArrDauSach, begin, end, MapId);
						btnBackTable.draw(MapId);
						btnNextTable.draw(MapId);
	            		break;
					}
					edThemISBN.deleteEdText(MAIN_COLOR, MapId);
					edThemTenSach.deleteEdText(MAIN_COLOR, MapId);
					edThemSoTrang.deleteEdText(MAIN_COLOR, MapId);
					edThemTacGia.deleteEdText(MAIN_COLOR, MapId);
					edThemNXB.deleteEdText(MAIN_COLOR, MapId);
					edThemTheLoai.deleteEdText(MAIN_COLOR, MapId);
					edSoLuong.deleteEdText(MAIN_COLOR, MapId);
					edViTri.deleteEdText(MAIN_COLOR, MapId);
					drawNotification();

					btnDieuchinh.deleteBtn(BG_COLOR, MapId);
					btnDeleteDauSach.deleteBtn(BG_COLOR, MapId);

					btnDanhMucSach.deleteBtn(ACTIVE_COLOR, MapId);
					if(!btnThemmoi.isChoose) {
						ViewDSTable(ArrDauSach, begin, end, MapId);
						btnNextTable.draw(MapId);
						btnBackTable.draw(MapId);
					}
					btnThemmoi.isChoose=false;
					btnThemmoi.draw(MapId);
					btnBackMenu.draw(MapId);
					btnExit.draw(MapId);
					btnEscapeActicle.deleteBtn(ACTIVE_COLOR, MapId);
					break;
            	case 110://Nhap vao ten sach can tim
            		ScanSearchDS(edTimDauSach, 30, ArrDauSach, searchDS, MapId);
            		mode = 1;//mode = 0: mac dinh,mode = 1: tim kiem
            		break;
            	case 111://Nhap ISBN
            		labelThemDauSach:
            		if(btnThemmoi.isChoose) {
		    			ScanNumber(edThemISBN, 5, MapId);
					}
            	case 112://Nhap Ten sach
            		ScanString(edThemTenSach, 25, MapId);
            	case 113://Nhap So trang
            		ScanNumber(edThemSoTrang, 5, MapId);
            	case 114://Nhap Tac gia
            		ScanString(edThemTacGia, 20, MapId);
            	case 118://Nhap So luong
            		ChinhSoLuong:
            		ScanNumber(edSoLuong, 3, MapId);
            	case 115://Nhap Nam xuat bang
					labelNhapNXB:
            		ScanNumber(edThemNXB, 4, MapId);
            	case 116://Nhap The loai
            		ScanString(edThemTheLoai, 20, MapId);
            	case 119://Nhap vi tri
            		if(btnThemmoi.isChoose) {
		        		ScanString(edViTri, 20, MapId);
		        		drawNotification();
		        		btnConfirmThemmoi.draw(MapId);
		        		break;
					}
            		btnDieuchinh.isLock=false;
            		btnDieuchinh.draw(MapId);
            		break;
            	case 120:
            	case 121:
            	case 122:
            	case 123:
            	case 124:
            	case 125://Chon cac dau sach trong table
            	case 126:
            	case 127:
            	case 128:
            	case 129:
            	case 130:
            	case 131:
            	case 132:
            		btnThemmoi.deleteBtn(BG_COLOR, MapId);
            		btnDieuchinh.isLock=true;
            		btnDieuchinh.draw(MapId);
            		btnDeleteDauSach.draw(MapId);
            		btnDanhMucSach.draw(MapId);
            		btnEscapeActicle.draw(MapId);
            		pos=MapId[y][x]-120+begin;
            		if(mode == 1) {//mode = 0: mac dinh,mode = 1: tim kiem
            			currentDS=searchDS.dsDauSach[pos];
					} else {
            			currentDS=ArrDauSach.dsDauSach[pos];
					}
            		strcpy(edThemISBN.content, currentDS->ISBN);
					strcpy(edThemTenSach.content, currentDS->tenSach.c_str());
					itoa(currentDS->soTrang, buffer, 10);
					strcpy(edThemSoTrang.content, buffer);
					strcpy(edThemTacGia.content, currentDS->tacGia.c_str());
					itoa(currentDS->soLuong, buffer, 10);
					strcpy(edSoLuong.content, buffer);
					itoa(currentDS->namXuatBan, buffer, 10);
					strcpy(edThemNXB.content, buffer);
					strcpy(edThemTheLoai.content, currentDS->theLoai.c_str());
					edThemISBN.draw(MapId);
					edThemTenSach.draw(MapId);
					edThemSoTrang.draw(MapId);
					edThemTacGia.draw(MapId);
					edSoLuong.draw(MapId);
					edThemNXB.draw(MapId);
					edThemTheLoai.draw(MapId);
					drawNotification();
            		break;
            	case 200://chuyen sang layoutDocGia
            		return 2;
            	case 300://chuyen sang layoutMuonTra
					return 3;
			}
			
        }
	}
	delay(10);
}
