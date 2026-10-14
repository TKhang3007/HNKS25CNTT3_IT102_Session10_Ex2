1. Phân tích bài toán I/O
Chức năng	Input	Output / Giá trị trả về
tinhGiaVe()	Giá gốc, trạng thái Early Bird	Giá thanh toán sau giảm giá
timVeTheoMa()	Mảng vé, số lượng vé, mã vé cần tìm	Vị trí vé nếu tìm thấy, -1 nếu không thấy
themVe()	Mảng vé, số lượng hiện tại, vé mới	Số lượng mới; giữ nguyên nếu mảng đầy hoặc mã vé trùng
checkInVe()	Mảng vé, số lượng, mã vé	Thông báo thành công, vé đã check-in hoặc không tìm thấy
huyVe()	Mảng vé, số lượng, mã vé cần hủy	Số lượng mới sau khi xóa hoặc giữ nguyên nếu thất bại
hienThiDanhSachVe()	Mảng vé, số lượng	In danh sách và giá thanh toán thực tế
2. Thiết kế cấu trúc và kiến trúc hàm
Cấu trúc VeSuKien
Mỗi vé lưu 6 thuộc tính theo đề bài:
- maVe: mã vé duy nhất.
- tenSuKien: tên sự kiện.
- loaiVe: khu vực vé.
- giaGoc: giá niêm yết.
- isEarlyBird: có áp dụng giảm giá hay không.
- daCheckIn: trạng thái sử dụng vé.
Mảng có tối đa MAX_VE = 50 vé.
Danh sách Function Prototypes
float tinhGiaVe(struct VeSuKien ve);
int timVeTheoMa(const struct VeSuKien dsVe[], int soLuongVe, int maVe);
int themVe(struct VeSuKien dsVe[], int soLuongVe, struct VeSuKien veMoi);
void checkInVe(struct VeSuKien dsVe[], int soLuongVe, int maVe);
int huyVe(struct VeSuKien dsVe[], int soLuongVe, int maVe);
void hienThiDanhSachVe(const struct VeSuKien dsVe[], int soLuongVe);


Hàm timVeTheoMa() là hàm tìm kiếm dùng chung. Cả checkInVe() và huyVe() đều gọi hàm này thay vì viết lại vòng lặp tìm mã vé. Điều đó giúp mã nguồn dễ đọc và giảm lỗi.
3. Sơ đồ xử lý logic
Luồng check-in QR
Nhận mã vé QR
    
Danh sách có rỗng không?
     Có -> Thông báo chưa có vé
     Không
          
    Gọi timVeTheoMa()
          
    Có tìm thấy vé không?
     Không -> Báo mã vé không tồn tại
     Có
          
    Vé đã check-in chưa?
     Rồi -> Từ chối, cảnh báo quét trùng
     Chưa -> daCheckIn = 1


Luồng hủy vé
Nhận mã vé cần hủy
    
Kiểm tra danh sách rỗng
    
Gọi timVeTheoMa()
    
Không tìm thấy -> Giữ nguyên số lượng
    
Tìm thấy -> Dồn các phần tử phía sau sang trái
    
Giảm soLuongVe đi 1
    
Trả về số lượng mới cho main()