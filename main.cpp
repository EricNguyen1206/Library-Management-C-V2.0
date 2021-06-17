#include <winbgim.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "define.h"
#include "model.h"
#include "layoutDauSach.h"
#include "layoutDocGia.h"
#include "layoutMuonTra.h"

using namespace std;


int main(int argc, char *argv[])
{
	initwindow(w, h);
	setbkcolor(BG_COLOR);
   	cleardevice();
	int **MapId = new int*[h];
	int x=0, y=0;
	for (int i=0; i<h; i++) {
		MapId[i] = new int[w];
	}
	resetMapID(MapId);
	
	Button btnRouteDauSach(w/2-BLOCK*5, BLOCK*3, BLOCK*10, BLOCK*2, DauSachTitle, 1);
	Button btnRouteDocGia(w/2-BLOCK*5, BLOCK*6, BLOCK*10, BLOCK*2, DocGiaTitle, 2);
	Button btnRouteMuonTra(w/2-BLOCK*5, BLOCK*9, BLOCK*10, BLOCK*2, MuonTraTitle, 3);
	
	drawStartScreen(btnRouteDauSach, btnRouteDocGia, btnRouteMuonTra, MapId);
	int Router;
	
	while(1) {
		delay(0.0001);
        if (ismouseclick(WM_LBUTTONDOWN)){
            getmouseclick(WM_LBUTTONDOWN, x, y);
            switch(MapId[y][x]) {
            	case 1:
            		label_1:
            		drawBox(0, 0, w, h, BG_COLOR);
            		Router = DauSachController(MapId, x, y);
            		if(Router == 2) {
            			goto label_2;
					} else if(Router == 3) {
						goto label_3;
					}
            		drawStartScreen(btnRouteDauSach, btnRouteDocGia, btnRouteMuonTra, MapId);
            		break;
            	case 2:
            		label_2:
            		drawBox(0, 0, w, h, BG_COLOR);
            		Router = DocGiaController(MapId, x, y);
            		if(Router == 1) {
            			goto label_1;
					} else if(Router == 3) {
						goto label_3;
					}
            		drawStartScreen(btnRouteDauSach, btnRouteDocGia, btnRouteMuonTra, MapId);
            		break;
            	case 3:
            		label_3:
            			drawBox(0, 0, w, h, BG_COLOR);
            		Router = MuonTraController(MapId, x, y);
            		if(Router == 1) {
            			goto label_1;
					} else if(Router == 2) {
            			goto label_2;
					}
            		drawStartScreen(btnRouteDauSach, btnRouteDocGia, btnRouteMuonTra, MapId);
            		break;
			}
			
        }
	}
	for(int i=0; i<h; i++) {
		delete [] MapId[i];
	}
	delete [] MapId;
	while(!kbhit()) delay(1);
	return 0;
}
