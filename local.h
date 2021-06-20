#pragma once
#include "define.h"
#include "model.h"
#include <string>
//#include "cautrucDocGia.h"
//#include "model1.h"

//Thuoc tinh trong table
char tableTitleDauSach[6][30] 	= {"ISBN", "Ten sach", "Trang", "Tac gia", "NXB", "The loai"};
char tableTitleDocGia1[5][30] 	= {"Ma the", "Ho", "Ten", "Gioi tinh", "Trang thai"};
char tableTitleMuonTra[4][30] 	= {"Ma sach", "Ten sach", "Ngay muon", "Ngay tra"};
char tableTitleDanhMuc[3][30] 	= {"Ma sach", "Trang thai", "Vi tri"};

//Hoanh do cac thuoc tinh trong table
int tableTitleWidthDauSach[6] 	= {80, 280, 70, 230, 90, TABLE_W-750-MG};
int tableTitleWidthDocGia1[5] 	= {100, 300, 230, 120, TABLE_W-750-MG};
int tableTitleWidthMuonTra[4] 	= {100, 300, 250, TABLE_W-650-MG};
int tableTitleWidthDanhMuc[3]	= {100, 300, TABLE_W-400-MG};

//Trang thai cac thuoc tinh du lieu
int YDS[6] 						= {BLOCK*6, BLOCK*8, BLOCK*10, BLOCK*12, BLOCK*14, BLOCK*16};
enum TrangThaiSachThuVien{choMuonDuoc, daMuon, daThanhLy}; //choMuonDuoc = 0, daMuon = 1,daThanhLy = 2  
enum TrangThaiSachMuonTra{dangMuon, daTra, lamMatSach}; // dang muon = 0; da tra = 1; lam mat sach = 2
enum ModeSapXepDocGia{maDocGia, hoTen};
enum TheLoaiSach{VanHoc, KinhTe, LichSu, TruyenTranh, GiaoTrinh, NgoaiNgu};

char *MaSach[6]					= {"VH", "KT", "LS", "TT", "GT", "NN"};
char TrangThaiSach[3][30] 		= {"CHO MUON DUOC", "DA CHO MUON", "DA THANH LY"};
char *TTMuonTra[10] 			= {"DANG MUON", "DA TRA", "LAM MAT"};
char *TTTDocGia[10] 			= {"KHOA", "HOAT DONG"};
char *PhaiDocGia[5] 			= {"NAM", "NU"};

char mess[30];
//Cac tieu de su dung
char AppTitle[] 				= "QUAN LY THU VIEN";
char DauSachTitle[] 			= "DANH SACH DAU SACH";
char ThemDauSach[] 				= "THEM DAU SACH";
char HieuChinhDauSach[] 		= "HIEU CHINH DAU SACH";
char ThemSach[] 				= "THEM SACH: ";
char ThemSachThanhCong[] 		= "THEM SACH THANH CONG!";
char HieuChinhSachThanhCong[] 	= "HIEU CHINH SACH THANH CONG!";
char XoaDauSachThanhCong[]		= "XOA DAU SACH THANH CONG";
char XoaSachThanhCong[]			= "XOA SACH THANH CONG";
char KhongDuocXoaSachNay[]		= "KHONG DUOC XOA SACH NAY";
char IsbnDaTonTai[]				= "ISBN DA TON TAI";
char NamXuatBanKhongHopLe[]		= "NAM XUAT BAN KHONG HOP LE";
char ChiDuocTangSoLuong[]		= "CHI DUOC TANG SO LUONG SACH";
char ThemDocGiaThanhCong[]		= "THEM DOC GIA THANH CONG";
char HieuChinhDocGiaThanhCong[]	= "HIEU CHINH DOC GIA THANH CONG";
char XoaDocGiaThanhCong[]		= "XOA DOC GIA THANH CONG";
char ThongTinKhongDuocDeTrong[] = "THONG TIN KHONG DUOC DE TRONG!";
char NhapSach[] 				= "NHAP SACH";
char HieuChinhSach[] 			= "HIEU CHINH SACH";
char ThongBao[] 				= "THONG BAO: ";
char DanhMucSach[80] 			= "DANH MUC SACH";
char DocGiaTitle[] 				= "DANH SACH DOC GIA";
char ThemDocGia[] 				= "THEM DOC GIA";
char HieuChinhDocGia[] 			= "HIEU CHINH DOC GIA";
char XoaDocGia[] 				= "XOA DOC GIA";
char MuonTraTitle[] 			= "DANH SACH MUON TRA";
char MuonSach[] 				= "MUON SACH";
char TraSach[] 					= "TRA SACH";
char TopTen[] 					= "TOP 10 CUON SACH MUON NHIEU NHAT";
char DSDM[] 					= "CAC SACH DANG MUON";




