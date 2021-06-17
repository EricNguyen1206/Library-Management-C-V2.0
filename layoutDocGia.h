#pragma once
#include "model.h"
#include "local.h"
#include "define.h"
#include "layoutDauSach.h"
#include "cautrucDocGia.h"
#include "model1.h"
#include <iostream>
#include <string>
#include <stdlib.h>

int DocGiaController(int **MapId, int &x, int &y) {
	int lenDG=0, begin=0, end, mode=1, index;
	int NewId;
	char buffer[33];
	NodeBST *p = new NodeBST;
	DocGia ListDG[MAXDOCGIA];
	DocGia current;
	CreateDocGiaArr(CayDocGia, ListDG, lenDG);
//	lenDG--';
	std::cout<<"\n lenDG:" << lenDG;
	refreshMainLayout(MapId);
	drawHeader(MapId, 2);
	
	Button btnThemDocGia(MG, UNIT*3+MG*2, BLOCK*4, BLOCK, "Them moi", 201);
	Button btnDieuChinhDocGia(ACTICLE-BLOCK*4, UNIT*3+MG*2, BLOCK*4, BLOCK, "Dieu chinh", 202);
	Button btnFilterId(ACTICLE+MG, BLOCK*3-MG, BLOCK*4, BLOCK, "Ma the", 203);
	Button btnFilterName(ACTICLE+BLOCK*4+MG, BLOCK*3-MG, BLOCK*4, BLOCK, "Ten", 204);
	Button btnBackTable(ACTICLE+MG, h-BLOCK*2+MG, BLOCK*3, BLOCK, "<Back", 205);
	Button btnNextTable(w-BLOCK*3-MG*2, h-BLOCK*2+MG, BLOCK*3, BLOCK, "Next>", 206);
	Button btnGenderMale(BLOCK, YDS[3], BLOCK*3, BLOCK, "Nam", 207);
	Button btnGenderFemale(BLOCK*4, YDS[3], BLOCK*3, BLOCK, "Nu", 208);
	Button btnConditionActive(BLOCK, YDS[4], BLOCK*4, BLOCK, "Hoat dong", 209);
	Button btnConditionBlocked(BLOCK*5, YDS[4], BLOCK*4, BLOCK, "Bi khoa", 210);
	
	EditText edIdCard(BLOCK, YDS[0], BLOCK*7-MG, BLOCK, "Ma the :","","", 211);
	EditText edLastName(BLOCK, YDS[1], BLOCK*7-MG, BLOCK, "Ho :","","", 212);
	EditText edFirstName(BLOCK, YDS[2], BLOCK*7-MG, BLOCK, "Ten :","","", 213);
	
	Button btnConfirmThemDocGia(BLOCK*4, h-BLOCK*2+MG, BLOCK*4, BLOCK, "Xac nhan", 214);
	Button btnXoaDocGia(MG, UNIT*3+MG*2, BLOCK*4, BLOCK, "Xoa", 216);
	
	btnBackMenu.draw(MapId);
	btnExit.draw(MapId);
	
	btnThemDocGia.draw(MapId);
	btnFilterId.isChoose=true;
	btnFilterId.draw(MapId);
	btnFilterName.draw(MapId);
	
	drawTable(MapId, tableTitleDocGia1, tableTitleWidthDocGia1, 5);
	end = (lenDG>=13) ? 13 : lenDG;
	SortDG(ListDG, lenDG, maDocGia);
	std::cout << "\nbegin:"<<begin<<" end:"<<end;
	PrintDGTable(ListDG, begin , end, MapId);
	btnBackTable.isLock=true;
	btnBackTable.draw(MapId);
	btnNextTable.draw(MapId);
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
				case 201:
					if(!(btnThemDocGia.isLock || btnThemDocGia.isChoose)) {
	            		drawActicle();
	            		btnThemDocGia.isChoose=true;
	            		btnThemDocGia.draw(MapId);
	            		NewId=getIdDocGia(lenDG+1);
	            		itoa(NewId, buffer, 10);
	            		strcpy(edIdCard.content, buffer);
	            		
	            		edIdCard.draw(MapId);
						edLastName.draw(MapId);
						edFirstName.draw(MapId);
						btnGenderMale.draw(MapId);
						btnGenderFemale.draw(MapId);
						btnConditionActive.draw(MapId);
						btnConditionBlocked.draw(MapId);
					}
					break;
            	case 202:
            		if(edLastName.content[0] == '\0' || edFirstName.content[0] == '\0' 
					|| (!btnGenderMale.isChoose && !btnGenderFemale.isChoose)
					|| (!btnConditionActive.isChoose && !btnConditionBlocked.isChoose)) {
            			drawNotification(ThongTinKhongDuocDeTrong);
					} else {
	            		drawActicle();
						p->data.ho=edLastName.content;
						p->data.ten=edFirstName.content;
						p->data.phai=btnGenderMale.isChoose?0:1;
						p->data.trangthai=btnConditionBlocked.isChoose?0:1;
						ListDG[index].ho=edLastName.content;
						ListDG[index].ten=edFirstName.content;
						ListDG[index].phai=btnGenderMale.isChoose?0:1;
						ListDG[index].trangthai=btnConditionBlocked.isChoose?0:1;
						refreshTable(MapId, tableTitleWidthDocGia1, 5);
						PrintDGTable(ListDG, begin, end, MapId);
						btnConditionBlocked.deleteBtn(MAIN_COLOR, MapId);
	            		btnConditionActive.deleteBtn(MAIN_COLOR, MapId);
						btnDieuChinhDocGia.deleteBtn(BG_COLOR, MapId);
	            		btnGenderFemale.deleteBtn(MAIN_COLOR, MapId);
	            		btnGenderMale.deleteBtn(MAIN_COLOR, MapId);
	            		edFirstName.deleteEdText(MAIN_COLOR, MapId);
	            		edLastName.deleteEdText(MAIN_COLOR, MapId);
	            		edIdCard.deleteEdText(MAIN_COLOR, MapId);
						drawNotification(HieuChinhDocGiaThanhCong);
	            		btnThemDocGia.isChoose=false;
	            		btnThemDocGia.isLock=false;
	            		btnThemDocGia.draw(MapId);
	            		edFirstName.clear();
	            		edLastName.clear();
	            		edIdCard.clear();
					}
					break;
				case 203:
					if(!btnFilterId.isChoose) {
						btnFilterId.toggle(btnFilterName, MapId);
						mode=maDocGia;
						SortDG(ListDG, lenDG, mode);
	            		refreshTable(MapId, tableTitleWidthDocGia1, 5);
						PrintDGTable(ListDG, begin, end, MapId);
					}
					break;
				case 204:
					if(!btnFilterName.isChoose) {
						btnFilterName.toggle(btnFilterId, MapId);
						refreshTable(MapId, tableTitleWidthDocGia1, 5);
						mode=hoTen;
						SortDG(ListDG, lenDG, mode);
	            		refreshTable(MapId, tableTitleWidthDocGia1, 5);
						PrintDGTable(ListDG, begin, end, MapId);
					}
					break;
				case 205:
					if(begin>0 && !btnBackTable.isLock) {
//						index = 0;
						begin-=13;
						end -= end%13==0 ? 13 : lenDG%13;
						if(begin==0) {
							btnBackTable.isLock = true;
							btnBackTable.draw(MapId);
						}
						refreshTable(MapId, tableTitleWidthDocGia1, 5);
//						PrintDocGiaTable(CayDocGia, begin, end, index, MapId);
						PrintDGTable(ListDG, begin , end, MapId);
						btnNextTable.isLock = false;
						btnNextTable.draw(MapId);
					} 
					break;
				case 206:
					if(end < lenDG && !btnNextTable.isLock) {
//						index = 0;
						begin+=13;
						if(lenDG-end<13) {
							end+=lenDG-end;
							btnNextTable.isLock = true;
							btnNextTable.draw(MapId);
						} 
						else end+=13;
						refreshTable(MapId, tableTitleWidthDocGia1, 5);
//						PrintDocGiaTable(CayDocGia, begin, end, index, MapId);
						PrintDGTable(ListDG, begin , end, MapId);
						btnBackTable.isLock = false;
						btnBackTable.draw(MapId);
					} else {
						btnNextTable.isLock = true;
						btnNextTable.draw(MapId);
					}
					break;
            	case 207:
            		if(!btnGenderMale.isChoose) {
            			btnGenderMale.toggle(btnGenderFemale, MapId);
            			if(btnDieuChinhDocGia.isLock) {
            				btnDieuChinhDocGia.isLock=false;
            				btnDieuChinhDocGia.draw(MapId);
						}
					}
            		break;
            	case 208:
            		if(!btnGenderFemale.isChoose) {
            			btnGenderFemale.toggle(btnGenderMale, MapId);
            			if(btnDieuChinhDocGia.isLock) {
            				btnDieuChinhDocGia.isLock=false;
            				btnDieuChinhDocGia.draw(MapId);
						}
					}
            		break;
            	case 209:
            		if(!btnConditionActive.isChoose) {
            			btnConditionActive.toggle(btnConditionBlocked, MapId);
            			if(btnDieuChinhDocGia.isLock) {
            				btnDieuChinhDocGia.isLock=false;
            				btnDieuChinhDocGia.draw(MapId);
						}
					}
            		break;
            	case 210:
            		if(!btnConditionBlocked.isChoose) {
            			btnConditionBlocked.toggle(btnConditionActive, MapId);
            			if(btnDieuChinhDocGia.isLock) {
            				btnDieuChinhDocGia.isLock=false;
            				btnDieuChinhDocGia.draw(MapId);
						}
					}
            		break;
            	case 212:
            	case 213:
            		drawNotification();
            		if(btnThemDocGia.isChoose) {
            			ScanString(edLastName, 13, MapId);
            			ScanString(edFirstName, 13, MapId);
            			btnConfirmThemDocGia.draw(MapId);
					} else {
						ScanString(edLastName, 13, MapId);
            			ScanString(edFirstName, 13, MapId);
            			btnDieuChinhDocGia.isLock=false;
            			btnDieuChinhDocGia.draw(MapId);
					}
            		break;
            	case 214:
            		if(edLastName.content[0] == '\0' || edFirstName.content[0] == '\0' 
					|| (!btnGenderMale.isChoose && !btnGenderFemale.isChoose)
					|| (!btnConditionActive.isChoose && !btnConditionBlocked.isChoose)) {
            			btnConfirmThemDocGia.deleteBtn(BG_COLOR, MapId);
            			drawNotification(ThongTinKhongDuocDeTrong);
					} else {//Tao Node Doc Gia, them vao BST
	            		DocGia DocGiaNew(
						NewId, 
						edLastName.content, 
						edFirstName.content, 
						btnGenderMale.isChoose?0:1, 
						btnConditionBlocked.isChoose?0:1
						); end+=(end%13==0||end!=lenDG)?0:1;
	            		std::cout<<InsertNode(CayDocGia, CreateNode(DocGiaNew));
	            		lenDG=0;
            			CreateDocGiaArr(CayDocGia, ListDG, lenDG);
            			lenDG--;
            			std::cout<<"\ncheck lenDG"<<lenDG;
						if(end<lenDG+1) {
							btnNextTable.isLock=false;
							btnNextTable.draw(MapId);
						}
            			std::cout<<"\ncheck lenDG sau them:"<<lenDG<<" check mode:"<<mode;
            			mode = btnFilterId.isChoose ? 0 : 1;
            			SortDG(ListDG, lenDG, mode);
	            		refreshTable(MapId, tableTitleWidthDocGia1, 5);
	            		PrintDGTable(ListDG, begin, end, MapId);
						btnConfirmThemDocGia.deleteBtn(BG_COLOR, MapId);
						btnConditionBlocked.deleteBtn(MAIN_COLOR, MapId);
	            		btnConditionActive.deleteBtn(MAIN_COLOR, MapId);
	            		btnGenderFemale.deleteBtn(MAIN_COLOR, MapId);
	            		btnGenderMale.deleteBtn(MAIN_COLOR, MapId);
	            		edFirstName.deleteEdText(MAIN_COLOR, MapId);
	            		edLastName.deleteEdText(MAIN_COLOR, MapId);
	            		edIdCard.deleteEdText(MAIN_COLOR, MapId);
						drawNotification(ThemDocGiaThanhCong);
	            		btnThemDocGia.isChoose=false;
	            		btnThemDocGia.isLock=false;
	            		btnThemDocGia.draw(MapId);
	            		edFirstName.clear();
	            		edLastName.clear();
	            		edIdCard.clear();
	            		lenDG++;
					}
            		break;
            	case 216:
            		end-=(end%13==0&&end!=lenDG)?0:1;
            		std::cout<<DeleteNodeBST(CayDocGia, p);
            		lenDG=0;
        			std::cout<<"\ncheck xoa";
        			CreateDocGiaArr(CayDocGia, ListDG, lenDG);
//        			lenDG--;
        			std::cout<<"\ncheck lenDG sau xoa:"<<lenDG<<" check mode:"<<mode;
        			mode = btnFilterId.isChoose ? 0 : 1;
        			SortDG(ListDG, lenDG, mode);
            		refreshTable(MapId, tableTitleWidthDocGia1, 5);
	            	PrintDGTable(ListDG, begin, end, MapId);
					btnConditionBlocked.deleteBtn(MAIN_COLOR, MapId);
            		btnConditionActive.deleteBtn(MAIN_COLOR, MapId);
					btnDieuChinhDocGia.deleteBtn(BG_COLOR, MapId);
            		btnGenderFemale.deleteBtn(MAIN_COLOR, MapId);
            		btnGenderMale.deleteBtn(MAIN_COLOR, MapId);
            		edFirstName.deleteEdText(MAIN_COLOR, MapId);
            		edLastName.deleteEdText(MAIN_COLOR, MapId);
            		edIdCard.deleteEdText(MAIN_COLOR, MapId);
					drawNotification(XoaDocGiaThanhCong);
            		btnThemDocGia.isChoose=false;
            		btnThemDocGia.isLock=false;
            		btnThemDocGia.draw(MapId);
            		edFirstName.clear();
            		edLastName.clear();
            		edIdCard.clear();
            		break;
            	case 230:
            	case 231:
            	case 232:
            	case 233:
            	case 234:
            	case 235:
            	case 236:
            	case 237:
            	case 238:
            	case 239:
            	case 240:
            	case 241:
            	case 242:
//            		std::cout<<" Id Doc Gia:"<<IdCurrentDocGia[MapId[y][x]-230];
            		btnThemDocGia.deleteBtn(BG_COLOR, MapId);
            		btnDieuChinhDocGia.isLock=true;
            		btnDieuChinhDocGia.draw(MapId);
            		btnXoaDocGia.draw(MapId);
	            	drawActicle();
	            	index=MapId[y][x]-230+begin;
	            	std::cout<<"\ncheck chi so "<<index;
	            	p=FindNodeById(CayDocGia, ListDG[MapId[y][x]-230+begin].MATHE);
	            	std::cout<<"\ncheck ma doc gia "<<p->data.MATHE;
	            	current=p->data;
	            	itoa(current.MATHE, buffer, 10);
	            	strcpy(edIdCard.content, buffer);
	            	strcpy(edLastName.content, current.ho.c_str());
	            	strcpy(edFirstName.content, current.ten.c_str());
            		if(current.phai==0) {
            			btnGenderMale.isChoose=true;
            			btnGenderFemale.isChoose=false;
					} else {
						btnGenderMale.isChoose=false;
            			btnGenderFemale.isChoose=true;
					}
					if(current.trangthai==0) {
						btnConditionActive.isChoose=false;
						btnConditionBlocked.isChoose=true;
					} else {
						btnConditionActive.isChoose=true;
						btnConditionBlocked.isChoose=false;
					}
            		edIdCard.draw(MapId);
					edLastName.draw(MapId);
					edFirstName.draw(MapId);
					btnGenderMale.draw(MapId);
					btnGenderFemale.draw(MapId);
					btnConditionActive.draw(MapId);
					btnConditionBlocked.draw(MapId);
            		break;
//            	case 300:
//            		return 3;
			}
			
        }
	}
	delay(10);
	std::cout << "Check5\n";
}
