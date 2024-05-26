#include "raylib.h"
#include <vector> // Sử dụng std::vector để lưu danh sách sinh viên
#include <string> // Sử dụng std::string cho tiện lợi

// Khai báo cấu trúc dữ liệu của sinh viên
struct SinhVien {
    int STT;
    int MSSV;
    std::string ten;
    std::string ho;
    std::string gender;
    int ngay;
    int thang;
    int nam;
    long int cccd;
};

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Raylib Integration Example");

    // Khởi tạo một vector để lưu danh sách sinh viên
    std::vector<SinhVien> danhSachSinhVien;

    // Thêm một số sinh viên vào vector
    danhSachSinhVien.push_back({1, 123456, "John", "Doe", "Nam", 1, 1, 2000, 12345678});
    danhSachSinhVien.push_back({2, 234567, "Jane", "Smith", "Nu", 2, 2, 1999, 23456781});
    // Thêm thêm sinh viên khác nếu cần

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Vẽ từng sinh viên trong vector lên màn hình
        for (size_t i = 0; i < danhSachSinhVien.size(); ++i) {
            const SinhVien& sinhVien = danhSachSinhVien[i];
            DrawText(("STT: " + std::to_string(sinhVien.STT)).c_str(), 10, 10 + 70 * i, 20, DARKGRAY);
            DrawText(("MSSV: " + std::to_string(sinhVien.MSSV)).c_str(), 10, 40 + 70 * i, 20, DARKGRAY);
            DrawText(("Ho ten: " + sinhVien.ho + " " + sinhVien.ten).c_str(), 10, 70 + 70 * i, 20, DARKGRAY);
            DrawText(("Gioi tinh: " + sinhVien.gender).c_str(), 10, 100 + 70 * i, 20, DARKGRAY);
            DrawText(("Ngay sinh: " + std::to_string(sinhVien.ngay) + "/" + std::to_string(sinhVien.thang) + "/" + std::to_string(sinhVien.nam)).c_str(), 10, 130 + 70 * i, 20, DARKGRAY);
            DrawText(("CCCD: " + std::to_string(sinhVien.cccd)).c_str(), 10, 160 + 70 * i, 20, DARKGRAY);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
