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

int timVeTheoMa(struct VeSuKien dsVe[], int soLuongVe, int maVe);
void themVe(struct VeSuKien dsVe[], int *soLuongVe, struct VeSuKien veMoi);
void checkInVe(struct VeSuKien dsVe[], int soLuongVe, int maVe);
void huyVe(struct VeSuKien dsVe[], int *soLuongVe, int maVe);
void hienThiDanhSach(struct VeSuKien dsVe[], int soLuongVe);

int main() {
    struct VeSuKien dsVe[MAX_VE];
    int soLuongVe = 3;

    dsVe[0] = (struct VeSuKien){1001, "Live Concert VIBE 2025", "VIP", 2000000, 1, 0};
    dsVe[1] = (struct VeSuKien){1002, "Live Concert VIBE 2025", "GA", 1000000, 0, 0};
    dsVe[2] = (struct VeSuKien){1003, "Live Concert VIBE 2025", "Zone A", 1500000, 1, 0};

    printf("=== DANH SACH BAN DAU ===\n");
    hienThiDanhSach(dsVe, soLuongVe);

    struct VeSuKien veMoi = {
        1004, "Live Concert VIBE 2025", "VIP", 2000000, 0, 0
    };

    printf("\n=== PHAT HANH VE MOI ===\n");
    themVe(dsVe, &soLuongVe, veMoi);

    printf("\n=== CHECK-IN VE 1001 ===\n");
    checkInVe(dsVe, soLuongVe, 1001);

    printf("\n=== QUET LAI VE 1001 ===\n");
    checkInVe(dsVe, soLuongVe, 1001);

    printf("\n=== HUY VE 1002 ===\n");
    huyVe(dsVe, &soLuongVe, 1002);

    printf("\n=== CHECK-IN VE KHONG TON TAI ===\n");
    checkInVe(dsVe, soLuongVe, 9999);

    printf("\n=== DANH SACH SAU CUNG ===\n");
    hienThiDanhSach(dsVe, soLuongVe);

    return 0;
}

int timVeTheoMa(struct VeSuKien dsVe[], int soLuongVe, int maVe) {
    int i;

    for (i = 0; i < soLuongVe; i++) {
        if (dsVe[i].maVe == maVe) {
            return i;
        }
    }

    return -1;
}

void themVe(struct VeSuKien dsVe[], int *soLuongVe, struct VeSuKien veMoi) {
    if (*soLuongVe >= MAX_VE) {
        printf("Danh sach da day, khong the phat hanh ve!\n");
        return;
    }

    dsVe[*soLuongVe] = veMoi;
    (*soLuongVe)++;

    printf("Them ve %d thanh cong!\n", veMoi.maVe);
}

void checkInVe(struct VeSuKien dsVe[], int soLuongVe, int maVe) {
    int viTri = timVeTheoMa(dsVe, soLuongVe, maVe);

    if (viTri == -1) {
        printf("Khong tim thay ma ve %d!\n", maVe);
        return;
    }

    if (dsVe[viTri].daCheckIn == 1) {
        printf("CANH BAO: Ve %d da check-in truoc do!\n", maVe);
        return;
    }

    dsVe[viTri].daCheckIn = 1;
    printf("Check-in ve %d thanh cong!\n", maVe);
}

void huyVe(struct VeSuKien dsVe[], int *soLuongVe, int maVe) {
    int viTri = timVeTheoMa(dsVe, *soLuongVe, maVe);
    int i;

    if (viTri == -1) {
        printf("Khong tim thay ma ve %d!\n", maVe);
        return;
    }

    for (i = viTri; i < *soLuongVe - 1; i++) {
        dsVe[i] = dsVe[i + 1];
    }

    (*soLuongVe)--;

    printf("Huy ve %d thanh cong!\n", maVe);
}

void hienThiDanhSach(struct VeSuKien dsVe[], int soLuongVe) {
    int i;
    float giaThanhToan;

    if (soLuongVe == 0) {
        printf("Danh sach ve dang rong!\n");
        return;
    }

    for (i = 0; i < soLuongVe; i++) {
        giaThanhToan = dsVe[i].giaGoc;

        if (dsVe[i].isEarlyBird == 1) {
            giaThanhToan = dsVe[i].giaGoc * 0.85;
        }

        printf("Ma ve: %d | Su kien: %s | Loai: %s | Gia: %.0f VND | Check-in: %s\n",
               dsVe[i].maVe,
               dsVe[i].tenSuKien,
               dsVe[i].loaiVe,
               giaThanhToan,
               dsVe[i].daCheckIn == 1 ? "Da" : "Chua");
    }
}
// timVeTheoMa: tìm vé, tr? v? v? trí ho?c -1.
// themVe: ki?m tra MAX_VE r?i thêm vé, tang soLuongVe.
// checkInVe: tìm vé, ki?m tra dã check-in r?i m?i c?p nh?t.
// huyVe: tìm vé, d?n m?ng và gi?m soLuongVe.
// Dùng con tr? d? c?p nh?t soLuongVe ngoài main.
