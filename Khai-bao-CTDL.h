// Phim nong
const int Backspace = 8, F2 = 60, Esc = 27, Enter = 13, Up = 72, Down = 80,
		 Left = 75, Right = 77, Delete = 83, F2 = 60, F3 = 61, Space = 32;
		 // F2: luu thong tin, F3:chuc nang them 

const int MAXDAUSACH = 1000, MAXDOCGIA = 1000, NGAYQUAHAN = 7, MAXSACHMUON = 3;	

//---- Danh Muc Sach-----
enum TrangThai{choMuonDuoc, daMuon, daThanhLy}; //choMuonDuoc = 0, daMuon = 1,daThanhLy = 2  
struct DanhMucSach{
	string maSach; // ISBN_stt
	TrangThai trangThai;
	string viTri;
};
struct NodeDanhMucSach{
	DanhMucSach info;
	NodeDanhMucSach *next;
};

//------- Dau Sach ------------
struct DauSach{
	string ISBN;
	int soTrang;
	int namXuatBan;
	string tenSach;
	string tacGia;
	string theLoai;
	NodeDanhMucSach *dms = NULL;
	//tu them
	int soLuong; //so luong danh muc sach
	int luotMuon;	// //so luot muon cho tung dau sach
}; 
struct DanhSachDauSach{
	int n;
	DauSach *dsDauSach[MAXDAUSACH];
};

// ---------- Muon Tra ------------
enum TrangThai {dangMuon, daTra, lamMatSach}; // dang muon = 0; da tra = 1; lam mat sach = 2
struct Date {
	int ngay;
	int thang;
	int nam;
};
struct MuonTra{
	string maSach;
	Date ngayMuon;
	Date ngayTra;
	TrangThai trangThai;
};
struct NodeMuonTra{
	MuonTra info;
	NodeMuonTra *next;
}
