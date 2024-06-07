#include "raylib.h"
#include <string.h>
#include <ctype.h> // Thêm thư viện này để sử dụng hàm tolower
#include "function.h"
void DrawButton(Rectangle button, const char* text, bool mouseOverButton) {
    DrawRectangleRec(button, mouseOverButton ? DARKGRAY : LIGHTGRAY);
    DrawText(text, button.x + button.width / 2 - MeasureText(text, 20) / 2, button.y + button.height / 2 - 10, 20, BLACK);
}
int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    // Khởi tạo cửa sổ đăng nhập
    InitWindow(screenWidth, screenHeight, "Login Interface Example");

    // Tạo các biến để lưu tên người dùng và mật khẩu
    char username[128] = "\0";
    char password[128] = "\0";
    bool mouseOnText = false;
    bool usernameBoxActive = false;
    bool passwordBoxActive = false;
    bool loginAttempted = false;
    bool loginSuccessful = false;
    bool showError = false; // Biến này chỉ hiển thị thông báo lỗi một lần

    // Vị trí và kích thước các ô nhập liệu
    Rectangle usernameBox = { screenWidth / 2 - 100, screenHeight / 2 - 50, 200, 40 };
    Rectangle passwordBox = { screenWidth / 2 - 100, screenHeight / 2 + 10, 200, 40 };
    Rectangle loginButton = { screenWidth / 2 - 50, screenHeight / 2 + 70, 100, 40 };

    SetTargetFPS(60);

    bool newWindowReady = false; // Biến để kiểm tra cửa sổ mới đã sẵn sàng hay chưa

    while (!WindowShouldClose()) {
        Vector2 mousePoint = GetMousePosition();

        // Kiểm tra nếu chuột ở trên một ô nhập liệu
        mouseOnText = CheckCollisionPointRec(mousePoint, usernameBox) || CheckCollisionPointRec(mousePoint, passwordBox);

        if (mouseOnText) {
            SetMouseCursor(MOUSE_CURSOR_IBEAM);
        }
        else {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }

        // Kiểm tra nhấp chuột vào ô nhập liệu
        if (CheckCollisionPointRec(mousePoint, usernameBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            usernameBoxActive = true;
            passwordBoxActive = false;
        }
        else if (CheckCollisionPointRec(mousePoint, passwordBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            usernameBoxActive = false;
            passwordBoxActive = true;
        }
        else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            usernameBoxActive = false;
            passwordBoxActive = false;
        }

        // Xử lý nhập liệu cho ô đang hoạt động
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("LOGIN", screenWidth / 2 -50, screenHeight / 2 -200, 40, RED);
        DrawText("Username:", screenWidth / 2 - 100, screenHeight / 2 - 70, 20, DARKGRAY);
        DrawRectangleRec(usernameBox, LIGHTGRAY);
        if (usernameBoxActive) DrawRectangleLinesEx(usernameBox, 1, RED);
        DrawText(username, screenWidth / 2 - 90, screenHeight / 2 - 40, 20, DARKGRAY);

        DrawText("Password:", screenWidth / 2 - 100, screenHeight / 2 - 10, 20, DARKGRAY);
        DrawRectangleRec(passwordBox, LIGHTGRAY);
        if (passwordBoxActive) DrawRectangleLinesEx(passwordBox, 1, RED);
        DrawText(password, screenWidth / 2 - 90, screenHeight / 2 + 20, 20, DARKGRAY);

        DrawRectangleRec(loginButton, LIGHTGRAY);
        DrawText("Login", screenWidth / 2 - 25, screenHeight / 2 + 80, 20, DARKGRAY);

        // Hiển thị thông báo lỗi nếu có
        if (showError) {
            DrawText("Invalid username or password", screenWidth / 2 - MeasureText("Invalid username or password", 20) / 2, screenHeight / 2 + 120, 20, RED);
        }


        EndDrawing();
        if (usernameBoxActive) {
            int key = GetKeyPressed();
            if ((key >= 32) && (key <= 125)) {
                int length = strlen(username);
                if (length < 127) {
                    char newChar = (char)key;
                    if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
                        newChar = toupper(newChar);
                    }
                    else {
                        newChar = tolower(newChar);
                    }
                    username[length] = newChar;
                    username[length + 1] = '\0';
                }
            }
            if (IsKeyPressed(KEY_BACKSPACE)) {
                int length = strlen(username);
                if (length > 0) username[length - 1] = '\0';
            }
        }
        else if (passwordBoxActive) {
            int key = GetKeyPressed();
            if ((key >= 32) && (key <= 125)) {
                int length = strlen(password);
                if (length < 127) {
                    char newChar = (char)key;
                    if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
                        newChar = toupper(newChar);
                    }
                    else {
                        newChar = tolower(newChar);
                    }
                    password[length] = newChar;
                    password[length + 1] = '\0';
                }
            }
            if (IsKeyPressed(KEY_BACKSPACE)) {
                int length = strlen(password);
                if (length > 0) password[length - 1] = '\0';
            }
        }

        // Kiểm tra thông tin đăng nhập khi nhấn nút "Login"
        if (CheckCollisionPointRec(mousePoint, loginButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            loginAttempted = true;
            if (!IsEmpty(username) && !IsEmpty(password)) {
                if (CheckLogin(username, password)) {
                    loginSuccessful = true;
                    // Sau khi đăng nhập thành công, thiết lập biến newWindowReady thành true
                    newWindowReady = true;
                    break;
                }
                else {
                    showError = true;
                }
            }
        }
    }

    if (loginSuccessful && newWindowReady) { // Kiểm tra cả hai điều kiện
        InitWindow(800, 600, "User Dashboard");
        SetTargetFPS(60);
        Rectangle buttons[6];
        const char* buttonLabels[6] = {
            "Create New School Year",
            "Create New Semester",
            "Add New Class",
            "View Classes",
            "Add Student to Class",
            "Doi mat khau"
        };

        bool createNewSchoolYearActive = false;
        char schoolYearInput[128] = "\0";
        Rectangle schoolYearInputBox = { screenWidth / 2 - 100, 450, 200, 40 };
        bool schoolYearInputBoxActive = false;
        bool semesterInputBoxActive = false;
        char semesterInput[128] = "\0";
        bool createNewSemesterActive = false;
        Rectangle semesterInputBox = { screenWidth / 2 - 100, 400,200, 40 };
        ListNamHoc L = { NULL };
        NamHoc* N = NULL;
        Semester* sm = NULL;

        for (int i = 0; i < 6; i++) {
            buttons[i].x = (screenWidth - 400) / 2; // Căn giữa theo chiều ngang
            buttons[i].y = 50 + i * 60; // Để lại khoảng trống 50 pixel phía trên và giữa các ô là 60 pixel
            buttons[i].width = 400; // Chiều rộng của ô
            buttons[i].height = 40;
        }
        while (!WindowShouldClose()) {
            Vector2 mousePoint = GetMousePosition();
            bool mouseOverButton[6] = { false };

            BeginDrawing();
            ClearBackground(RAYWHITE);

            for (int i = 0; i < 6; i++) {
                mouseOverButton[i] = CheckCollisionPointRec(mousePoint, buttons[i]);
                DrawButton(buttons[i], buttonLabels[i], mouseOverButton[i]);

                if (mouseOverButton[i] && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    DrawRectangleRec(buttons[i], RED);
                    switch (i) {
                    case 0:
                        createNewSchoolYearActive = true;
                        break;
                    case 1:
                        createNewSemesterActive = true;
                        break;
                        // Implement other cases as needed
                    }
                }
            }

            if (createNewSchoolYearActive) {
                DrawRectangleRec(schoolYearInputBox, LIGHTGRAY);
                DrawText(schoolYearInput, schoolYearInputBox.x + 5, schoolYearInputBox.y + 10, 20, DARKGRAY);
                DrawText("Enter School Year (e.g., 2020-2021):", schoolYearInputBox.x, schoolYearInputBox.y -20, 20, LIGHTGRAY);

                if (CheckCollisionPointRec(mousePoint, schoolYearInputBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    schoolYearInputBoxActive = true;
                }
                else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    schoolYearInputBoxActive = false;
                }

                if (schoolYearInputBoxActive) {
                    int key = GetKeyPressed();
                    if ((key >= 32) && (key <= 125)) {
                        int length = strlen(schoolYearInput);
                        if (length < 127) {
                            schoolYearInput[length] = (char)key;
                            schoolYearInput[length + 1] = '\0';
                        }
                    }
                    if (IsKeyPressed(KEY_BACKSPACE)) {
                        int length = strlen(schoolYearInput);
                        if (length > 0) schoolYearInput[length - 1] = '\0';
                    }
                }

                if (IsKeyPressed(KEY_ENTER)) {
                    taonamhoc(L, N, schoolYearInput);
                    createNewSchoolYearActive = false;
                    memset(schoolYearInput, 0, sizeof(schoolYearInput)); // Reset input
                }
            }
            if (createNewSemesterActive && IsWindowReady())
            {
                
                    taohocky(sm, L);
                    CloseWindow();
                    createNewSemesterActive = false;
                

            }


            EndDrawing();
        }
    }
    CloseWindow();
    return 0;
}




