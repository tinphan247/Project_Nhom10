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
void DrawButton(Rectangle button, const char* text, bool mouseOverButton) 
{
    DrawRectangleRec(button, mouseOverButton ? DARKGRAY : LIGHTGRAY);
    DrawText(text, button.x + button.width / 2 - MeasureText(text, 20) / 2, button.y + button.height / 2 - 10, 20, BLACK);
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
    const int screenWidth = 1400;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "");

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
    int scrollBarYOffset = 0;
    int maxDisplayedLines = 0;

    while (!WindowShouldClose())
    {
        int i = 1;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        NamHoc* temp = L.phead;
        int textWidth = MeasureText("Danh sach cac nam hien co:", 20);
        int xPosition = (screenWidth - textWidth) / 2;
        DrawText("Danh sach cac nam hien co:", xPosition, 50 - scrollBarYOffset, 20, RED);
        while (temp != NULL) {
            // Convert std::string to C-style string
            const char* kt = temp->ngaybatdau.c_str();
            textWidth = MeasureText(kt, 20);
            xPosition = (screenWidth - textWidth) / 2;
            DrawText(kt, xPosition, 50 * (i + 1) - scrollBarYOffset, 20, BLACK); // Điều chỉnh vị trí bắt đầu
            temp = temp->next;
            i++;
        }

        // Tính toán vị trí thanh cuộn
        Rectangle scrollBar = { screenWidth - 20, 0, 20, screenHeight };
        float scrollBarHeight = screenHeight * screenHeight / ((float)i * 50);
        float maxScrollBarY = screenHeight - scrollBarHeight;
        float scrollBarY = ((float)scrollBarYOffset / (i * 50)) * maxScrollBarY;
        scrollBar.height = scrollBarHeight;
        scrollBar.y = scrollBarY;
        DrawRectangleRec(scrollBar, GRAY);

        // Xử lý sự kiện cuộn chuột
        int scroll = GetMouseWheelMove();
        scrollBarYOffset += scroll * 50*(-1);
        if (scrollBarYOffset < 0) scrollBarYOffset = 0;
        if (scrollBarYOffset > ((i - maxDisplayedLines) * 50)) scrollBarYOffset = (i - maxDisplayedLines) * 50;

        // Cập nhật vị trí dọc hiện tại
        int currentYOffset = 0;

        // Vẽ các trường nhập và nút xác nhận
        // Calculate starting Y position for input fields
        int startY = 50 * (i + 1) + 50;

        // Draw input fields and labels
        currentYOffset = startY - scrollBarYOffset;

        textWidth = MeasureText("Chon nam hoc:", 20);
        xPosition = (screenWidth - textWidth) / 2;
        DrawText("Chon nam hoc:", xPosition, currentYOffset, 20, BLACK);
        DrawRectangle((screenWidth - 400) / 2, currentYOffset + 30, 400, 40, isYearInputActive ? LIGHTGRAY : GRAY);
        DrawText(yearInput.c_str(), (screenWidth - 400) / 2 + 10, currentYOffset + 40, 20, BLACK);

        textWidth = MeasureText("Chon thu tu cua hoc ki (1-3):", 20);
        xPosition = (screenWidth - textWidth) / 2;
        DrawText("Chon thu tu cua hoc ki (1-3):", xPosition, currentYOffset + 80, 20, BLACK);
        DrawRectangle((screenWidth - 400) / 2, currentYOffset + 110, 400, 40, isOrdinalInputActive ? LIGHTGRAY : GRAY);
        DrawText(ordinalInput.c_str(), (screenWidth - 400) / 2 + 10, currentYOffset + 120, 20, BLACK);

        textWidth = MeasureText("Nhap vao ngay bat dau hoc ki (VD 01/01/2024):", 20);
        xPosition = (screenWidth - textWidth) / 2;
        DrawText("Nhap vao ngay bat dau hoc ki (VD 01/01/2024):", xPosition, currentYOffset + 160, 20, BLACK);
        DrawRectangle((screenWidth - 400) / 2, currentYOffset + 190, 400, 40, isStartDateInputActive ? LIGHTGRAY : GRAY);
        DrawText(startDateInput.c_str(), (screenWidth - 400) / 2 + 10, currentYOffset + 200, 20, BLACK);

        textWidth = MeasureText("Nhap vao ngay ket thuc hoc ki (VD 01/01/2024):", 20);
        xPosition = (screenWidth - textWidth) / 2;
        DrawText("Nhap vao ngay ket thuc hoc ki (VD 01/01/2024):", xPosition, currentYOffset + 240, 20, BLACK);
        DrawRectangle((screenWidth - 400) / 2, currentYOffset + 270, 400, 40, isEndDateInputActive ? LIGHTGRAY : GRAY);
        DrawText(endDateInput.c_str(), (screenWidth - 400) / 2 + 10, currentYOffset + 280, 20, BLACK);

        float confirmButtonX = (screenWidth - 200) / 2;
        DrawRectangle(confirmButtonX, currentYOffset + 330, 200, 50, isConfirmButtonPressed ? RED : MAROON);
        DrawText("Xac Nhan", confirmButtonX + 50, currentYOffset + 345, 20, WHITE);

        if (!isInputValid) {
            DrawText(errorMessage.c_str(), screenWidth - MeasureText(errorMessage.c_str(), 20) - 10, screenHeight - 30, 20, RED);
        }

        // Xử lý sự kiện chuột
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePosition = GetMousePosition();
            if (CheckCollisionPointRec(mousePosition, { (float)(screenWidth - 400) / 2, (float)currentYOffset + 30, 400, 40 })) {
                isYearInputActive = true;
                isOrdinalInputActive = false;
                isStartDateInputActive = false;
                isEndDateInputActive = false;
                isConfirmButtonPressed = false;
            }
            else if (CheckCollisionPointRec(mousePosition, { (float)(screenWidth - 400) / 2, (float)currentYOffset + 110, 400, 40 })) {
                isOrdinalInputActive = true;
                isYearInputActive = false;
                isStartDateInputActive = false;
                isEndDateInputActive = false;
                isConfirmButtonPressed = false;
            }
            else if (CheckCollisionPointRec(mousePosition, { (float)(screenWidth - 400) / 2, (float)currentYOffset + 190, 400, 40 })) {
                isStartDateInputActive = true;
                isYearInputActive = false;
                isOrdinalInputActive = false;
                isEndDateInputActive = false;
                isConfirmButtonPressed = false;
            }
            else if (CheckCollisionPointRec(mousePosition, { (float)(screenWidth - 400) / 2, (float)currentYOffset + 270, 400, 40 })) {
                isEndDateInputActive = true;
                isYearInputActive = false;
                isOrdinalInputActive = false;
                isStartDateInputActive = false;
                isConfirmButtonPressed = false;
            }
            else if (CheckCollisionPointRec(mousePosition, { confirmButtonX, (float)currentYOffset + 330, 200, 50 })) {
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
                    // Ham them 1 hoc ky vao nam hoc da chon
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
                            cout << "Da them 1 hoc ky vao nam hoc " << temp->ngaybatdau << std::endl;
                            break;
                        }
                        temp = temp->next;
                    }

                    if (!yearFound) {
                        isInputValid = false;
                        errorMessage = "Year not found!";
                    }
                    else {
                        // Save the input data to the Semester object
                        H->Ngaybatdau = startDateInput;
                        H->thutu = stoi(ordinalInput);
                        H->Ngayketthuc = endDateInput;

                        // Close the window
                        CloseWindow();
                        break; // Exit the loop after saving and closing the window
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

        // Xử lý phím bấm cho các ô nhập dữ liệu
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
            if (IsKeyPressed(KEY_BACKSPACE) && !ordinalInput.empty())
            {
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

   
}



void InitList(ListCourses& list) {
    list.head = NULL;
    list.tail = NULL;
    list.size = 0;
}

void AddCourse(ListCourses& List, Course* newCourse) {
    if (newCourse == NULL) return;
    if (List.head == NULL) {
        List.head = newCourse;
        List.tail = newCourse;
    }
    else {
        List.tail->next = newCourse;
        List.tail = newCourse;
    }
    List.size++;
}


void DrawCourseTable(const Course* courses, int numRows)
{
    const int screenWidth = 1400;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "");
    const float screenRatioX = (float)GetScreenWidth() / screenWidth;
    const float screenRatioY = (float)GetScreenHeight() / screenHeight;

    const int numCols = 8;

    const int cellWidth = (screenWidth - 2 * 50) / numCols * screenRatioX; // Adjusted to fit the entire screen width with padding
    const int cellHeight = 80 * screenRatioY; // Increased height to separate data further
    const int textPadding = 10 * ((screenRatioX + screenRatioY) / 2); // Adjusted padding based on average screen ratio

    const int startX = (screenWidth - (numCols * cellWidth)) / 2; // Centered horizontally
    const int startY = 100 * screenRatioY; // Increased startY for more separation

    const char* headers[numCols] = { "ID", "Ten khoa hoc", "Lop", "Giao vien", "Nam hoc", "So tin chi", " week day", "Session" };

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw headers
        for (int i = 0; i < numCols; i++) {
            DrawRectangle(startX + i * cellWidth, startY, cellWidth, cellHeight, LIGHTGRAY);
            int textWidth = MeasureText(headers[i], 15 * ((screenRatioX + screenRatioY) / 2)); // Adjusted font size based on average screen ratio
            int textX = startX + i * cellWidth + (cellWidth - textWidth) / 2;
            DrawText(headers[i], textX, startY + textPadding, 15 * ((screenRatioX + screenRatioY) / 2), BLACK); // Adjusted font size
        }

        // Draw data
        for (int i = 0; i < numRows; i++) {
            DrawRectangle(startX, startY + (i + 1) * cellHeight, cellWidth * numCols, cellHeight, RAYWHITE); // Draw a rectangle for the entire row
            for (int j = 0; j < numCols; j++) {
                int textWidth = 0;
                int textX = startX + j * cellWidth + textPadding;
                const char* textToDraw = nullptr;
                switch (j) {
                case 0:
                    textToDraw = courses[i].id.c_str();
                    textWidth = MeasureText(textToDraw, 15 * ((screenRatioX + screenRatioY) / 2)); // Adjusted font size based on average screen ratio
                    break;
                case 1:
                    textToDraw = courses[i].courseName.c_str();
                    textWidth = MeasureText(textToDraw, 15 * ((screenRatioX + screenRatioY) / 2)); // Adjusted font size based on average screen ratio
                    break;
                case 2:
                    textToDraw = courses[i].ClassName.c_str();
                    textWidth = MeasureText(textToDraw, 15 * ((screenRatioX + screenRatioY) / 2)); // Adjusted font size based on average screen ratio
                    break;
                case 3:
                    textToDraw = courses[i].teacherName.c_str();
                    textWidth = MeasureText(textToDraw, 15 * ((screenRatioX + screenRatioY) / 2)); // Adjusted font size based on average screen ratio
                    break;
                case 4:
                    textToDraw = TextFormat("%d", courses[i].academicYear);
                    textWidth = MeasureText(textToDraw, 15 * ((screenRatioX + screenRatioY) / 2)); // Adjusted font size based on average screen ratio
                    break;
                case 5:
                    textToDraw = TextFormat("%d", courses[i].Credits);
                    textWidth = MeasureText(textToDraw, 15 * ((screenRatioX + screenRatioY) / 2)); // Adjusted font size based on average screen ratio
                    break;
                case 6:
                    textToDraw = courses[i].wDay.c_str();
                    textWidth = MeasureText(textToDraw, 15 * ((screenRatioX + screenRatioY) / 2)); // Adjusted font size based on average screen ratio
                    break;
                case 7:
                    textToDraw = courses[i].session.c_str();
                    textWidth = MeasureText(textToDraw, 15 * ((screenRatioX + screenRatioY) / 2)); // Adjusted font size based on average screen ratio
                    break;
                }
                textX += (cellWidth - textWidth) / 2;
                DrawText(textToDraw, textX, startY + (i + 1) * cellHeight + textPadding, 15 * ((screenRatioX + screenRatioY) / 2), DARKGRAY); // Adjusted font size
            }
        }

        EndDrawing();
    }

    CloseWindow();
}


Course* InputCourse(string id, string CourseName, string ClassName, string GVName, int AcademicYear, int Credits, string wDay, string Session) {
    Course* newCourse = new Course;
    newCourse->id = id;
    newCourse->courseName = CourseName;
    newCourse->ClassName = ClassName;
    newCourse->teacherName = GVName;
    newCourse->academicYear = AcademicYear;
    newCourse->Credits = Credits;
    newCourse->wDay = wDay;
    newCourse->session = Session;
    newCourse->next = NULL;
    cout << newCourse->id << endl;
    cout << newCourse->courseName << endl;
    cout << newCourse->ClassName << endl;
    cout << newCourse->teacherName << endl;
    cout << newCourse->academicYear << endl;
    cout << newCourse->Credits << endl;
    cout << newCourse->wDay << endl;
    cout << newCourse->session << endl;
    return newCourse;
}
void ShowInputCoursePage(string& id, string& CourseName, string& ClassName, string& GVName, int& AcademicYear, int& Credits, string& wDay, string& Session) {
    const int numFields = 8;
    const char* fieldLabels[numFields] = {
        "ID", "Ten khoa hoc", "Lop", "Giao vien", "Nam hoc", "So tin chi", "Nhap week day(MON / TUE...) :", "Nhap Session [S1 (07:30), S2 (09:30), S3(13:30), S4 (15:30)]:"
    };

    string inputs[numFields];
    bool fieldsActive[numFields] = { false };
    bool fieldsError[numFields] = { false };
    int fieldLengths[numFields] = { 10, 50, 10, 50, 4, 2, 3, 5 };

    int activeField = -1;
    bool enterPressed = false;

    InitWindow(1400, 800, "Course Input");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Vẽ tiêu đề trang
        DrawText("Nhap thong tin khoa hoc", 50, 20, 30, DARKGRAY);

        for (int i = 0; i < numFields; i++) {
            // Vẽ tiêu đề của mỗi trường ngay trên ô nhập liệu
            DrawText(fieldLabels[i], 50, 70 + i * 80, 20, BLACK);

            Rectangle inputBox = { 200, 100 + i * 80, 800, 30 };
            // Vẽ ô nhập liệu
            DrawRectangleRec(inputBox, LIGHTGRAY);
            DrawRectangleLinesEx(inputBox, 1, fieldsActive[i] ? RED : BLACK);
            // Vẽ dữ liệu nhập vào
            DrawText(inputs[i].c_str(), 210, 105 + i * 80, 20, BLACK);

            if (fieldsError[i]) {
                // Nếu có lỗi, in dòng chữ báo lỗi ở góc phải dưới cùng của ô nhập liệu
                DrawText("Error!", inputBox.x + inputBox.width - MeasureText("Error!", 20) - 10, inputBox.y + inputBox.height - 25, 20, RED);
            }

            if (CheckCollisionPointRec(GetMousePosition(), inputBox)) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    activeField = i;
                    for (int j = 0; j < numFields; j++) {
                        fieldsActive[j] = (j == i);
                    }
                }
            }
        }

        if (activeField != -1) {
            int key = GetKeyPressed();
            if (key >= 32 && key <= 125 && inputs[activeField].length() < fieldLengths[activeField]) {
                // Kiểm tra trường hợp đặc biệt cho trường "So tin chi"
                if (activeField == 5 && key >= '0' && key <= '9') {
                    inputs[activeField] += (char)key;
                }
                // Kiểm tra trường hợp đặc biệt cho trường "Nam hoc"
                else if (activeField == 4 && key >= '0' && key <= '9') {
                    inputs[activeField] += (char)key;
                }
                // Trường hợp nhập các kí tự khác
                else if (activeField != 4 && activeField != 5 && activeField != 6) { // Không cho nhập kí tự vào trường "Nhap week day"
                    inputs[activeField] += (char)key;
                }
                else if (activeField == 6 && ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z'))) { // Chỉ cho phép nhập kí tự chữ vào trường "Nhap week day"
                    inputs[activeField] += (char)key;
                }
            }
            if (key == KEY_BACKSPACE && !inputs[activeField].empty()) {
                inputs[activeField].pop_back();
            }
            if (key == KEY_ENTER) {
                enterPressed = true;
                bool allFieldsFilled = true;
                for (int i = 0; i < numFields; i++) {
                    if (inputs[i].empty()) {
                        fieldsError[i] = true;
                        allFieldsFilled = false;
                    }
                    else {
                        fieldsError[i] = false;
                    }
                }
                if (allFieldsFilled) {
                    // Kiểm tra tính hợp lệ của dữ liệu nhập vào cho trường "Nam hoc"


                    // Kiểm tra tính hợp lệ của dữ liệu nhập vào cho trường "Nhap week day"
                    if (inputs[6] != "MON" && inputs[6] != "TUE" && inputs[6] != "WED" && inputs[6] != "THU" && inputs[6] != "FRI" && inputs[6] != "SAT" && inputs[6] != "SUN") {
                        fieldsError[6] = true; // Đánh dấu trường "Nhap week day" có lỗi
                        allFieldsFilled = false; // Đặt lại biến kiểm tra để không thoát khỏi vòng lặp
                    }
                    else {
                        fieldsError[6] = false; // Đánh d
                    }

                    if (allFieldsFilled) {
                        // Nếu không có lỗi, gán dữ liệu vào các biến và thoát khỏi vòng lặp
                        id = inputs[0];
                        CourseName = inputs[1];
                        ClassName = inputs[2];
                        GVName = inputs[3];
                        AcademicYear = stoi(inputs[4]);
                        Credits = stoi(inputs[5]);
                        wDay = inputs[6];
                        Session = inputs[7];
                        break;
                    }
                }
            }

        }


        EndDrawing();
    }

    CloseWindow();
}


