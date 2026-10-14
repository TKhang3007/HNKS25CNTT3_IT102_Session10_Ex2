#include <stdio.h>

#define MAX_VE 50

struct VeSuKien {
    int maVe;
    char tenSuKien[50];
    char loaiVe[20];
    float giaGoc;
    int isEarlyBird;
    int daCheckIn;
};

float tinhGiaVe(struct VeSuKien ve);

int timVeTheoMa(const struct VeSuKien dsVe[], int soLuongVe, int maVe);

int themVe(struct VeSuKien dsVe[], int soLuongVe, struct VeSuKien veMoi);

void checkInVe(struct VeSuKien dsVe[], int soLuongVe, int maVe);

int huyVe(struct VeSuKien dsVe[], int soLuongVe, int maVe);

void hienThiDanhSachVe(const struct VeSuKien dsVe[], int soLuongVe);

int main() {
    struct VeSuKien dsVe[MAX_VE];
    int soLuongVe = 3;

    struct VeSuKien ve1 = {
        1001, "Live Concert VIBE 2025", "VIP",
        2000000.0f, 1, 0
    };

    struct VeSuKien ve2 = {
        1002, "Live Concert VIBE 2025", "Zone A",
        1200000.0f, 0, 0
    };

    struct VeSuKien ve3 = {
        1003, "Live Concert VIBE 2025", "GA",
        800000.0f, 1, 0
    };

    dsVe[0] = ve1;
    dsVe[1] = ve2;
    dsVe[2] = ve3;

    printf("===== TICKETBOX - LIVE CONCERT VIBE 2025 =====\n");

    printf("\n1. DANH SACH VE BAN DAU\n");
    hienThiDanhSachVe(dsVe, soLuongVe);

    printf("\n2. PHAT HANH VE MOI\n");

    struct VeSuKien ve4 = {
        1004, "Live Concert VIBE 2025", "VIP",
        2500000.0f, 1, 0
    };

    soLuongVe = themVe(dsVe, soLuongVe, ve4);

    printf("\n3. CHECK-IN VE 1002\n");
    checkInVe(dsVe, soLuongVe, 1002);

    printf("\n4. THU QUET LAI VE 1002\n");
    checkInVe(dsVe, soLuongVe, 1002);

    printf("\n5. HUY VE 1001\n");
    soLuongVe = huyVe(dsVe, soLuongVe, 1001);

    printf("\n6. CHECK-IN VE KHONG TON TAI 9999\n");
    checkInVe(dsVe, soLuongVe, 9999);

    printf("\n7. DANH SACH VE SAU KHI XU LY\n");
    hienThiDanhSachVe(dsVe, soLuongVe);

    return 0;
}

float tinhGiaVe(struct VeSuKien ve) {
    if (ve.isEarlyBird == 1) {
        return ve.giaGoc * 0.85f;
    }

    return ve.giaGoc;
}

int timVeTheoMa(const struct VeSuKien dsVe[], int soLuongVe, int maVe) {
    int i;

    for (i = 0; i < soLuongVe; i++) {
        if (dsVe[i].maVe == maVe) {
            return i;
        }
    }

    return -1;
}

int themVe(struct VeSuKien dsVe[], int soLuongVe, struct VeSuKien veMoi) {

    if (soLuongVe >= MAX_VE) {
        printf("[LOI] Danh sach da day, khong the them ve!\n");
        return soLuongVe;
    }

    if (timVeTheoMa(dsVe, soLuongVe, veMoi.maVe) != -1) {
        printf("[LOI] Ma ve %d da ton tai!\n", veMoi.maVe);
        return soLuongVe;
    }

    veMoi.daCheckIn = 0;

    dsVe[soLuongVe] = veMoi;
    soLuongVe++;

    printf("[THANH CONG] Da phat hanh ve %d (%s).\n",
           veMoi.maVe, veMoi.loaiVe);

    return soLuongVe;
}

void checkInVe(struct VeSuKien dsVe[], int soLuongVe, int maVe) {
    int viTri;

    if (soLuongVe == 0) {
        printf("[LOI] Danh sach ve dang rong!\n");
        return;
    }

    viTri = timVeTheoMa(dsVe, soLuongVe, maVe);

    if (viTri == -1) {
        printf("[LOI] Ma ve %d khong ton tai!\n", maVe);
        return;
    }

    if (dsVe[viTri].daCheckIn == 1) {
        printf("[CANH BAO GIAN LAN] Ve %d da check-in truoc do!\n",
               maVe);
        return;
    }

    dsVe[viTri].daCheckIn = 1;

    printf("[THANH CONG] Check-in ve %d thanh cong!\n", maVe);
}

int huyVe(struct VeSuKien dsVe[], int soLuongVe, int maVe) {
    int viTri;
    int i;

    if (soLuongVe == 0) {
        printf("[LOI] Danh sach ve dang rong, khong the huy!\n");
        return soLuongVe;
    }

    viTri = timVeTheoMa(dsVe, soLuongVe, maVe);

    if (viTri == -1) {
        printf("[LOI] Khong tim thay ve %d de huy!\n", maVe);
        return soLuongVe;
    }

    for (i = viTri; i < soLuongVe - 1; i++) {
        dsVe[i] = dsVe[i + 1];
    }

    soLuongVe--;

    printf("[THANH CONG] Da huy ve %d.\n", maVe);

    return soLuongVe;
}

void hienThiDanhSachVe(const struct VeSuKien dsVe[],
                       int soLuongVe) {
    int i;

    if (soLuongVe == 0) {
        printf("Danh sach ve dang rong!\n");
        return;
    }

    printf("--------------------------------------------------------------------------------------\n");
    printf("%-8s %-28s %-10s %-15s %-12s %-12s\n",
           "Ma ve", "Ten su kien", "Loai ve",
           "Gia thanh toan", "Early Bird", "Check-in");

    printf("--------------------------------------------------------------------------------------\n");

    for (i = 0; i < soLuongVe; i++) {
        printf("%-8d %-28s %-10s %-15.0f %-12s %-12s\n",
               dsVe[i].maVe,
               dsVe[i].tenSuKien,
               dsVe[i].loaiVe,
               tinhGiaVe(dsVe[i]),
               dsVe[i].isEarlyBird == 1 ? "Co" : "Khong",
               dsVe[i].daCheckIn == 1 ? "Da vao" : "Chua vao");
    }

    printf("--------------------------------------------------------------------------------------\n");
}