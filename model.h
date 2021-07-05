#pragma once
#include <iostream>
#include "define.h"
#include "local.h"
#include <string>
#include "cautrucDocGia.h"
#include "model1.h"

void resetMapID(int **MapId);
void refreshMapID(int **MapId);
void setId(int **MapId, int x, int y, int width, int height, int Id);
void drawBox(int x, int y, int width, int height, int color);
void drawTitle(char title[], int align, int font_size);
//void ViewStartScreen(Button routeDauSach, Button routeDocGia, Button routeMuonTra, Button ExitApp int **MapId);
void drawHeader(int **MapId, int index);
void refreshMainLayout(int **MapId);
void drawActicle();
//void drawActicle(int **MapId, char title[]="", Button btn);
//void drawNotification(char noti[]=NULL);
void refreshTable(int **MapId, int widthArr[], int colNum);
void drawTable(int **MapId, char title[][30], int widthArr[], int colNum);
void printMapId(int **MapId, int x, int y, int width, int height);
//void ScanString(EditText &EDIT, int maxlen, int **MapId);
//void ScanNumber(EditText &EDIT, int maxlen, int **MapId);

struct Button{
	int ID;
	int x, y;
	int width, height;
	char title[30];
	bool isHover, isChoose, isLock;
	
	Button(int xx, int yy, int wid, int hei, char s[30], int id){
		x = xx; y = yy;
		width = wid; height = hei;
		strcpy(title, s);
		ID = id;
		isHover = false;
		isChoose = false;
		isLock = false;
	}
	
	
	void draw(int **MapId){
		drawBox(x, y, width, height, isLock ? MAIN_COLOR : (isChoose ? ACTIVE_COLOR : DEFAULT_COLOR));
		setId(MapId, x, y, width, height, ID);
		settextstyle(BUTTON_FONT, 0, 2);
		setbkcolor( isLock ? MAIN_COLOR : (isChoose ? ACTIVE_COLOR : DEFAULT_COLOR));
		setcolor(isHover ? BG_COLOR : 0);
		outtextxy(x+width/2-textwidth(this->title)/2, y+height/2-textheight(this->title)/2, title);
		setbkcolor(BG_COLOR);
	}
	
	void deleteBtn(int color, int **MapId) {
//		this->isLock=false;
//		this->isHover=false;
//		this->isChoose=false;
		setfillstyle(1, color);
		bar(this->x, this->y, this->x+this->width+1, this->y+this->height+1);
		setId(MapId, this->x, this->y, this->width, this->height, 0);
	}
	
	bool isMouseHover(int mx, int my){
		if(mx >= x && mx <= x+width && my >= y  && my <= y+height){
			return true;
		}
		return false;
	}
	
	void toggle(Button &btn, int **MapId) {
		if(this->isChoose) {
			this->isChoose=false;
			this->draw(MapId);
			delay(10);
			btn.isChoose=true;
		} else {
			this->isChoose=true;
			this->draw(MapId);
			delay(10);
			btn.isChoose=false;
		}
		btn.draw(MapId);
		return;
	}
};
Button btnDausach(BLOCK*23, BLOCK, BLOCK*4, UNIT, "Dau sach", 100);
Button btnDocgia(BLOCK*27+MG, BLOCK, BLOCK*3, UNIT, "Doc gia", 200);
Button btnMuontrasach(BLOCK*30 + MG*2, BLOCK, BLOCK*5, UNIT, "Muon tra sach", 300);
Button btnBackMenu(0, 0, BLOCK+MG, UNIT, "<<", -1);
Button btnExit(w-BLOCK, 0, BLOCK, UNIT, "X", -2);

struct EditText{
	int ID;
	int x, y;
	int width, height;
	char title[30], content[30], hint[30];
	bool isHover, isChoose;
	char** dataFill;
	
	EditText(int xx, int yy, int wid, int hei, char s[30], char c[30], char hi[30],int id, char** datafill = NULL){
		x = xx; y = yy;
		ID=id;
		width = wid; height = hei;
		strcpy(title, s);
		strcpy(content, c);
		strcpy(hint, hi);
		isHover = false;
		dataFill = datafill;
	}
	
	void draw(int **MapId){
		settextstyle(TEXT_FONT, 0, 2);
		setcolor(0);
		char buffer[30];
		
		setbkcolor(MAIN_COLOR);
		outtextxy(x, y+(height-textheight("TD"))/2, title);// Ve tieu de
		drawBox(x+BLOCK*4, y, width, height, BG_COLOR);
		setId(MapId, x+BLOCK*4, y, width, height, ID);
		
		if(strlen(content) == 0){
			// Ve hint 
			setcolor(MAIN_COLOR);
			setbkcolor(BG_COLOR);
			outtextxy(x+BLOCK*4+MG, y+(height-textheight("H"))/2, hint);
		}else{
			// Ve noi dung nguoi dung nhap vao
			setcolor(0);
			setbkcolor(BG_COLOR);
			if(textwidth(this->content)<this->width) {
				outtextxy(x+BLOCK*4+MG, y+(height-textheight("C"))/2, content);
			} else {
				int len = (this->width)/textwidth("C");
				char c[len];
				strcpy(buffer, this->content);
				strncpy(c,strrev(buffer), len);
				outtextxy(x+BLOCK*4+MG, y+(height-textheight("C"))/2, strrev(c));
			}
			
			if(dataFill != NULL){
				int pos = toInt();
				if(pos != -1) outtextxy(x+width - textwidth(dataFill[pos]) -20, y+(height-textheight("C"))/2, dataFill[pos]);
			}
		}
		setbkcolor(BG_COLOR);
	}
		
	
	void deleteEdText(int color, int **MapId) {
		setfillstyle(1, color);
		bar(this->x, this->y, this->x+this->width+BLOCK*4+1, this->y+this->height+1);
		setId(MapId, this->x, this->y, this->width, this->height, 0);
	}
	
	int toInt(){
		int x = 0;
		for(int i=0; i<strlen(content); i++){
			if(i > 0 && content[i] == '_') break;
			if(content[i] >= '0' && content[i] <= '9') x = x*10 + (content[i]-'0');
			else return -1;
		}
		return x;
	}
	
	char* trim(){
		int n = strlen(content);
		if(content[n-1] == ' ') content[n-1] = '\0';
		return content;
	}
	
	bool isMouseHover(int mx, int my){
		if(mx >= x+160 && mx <= x+width && my >= y && my <= y+height){
			return true;
		}
		return false;
	}
	
	void clear() {
		memset(&this->content[0], 0, sizeof(this->content));
	}
};

void resetMapID(int **MapId) {
	int i,j;
	for(i=0;i<h; i++) {
		for(j=0; j<w; j++) {
			MapId[i][j]=0;
		}
	}
}


void refreshMapID(int **MapId) {
	int i,j;
	for(i=2;i<h; i++) {
		for(j=0; j<w; j++) {
			MapId[i][j]=0;
		}
	}
}

void setId(int **MapId, int x, int y, int width, int height, int Id) {
	int wid=(x+width);
	int hei=(y+height);
	for(int i=y; i<hei; i++) {
		for(int j=x; j<wid; j++) {
			MapId[i][j]=Id;
		}
	}
}

void drawBox(int x, int y, int width, int height, int color) {
	setfillstyle(1, color);
	bar(x, y, x+width, y+height);
	setcolor(0);
	rectangle(x, y, x+width, y+height);
}

void drawTitle(char title[], int align, int font_size) {//align 1 = left; align 0 = center
	switch(align) {
		case 0:
			settextstyle(TITLE_FONT, 0, font_size);
			setbkcolor(font_size==4 ? MAIN_COLOR : ACTIVE_COLOR);
			setcolor(0);
			outtextxy((w-textwidth(title))/2, BLOCK, title);
			break;
		case 1:
			settextstyle(TITLE_FONT, 0, font_size);
			setbkcolor(font_size==4 ? MAIN_COLOR : ACTIVE_COLOR);
			setcolor(0);
			outtextxy(100, BLOCK, title);
			break;
		
	}
	
}

void ViewStartScreen(Button routeDauSach, Button routeDocGia, Button routeMuonTra, Button InfoProject, Button ExitApp, int **MapId) {
	resetMapID(MapId);
	drawBox(0, 0, w, h, BG_COLOR);
	drawBox(w/2-BLOCK*6, UNIT, BLOCK*12, BLOCK*16, MAIN_COLOR);
	drawTitle(AppTitle, 0, 4);
	routeDauSach.draw(MapId);
	routeDocGia.draw(MapId);
	routeMuonTra.draw(MapId);
	InfoProject.draw(MapId);
	ExitApp.draw(MapId);
}

int AppInfoController(int **MapId) {
	int x, y;
	resetMapID(MapId);
	drawBox(0, 0, w, h, MAIN_COLOR);
	drawBox(0, 0, w, UNIT, MAIN_COLOR);
	btnBackMenu.draw(MapId);
	btnExit.draw(MapId);
	drawTitle(InforProjectTitle, 0, 4);
	settextstyle(TITLE_FONT, 0, 3);
	setbkcolor(MAIN_COLOR);
	setcolor(0);
	outtextxy((w-textwidth("Mon hoc"))/2, HEADER, "Mon hoc");
	outtextxy((w-textwidth("CAU TRUC DU LIEU & GIAI THUAT"))/2, HEADER+UNIT, "CAU TRUC DU LIEU & GIAI THUAT");
	outtextxy((w-textwidth("Giang vien"))/2, YDS[0], "Giang vien");
	outtextxy((w-textwidth("LUU NGUYEN KY THU"))/2, YDS[0]+UNIT, "LUU NGUYEN KY THU");
	outtextxy((w-textwidth("Sinh vien"))/2, YDS[1], "Sinh vien");
	outtextxy((w-textwidth("NGUYEN TRONG TIN, NGUYEN THI NGAN"))/2, YDS[1]+UNIT, "NGUYEN TRONG TIN, NGUYEN THI NGAN");
	outtextxy((w-textwidth("De tai"))/2, YDS[2], "De tai");
	outtextxy((w-textwidth("QUAN LY THU VIEN"))/2, YDS[2]+UNIT, "QUAN LY THU VIEN");
	outtextxy((w-textwidth("----------O----------"))/2, h-BLOCK*6, "----------O----------");
	outtextxy((w-textwidth("2021"))/2, h-BLOCK*3, "2021");
	
	while(1) {
		delay(0.0001);
        if (ismouseclick(WM_LBUTTONDOWN)){
            getmouseclick(WM_LBUTTONDOWN, x, y);
            std::cout<<"\nleft click:"<<x<<" "<<y<<"="<<MapId[y][x];
            switch(MapId[y][x]) {
            	case -1:
            		return 0;
            	case -2:
            		return 5;
            }
        }
    }
    delay(10);
}

void drawHeader(int **MapId, int index) {
	switch(index) {
		case 1:
		case 100:
			drawTitle(DauSachTitle, 1, 4);
			btnDausach.isChoose=true;
			btnDocgia.isChoose=false;
			btnMuontrasach.isChoose=false;
			btnDausach.draw(MapId);
			btnDocgia.draw(MapId);
			btnMuontrasach.draw(MapId);
			break;
			
		case 2:
		case 200:
			drawTitle(DocGiaTitle, 1, 4);
			btnDausach.isChoose=false;
			btnDocgia.isChoose=true;
			btnMuontrasach.isChoose=false;
			btnDausach.draw(MapId);
			btnDocgia.draw(MapId);
			btnMuontrasach.draw(MapId);
			break;
			
		case 3:
		case 300:
			drawTitle(MuonTraTitle, 1, 4);
			btnDausach.isChoose=false;
			btnDocgia.isChoose=false;
			btnMuontrasach.isChoose=true;
			btnDausach.draw(MapId);
			btnDocgia.draw(MapId);
			btnMuontrasach.draw(MapId);
			break;
			
		default:
			break;
	}
}


void refreshMainLayout(int **MapId) {
	drawBox(0, 0, w, UNIT, 7);
	drawBox(0, UNIT, w, UNIT+MG*2, 7);
	drawActicle();
	drawBox(ACTICLE+MG, HEADER, TABLE_W-MG*2, TABLE_H, 7);
	drawBox(ACTICLE+MG, HEADER, TABLE_W-MG*2, BLOCK, 1);
	refreshMapID(MapId);
}


void drawActicle() {
	drawBox(MG, HEADER, ACTICLE-MG, h-HEADER-MG, MAIN_COLOR);
	drawBox(MG, HEADER, ACTICLE-MG, BLOCK, ACTIVE_COLOR);
	drawBox(MG, h-BLOCK*2-MG, ACTICLE-MG, BLOCK*2, BG_COLOR);
}

void drawActicle(int **MapId, char title[], EditText edThongBao) {
	drawBox(MG, HEADER, ACTICLE-MG, h-HEADER-MG, MAIN_COLOR);
	drawBox(MG, HEADER, ACTICLE-MG, BLOCK, ACTIVE_COLOR);
	drawBox(MG, h-BLOCK*2-MG, ACTICLE-MG, BLOCK*2, BG_COLOR);
	setbkcolor(ACTIVE_COLOR);
	settextstyle(TITLE_FONT, 0, 1);
	setcolor(0);
	outtextxy(BLOCK*3, BLOCK*4+MG, title);
	edThongBao.draw(MapId);
}

void drawNotification(char noti[]=NULL) {
	if(noti == NULL) {
		drawBox(MG, h-BLOCK*2-MG, ACTICLE-MG, BLOCK*2, BG_COLOR);
		return;
	}
	setbkcolor(BG_COLOR);
	settextstyle(TEXT_FONT, 0, 2);
	outtextxy((ACTICLE-textwidth(ThongBao))/2, h-BLOCK*2, ThongBao);
	outtextxy((ACTICLE-textwidth(noti))/2, h-BLOCK, noti);
}

void refreshTable(int **MapId, int widthArr[], int colNum) {
	int j, x=ACTICLE+MG, y=HEADER+BLOCK;
	setId(MapId, x, y, TABLE_W, TABLE_H-BLOCK, 0);
	for(j=0; j<colNum; j++) {
		drawBox(x, y, widthArr[j], TABLE_H-BLOCK, MAIN_COLOR);
		x+=widthArr[j];
	}
}

void drawTable(int **MapId, char title[][30], int widthArr[], int colNum) {
	int i;
	int xm=ACTICLE+MG;
	settextstyle(TITLE_FONT, 0, 1);
	setcolor(0);
	setbkcolor(ACTIVE_COLOR);
	for(i=0; i<colNum; i++) {
		drawBox(xm, HEADER, widthArr[i], TABLE_H, ACTIVE_COLOR);
		outtextxy(xm+MG, HEADER+MG, title[i]);
		xm+=widthArr[i];
	}
	refreshTable(MapId, widthArr, colNum);
}


void ViewDGTable(DocGia *ListDG, int begin, int end, int **MapId) {
	int row=0;
	int X;
	int Y=HEADER+BLOCK+MG;
	drawTable(MapId, tableTitleDocGia1, tableTitleWidthDocGia1, 5);
	setcolor(0);
	setbkcolor(MAIN_COLOR);
	settextstyle(TEXT_FONT, 0, 2);
	for(int i=begin; i<end; i++) {
		X=ACTICLE+MG*2;
		char buffer [30];
		itoa(ListDG[i].MATHE, buffer, 10);
		outtextxy(X, Y, buffer);
		outtextxy(X+=100, Y, ListDG[i].ho.c_str());
		outtextxy(X+=300, Y, ListDG[i].ten.c_str());
		outtextxy(X+=230, Y, PhaiDocGia[ListDG[i].phai]);
		outtextxy(X+=120, Y, TTTDocGia[ListDG[i].trangthai]);
		setId(MapId, ACTICLE+MG, Y, TABLE_W, BLOCK, 230+row);
		row++;
		Y+=BLOCK;
	}
	cout << "\ncheck ham in doc gia";
}

void ViewDSTable(ArrPointerDauSach ArrDauSach, int begin, int end, int **MapId) {
	int row=0;
	int X;
	int Y=HEADER+BLOCK+MG;
	DauSach *pointerDS;
	drawTable(MapId, tableTitleDauSach, tableTitleWidthDauSach, 6);
	setcolor(0);
	setbkcolor(MAIN_COLOR);
	settextstyle(TEXT_FONT, 0, 2);
	for(int i=begin; i<end; i++) {
		pointerDS=new DauSach;
		pointerDS=ArrDauSach.dsDauSach[i];
		X=ACTICLE+MG*2;
		char buffer [30];
		outtextxy(X, Y, pointerDS->ISBN);
		outtextxy(X+=80, Y, pointerDS->tenSach.c_str());
		itoa(pointerDS->soTrang, buffer, 10);
		outtextxy(X+=280, Y, buffer);
		outtextxy(X+=70, Y, pointerDS->tacGia.c_str());
		itoa(pointerDS->namXuatBan, buffer, 10);
		outtextxy(X+=230, Y, buffer);
		outtextxy(X+=90, Y, pointerDS->theLoai.c_str());
		setId(MapId, ACTICLE+MG, Y, TABLE_W, BLOCK, 120+row);
		row++;
		Y+=BLOCK;
	}
	std::cout << "\ncheck ham in dau sach";
}

void ViewDanhMucTable(ListDMS *listDMS, int begin, int end, int **MapId) {
	int row=0;
	int X;
	int Y=HEADER+BLOCK+MG;
	char buffer [30];
	NodeDMS *nodeDMS=listDMS->pFirst;
	drawTable(MapId, tableTitleDanhMuc, tableTitleWidthDanhMuc, 3);
	setcolor(0);
	setbkcolor(MAIN_COLOR);
	settextstyle(TEXT_FONT, 0, 2);
	NodeDMS *pNode = listDMS->pFirst;
	X=ACTICLE+MG*2;
	for(int i=0; i<end; i++) {
		if(i>=begin) {
			outtextxy(X, Y, pNode->data.MaSach);
			outtextxy(X+100, Y, TrangThaiSach[pNode->data.TrangThai]);
			outtextxy(X+400, Y, pNode->data.ViTri.c_str());
			pNode=pNode->next;
			setId(MapId, ACTICLE+MG, Y, TABLE_W, BLOCK, 140+i-begin);
			Y+=BLOCK;
		}
	}
	std::cout << "\ncheck ham in dau sach";
}

void ViewSachMuonTable(DocGia docgia, int **MapId) {
	int X;
	int Y=HEADER+BLOCK+MG;
	NodeMuonTra *pNode=docgia.listMT->pFirst;
	string date;
	char buffer[30];
	drawTable(MapId, tableTitleMuonTra, tableTitleWidthMuonTra, 4);
	setcolor(0);
	setbkcolor(MAIN_COLOR);
	settextstyle(TEXT_FONT, 0, 2);
	int count=0;
	while(pNode!=NULL) {
		X=ACTICLE+MG*2;
		setId(MapId, X, Y, TABLE_W, BLOCK, 330+count);
		outtextxy(X, Y, pNode->data.maSach.c_str());
		date = (
			string(itoa(pNode->data.ngayMuon.ngay, buffer, 10)) + "/" 
			+ string(itoa(pNode->data.ngayMuon.thang, buffer, 10)) + "/" 
			+ string(itoa(pNode->data.ngayMuon.nam, buffer, 10))
		);
		outtextxy(X+=tableTitleWidthMuonTra[0], Y, date.c_str());
		date = (
			string(itoa(pNode->data.ngayTra.ngay, buffer, 10)) + "/" 
			+ string(itoa(pNode->data.ngayTra.thang, buffer, 10)) + "/" 
			+ string(itoa(pNode->data.ngayTra.nam, buffer, 10))
		);
		outtextxy(X+=tableTitleWidthMuonTra[1], Y, date.c_str());
		outtextxy(X+=tableTitleWidthMuonTra[2], Y, TTMuonTra[pNode->data.trangThai]);
		Y+=BLOCK;
		count++;
		pNode=pNode->next;
	}
	std::cout << "\ncheck ham in Sach muon";
}

void ViewTopTenDauSachTable(DauSach *ArrTopTen[], int **MapId) {
	int X;
	int Y=HEADER+BLOCK+MG;
	char buffer[30];
	DauSach *dausach;
	drawTable(MapId, tableTitleDauSach, tableTitleWidthDauSach, 6);
	setcolor(0);
	setbkcolor(MAIN_COLOR);
	settextstyle(TEXT_FONT, 0, 2);
	int count=0;
	for(int i=0; i<10; i++) {
		X=ACTICLE+MG*2;
		dausach=new DauSach;
		dausach=ArrTopTen[i];
		outtextxy(X, Y, dausach->ISBN);
		outtextxy(X+=tableTitleWidthDauSach[0], Y, dausach->tenSach.c_str());
		itoa(dausach->soTrang, buffer, 10);
		outtextxy(X+=tableTitleWidthDauSach[1], Y, buffer);
		outtextxy(X+=tableTitleWidthDauSach[2], Y, dausach->tacGia.c_str());
		itoa(dausach->namXuatBan, buffer, 10);
		outtextxy(X+=tableTitleWidthDauSach[3], Y, buffer);
		outtextxy(X+=tableTitleWidthDauSach[4], Y, dausach->theLoai.c_str());
		setId(MapId, ACTICLE+MG, Y, TABLE_W, BLOCK, 350+i);
		Y+=BLOCK;
	}
	std::cout << "\ncheck ham in Top 10 DS";
}

void ViewDocGiaQuaHan(ListDGQuaHan list, int page, int **MapId) {
	int X;
	int Y=HEADER+BLOCK+MG;
	int row=(list.n >= 13) ? 13 : list.n;
	int begin=page*13, end=page*13+13, k=0;
	char buffer[30];
	NodeDGQuaHan *pNode;
	pNode=list.pFirst;
	drawTable(MapId, tableTitleQuaHan1, tableTitleWidthQuaHan1, 6);
	setcolor(0);
	setbkcolor(MAIN_COLOR);
	settextstyle(TEXT_FONT, 0, 2);
	std::cout<<"\ncheck begin:"<<begin<<" end:"<<end;
	while(k<end && pNode!=NULL) {
		std::cout<<"\ncheck k";
		if(k>=begin) {
			std::cout<<"\ncheck node:"<<pNode->data.MATHE;
			X=ACTICLE+MG*2;
			itoa(pNode->data.MATHE, buffer, 10);
			outtextxy(X, Y, buffer);
			outtextxy(X+=tableTitleWidthQuaHan1[0], Y, pNode->data.ho.c_str());
			outtextxy(X+=tableTitleWidthQuaHan1[1], Y, pNode->data.ten.c_str());
			outtextxy(X+=tableTitleWidthQuaHan1[2], Y, PhaiDocGia[pNode->data.phai]);
			outtextxy(X+=tableTitleWidthQuaHan1[3], Y, TTTDocGia[pNode->data.trangthai]);
			itoa(pNode->soNgayQuaHan, buffer, 10);
			outtextxy(X+=tableTitleWidthQuaHan1[4], Y, buffer);
			Y+=BLOCK;
		}
		k++;
		pNode=pNode->next;
	}
	std::cout << "\ncheck ham in doc gia qua han";
}

void printMapId(int **MapId) {
	for(int i=0; i<h; i+=38) {
		for(int j=0; j<w; j+=38) {
			std::cout << MapId[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "Day la MapId\n\n";
}

void ScanString(EditText &EDIT, int maxlen, int **MapId) {
	char c;
	int len;
	len=strlen(EDIT.content);
	EDIT.content[len]='_';
	EDIT.content[len+1]='\0';
	EDIT.draw(MapId);
	while(1) {
		len=strlen(EDIT.content);
		c=getch();
		if((c>='A' && c<='Z' || c>='0' && c<='9' || c=='_' || c==' ')  && len<=maxlen) {
			EDIT.content[len-1]=c;
			EDIT.content[len]='_';
			EDIT.content[len+1]='\0';
		} else if((c>='a' && c<='z')  && len<=maxlen) {
			c=c-'a'+'A';
			EDIT.content[len-1]=c;
			EDIT.content[len]='_';
			EDIT.content[len+1]='\0';
		} else if(c==BACKSPACE) {
			if(len==0 || EDIT.content[0]=='_') {
				continue;
			} else {
				EDIT.content[len-2]='_';
				EDIT.content[len-1]='\0';
				EDIT.content[len]='\0';
			}
		} else if(c==ENTER) {
			break;
		}
		EDIT.draw(MapId);
	}
	EDIT.content[len]='\0';
	EDIT.content[len-1]='\0';
	EDIT.draw(MapId);
}

void ScanNumber(EditText &EDIT, int maxlen, int **MapId) {
	char c;
	int len;
	len=strlen(EDIT.content);
	EDIT.content[len]='_';
	EDIT.content[len+1]='\0';
	EDIT.draw(MapId);
	while(1) {
		len=strlen(EDIT.content);
		c=getch();
		if((c>='0' && c<='9')  && len<=maxlen) {
			EDIT.content[len-1]=c;
			EDIT.content[len]='_';
			EDIT.content[len+1]='\0';
		} else if(c==BACKSPACE) {
			if(len==0 || EDIT.content[0]=='_') {
				continue;
			} else {
				EDIT.content[len-2]='_';
				EDIT.content[len-1]='\0';
				EDIT.content[len]='\0';
			}
		} else if(c==ENTER) {
			break;
		}
//		std::cout<<"\n"<<len<<" "<<EDIT.content;
		EDIT.draw(MapId);
	}
	EDIT.content[len]='\0';
	EDIT.content[len-1]='\0';
	EDIT.draw(MapId);
}

ScanSearchDS(EditText &EDIT, int maxlen, ArrPointerDauSach dsds, ArrPointerDauSach &searchDS, int **MapId) {
	char c;
	int len;
	len=strlen(EDIT.content);
	EDIT.content[len]='_';
	EDIT.content[len+1]='\0';
	EDIT.draw(MapId);
	std::cout<<"\ncheck ham search";
	while(1) {
		len=strlen(EDIT.content);
		c=getch();
		if((c>='A' && c<='Z' || c>='0' && c<='9' || c=='_' || c==' ')  && len<=maxlen) {
			EDIT.content[len-1]=c;
			EDIT.content[len]='_';
			EDIT.content[len+1]='\0';
			len++;
			searchDS = SearchDauSach(dsds, EDIT.content);
			std::cout<<"\ncheck search n:"<<searchDS.n;
            ViewDSTable(searchDS, 0, searchDS.n>=13?13:searchDS.n, MapId);

		} else if((c>='a' && c<='z')  && len<=maxlen) {
			c=c-'a'+'A';
			EDIT.content[len-1]=c;
			EDIT.content[len]='_';
			EDIT.content[len+1]='\0';
			len++;
			searchDS = SearchDauSach(dsds, EDIT.content);
			std::cout<<"\ncheck search n:"<<searchDS.n;
           	ViewDSTable(searchDS, 0, searchDS.n>=13?13:searchDS.n, MapId);
			
		} else if(c==BACKSPACE) {
			if(len==0 || EDIT.content[0]=='_') {
				continue;
			} else {
				EDIT.content[len-2]='_';
				EDIT.content[len-1]='\0';
				EDIT.content[len]='\0';
				len--;
				
				searchDS = SearchDauSach(dsds, EDIT.content);
				std::cout<<"\ncheck search n:"<<searchDS.n;
	        	ViewDSTable(searchDS, 0, searchDS.n>=13?13:searchDS.n, MapId);
			}
		} else if(c==ENTER) {
			searchDS = SearchDauSach(dsds, EDIT.content);
			std::cout<<"\ncheck search n:"<<searchDS.n;
            ViewDSTable(searchDS, 0, searchDS.n>=13?13:searchDS.n, MapId);
			break;
		}
		EDIT.draw(MapId);
	}
	EDIT.content[len]='\0';
	EDIT.content[len-1]='\0';
	EDIT.draw(MapId);
}
