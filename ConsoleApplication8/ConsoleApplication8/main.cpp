#include "function.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "");

    ListCourses LC;
    InitList(LC);
    ListNamHoc LNH = { NULL };
    NamHoc* N = NULL;
    Semester* sm = NULL;
    char username[128] = "\0";
    char password[128] = "\0";
    bool mouseOnText = false;
    bool usernameBoxActive = false;
    bool passwordBoxActive = false;
    bool loginAttempted = false;
    bool loginSuccessful = false;
    bool showError = false;

    Rectangle usernameBox = { screenWidth / 2 - 100, screenHeight / 2 - 50, 200, 40 };
    Rectangle passwordBox = { screenWidth / 2 - 100, screenHeight / 2 + 10, 200, 40 };
    Rectangle loginButton = { screenWidth / 2 - 50, screenHeight / 2 + 70, 100, 40 };

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        Vector2 mousePoint = GetMousePosition();
        mouseOnText = CheckCollisionPointRec(mousePoint, usernameBox) || CheckCollisionPointRec(mousePoint, passwordBox);

        if (mouseOnText) {
            SetMouseCursor(MOUSE_CURSOR_IBEAM);
        }
        else {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }

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

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("LOGIN", screenWidth / 2 - 50, screenHeight / 2 - 200, 40, RED);
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

        if (CheckCollisionPointRec(mousePoint, loginButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            loginAttempted = true;
            if (!IsEmpty(username) && !IsEmpty(password)) {
                if (CheckLogin(username, password)) {
                    loginSuccessful = true;
                    break;
                }
                else {
                    showError = true;
                }
            }
        }
    }

    if (loginSuccessful) {
        const int dashboardWidth = 1400;
        const int dashboardHeight = 800;
        InitWindow(dashboardWidth, dashboardHeight,"");
        SetTargetFPS(60);

        Rectangle buttons[6];
        const char* buttonLabels[6] = {
            "Create New School Year",
            "Create New Semester",
            "Add Course",
            "View Classes",
            "Add Student to Class",
            "View Course"
        };
        bool ViewCourseActive = false;
        char ViewCourseInput[128] = "\0";
        bool createNewSchoolYearActive = false;
        char schoolYearInput[128] = "\0";
        bool ViewCourseInputBoxActive = false;
        Rectangle ViewCourseInputBox = { dashboardWidth / 2 - 100, 250, 200, 40 };
        Rectangle schoolYearInputBox = { dashboardWidth / 2 - 100, 450, 200, 40 };
        bool schoolYearInputBoxActive = false;
        bool semesterInputBoxActive = false;
        char semesterInput[128] = "\0";
        bool createNewSemesterActive = false;
        Rectangle semesterInputBox = { dashboardWidth / 2 - 100, 400, 200, 40 };
        bool createNewCourseActive = false;

        for (int i = 0; i < 6; i++) {
            buttons[i].x = (dashboardWidth - 400) / 2;
            buttons[i].y = 50 + i * 60;
            buttons[i].width = 400;
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
                    case 2:
                        createNewCourseActive = true;
                        break;
                    case 5:
                        ViewCourseActive = true;
                        break;
                    }
                }
            }
            if (createNewSchoolYearActive)
            {
                DrawRectangleRec(schoolYearInputBox, LIGHTGRAY);
                DrawText(schoolYearInput, schoolYearInputBox.x + 5, schoolYearInputBox.y + 10, 20, DARKGRAY);
                DrawText("Enter School Year (e.g., 2020-2021):", schoolYearInputBox.x, schoolYearInputBox.y - 20, 20, LIGHTGRAY);

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
                    taonamhoc(LNH, N, schoolYearInput);
                    createNewSchoolYearActive = false;
                    memset(schoolYearInput, 0, sizeof(schoolYearInput));
                }
            }

            if (createNewSemesterActive) 
            {
                taohocky(sm, LNH);
                createNewSemesterActive = false;
            }

            if (createNewCourseActive)
            {
                string id, CourseName, ClassName, GVName, wDay, Session;
                int AcademicYear, Credits;
                // Hiển thị giao diện nhập liệu và nhận giá trị đầu vào
                ShowInputCoursePage(id, CourseName, ClassName, GVName, AcademicYear, Credits, wDay, Session);
                // Tạo đối tượng Course với dữ liệu đã nhập
                Course* newCourse = InputCourse(id, CourseName, ClassName, GVName, AcademicYear, Credits, wDay, Session);
                AddCourse(LC, newCourse);
                createNewCourseActive = false;
                
            }
            if (ViewCourseActive)
            {
                // Tạo một mảng động để lưu trữ các đối tượng Course từ danh sách liên kết
                // Đếm số lượng khóa học trong danh sách liên kết
                int numRows = 0;
                Course* tempCount = LC.head;
                while (tempCount != nullptr) {
                    numRows++;
                    tempCount = tempCount->next;
                }

                // Tạo một mảng động để lưu trữ các đối tượng Course từ danh sách liên kết
                Course* courseArray = new Course[numRows];
                Course* temp = LC.head;

                // Sao chép thông tin từ danh sách liên kết vào mảng
                for (int i = 0; i < numRows && temp != nullptr; i++) {
                    courseArray[i] = *temp;
                    temp = temp->next;
                }

                // Gọi hàm DrawCourseTable với mảng đã tạo
                DrawCourseTable(courseArray, numRows);

                
                

                ViewCourseActive = false;
            }
            EndDrawing();
        }
    }

    CloseWindow();
    return 0;
}
