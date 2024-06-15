#include "project.h"

bool IsEmpty(const char* str)
{
    return strlen(str) == 0;
}
ListUser* addListUser(const string& path) {
    ifstream ifile(path);
    if (!ifile.is_open()) {
        cerr << "Không thể mở file." << endl;
        return nullptr;
    }

    ListUser* LUR = new ListUser;
    LUR->phead = nullptr;
    LUR->ptail = nullptr;
    string temp;
    getline(ifile, temp); // Bỏ qua dòng tiêu đề

    while (ifile.peek() != EOF) {
        User* u = new User;

        getline(ifile, u->id, ',');
        getline(ifile, u->pass, ',');
        getline(ifile, u->ho, ',');
        getline(ifile, u->ten, ',');
        getline(ifile, u->ClassName, ',');
        getline(ifile, u->gender, ',');

        getline(ifile, temp, '/');
        u->birth.month = stoi(temp);
        getline(ifile, temp, '/');
        u->birth.day = stoi(temp);
        getline(ifile, temp, ',');
        u->birth.year = stoi(temp);

        getline(ifile, u->academicYear, ',');
        getline(ifile, temp, '\n');
        if (temp == "TRUE")
        {
            u->staff = true;
        }
        else
        {
            u->staff = false;
        }

        u->next = nullptr;
        if (LUR->phead == nullptr) {
            LUR->phead = u;
            LUR->ptail = u;
        }
        else {
            LUR->ptail->next = u;
            LUR->ptail = u;
        }
    }
    ifile.close();
    return LUR;
}
bool CheckLogin(const char* username, const char* password, bool& checkstaff, ListUser*& LU)
{
    if (!LU)
    {
        return false;
    }

    User* temp = LU->phead;
    while (temp != nullptr)
    {
        if (temp->id == username && temp->pass == password)
        {
            checkstaff = temp->staff;
            return true;
        }
        temp = temp->next;
    }
    return false;
}
void DrawButton(Rectangle button, const char* text, bool mouseOverButton)
{
    DrawRectangleRec(button, mouseOverButton ? DARKGRAY : LIGHTGRAY);
    DrawText(text, button.x + button.width / 2 - MeasureText(text, 20) / 2, button.y + button.height / 2 - 10, 20, BLACK);
}


void taonamhoc(ListNamHoc& L, NamHoc*& N, const char* thoigiannamhoc)
{
    N = new NamHoc();
    N->ngaybatdau = thoigiannamhoc;
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
    const int screenWidth = 1366;
    const int screenHeight = 768;

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
        scrollBarYOffset += scroll * 50 * (-1);
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


bool courseWasDeleted = false;
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
void showCourseDetails(ListCourses& List,Course& course) {
    const int detailScreenWidth = 1366;
    const int detailScreenHeight = 768;
    InitWindow(detailScreenWidth, detailScreenHeight, "Course Details");

    bool shouldDelete = false;
    bool shouldClose = false;

    while (!WindowShouldClose() && !shouldClose) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        int textY = 50;
        const int textPadding = 10;
        DrawText(("ID: " + course.id).c_str(), 50, textY, 20, BLACK);
        textY += 30 + textPadding;
        DrawText(("Course Name: " + course.courseName).c_str(), 50, textY, 20, BLACK);
        textY += 30 + textPadding;
        DrawText(("Class Name: " + course.ClassName).c_str(), 50, textY, 20, BLACK);
        textY += 30 + textPadding;
        DrawText(("Teacher Name: " + course.teacherName).c_str(), 50, textY, 20, BLACK);
        textY += 30 + textPadding;
        DrawText(("Academic Year: " + std::to_string(course.academicYear)).c_str(), 50, textY, 20, BLACK);
        textY += 30 + textPadding;
        DrawText(("Credits: " + std::to_string(course.Credits)).c_str(), 50, textY, 20, BLACK);
        textY += 30 + textPadding;
        DrawText(("Week Day: " + course.wDay).c_str(), 50, textY, 20, BLACK);
        textY += 30 + textPadding;
        DrawText(("Session: " + course.session).c_str(), 50, textY, 20, BLACK);

        Rectangle deleteButton = { detailScreenWidth / 2 - 50, detailScreenHeight - 100, 100, 50 };
        DrawRectangleRec(deleteButton, RED);
        DrawText("DELETE", detailScreenWidth / 2 - MeasureText("DELETE", 20) / 2, detailScreenHeight - 85, 20, WHITE);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), deleteButton)) {
            shouldDelete = true;
            shouldClose = true;
        }

        EndDrawing();
    }

    CloseWindow();
    if (shouldDelete) {
        RemoveCourse(List, Find_ID(List, course.id));
        courseWasDeleted = true;
    }
}
void viewcourse(ListCourses List, Course*& courses, int& numRows) {
    const int screenWidth = 1366;
    const int screenHeight = 768;
    InitWindow(screenWidth, screenHeight, "");
    const float screenRatioX = (float)GetScreenWidth() / screenWidth;
    const float screenRatioY = (float)GetScreenHeight() / screenHeight;

    const int numCols = 8;
    const int cellWidth = (screenWidth - 2 * 50) / numCols * screenRatioX;
    const int cellHeight = 80 * screenRatioY;
    const int textPadding = 10 * ((screenRatioX + screenRatioY) / 2);

    const int startX = (screenWidth - (numCols * cellWidth)) / 2;
    const int startY = 100 * screenRatioY;

    const char* headers[numCols] = { "ID", "Ten khoa hoc", "Lop", "Giao vien", "Nam hoc", "So tin chi", " week day", "Session" };

    int scrollBarYOffset = 0;
    int maxDisplayedLines = (screenHeight - startY - cellHeight) / cellHeight; // Adjust the max displayed lines based on available space

    int selectedCourse = 0;

    while (!WindowShouldClose()) {
        // Handle keyboard input
        if (IsKeyPressed(KEY_DOWN) && selectedCourse < numRows - 1) {
            selectedCourse++;
        }
        if (IsKeyPressed(KEY_UP) && selectedCourse > 0) {
            selectedCourse--;
        }
        if (IsKeyPressed(KEY_ENTER)) {
            showCourseDetails(List, courses[selectedCourse]);

            // Check if a course was deleted
            if (courseWasDeleted) {
                // Remove the course from List
                numRows--;  // Decrease number of rows

                // Update the courses array if needed
                // Here we assume courses is an array of Course structs or objects
                // Update courses by fetching data from List again
                Course* newCourses = new Course[numRows];  // Allocate new array for courses

                // Copy data from List to newCourses array
                Course* cur = List.head;
                int index = 0;
                while (cur != NULL) {
                    newCourses[index] = *cur;
                    cur = cur->next;
                    index++;
                }

                // Assign newCourses and newNumRows back to the original variables
                delete[] courses;  // Delete old courses array if necessary
                courses = newCourses;

                // Reset courseWasDeleted flag
                courseWasDeleted = false;

                // Close current window and reinitialize to refresh the course list
                CloseWindow();
                InitWindow(screenWidth, screenHeight, "");
            }
        }

        // Adjust scroll position to keep the selected course visible
        if (selectedCourse * cellHeight < scrollBarYOffset) {
            scrollBarYOffset = selectedCourse * cellHeight;
        }
        if (selectedCourse * cellHeight >= scrollBarYOffset + maxDisplayedLines * cellHeight) {
            scrollBarYOffset = (selectedCourse + 1) * cellHeight - maxDisplayedLines * cellHeight;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw headers
        for (int i = 0; i < numCols; i++) {
            DrawRectangle(startX + i * cellWidth, startY, cellWidth, cellHeight, LIGHTGRAY);
            int textWidth = MeasureText(headers[i], 15 * ((screenRatioX + screenRatioY) / 2));
            int textX = startX + i * cellWidth + (cellWidth - textWidth) / 2;
            DrawText(headers[i], textX, startY + textPadding, 15 * ((screenRatioX + screenRatioY) / 2), BLACK);
        }

        // Draw data
        for (int i = 0; i < numRows; i++) {
            if (startY + (i + 1) * cellHeight - scrollBarYOffset < startY + cellHeight) {
                continue; // Skip drawing rows above the visible area
            }
            if (startY + (i + 1) * cellHeight - scrollBarYOffset > screenHeight - cellHeight) {
                break; // No need to draw rows below the visible area
            }

            Color rowColor = (i == selectedCourse) ? SKYBLUE : RAYWHITE;
            DrawRectangle(startX, startY + (i + 1) * cellHeight - scrollBarYOffset, cellWidth * numCols, cellHeight, rowColor);

            for (int j = 0; j < numCols; j++) {
                int textWidth = 0;
                int textX = startX + j * cellWidth + textPadding;
                const char* textToDraw = nullptr;
                switch (j) {
                case 0:
                    textToDraw = courses[i].id.c_str();
                    textWidth = MeasureText(textToDraw, 15 * ((screenRatioX + screenRatioY) / 2));
                    break;
                case 1:
                    textToDraw = courses[i].courseName.c_str();
                    textWidth = MeasureText(textToDraw, 15 * ((screenRatioX + screenRatioY) / 2));
                    break;
                case 2:
                    textToDraw = courses[i].ClassName.c_str();
                    textWidth = MeasureText(textToDraw, 15 * ((screenRatioX + screenRatioY) / 2));
                    break;
                case 3:
                    textToDraw = courses[i].teacherName.c_str();
                    textWidth = MeasureText(textToDraw, 15 * ((screenRatioX + screenRatioY) / 2));
                    break;
                case 4:
                    textToDraw = TextFormat("%d", courses[i].academicYear);
                    textWidth = MeasureText(textToDraw, 15 * ((screenRatioX + screenRatioY) / 2));
                    break;
                case 5:
                    textToDraw = TextFormat("%d", courses[i].Credits);
                    textWidth = MeasureText(textToDraw, 15 * ((screenRatioX + screenRatioY) / 2));
                    break;
                case 6:
                    textToDraw = courses[i].wDay.c_str();
                    textWidth = MeasureText(textToDraw, 15 * ((screenRatioX + screenRatioY) / 2));
                    break;
                case 7:
                    textToDraw = courses[i].session.c_str();
                    textWidth = MeasureText(textToDraw, 15 * ((screenRatioX + screenRatioY) / 2));
                    break;
                default:
                    break;
                }
                textX += (cellWidth - textWidth) / 2;
                DrawText(textToDraw, textX, startY + (i + 1) * cellHeight - scrollBarYOffset + textPadding, 15 * ((screenRatioX + screenRatioY) / 2), DARKGRAY);
            }
        }

        // Calculate and draw scrollbar
        Rectangle scrollBar = { screenWidth - 20, startY + cellHeight, 20, screenHeight - 2 * cellHeight };
        float scrollBarHeight = screenHeight * screenHeight / ((float)numRows * cellHeight);
        float maxScrollBarY = screenHeight - 2 * cellHeight - scrollBarHeight;
        float scrollBarY = ((float)scrollBarYOffset / (numRows * cellHeight)) * maxScrollBarY;
        scrollBar.height = scrollBarHeight;
        scrollBar.y = startY + cellHeight + scrollBarY;
        DrawRectangleRec(scrollBar, GRAY);

        // Handle mouse wheel scrolling
        int scroll = GetMouseWheelMove();
        scrollBarYOffset += scroll * 50 * (-1); // Adjust scrolling speed as needed

        // Limit scrollBarYOffset within valid range
        if (scrollBarYOffset < 0) {
            scrollBarYOffset = 0;
        }
        if (scrollBarYOffset > (numRows - maxDisplayedLines) * cellHeight) {
            scrollBarYOffset = (numRows - maxDisplayedLines) * cellHeight;
        }

        EndDrawing();
    }

    CloseWindow();
}
void RemoveCourse(ListCourses& List, Course* course) {
    if (List.head == NULL) {
        return;
    }
    else if (List.head == course) {
        List.head = course->next;
        if (List.tail == course) {
            List.tail = NULL;
        }
    }
    else {
        // duyet list tim course
        Course* cur = List.head;
        while (cur != NULL && cur->next != course) {
            cur = cur->next;
        }
        //luc nay cur->next = course hoac cur == NULL
        if (cur->next == course) {
            cur->next = course->next;
            if (List.tail == course) {
                List.tail = cur;
            }
        }
        else { // luc nay cur = NULL -> ko tim thay course
            return;
        }
    }
}
Course* Find_ID(ListCourses List, string id) {
    Course* cur = List.head;
    while (cur != NULL && cur->id != id) {
        cur = cur->next;
    }
    return cur;
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

ListSV* addListSV(string path)
{
    ifstream ifile;
    ifile.open(path);
    if (!ifile.is_open())
    {
        cout << "loi";
        return NULL;
    }
    ListSV* List = new ListSV;
    List->phead = NULL;
    List->ptail = NULL;
    string temp;
    getline(ifile, temp);
    while (ifile.peek() != EOF)
    {
        SinhVien* newSV = new SinhVien;

        getline(ifile, newSV->mssv, ',');
        getline(ifile, newSV->ho, ',');
        getline(ifile, newSV->ten, ',');
        getline(ifile, newSV->ClassName, ',');
        getline(ifile, newSV->gender, ',');
        //doc ngay sinh
        getline(ifile, temp, '/');
        newSV->birth.month = stoi(temp);
        getline(ifile, temp, '/');
        newSV->birth.day = stoi(temp);
        getline(ifile, temp, ',');
        newSV->birth.year = stoi(temp);
        getline(ifile, newSV->cccd);
        newSV->Lc = NULL;
        newSV->next = NULL;
        if (List->phead == NULL)
        {
            List->phead = newSV;
            List->ptail = newSV;
        }
        else
        {
            List->ptail->next = newSV;
            List->ptail = newSV;
        }


    }
    ifile.close();

    //return
    return List;

}
void DrawStudentListFromData(ListSV* studentList, int numRows) {
    const int screenWidth = 1366;
    const int screenHeight = 768;
    InitWindow(screenWidth, screenHeight, "");
    const float screenRatioX = (float)GetScreenWidth() / screenWidth;
    const float screenRatioY = (float)GetScreenHeight() / screenHeight;

    const int numCols = 8; // Số cột bao gồm số thứ tự, MSSV, Họ, Tên, Lớp, Giới Tính, Ngày Sinh, CCCD
    const int columnSpacing = 20; // Khoảng cách giữa các cột

    const int cellWidth = (screenWidth - 2 * 50 - (numCols - 1) * columnSpacing) / numCols * screenRatioX; // Adjusted to fit the entire screen width with padding
    const int cellHeight = 80 * screenRatioY; // Increased height to separate data further
    const int textPadding = 10 * ((screenRatioX + screenRatioY) / 2); // Adjusted padding based on average screen ratio

    const int startX = (screenWidth - (numCols * cellWidth + (numCols - 1) * columnSpacing)) / 2; // Centered horizontally
    const int startY = 100 * screenRatioY; // Increased startY for more separation

    const char* headers[numCols] = { "STT", "MSSV", "Ho", "Ten", "Lop", "Gioi Tinh", "Ngay Sinh", "CCCD" };

    // Thêm thanh cuộn
    int scrollBarYOffset = 0;
    int maxDisplayedLines = screenHeight / cellHeight - 2; // Trừ 2 cho phần header và phần input

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw headers
        for (int i = 0; i < numCols; i++) {
            DrawRectangle(startX + (cellWidth + columnSpacing) * i, startY, cellWidth, cellHeight, LIGHTGRAY);
            int textWidth = MeasureText(headers[i], 15 * ((screenRatioX + screenRatioY) / 2)); // Adjusted font size based on average screen ratio
            int textX = startX + (cellWidth + columnSpacing) * i + (cellWidth - textWidth) / 2;
            DrawText(headers[i], textX, startY + textPadding, 15 * ((screenRatioX + screenRatioY) / 2), BLACK); // Adjusted font size
        }

        // Draw data
        const SinhVien* currentSV = studentList->phead;

        // Thanh cuộn
        Rectangle scrollBar = { screenWidth - 20, startY + cellHeight, 20, screenHeight - 2 * cellHeight };
        float scrollBarHeight = screenHeight * screenHeight / ((float)numRows * cellHeight);
        float maxScrollBarY = screenHeight - 2 * cellHeight - scrollBarHeight;
        float scrollBarY = ((float)scrollBarYOffset / (numRows * cellHeight)) * maxScrollBarY;
        scrollBar.height = scrollBarHeight;
        scrollBar.y = startY + cellHeight + scrollBarY;
        DrawRectangleRec(scrollBar, GRAY);

        // Xử lý sự kiện cuộn chuột
        int scroll = GetMouseWheelMove();
        scrollBarYOffset += scroll * 50 * (-1); // Điều chỉnh tốc độ cuộn tùy thuộc vào yêu cầu của ứng dụng

        // Giới hạn vị trí cuộn
        if (scrollBarYOffset < 0) scrollBarYOffset = 0;
        if (scrollBarYOffset > (numRows - maxDisplayedLines) * cellHeight) {
            scrollBarYOffset = (numRows - maxDisplayedLines) * cellHeight;
        }

        // Vẽ lại dữ liệu với vị trí cuộn mới
        int visibleStartIndex = scrollBarYOffset / cellHeight;
        int visibleEndIndex = visibleStartIndex + maxDisplayedLines;
        int currentIndex = 0;
        currentSV = studentList->phead;

        while (currentIndex < visibleStartIndex && currentSV != nullptr) {
            currentSV = currentSV->next;
            currentIndex++;
        }

        for (int i = visibleStartIndex; i < visibleEndIndex && currentSV != nullptr; i++) {
            // Vẽ dữ liệu cho hàng hiện tại
            DrawRectangle(startX, startY + (i - visibleStartIndex + 1) * cellHeight, cellWidth * numCols + columnSpacing * (numCols - 1), cellHeight, RAYWHITE); // Vẽ hình chữ nhật cho toàn bộ hàng
            DrawText(std::to_string(i + 1).c_str(), startX + textPadding, startY + (i - visibleStartIndex + 1) * cellHeight + textPadding, 15, DARKGRAY); // Số thứ tự
            DrawText(currentSV->mssv.c_str(), startX + (cellWidth + columnSpacing) * 1 + textPadding, startY + (i - visibleStartIndex + 1) * cellHeight + textPadding, 15, DARKGRAY); // MSSV
            DrawText(currentSV->ho.c_str(), startX + (cellWidth + columnSpacing) * 2 + textPadding, startY + (i - visibleStartIndex + 1) * cellHeight + textPadding, 15, DARKGRAY); // Ho
            DrawText(currentSV->ten.c_str(), startX + (cellWidth + columnSpacing) * 3 + textPadding, startY + (i - visibleStartIndex + 1) * cellHeight + textPadding, 15, DARKGRAY); // Ten
            DrawText(currentSV->ClassName.c_str(), startX + (cellWidth + columnSpacing) * 4 + textPadding, startY + (i - visibleStartIndex + 1) * cellHeight + textPadding, 15, DARKGRAY); // Lop
            DrawText(currentSV->gender.c_str(), startX + (cellWidth + columnSpacing) * 5 + textPadding, startY + (i - visibleStartIndex + 1) * cellHeight + textPadding, 15, DARKGRAY); // Gioi Tinh
            string birthday = TextFormat("%02d/%02d/%d", currentSV->birth.day, currentSV->birth.month, currentSV->birth.year);
            DrawText(birthday.c_str(), startX + (cellWidth + columnSpacing) * 6 + textPadding, startY + (i - visibleStartIndex + 1) * cellHeight + textPadding, 15, DARKGRAY); // Ngay Sinh
            DrawText(currentSV->cccd.c_str(), startX + (cellWidth + columnSpacing) * 7 + textPadding, startY + (i - visibleStartIndex + 1) * cellHeight + textPadding, 15, DARKGRAY); // CCCD

            currentSV = currentSV->next;
        }

        // Vẽ hàng header sau cùng để đảm bảo màu không bị đứt đoạn
        DrawRectangle(startX, startY, cellWidth * numCols + columnSpacing * (numCols - 1), cellHeight, LIGHTGRAY);
        for (int i = 0; i < numCols; i++) {
            int textWidth = MeasureText(headers[i], 15 * ((screenRatioX + screenRatioY) / 2)); // Adjusted font size based on average screen ratio
            int textX = startX + (cellWidth + columnSpacing) * i + (cellWidth - textWidth) / 2;
            DrawText(headers[i], textX, startY + textPadding, 15 * ((screenRatioX + screenRatioY) / 2), BLACK); // Adjusted font size
        }

        // Kết thúc vẽ
        EndDrawing();
    }

    CloseWindow();
}
void saveListUser(ListUser* LUR, const string& path) {
    ofstream ofile(path);
    if (!ofile.is_open()) {
        cerr << "Không thể mở file để ghi." << endl;
        return;
    }

    // Write header line
    ofile << "id,pass,ho,ten,ClassName,gender,birth,academicYear,staff\n";

    // Traverse through the list and write each user's information
    User* current = LUR->phead;
    while (current != nullptr) {
        ofile << current->id << ","
            << current->pass << ","
            << current->ho << ","
            << current->ten << ","
            << current->ClassName << ","
            << current->gender << ","
            << current->birth.month << "/" << current->birth.day << "/" << current->birth.year << ","
            << current->academicYear << ",";
        if (current->staff) {
            ofile << "TRUE\n";
        }
        else {
            ofile << "FALSE\n";
        }
        current = current->next;
    }

    ofile.close();
}
void ChangePassword(ListUser* userList, const char* username, const char* password) {
    const int dashboardWidth = 1366;
    const int dashboardHeight = 768;
    InitWindow(dashboardWidth, dashboardHeight, "");

    bool changePasswordActive = true;
    char currentPassword[128] = "\0";
    char newPassword[128] = "\0";
    char confirmedNewPassword[128] = "\0";
    Rectangle currentPasswordBox = { dashboardWidth / 2 - 150, 200, 300, 40 };
    Rectangle newPasswordBox = { dashboardWidth / 2 - 150, 280, 300, 40 };
    Rectangle confirmedNewPasswordBox = { dashboardWidth / 2 - 150, 360, 300, 40 };
    bool currentPasswordBoxActive = false;
    bool newPasswordBoxActive = false;
    bool confirmedNewPasswordBoxActive = false;
    bool confirmPassword = false;
    char errorMessage[256] = "\0";

    const int maxPasswordLength = 24; // Maximum password length is 24 characters

    SetTargetFPS(60);

    while (!WindowShouldClose() && changePasswordActive) {
        Vector2 mousePoint = GetMousePosition();

        // Handle user input
        if (CheckCollisionPointRec(mousePoint, currentPasswordBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentPasswordBoxActive = true;
            newPasswordBoxActive = false;
            confirmedNewPasswordBoxActive = false;
        }
        else if (CheckCollisionPointRec(mousePoint, newPasswordBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentPasswordBoxActive = false;
            newPasswordBoxActive = true;
            confirmedNewPasswordBoxActive = false;
        }
        else if (CheckCollisionPointRec(mousePoint, confirmedNewPasswordBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentPasswordBoxActive = false;
            newPasswordBoxActive = false;
            confirmedNewPasswordBoxActive = true;
        }
        else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            currentPasswordBoxActive = false;
            newPasswordBoxActive = false;
            confirmedNewPasswordBoxActive = false;
        }

        // Process key presses in input boxes
        if (currentPasswordBoxActive) {
            int key = GetKeyPressed();
            if ((key >= 32) && (key <= 125)) {
                int length = strlen(currentPassword);
                if (length < maxPasswordLength) {
                    char newChar = (char)key;
                    if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
                        newChar = toupper(newChar);
                    }
                    else {
                        newChar = tolower(newChar);
                    }
                    currentPassword[length] = newChar;
                    currentPassword[length + 1] = '\0';
                }
            }
            if (IsKeyPressed(KEY_BACKSPACE)) {
                int length = strlen(currentPassword);
                if (length > 0)
                    currentPassword[length - 1] = '\0';
            }
        }
        else if (newPasswordBoxActive) {
            int key = GetKeyPressed();
            if ((key >= 32) && (key <= 125)) {
                int length = strlen(newPassword);
                if (length < maxPasswordLength) {
                    char newChar = (char)key;
                    if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
                        newChar = toupper(newChar);
                    }
                    else {
                        newChar = tolower(newChar);
                    }
                    newPassword[length] = newChar;
                    newPassword[length + 1] = '\0';
                }
            }
            if (IsKeyPressed(KEY_BACKSPACE)) {
                int length = strlen(newPassword);
                if (length > 0)
                    newPassword[length - 1] = '\0';
            }
        }
        else if (confirmedNewPasswordBoxActive) {
            int key = GetKeyPressed();
            if ((key >= 32) && (key <= 125)) {
                int length = strlen(confirmedNewPassword);
                if (length < maxPasswordLength) {
                    char newChar = (char)key;
                    if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
                        newChar = toupper(newChar);
                    }
                    else {
                        newChar = tolower(newChar);
                    }
                    confirmedNewPassword[length] = newChar;
                    confirmedNewPassword[length + 1] = '\0';
                }
            }
            if (IsKeyPressed(KEY_BACKSPACE)) {
                int length = strlen(confirmedNewPassword);
                if (length > 0)
                    confirmedNewPassword[length - 1] = '\0';
            }
        }

        // Draw everything once per frame
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw interface elements
        DrawText("Change Password", dashboardWidth / 2 - MeasureText("Change Password", 30) / 2, 100, 30, DARKGRAY);

        // Current Password
        DrawText("Current Password:", dashboardWidth / 2 - 150, 170, 20, DARKGRAY);
        DrawRectangleRec(currentPasswordBox, LIGHTGRAY);
        if (currentPasswordBoxActive)
            DrawRectangleLinesEx(currentPasswordBox, 1, RED);
        DrawText(currentPassword, currentPasswordBox.x + 5, currentPasswordBox.y + 10, 20, DARKGRAY);

        // New Password
        DrawText("New Password:", dashboardWidth / 2 - 150, 250, 20, DARKGRAY);
        DrawRectangleRec(newPasswordBox, LIGHTGRAY);
        if (newPasswordBoxActive)
            DrawRectangleLinesEx(newPasswordBox, 1, RED);
        DrawText(newPassword, newPasswordBox.x + 5, newPasswordBox.y + 10, 20, DARKGRAY);

        // Confirm New Password
        DrawText("Confirm New Password:", dashboardWidth / 2 - 150, 330, 20, DARKGRAY);
        DrawRectangleRec(confirmedNewPasswordBox, LIGHTGRAY);
        if (confirmedNewPasswordBoxActive)
            DrawRectangleLinesEx(confirmedNewPasswordBox, 1, RED);
        DrawText(confirmedNewPassword, confirmedNewPasswordBox.x + 5, confirmedNewPasswordBox.y + 10, 20, DARKGRAY);

        // Change Password Button
        Rectangle changePasswordButton = { dashboardWidth / 2 - 50, 420, 100, 40 };
        DrawRectangleRec(changePasswordButton, LIGHTGRAY);
        DrawText("Change", changePasswordButton.x + 5, changePasswordButton.y + 10, 20, DARKGRAY);

        // Check if Change button is pressed
        if (CheckCollisionPointRec(mousePoint, changePasswordButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            // Locate the user in the list
            User* temp = userList->phead;
            while (temp != NULL)
            {
                if (username == temp->id && password == temp->pass)
                {
                    break;
                }
                temp = temp->next;
            }

            // Check current and new passwords
            if (currentPassword == temp->pass) {
                if (strlen(newPassword) > 0 && strcmp(newPassword, confirmedNewPassword) == 0) {
                    // Update password in the system
                    temp->pass = newPassword;
                    confirmPassword = true;
                    strcpy_s(errorMessage, 50, "Password changed successfully!");
                }
                else {
                    strcpy_s(errorMessage, 100, "Error: New passwords do not match or are invalid.");
                }
            }
            else {
                strcpy_s(errorMessage, 38, "Error: Current password is incorrect.");
            }
            if (confirmPassword) {
                changePasswordActive = false;
            }
        }

        // Draw error message if there is any
        DrawText(errorMessage, dashboardWidth - MeasureText(errorMessage, 20) - 10, dashboardHeight - 30, 20, RED);
        EndDrawing();
    }
    CloseWindow(); // Close window when done
}
bool Login(ListUser* LUR, char* username, char* password, bool& checkstaff) {
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Login");

    bool mouseOnText = false;
    bool usernameBoxActive = false;
    bool passwordBoxActive = false;
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
            if (!IsEmpty(username) && !IsEmpty(password)) {
                if (CheckLogin(username, password, checkstaff, LUR)) {
                    loginSuccessful = true;
                    break;
                }
                else {
                    showError = true;
                }
            }
        }
    }

    CloseWindow();
    return loginSuccessful;
}
void CreateNewSchoolYeabutton(bool& createNewSchoolYearActive, bool& schoolYearInputBoxActive, char* schoolYearInput, ListNamHoc& LNH, NamHoc*& N, Vector2 mousePoint) {
    const int screenWidth = 1366;
    const int screenHeight = 768;
    Rectangle schoolYearInputBox = { screenWidth / 2 - 100, 450, 200, 40 };

    // Vẽ các thành phần của giao diện người dùng
    DrawRectangleRec(schoolYearInputBox, LIGHTGRAY);
    DrawText(schoolYearInput, schoolYearInputBox.x + 5, schoolYearInputBox.y + 10, 20, DARKGRAY);
    DrawText("Enter School Year (e.g., 2020-2021):", schoolYearInputBox.x, schoolYearInputBox.y - 20, 20, LIGHTGRAY);

    // Kiểm tra tương tác của người dùng với hộp văn bản
    if (CheckCollisionPointRec(mousePoint, schoolYearInputBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        schoolYearInputBoxActive = true;
    }
    else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        schoolYearInputBoxActive = false;
    }

    // Nhận ký tự từ bàn phím nếu hộp văn bản đang hoạt động
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

    // Xử lý khi người dùng nhấn phím ENTER
    if (IsKeyPressed(KEY_ENTER)) {
        taonamhoc(LNH, N, schoolYearInput);
        createNewSchoolYearActive = false;
        memset(schoolYearInput, 0, sizeof(schoolYearInput));
    }
}
void AddStudentsbutton(char* AddsvInput, Rectangle AddsvInputBox, bool& AddsvInputBoxActive) {
    static bool showError = false;

    // Vẽ hộp nhập liệu và chuỗi ký tự hiện tại
    DrawRectangleRec(AddsvInputBox, LIGHTGRAY);
    DrawText(AddsvInput, AddsvInputBox.x + 5, AddsvInputBox.y + 10, 20, DARKGRAY);
    DrawText("Input file want to read", AddsvInputBox.x, AddsvInputBox.y - 20, 20, LIGHTGRAY);

    // Xử lý nhập liệu từ bàn phím
    if (AddsvInputBoxActive) {
        int key = GetKeyPressed();
        if ((key >= 32) && (key <= 125)) {
            int length = strlen(AddsvInput);
            if (length < 127) {
                char newChar = (char)key;
                if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
                    newChar = toupper(newChar);
                }
                else {
                    newChar = tolower(newChar);
                }
                AddsvInput[length] = newChar;
                AddsvInput[length + 1] = '\0';
            }
        }
        if (IsKeyPressed(KEY_BACKSPACE)) {
            int length = strlen(AddsvInput);
            if (length > 0) AddsvInput[length - 1] = '\0';
        }
    }

    // Xử lý khi nhấn phím ENTER
    if (IsKeyPressed(KEY_ENTER)) {
        ListSV* svList = addListSV(AddsvInput);
        if (svList == NULL) {
            showError = true;  // Set the error flag
            return;
        }
        showError = false;  // Reset the error flag if file is successfully opened

        int numRows = 0;
        SinhVien* currentSV = svList->phead;
        while (currentSV != nullptr) {
            numRows++;
            currentSV = currentSV->next;
        }
        DrawStudentListFromData(svList, numRows);
        memset(AddsvInput, 0, 128);  // Clear the input buffer
        AddsvInputBoxActive = false;
    }

    // Vẽ thông báo lỗi nếu không thể mở file
    if (showError) {
        const char* errorMsg = "Unable to open file";
        int fontSize = 20;
        int textWidth = MeasureText(errorMsg, fontSize);
        int posX = GetScreenWidth() - textWidth - 10;
        int posY = GetScreenHeight() - fontSize - 10;

        DrawText(errorMsg, posX, posY, fontSize, RED);
    }
}
User* timnodeuser(ListUser* LUR, string username, string password)
{
    User* temp = LUR->phead;
    while (temp != NULL)
    {
        if (temp->id == username && temp->pass == password)
        {
            return temp;
            break;
        }
        temp = temp->next;
    }
}
void DisplayProfileInfo(User* user) {
    const int windowWidth = 1366;
    const int windowHeight = 768;
    const int buttonWidth = 120;
    const int buttonHeight = 40;
    const int backButtonX = windowWidth - buttonWidth - 20;
    const int backButtonY = windowHeight - buttonHeight - 20;
    bool backButtonPressed = false;

    InitWindow(windowWidth, windowHeight, "Profile");

    while (!WindowShouldClose() && !backButtonPressed) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw personal information on the screen
        DrawText(TextFormat("ID: %s", user->id.c_str()), 50, 50, 20, BLACK);  // user->id is a string
        DrawText(TextFormat("Full Name: %s %s", user->ho.c_str(), user->ten.c_str()), 50, 80, 20, BLACK);
        DrawText(TextFormat("Date of Birth: %02d/%02d/%d", user->birth.day, user->birth.month, user->birth.year), 50, 110, 20, BLACK);
        DrawText(TextFormat("Gender: %s", user->gender.c_str()), 50, 140, 20, BLACK);
        DrawText(TextFormat("Academic Year: %s", user->academicYear.c_str()), 50, 170, 20, BLACK);

        // Draw back button
        DrawRectangle(backButtonX, backButtonY, buttonWidth, buttonHeight, LIGHTGRAY);
        DrawText("Back", backButtonX + 20, backButtonY + 10, 20, BLACK);

        // Check if mouse is over back button
        Vector2 mousePoint = GetMousePosition();
        if (CheckCollisionPointRec(mousePoint, { (float)backButtonX, (float)backButtonY, (float)buttonWidth, (float)buttonHeight }) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            backButtonPressed = true;
        }

        EndDrawing();
    }

    CloseWindow();
}
void ShowImportCoursePage(string& pathC) {
    const int screenWidth = 1366;
    const int screenHeight = 768;
    bool pathBoxActive = false;
    char pathInput[256] = "\0";
    bool importButtonClicked = false;

    Rectangle pathBox = { screenWidth / 2 - 250, screenHeight / 2 - 20, 500, 40 };
    Rectangle importButton = { screenWidth / 2 - 50, screenHeight / 2 + 40, 100, 40 };

    bool showWindow = true;

    InitWindow(screenWidth, screenHeight, "Import Course");
    SetTargetFPS(60);

    while (!WindowShouldClose() && showWindow) {
        Vector2 mousePoint = GetMousePosition();
        bool mouseOverImport = CheckCollisionPointRec(mousePoint, importButton);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Import Course from File", screenWidth / 2 - MeasureText("Import Course from File", 20) / 2, screenHeight / 2 - 80, 20, DARKGRAY);

        DrawRectangleRec(pathBox, LIGHTGRAY);
        if (pathBoxActive) DrawRectangleLinesEx(pathBox, 1, RED);
        DrawText(pathInput, pathBox.x + 5, pathBox.y + 10, 20, DARKGRAY);

        DrawRectangleRec(importButton, mouseOverImport ? LIGHTGRAY : GRAY);
        DrawText("Import", importButton.x + 20, importButton.y + 10, 20, DARKGRAY);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (CheckCollisionPointRec(mousePoint, pathBox)) {
                pathBoxActive = true;
            }
            else {
                pathBoxActive = false;
            }

            if (CheckCollisionPointRec(mousePoint, importButton)) {
                importButtonClicked = true;
            }
        }

        if (pathBoxActive) {
            int key = GetKeyPressed();
            if ((key >= 32) && (key <= 125)) {
                int length = strlen(pathInput);
                if (length < 255) {
                    char newChar = (char)key;

                    // Check if Shift key is pressed
                    if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
                        newChar = toupper(newChar); // Chuyển đổi sang chữ hoa
                    }
                    else {
                        newChar = tolower(newChar); // Chuyển đổi sang chữ thường
                    }

                    pathInput[length] = newChar;
                    pathInput[length + 1] = '\0';
                }
            }
            if (IsKeyPressed(KEY_BACKSPACE)) {
                int length = strlen(pathInput);
                if (length > 0) pathInput[length - 1] = '\0';
            }
        }

        if (importButtonClicked && !IsEmpty(pathInput)) {
            pathC = pathInput;  // Lưu đường dẫn được nhập bởi người dùng
            memset(pathInput, 0, sizeof(pathInput));  // Xóa bộ nhớ đệm pathInput
            showWindow = false; // Đóng cửa sổ import
        }

        EndDrawing();
    }

    CloseWindow();
}
void ImportCourseFile(ListCourses& List, string path)
{
    ifstream ifile;
    ifile.open(path);
    if (!ifile.is_open()) {
        cout << "Khong the mo file" << endl;
        return;
    }
    string temp;
    getline(ifile, temp);
    while (!ifile.eof()) {
        Course* cur = new Course;
        getline(ifile, cur->id, ',');
        getline(ifile, cur->courseName, ',');
        getline(ifile, cur->teacherName, ',');
        getline(ifile, cur->ClassName, ',');
        //ID,Course name,Teacher name,ClassName,Credits,Academic year,Number of students,Day of the week,Session
        //BAA00004, Pháp luật đại cương, Le Thi Thu, 23CTT5, 3, 2023, 50, WED, S1 - S2
        getline(ifile, temp, ',');
        cur->Credits = stoi(temp);
        getline(ifile, temp, ',');
        cur->academicYear = stoi(temp);
        getline(ifile, temp, ',');
        cur->maxStudents = stoi(temp);
        getline(ifile, cur->wDay, ',');
        getline(ifile, cur->session);
        cur->next = NULL;
        AddCourse(List, cur);
    }
    ifile.close();

}
void CourseDashboard(int screenWidth, int screenHeight, ListCourses& LC) {
    InitWindow(screenWidth, screenHeight, "Course Dashboard");

    // Define button properties
    Rectangle inputCourseButton = { screenWidth / 2 - 100, screenHeight / 2 - 60, 220, 40 };
    Rectangle importCourseButton = { screenWidth / 2 - 100, screenHeight / 2 + 20, 220, 40 };
    Rectangle backButton = { screenWidth / 2 - 100, screenHeight / 2 + 100, 220, 40 };

    // Flags to indicate which action is currently active
    bool inputCourseActive = false;
    bool importCourseActive = false;

    while (!WindowShouldClose()) {
        Vector2 mousePoint = GetMousePosition();
        bool inputCourseMouseOver = CheckCollisionPointRec(mousePoint, inputCourseButton);
        bool importCourseMouseOver = CheckCollisionPointRec(mousePoint, importCourseButton);
        bool backMouseOver = CheckCollisionPointRec(mousePoint, backButton);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw buttons
        DrawRectangleRec(inputCourseButton, inputCourseMouseOver ? LIGHTGRAY : GRAY);
        DrawText("Create New Course", inputCourseButton.x + 10, inputCourseButton.y + 10, 20, DARKGRAY);
        DrawRectangleRec(importCourseButton, importCourseMouseOver ? LIGHTGRAY : GRAY);
        DrawText("Import Course", importCourseButton.x + 30, importCourseButton.y + 10, 20, DARKGRAY);
        DrawRectangleRec(backButton, backMouseOver ? LIGHTGRAY : GRAY);
        DrawText("Back", backButton.x + 10, backButton.y + 10, 20, DARKGRAY);

        // Handle button presses
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (inputCourseMouseOver) {
                inputCourseActive = true;
                importCourseActive = false;  // Ensure only one action is active at a time
            }
            else if (importCourseMouseOver) {
                importCourseActive = true;
                inputCourseActive = false;  // Ensure only one action is active at a time
            }
            else if (backMouseOver) {
                CloseWindow();
                return;
            }
        }

        // If input course button is active
        if (inputCourseActive) {
            // Implementation for creating a new course
            string id, CourseName, ClassName, GVName, wDay, Session;
            int AcademicYear, Credits;

            // UI for entering course details and receiving input
            ShowInputCoursePage(id, CourseName, ClassName, GVName, AcademicYear, Credits, wDay, Session);

            // Create a new Course object with the input data
            Course* newCourse = InputCourse(id, CourseName, ClassName, GVName, AcademicYear, Credits, wDay, Session);

            // Add the new Course to the ListCourses
            AddCourse(LC, newCourse);

            // Reset flags and active states
            inputCourseActive = false;
            break;
        }
        else if (importCourseActive) {
            // Handle file input for importing courses
            string path;
            ShowImportCoursePage(path);
            ImportCourseFile(LC, path);
            // Optionally handle post-import actions or UI state updates here

            importCourseActive = false;
            break;
        }

        EndDrawing();
    }

    CloseWindow();  // Close the course dashboard window
}
