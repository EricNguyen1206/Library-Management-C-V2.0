# Library-Management-C-V2.0
*Các hạn chế của đồ án làm chưa tốt:
- Cấu trúc dữ liệu chính chứa data đọc giả và đầu sách vẫn còn khai báo global (do tác giả chưa fix được lỗi khi truyền cấu trúc qua các layout, một phần do bất cập về thư viện đồ họa)
- Việc cảnh báo người vẫn còn chung chung, chưa cụ thể (chủ yếu do tác giả lười, không viết cảnh báo riêng cho từng case cụ thể)
- Thuật toán thêm đầu sách chưa thật sự tối ưu, về mặt thuật toán sắp xếp và cả thêm khi đã có thứ tự
- Một điểm chưa hợp lý khi khai báo cấu trúc danh sách trong cấu trúc cây là khai báo kiểu con trỏ, điều này không ảnh hưởng đến hiệu năng nhưng gây ra sự phức tạp và khó bảo trì
*Các điểm "tạm ổn của đồ án"
- Thuật toán thực hiện bằng thư viện đồ họa, cho giao diện dễ nhìn đối với mặt bằng chung.
- Không có lỗi đồ họa trong tất cả các giao diện
- Xử lý ổn tất cả yêu cầu đề bài và các nghiệp vụ liên quan (thêm, đọc dữ liệu, xóa có điều kiện, sửa)
- Đọc và lưu dữ liệu vào file
- Tìm kiếm dạng nhúng
