#pragma once
#include "model.h"
#include "local.h"
#include "define.h"
#include "layoutDauSach.h"
#include "layoutDauSach.h"

int MuonTraController(int **MapId, int &x, int &y) {
	refreshMainLayout(MapId);
	drawHeader(MapId, 3);
	
	Button btnMuonSach(MG, UNIT*3+MG*2, BLOCK*4, BLOCK, "Muon Sach", 301);
	Button btnTraSach(ACTICLE-BLOCK*4, UNIT*3+MG*2, BLOCK*4, BLOCK, "Tra sach", 302);
	Button btnTopTen(w-BLOCK*10-MG, UNIT*3+MG*2, BLOCK*9, BLOCK, "Top 10 sach muon nhieu", 303);
	Button btnSearchDocGia(ACTICLE-BLOCK-MG*3, YDS[0], BLOCK+MG*2, BLOCK, "Tim", 304);
	
	EditText edSearchDocGia(MG*2, YDS[0], BLOCK*6, BLOCK, "Nhap ma the :", "", "Toi da 5 so", 310);
	EditText edNameDocGia(BLOCK, YDS[1], BLOCK*7-MG, BLOCK, "Doc gia :", "", "", 311);
	EditText edMaTheDocGia(BLOCK, YDS[2], BLOCK*7-MG, BLOCK, "Ma the :", "", "", 312);
	EditText edGioiTinhDocGia(BLOCK, YDS[3], BLOCK*7-MG, BLOCK, "Gioi tinh :", "", "", 313);
	EditText edTrangThaiTheDocGia(BLOCK, YDS[4], BLOCK*7-MG, BLOCK, "Trang thai the :", "", "", 314);
	
	btnBackMenu.draw(MapId);
	btnExit.draw(MapId);
	
	btnMuonSach.draw(MapId);
	btnTraSach.draw(MapId);
	btnTopTen.draw(MapId);
	btnSearchDocGia.draw(MapId);
	
	edSearchDocGia.draw(MapId);
	edNameDocGia.draw(MapId);
	edMaTheDocGia.draw(MapId);
	edGioiTinhDocGia.draw(MapId);
	edTrangThaiTheDocGia.draw(MapId);
	
	drawTable(MapId, tableTitleMuonTra, tableTitleWidthMuonTra, 4);
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
            		btnMuonSach.toggle(btnMuonSach, MapId);
            		break;
            	case 302:
            		btnTraSach.toggle(btnTraSach, MapId);
            		break;
            	case 303:
            		btnTraSach.toggle(btnTraSach, MapId);
            		break;
            	case 304:
            		edSearchDocGia.clear();
            		break;
            	case 310:
            		ScanNumber(edSearchDocGia, 5, MapId);
            		edSearchDocGia.clear();
            		break;
			}
			
        }
	}
	delay(10);
	std::cout << "Check5\n";
}

