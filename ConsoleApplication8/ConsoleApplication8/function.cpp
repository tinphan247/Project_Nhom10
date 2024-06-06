#include "function.h"

bool IsEmpty(const char* str)
{
    return strlen(str) == 0;
}

bool CheckLogin(const char* username, const char* password) 
{
    // Thực hiện kiểm tra thông tin đăng nhập ở đây
    if (strcmp(username, "AD") == 0 && strcmp(password, "123") == 0)
    {
        return true;
    }
    else {
        return false;
    }
}
void taonamhoc(ListNamHoc& L, NamHoc*& N, const char* thoigiannamhoc)
{
    N = new NamHoc();
    N->ngaybatdau= thoigiannamhoc;
    if (L.phead == NULL) {
        L.phead = N;
    }
    else {
        NamHoc* temp = L.phead;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = N;
    }
    N->next = NULL;
    N->Hocky = NULL;
}



void taohocky(Semester*& H, ListNamHoc& L) {
    H = new Semester();
    int screenWidth = 800;
    int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Tao Hoc Ky");

    SetTargetFPS(60);

    bool isYearInputActive = false;
    bool isOrdinalInputActive = false;
    bool isStartDateInputActive = false;
    bool isEndDateInputActive = false;
    bool isConfirmButtonPressed = false;

    std::string yearInput = "";
    std::string ordinalInput = "";
    std::string startDateInput = "";
    std::string endDateInput = "";

    bool isInputValid = true;
    std::string errorMessage = "";

    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        NamHoc* temp = L.phead;
        int textWidth = MeasureText("Danh sach cac nam hien co:", 20);
        int screenWidth = 800; // assuming screenWidth is 800
        int xPosition = (screenWidth - textWidth) / 2;
        DrawText("Danh sach cac nam hien co:", xPosition, 50 * 0, 20, RED);
        int i = 1;
        while (temp != NULL) {
            // Chuyển đổi std::string sang chuỗi ký tự C
            const char* kt = temp->ngaybatdau.c_str();
            DrawText(kt, 400, 50 * i, 20, BLACK);
            temp = temp->next;
            i++;
        }
        // Vẽ các phần nhập liệu
        DrawText("Chon nam hoc:", 200, 200, 20, BLACK);
        DrawRectangle(200, 230, 400, 40, isYearInputActive ? LIGHTGRAY : GRAY);
        DrawText(yearInput.c_str(), 210, 240, 20, BLACK);

        DrawText("Chon thu tu cua hoc ki (1-3):", 200, 280, 20, BLACK);
        DrawRectangle(200, 310, 400, 40, isOrdinalInputActive ? LIGHTGRAY : GRAY);
        DrawText(ordinalInput.c_str(), 210, 320, 20, BLACK);

        DrawText("Nhap vao ngay bat dau hoc ki (VD 01/01/2024):", 200, 360, 20, BLACK);
        DrawRectangle(200, 390, 400, 40, isStartDateInputActive ? LIGHTGRAY : GRAY);
        DrawText(startDateInput.c_str(), 210, 400, 20, BLACK);

        DrawText("Nhap vao ngay ket thuc hoc ki (VD 01/01/2024):", 200, 440, 20, BLACK);
        DrawRectangle(200, 470, 400, 40, isEndDateInputActive ? LIGHTGRAY : GRAY);
        DrawText(endDateInput.c_str(), 210, 480, 20, BLACK);

        float confirmButtonX = screenWidth / 2 - 100;
        DrawRectangle(confirmButtonX, 530, 200, 50, isConfirmButtonPressed ? RED : MAROON);
        DrawText("Xac Nhan", confirmButtonX + 50, 545, 20, WHITE);

        if (!isInputValid) {
            DrawText(errorMessage.c_str(), screenWidth - MeasureText(errorMessage.c_str(), 20) - 10, screenHeight - 30, 20, RED);
        }

        // Xử lý sự kiện chuột để chọn ô nhập liệu
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePosition = GetMousePosition();
            if (CheckCollisionPointRec(mousePosition, { 200, 230, 400, 40 })) {
                isYearInputActive = true;
                isOrdinalInputActive = false;
                isStartDateInputActive = false;
                isEndDateInputActive = false;
                isConfirmButtonPressed = false;
            }
            else if (CheckCollisionPointRec(mousePosition, { 200, 310, 400, 40 })) {
                isOrdinalInputActive = true;
                isYearInputActive = false;
                isStartDateInputActive = false;
                isEndDateInputActive = false;
                isConfirmButtonPressed = false;
            }
            else if (CheckCollisionPointRec(mousePosition, { 200, 390, 400, 40 })) {
                isStartDateInputActive = true;
                isYearInputActive = false;
                isOrdinalInputActive = false;
                isEndDateInputActive = false;
                isConfirmButtonPressed = false;
            }
            else if (CheckCollisionPointRec(mousePosition, { 200, 470, 400, 40 })) {
                isEndDateInputActive = true;
                isYearInputActive = false;
                isOrdinalInputActive = false;
                isStartDateInputActive = false;
                isConfirmButtonPressed = false;
            }
            else if (CheckCollisionPointRec(mousePosition, { confirmButtonX, 530, 200, 50 })) {
                isConfirmButtonPressed = true;
                isInputValid = true;
                errorMessage = "";

                // Validate inputs
                if (yearInput.empty()) {
                    isInputValid = false;
                    errorMessage = "Year input is empty!";
                }
                else if (ordinalInput.empty()) {
                    isInputValid = false;
                    errorMessage = "Ordinal input is empty!";
                }
                else if (startDateInput.empty()) {
                    isInputValid = false;
                    errorMessage = "Start date input is empty!";
                }
                else if (endDateInput.empty()) {
                    isInputValid = false;
                    errorMessage = "End date input is empty!";
                }
                else {
                    // Validate year input
                    NamHoc* temp = L.phead;
                    bool yearFound = false;
                    while (temp != NULL) {
                        if (temp->ngaybatdau == yearInput) {
                            yearFound = true;
                            if (temp->Hocky == NULL) {
                                temp->Hocky = H;
                            }
                            else {
                                Semester* temphocky = temp->Hocky;
                                while (temphocky->next != NULL) {
                                    temphocky = temphocky->next;
                                }
                                temphocky->next = H;
                            }
                            std::cout << "Da them 1 hoc ky vao nam hoc " << temp->ngaybatdau << std::endl;
                            break;
                        }
                        temp = temp->next;
                    }

                    if (!yearFound) {
                        isInputValid = false;
                        errorMessage = "Year not found!";
                    }
                    else {
                        // Lưu thông tin từ các ô vào biến tương ứng của Semester
                        H->Ngaybatdau = startDateInput;
                        H->thutu = std::stoi(ordinalInput);
                        H->Ngayketthuc = endDateInput;

                        // Đóng cửa sổ
                        CloseWindow();
                        break; // Thoát khỏi hàm sau khi lưu và đóng cửa sổ
                    }
                }
            }
            else {
                isYearInputActive = false;
                isOrdinalInputActive = false;
                isStartDateInputActive = false;
                isEndDateInputActive = false;
                isConfirmButtonPressed = false;
            }
        }

        // Xử lý nhập liệu từ người dùng cho ô tương ứng
        int key = GetKeyPressed();
        if (isYearInputActive) {
            if (key >= 32 && key <= 125) {
                yearInput += static_cast<char>(key);
            }
            if (IsKeyPressed(KEY_BACKSPACE) && !yearInput.empty()) {
                yearInput.pop_back();
            }
        }

        if (isOrdinalInputActive) {
            if (key >= 32 && key <= 125) {
                ordinalInput += static_cast<char>(key);
            }
            if (IsKeyPressed(KEY_BACKSPACE) && !ordinalInput.empty()) {
                ordinalInput.pop_back();
            }
        }

        if (isStartDateInputActive) {
            if (key >= 32 && key <= 125) {
                startDateInput += static_cast<char>(key);
            }
            if (IsKeyPressed(KEY_BACKSPACE) && !startDateInput.empty()) {
                startDateInput.pop_back();
            }
        }

        if (isEndDateInputActive) {
            if (key >= 32 && key <= 125) {
                endDateInput += static_cast<char>(key);
            }
            if (IsKeyPressed(KEY_BACKSPACE) && !endDateInput.empty()) {
                endDateInput.pop_back();
            }
        }

        EndDrawing();
    }

   // CloseWindow();
}


