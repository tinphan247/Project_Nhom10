#include "function.h"

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
        if (temp == "TRUE") {
            u->staff = true;
        }
        else {
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

bool IsValidSchoolYearFormat(const char* input) {
    //kiem tra dinh dang cua nam hoc
    if (strlen(input) != 9) return false;
    for (int i = 0; i < 9; ++i) {
        if (i == 4) {
            if (input[i] != '-') return false; // ki tu thu nam phai la '-'
        }
        else {
            if (input[i] < '0' || input[i] > '9') return false; // tat cac ki tu con lai phai la so
        }
    }

    return true;
}


Semester* taohocky(Semester*& H, ListNamHoc& L) {
    const int screenWidth = 1366;
    const int screenHeight = 768;
    H = new Semester;
    InitWindow(screenWidth, screenHeight, "Tao hoc ky");
    SetTargetFPS(60);
    bool isYearInputActive = false;
    bool isOrdinalInputActive = false;
    bool isStartDateInputActive = false;
    bool isEndDateInputActive = false;
    bool isConfirmButtonPressed = false;

    string yearInput = "";
    string ordinalInput = "";
    string startDateInput = "";
    string endDateInput = "";

    bool isInputValid = true;
    string errorMessage = "";

    // Gia tri cua con lan chuot
    int scrollBarYOffset = 0;
    int maxDisplayedLines = 0;
    bool semesterAdded = false; // Dieu kien kiem tra xem Hoc ky da duoc them hay chua

    while (!WindowShouldClose() && !semesterAdded) {
        int i = 1;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // In ra danh sach cac nam hoc
        NamHoc* temp = L.phead;
        int textWidth = MeasureText("Danh sach cac nam hien co:", 20);
        int xPosition = (screenWidth - textWidth) / 2;
        DrawText("Danh sach cac nam hien co:", xPosition, 50 - scrollBarYOffset, 20, RED);

        while (temp != NULL) {
            const char* kt = temp->ngaybatdau.c_str();
            textWidth = MeasureText(kt, 20);
            xPosition = (screenWidth - textWidth) / 2;
            DrawText(kt, xPosition, 50 * (i + 1) - scrollBarYOffset, 20, BLACK); // Dieu chinh vi tri bat dau
            temp = temp->next;
            i++;
        }

        // Tim vi tri cua con lan chuot
        Rectangle scrollBar = { screenWidth - 20, 0, 20, screenHeight };
        float scrollBarHeight = screenHeight * screenHeight / ((float)i * 50);
        float maxScrollBarY = screenHeight - scrollBarHeight;
        float scrollBarY = ((float)scrollBarYOffset / (i * 50)) * maxScrollBarY;
        scrollBar.height = scrollBarHeight;
        scrollBar.y = scrollBarY;
        DrawRectangleRec(scrollBar, GRAY);

        // Xu ly thao tac chuot(cuon len hoac cuon xuong)
        int scroll = GetMouseWheelMove();
        scrollBarYOffset += scroll * 50 * (-1);
        if (scrollBarYOffset < 0) scrollBarYOffset = 0;
        if (scrollBarYOffset > ((i - maxDisplayedLines) * 50)) scrollBarYOffset = (i - maxDisplayedLines) * 50;
        int currentYOffset = 0;

        // In ra cac tieu de cua o nhap va nut confirm
        int startY = 50 * (i + 1) + 50;

        currentYOffset = startY - scrollBarYOffset;

        textWidth = MeasureText("Chon nam hoc:", 20);
        xPosition = (screenWidth - textWidth) / 2;
        DrawText("Chon nam hoc:", xPosition, currentYOffset, 20, BLACK);
        DrawRectangle((screenWidth - 400) / 2, currentYOffset + 30, 400, 40, isYearInputActive ? LIGHTGRAY : GRAY);
        DrawText(yearInput.c_str(), (screenWidth - 400) / 2 + 10, currentYOffset + 40, 20, BLACK);

        textWidth = MeasureText("Chon thu tu cua hoc ki (1-3):", 20);
        xPosition = (screenWidth - textWidth) / 2;
        DrawText("Nhap thu tu cua hoc ki (1-3):", xPosition, currentYOffset + 80, 20, BLACK);
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

        // in ra loi neu ko dung dinh dang
        if (!isInputValid) {
            DrawText(errorMessage.c_str(), screenWidth - MeasureText(errorMessage.c_str(), 20) - 10, screenHeight - 30, 20, RED);
        }
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
                else if (ordinalInput < "1" || ordinalInput > "3") {
                    isInputValid = false;
                    errorMessage = "Ordinal input must be between 1 and 3!";
                }
                else {
                    // Chuyen thanh so nguyen de so sanh
                    int newOrdinal = stoi(ordinalInput);

                    // Kiem tra thu tu hoc ki da ton tai hay chua
                    NamHoc* temp = L.phead;
                    bool yearFound = false;
                    while (temp != NULL) {
                        if (temp->ngaybatdau == yearInput) {
                            yearFound = true;
                            Semester* currentSemester = temp->Hocky;
                            bool ordinalExists = false;
                            while (currentSemester != NULL) {
                                if (currentSemester->thutu == newOrdinal) {
                                    ordinalExists = true;
                                    break;
                                }
                                currentSemester = currentSemester->next;
                            }

                            // Neu chua ton tai thi them 1 hoc ky
                            if (!ordinalExists) {
                                // Ham tao hoc ky                             
                                H->thutu = newOrdinal;
                                H->Ngaybatdau = startDateInput;
                                H->Ngayketthuc = endDateInput;
                                H->next = NULL;
                                H->namhoc = yearInput;
                                H->lc = new ListCourses;
                                H->lc->head = NULL;
                                H->lc->tail = NULL;
                                H->showsemester = true;
                                if (temp->Hocky == NULL) {
                                    temp->Hocky = H;
                                }
                                else {
                                    Semester* current = temp->Hocky;
                                    Semester* previous = NULL;
                                    while (current != NULL && current->thutu < newOrdinal) {
                                        previous = current;
                                        current = current->next;
                                    }
                                    if (previous == NULL) {
                                        H->next = temp->Hocky;
                                        temp->Hocky = H;
                                    }
                                    else {
                                        previous->next = H;
                                        H->next = current;
                                    }
                                }
                                cout << "Da them 1 hoc ky vao nam hoc " << temp->ngaybatdau << endl;
                                semesterAdded = true;
                                break;
                            }
                            else {
                                isInputValid = false;
                                errorMessage = "Ordinal already exists for this academic year!";
                                break;
                            }
                        }
                        temp = temp->next;
                    }
                    if (!yearFound) {
                        isInputValid = false;
                        errorMessage = "Selected year not found!";
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

        // Xu ly thong tin nhap vao tu ban phim
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
            if (key >= 48 && key <= 57) { // Chi chpa nhan tu 1 den 3
                ordinalInput += static_cast<char>(key);
            }
            if (IsKeyPressed(KEY_BACKSPACE) && !ordinalInput.empty()) {
                ordinalInput.pop_back();
            }
        }

        if (isStartDateInputActive || isEndDateInputActive) {
            if (key >= 32 && key <= 125) {
                if (isStartDateInputActive) {
                    startDateInput += static_cast<char>(key);
                }
                else {
                    endDateInput += static_cast<char>(key);
                }
            }
            if (IsKeyPressed(KEY_BACKSPACE)) {
                if (isStartDateInputActive && !startDateInput.empty()) {
                    startDateInput.pop_back();
                }
                else if (isEndDateInputActive && !endDateInput.empty()) {
                    endDateInput.pop_back();
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return H;
}
void InitList(ListCourses* list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

void AddCourse(ListCourses*& List, Course* newCourse) {
    if (newCourse == NULL) return;
    newCourse->lsv = new ListSV;
    newCourse->lsv->phead = NULL;
    newCourse->lsv->ptail = NULL;
    if (List->head == NULL) {
        List->head = newCourse;
        List->tail = newCourse;
    }
    else {
        List->tail->next = newCourse;
        List->tail = newCourse;
    }
    List->size++;
}
bool courseWasDeleted = false;
void showCourseDetails(ListCourses*& List, Course& course) {
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
        DrawText(("Academic Year: " + to_string(course.academicYear)).c_str(), 50, textY, 20, BLACK);
        textY += 30 + textPadding;
        DrawText(("Credits: " + to_string(course.Credits)).c_str(), 50, textY, 20, BLACK);
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
void RemoveCourse(ListCourses*& List, Course* course) {
    if (List->head == NULL) {
        return;
    }
    else if (List->head == course) {
        List->head = course->next;
        if (List->tail == course) {
            List->tail = NULL;
        }
    }
    else {
        // duyet list tim course
        Course* cur = List->head;
        while (cur != NULL && cur->next != course) {
            cur = cur->next;
        }
        //luc nay cur->next = course hoac cur == NULL
        if (cur->next == course) {
            cur->next = course->next;
            if (List->tail == course) {
                List->tail = cur;
            }
        }
        else { // luc nay cur = NULL -> ko tim thay course
            return;
        }
    }
}
Course* Find_ID(ListCourses*& List, string id) {
    Course* cur = List->head;
    while (cur != NULL && cur->id != id) {
        cur = cur->next;
    }
    return cur;
}

void viewcourse(ListCourses*& List, Course*& courses, int& numRows) {
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
    int maxDisplayedLines = (screenHeight - startY - cellHeight) / cellHeight;
    int selectedCourse = 0;

    while (!WindowShouldClose()) {
        // Xu ly thong tin nhap vao tu ban phim
        if (IsKeyPressed(KEY_DOWN) && selectedCourse < numRows - 1) {
            selectedCourse++;
        }
        if (IsKeyPressed(KEY_UP) && selectedCourse > 0) {
            selectedCourse--;
        }
        if (IsKeyPressed(KEY_ENTER)) {
            showCourseDetails(List, courses[selectedCourse]);
            if (courseWasDeleted) {
                numRows--;
                Course* newCourses = new Course[numRows];
                Course* cur = List->head;
                int index = 0;
                while (cur != NULL) {
                    newCourses[index] = *cur;
                    cur = cur->next;
                    index++;
                }
                delete[] courses;
                courses = newCourses;
                courseWasDeleted = false;
                CloseWindow();
                InitWindow(screenWidth, screenHeight, "");
            }
        }
        if (selectedCourse * cellHeight < scrollBarYOffset) {
            scrollBarYOffset = selectedCourse * cellHeight;
        }
        if (selectedCourse * cellHeight >= scrollBarYOffset + maxDisplayedLines * cellHeight) {
            scrollBarYOffset = (selectedCourse + 1) * cellHeight - maxDisplayedLines * cellHeight;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // In tieu de
        for (int i = 0; i < numCols; i++) {
            DrawRectangle(startX + i * cellWidth, startY, cellWidth, cellHeight, LIGHTGRAY);
            int textWidth = MeasureText(headers[i], 15 * ((screenRatioX + screenRatioY) / 2));
            int textX = startX + i * cellWidth + (cellWidth - textWidth) / 2;
            DrawText(headers[i], textX, startY + textPadding, 15 * ((screenRatioX + screenRatioY) / 2), BLACK);
        }

        // In cac thong tin cua tieu de
        for (int i = 0; i < numRows; i++) {
            if (startY + (i + 1) * cellHeight - scrollBarYOffset < startY + cellHeight) {
                continue;
            }
            if (startY + (i + 1) * cellHeight - scrollBarYOffset > screenHeight - cellHeight) {
                break;
            }
            Color rowColor = (i == selectedCourse) ? SKYBLUE : RAYWHITE;
            DrawRectangle(startX, startY + (i + 1) * cellHeight - scrollBarYOffset, cellWidth * numCols, cellHeight, rowColor);
            const int fontSize = 15 * ((screenRatioX + screenRatioY) / 2);
            for (int j = 0; j < 8; j++) {
                int textWidth = 0;
                int textX = startX + j * cellWidth + textPadding;
                string textToDraw;

                switch (j) {
                case 0:
                    textToDraw = courses[i].id;
                    break;
                case 1:
                    textToDraw = courses[i].courseName;
                    break;
                case 2:
                    textToDraw = courses[i].ClassName;
                    break;
                case 3:
                    textToDraw = courses[i].teacherName;
                    break;
                case 4:
                    textToDraw = to_string(courses[i].academicYear);
                    break;
                case 5:
                    textToDraw = to_string(courses[i].Credits);
                    break;
                case 6:
                    textToDraw = courses[i].wDay;
                    break;
                case 7:
                    textToDraw = courses[i].session;
                    break;
                default:
                    break;
                }
                textWidth = MeasureText(textToDraw.c_str(), fontSize);
                textX += (cellWidth - textWidth) / 2;
                DrawText(textToDraw.c_str(), textX, startY + (i + 1) * cellHeight - scrollBarYOffset + textPadding, fontSize, DARKGRAY);
            }
        }
        Rectangle scrollBar = { screenWidth - 20, startY + cellHeight, 20, screenHeight - 2 * cellHeight };
        float scrollBarHeight = screenHeight * screenHeight / ((float)numRows * cellHeight);
        float maxScrollBarY = screenHeight - 2 * cellHeight - scrollBarHeight;
        float scrollBarY = ((float)scrollBarYOffset / (numRows * cellHeight)) * maxScrollBarY;
        scrollBar.height = scrollBarHeight;
        scrollBar.y = startY + cellHeight + scrollBarY;
        DrawRectangleRec(scrollBar, GRAY);
        int scroll = GetMouseWheelMove();
        scrollBarYOffset += scroll * 50 * (-1);
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

    InitWindow(1366, 768, "Course Input");
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
                    // Kiểm tra tính hợp lệ của dữ liệu nhập vào cho "Nam hoc"


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
    return List;

}
void RemoveStudent(ListSV* studentList, int index) {
    if (index < 0) return;

    SinhVien* current = studentList->phead;
    SinhVien* previous = nullptr;
    int currentIndex = 0;

    while (current != nullptr && currentIndex < index) {
        previous = current;
        current = current->next;
        currentIndex++;
    }

    if (current == nullptr) return;

    if (previous == nullptr) {
        studentList->phead = current->next;
    }
    else {
        previous->next = current->next;
    }

    delete current;
}
void DisplayStudentDetails(SinhVien* student, ListSV* studentList, int studentIndex) {
    const int detailScreenWidth = 1366;
    const int detailScreenHeight = 768;
    InitWindow(detailScreenWidth, detailScreenHeight, "Student Details");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText(("MSSV: " + student->mssv).c_str(), 20, 20, 20, DARKGRAY);
        DrawText(("Ho: " + student->ho).c_str(), 20, 60, 20, DARKGRAY);
        DrawText(("Ten: " + student->ten).c_str(), 20, 100, 20, DARKGRAY);
        DrawText(("Lop: " + student->ClassName).c_str(), 20, 140, 20, DARKGRAY);
        DrawText(("Gioi Tinh: " + student->gender).c_str(), 20, 180, 20, DARKGRAY);
        string birthday = to_string(student->birth.day) + "/" + to_string(student->birth.month) + "/" + to_string(student->birth.year);
        DrawText(("Ngay Sinh: " + birthday).c_str(), 20, 220, 20, DARKGRAY);
        DrawText(("CCCD: " + student->cccd).c_str(), 20, 260, 20, DARKGRAY);

        Rectangle deleteButton = { detailScreenWidth / 2 - 50, detailScreenHeight - 100, 100, 50 };
        DrawRectangleRec(deleteButton, RED);
        DrawText("DELETE", detailScreenWidth / 2 - MeasureText("DELETE", 20) / 2, detailScreenHeight - 85, 20, WHITE);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePoint = GetMousePosition();
            if (CheckCollisionPointRec(mousePoint, deleteButton)) {
                // Delete the student and close the window
                RemoveStudent(studentList, studentIndex);
                CloseWindow();
                break;
            }
        }

        EndDrawing();
    }
}


void DrawStudentListFromData(ListSV* studentList, int numRows) {
    const int screenWidth = 1366;
    const int screenHeight = 768;
    InitWindow(screenWidth, screenHeight, "");
    const float screenRatioX = (float)GetScreenWidth() / screenWidth;
    const float screenRatioY = (float)GetScreenHeight() / screenHeight;

    const int numCols = 8; // Số cột bao gồm số thứ tự, MSSV, Họ, Tên, Lớp, Giới Tính, Ngày Sinh, CCCD
    const int columnSpacing = 20; // Khoảng cách giữa các cột

    const int cellWidth = (screenWidth - 2 * 50 - (numCols - 1) * columnSpacing) / numCols * screenRatioX;
    const int cellHeight = 80 * screenRatioY;
    const int textPadding = 10 * ((screenRatioX + screenRatioY) / 2);

    const int startX = (screenWidth - (numCols * cellWidth + (numCols - 1) * columnSpacing)) / 2;
    const int startY = 100 * screenRatioY;

    const char* headers[numCols] = { "STT", "MSSV", "Ho", "Ten", "Lop", "Gioi Tinh", "Ngay Sinh", "CCCD" };

    // Thêm thanh cuộn
    int scrollBarYOffset = 0;
    int maxDisplayedLines = screenHeight / cellHeight - 2; // Trừ 2 cho phần header và phần input
    int selectedStudentIndex = -1; // Biến lưu chỉ số sinh viên được chọn

    while (!WindowShouldClose()) {
        // Xử lý sự kiện bàn phím
        if (IsKeyPressed(KEY_DOWN)) {
            selectedStudentIndex++;
            if (selectedStudentIndex >= numRows) selectedStudentIndex = numRows - 1;
            if (selectedStudentIndex >= maxDisplayedLines + scrollBarYOffset / cellHeight) {
                scrollBarYOffset += cellHeight;
                if (scrollBarYOffset > (numRows - maxDisplayedLines) * cellHeight) {
                    scrollBarYOffset = (numRows - maxDisplayedLines) * cellHeight;
                }
            }
        }
        if (IsKeyPressed(KEY_UP)) {
            selectedStudentIndex--;
            if (selectedStudentIndex < 0) selectedStudentIndex = 0;
            if (selectedStudentIndex < scrollBarYOffset / cellHeight) {
                scrollBarYOffset -= cellHeight;
                if (scrollBarYOffset < 0) scrollBarYOffset = 0;
            }
        }
        if (IsKeyPressed(KEY_ENTER) && selectedStudentIndex >= 0 && selectedStudentIndex < numRows) {
            // Lấy thông tin sinh viên được chọn
            int currentIndex = 0;
            SinhVien* currentSV = studentList->phead;
            while (currentIndex < selectedStudentIndex && currentSV != nullptr) {
                currentSV = currentSV->next;
                currentIndex++;
            }
            if (currentSV != nullptr) {
                // Hiển thị cửa sổ chi tiết sinh viên
                DisplayStudentDetails(currentSV, studentList, selectedStudentIndex);
                numRows--; // Giảm số lượng sinh viên khi xóa
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // In tiêu đề
        for (int i = 0; i < numCols; i++) {
            DrawRectangle(startX + (cellWidth + columnSpacing) * i, startY, cellWidth, cellHeight, LIGHTGRAY);
            int textWidth = MeasureText(headers[i], 15 * ((screenRatioX + screenRatioY) / 2));
            int textX = startX + (cellWidth + columnSpacing) * i + (cellWidth - textWidth) / 2;
            DrawText(headers[i], textX, startY + textPadding, 15 * ((screenRatioX + screenRatioY) / 2), BLACK);
        }

        // In thông tin của từng tiêu đề
        SinhVien* currentSV = studentList->phead;

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
        int stt = visibleStartIndex + 1; // Số thứ tự bắt đầu từ vị trí hiển thị đầu tiên
        for (int i = visibleStartIndex; i < visibleEndIndex && currentSV != nullptr; i++) {
            // Vẽ dữ liệu cho hàng hiện tại
            Color rowColor = (i == selectedStudentIndex) ? SKYBLUE : RAYWHITE;
            DrawRectangle(startX, startY + (i - visibleStartIndex + 1) * cellHeight, cellWidth * numCols + columnSpacing * (numCols - 1), cellHeight, rowColor); // Vẽ hình chữ nhật cho toàn bộ hàng
            string sttStr = to_string(stt);
            DrawText(sttStr.c_str(), startX + textPadding, startY + (i - visibleStartIndex + 1) * cellHeight + textPadding, 15, DARKGRAY);
            DrawText(currentSV->mssv.c_str(), startX + (cellWidth + columnSpacing) * 1 + textPadding, startY + (i - visibleStartIndex + 1) * cellHeight + textPadding, 15, DARKGRAY);
            DrawText(currentSV->ho.c_str(), startX + (cellWidth + columnSpacing) * 2 + textPadding, startY + (i - visibleStartIndex + 1) * cellHeight + textPadding, 15, DARKGRAY);
            DrawText(currentSV->ten.c_str(), startX + (cellWidth + columnSpacing) * 3 + textPadding, startY + (i - visibleStartIndex + 1) * cellHeight + textPadding, 15, DARKGRAY);
            DrawText(currentSV->ClassName.c_str(), startX + (cellWidth + columnSpacing) * 4 + textPadding, startY + (i - visibleStartIndex + 1) * cellHeight + textPadding, 15, DARKGRAY);
            DrawText(currentSV->gender.c_str(), startX + (cellWidth + columnSpacing) * 5 + textPadding, startY + (i - visibleStartIndex + 1) * cellHeight + textPadding, 15, DARKGRAY);
            string birthday = to_string(currentSV->birth.day) + "/" + to_string(currentSV->birth.month) + "/" + to_string(currentSV->birth.year);
            DrawText(birthday.c_str(), startX + (cellWidth + columnSpacing) * 6 + textPadding, startY + (i - visibleStartIndex + 1) * cellHeight + textPadding, 15, DARKGRAY);
            DrawText(currentSV->cccd.c_str(), startX + (cellWidth + columnSpacing) * 7 + textPadding, startY + (i - visibleStartIndex + 1) * cellHeight + textPadding, 15, DARKGRAY);
            stt++;
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
    ofile << "id,pass,ho,ten,ClassName,gender,birth,academicYear,staff\n";
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

    const int maxPasswordLength = 24; //Độ dài tối đa của mật khẩu

    SetTargetFPS(60);

    while (!WindowShouldClose() && changePasswordActive) {
        Vector2 mousePoint = GetMousePosition();
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
        //Xử lý thông tin nhập vào từ bàn phím
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

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Change Password", dashboardWidth / 2 - MeasureText("Change Password", 30) / 2, 100, 30, DARKGRAY);
        DrawText("Current Password:", dashboardWidth / 2 - 150, 170, 20, DARKGRAY);
        DrawRectangleRec(currentPasswordBox, LIGHTGRAY);
        if (currentPasswordBoxActive)
            DrawRectangleLinesEx(currentPasswordBox, 1, RED);
        DrawText(currentPassword, currentPasswordBox.x + 5, currentPasswordBox.y + 10, 20, DARKGRAY);
        DrawText("New Password:", dashboardWidth / 2 - 150, 250, 20, DARKGRAY);
        DrawRectangleRec(newPasswordBox, LIGHTGRAY);
        if (newPasswordBoxActive)
            DrawRectangleLinesEx(newPasswordBox, 1, RED);
        DrawText(newPassword, newPasswordBox.x + 5, newPasswordBox.y + 10, 20, DARKGRAY);
        DrawText("Confirm New Password:", dashboardWidth / 2 - 150, 330, 20, DARKGRAY);
        DrawRectangleRec(confirmedNewPasswordBox, LIGHTGRAY);
        if (confirmedNewPasswordBoxActive)
            DrawRectangleLinesEx(confirmedNewPasswordBox, 1, RED);
        DrawText(confirmedNewPassword, confirmedNewPasswordBox.x + 5, confirmedNewPasswordBox.y + 10, 20, DARKGRAY);
        Rectangle changePasswordButton = { dashboardWidth / 2 - 50, 420, 100, 40 };
        DrawRectangleRec(changePasswordButton, LIGHTGRAY);
        DrawText("Change", changePasswordButton.x + 5, changePasswordButton.y + 10, 20, DARKGRAY);

        // Kiểm tra nút confirm được ấn chưa
        if (CheckCollisionPointRec(mousePoint, changePasswordButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            User* temp = userList->phead;
            while (temp != NULL)
            {
                if (username == temp->id && password == temp->pass)
                {
                    break;
                }
                temp = temp->next;
            }
            if (currentPassword == temp->pass) {
                if (strlen(newPassword) > 0 && strcmp(newPassword, confirmedNewPassword) == 0) {
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

        // In ra lỗi
        DrawText(errorMessage, dashboardWidth - MeasureText(errorMessage, 20) - 10, dashboardHeight - 30, 20, RED);
        EndDrawing();
    }
    CloseWindow();
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
void CreateNewSchoolYeabutton(bool& createNewSchoolYearActive, bool& schoolYearInputBoxActive, char* schoolYearInput, ListNamHoc& LNH, NamHoc*& N, Vector2 mousePoint, bool& showError) {
    const int screenWidth = 1366;
    const int screenHeight = 768;
    const int inputBoxWidth = 200;
    const int inputBoxHeight = 40;
    Rectangle schoolYearInputBox = { screenWidth / 2 - inputBoxWidth / 2, screenHeight - 100, inputBoxWidth, inputBoxHeight };
    DrawRectangleRec(schoolYearInputBox, LIGHTGRAY);
    DrawText(schoolYearInput, schoolYearInputBox.x + 5, schoolYearInputBox.y + 10, 20, DARKGRAY);
    DrawText("Enter School Year (e.g., 2020-2021):", schoolYearInputBox.x, schoolYearInputBox.y - 20, 20, LIGHTGRAY);
    if (showError) {
        DrawText("Invalid format. Use nnnn-nnnn.", schoolYearInputBox.x, schoolYearInputBox.y + 50, 20, RED);
    }
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
        if (IsValidSchoolYearFormat(schoolYearInput)) {
            taonamhoc(LNH, N, schoolYearInput);
            createNewSchoolYearActive = false;
            showError = false;
            memset(schoolYearInput, 0, sizeof(char) * 128); // Clear the input buffer
        }
        else {
            showError = true; // Show error message if format is invalid
        }
    }
}

void AddStudentsbutton(char* AddsvInput, Rectangle& AddsvInputBox, bool& AddsvInputBoxActive, ListCourses*& LC, float screenWidth, float screenHeight) {
    static bool showError = false;

    // Thiết lập vị trí cho ô nhập liệu
    const int inputBoxWidth = 200;
    const int inputBoxHeight = 40;
    AddsvInputBox = { screenWidth / 2 - inputBoxWidth / 2, screenHeight - 100, inputBoxWidth, inputBoxHeight };

    // Vẽ khung nhập liệu và chuỗi ký tự hiện tại
    DrawRectangleRec(AddsvInputBox, LIGHTGRAY);
    DrawText(AddsvInput, AddsvInputBox.x + 5, AddsvInputBox.y + 10, 20, DARKGRAY);
    DrawText("Input course name:", AddsvInputBox.x, AddsvInputBox.y - 20, 20, LIGHTGRAY);

    // Xử lý thông tin nhập từ bàn phím
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
        Course* temp = LC->head;
        while (temp != NULL) {
            if (temp->courseName == AddsvInput) {
                break;
            }
            temp = temp->next;
        }
        if (temp == NULL) {
            cout << "Error: Course not found." << endl;
        }
        else {
            AddstudentDashboard(screenWidth, screenHeight, LC, temp);
        }
        memset(AddsvInput, 0, 128);
        AddsvInputBoxActive = false;
    }

    // Vẽ thông báo lỗi nếu có
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
    //Tạo cửa sổ mới
    InitWindow(windowWidth, windowHeight, "Profile");

    while (!WindowShouldClose() && !backButtonPressed) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText(("ID: " + user->id).c_str(), 50, 50, 20, BLACK);
        DrawText(("Full Name: " + user->ho + " " + user->ten).c_str(), 50, 80, 20, BLACK);
        DrawText(("Date of Birth: " +
            to_string(user->birth.day) + "/" +
            to_string(user->birth.month) + "/" +
            to_string(user->birth.year)).c_str(), 50, 110, 20, BLACK);
        DrawText(("Gender: " + user->gender).c_str(), 50, 140, 20, BLACK);
        DrawText(("Academic Year: " + user->academicYear).c_str(), 50, 170, 20, BLACK);
        DrawRectangle(backButtonX, backButtonY, buttonWidth, buttonHeight, LIGHTGRAY);
        DrawText("Back", backButtonX + 20, backButtonY + 10, 20, BLACK);
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
void ImportCourseFile(ListCourses*& List, string path)
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
void CourseDashboard(int screenWidth, int screenHeight, ListCourses*& LC) {
    InitWindow(screenWidth, screenHeight, "Course Dashboard");
    Rectangle inputCourseButton = { screenWidth / 2 - 100, screenHeight / 2 - 60, 220, 40 };
    Rectangle importCourseButton = { screenWidth / 2 - 100, screenHeight / 2 + 20, 220, 40 };
    Rectangle backButton = { screenWidth / 2 - 100, screenHeight / 2 + 100, 220, 40 };
    bool inputCourseActive = false;
    bool importCourseActive = false;

    while (!WindowShouldClose()) {
        Vector2 mousePoint = GetMousePosition();
        bool inputCourseMouseOver = CheckCollisionPointRec(mousePoint, inputCourseButton);
        bool importCourseMouseOver = CheckCollisionPointRec(mousePoint, importCourseButton);
        bool backMouseOver = CheckCollisionPointRec(mousePoint, backButton);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangleRec(inputCourseButton, inputCourseMouseOver ? LIGHTGRAY : GRAY);
        DrawText("Create New Course", inputCourseButton.x + 10, inputCourseButton.y + 10, 20, DARKGRAY);
        DrawRectangleRec(importCourseButton, importCourseMouseOver ? LIGHTGRAY : GRAY);
        DrawText("Import Course", importCourseButton.x + 30, importCourseButton.y + 10, 20, DARKGRAY);
        DrawRectangleRec(backButton, backMouseOver ? LIGHTGRAY : GRAY);
        DrawText("Back", backButton.x + 80, backButton.y + 10, 20, DARKGRAY);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (inputCourseMouseOver) {
                inputCourseActive = true;
                importCourseActive = false;
            }
            else if (importCourseMouseOver) {
                importCourseActive = true;
                inputCourseActive = false;
            }
            else if (backMouseOver) {
                CloseWindow();
                return;
            }
        }
        if (inputCourseActive) {
            string id, CourseName, ClassName, GVName, wDay, Session;
            int AcademicYear, Credits;
            ShowInputCoursePage(id, CourseName, ClassName, GVName, AcademicYear, Credits, wDay, Session);
            bool validInput = !id.empty() && !CourseName.empty() && !ClassName.empty() && !GVName.empty() &&
                !wDay.empty() && !Session.empty() && AcademicYear != -1 && Credits != -1;

            if (validInput) {
                Course* newCourse = InputCourse(id, CourseName, ClassName, GVName, AcademicYear, Credits, wDay, Session);
                AddCourse(LC, newCourse);
            }
            inputCourseActive = false;
            break;
        }
        else if (importCourseActive) {
            string path;
            ShowImportCoursePage(path);
            ImportCourseFile(LC, path);
            importCourseActive = false;
            break;
        }

        EndDrawing();
    }
    CloseWindow();
}

void add1StudentCourse(Course*& cour, SinhVien*& sv) {
    if (cour->lsv == NULL) {
        cour->lsv = new ListSV;  // Khởi tạo lsv nếu chưa được khởi tạo
        cour->lsv->phead = sv;
        cour->lsv->ptail = sv;
        sv->next = NULL;  // Đảm bảo sv là sinh viên cuối cùng
    }
    else {
        if (cour->lsv->phead == NULL) {  // Nếu danh sách rỗng
            cour->lsv->phead = sv;
            cour->lsv->ptail = sv;
        }
        else {
            cour->lsv->ptail->next = sv;
            cour->lsv->ptail = sv;
        }
        sv->next = NULL;  // Đảm bảo sv là sinh viên cuối cùng
    }
}

void AddstudentDashboard(int screenWidth, int screenHeight, ListCourses*& LC, Course* cour) {
    InitWindow(screenWidth, screenHeight, "Add student Dashboard");

    char AddsvInput[128] = "\0";
    Rectangle AddsvInputBox = { screenWidth / 2 - 150, screenHeight / 2 + 120, 300, 40 }; // Điều chỉnh vị trí và kích thước ô nhập liệu
    bool AddsvInputBoxActive = false;
    bool showError = false;
    Rectangle inputstudentButton = { screenWidth / 2 - 110, screenHeight / 2 - 60, 220, 40 };
    Rectangle importstudentButton = { screenWidth / 2 - 110, screenHeight / 2, 220, 40 }; // Điều chỉnh vị trí nút import student
    Rectangle viewstudentButton = { screenWidth / 2 - 110, screenHeight / 2 + 80, 220, 40 }; // Điều chỉnh vị trí nút view student
    Rectangle backButton = { screenWidth / 2 - 110, screenHeight / 2 + 160, 220, 40 }; // Điều chỉnh vị trí nút back
    bool inputstudentActive = false;
    bool importstudentActive = false;
    bool viewstudentActive = false;
    bool studentSaved = false;
    while (!WindowShouldClose()) {
        Vector2 mousePoint = GetMousePosition();
        bool inputstudentMouseOver = CheckCollisionPointRec(mousePoint, inputstudentButton);
        bool importstudentMouseOver = CheckCollisionPointRec(mousePoint, importstudentButton);
        bool viewstudentMouseOver = CheckCollisionPointRec(mousePoint, viewstudentButton);
        bool backMouseOver = CheckCollisionPointRec(mousePoint, backButton);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangleRec(inputstudentButton, inputstudentMouseOver ? LIGHTGRAY : GRAY);
        DrawText("Add New Student", inputstudentButton.x + 10, inputstudentButton.y + 10, 20, DARKGRAY);
        DrawRectangleRec(importstudentButton, importstudentMouseOver ? LIGHTGRAY : GRAY);
        DrawText("Import list Student", importstudentButton.x + 20, importstudentButton.y + 10, 20, DARKGRAY);
        DrawRectangleRec(viewstudentButton, viewstudentMouseOver ? LIGHTGRAY : GRAY);
        DrawText("View Student", viewstudentButton.x + 30, viewstudentButton.y + 10, 20, DARKGRAY);
        DrawRectangleRec(backButton, backMouseOver ? LIGHTGRAY : GRAY);
        DrawText("Back", backButton.x + 80, backButton.y + 10, 20, DARKGRAY);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (inputstudentMouseOver) {
                inputstudentActive = true;
                importstudentActive = false;
                viewstudentActive = false;
            }
            else if (importstudentMouseOver) {
                importstudentActive = true;
                inputstudentActive = false;
                viewstudentActive = false;
                AddsvInputBoxActive = true;
            }
            else if (viewstudentMouseOver) {
                viewstudentActive = true;
                inputstudentActive = false;
                importstudentActive = false;
            }
            else if (backMouseOver) {
                CloseWindow();
                return;
            }
        }

        if (inputstudentActive) {
            createnewstudent(cour, studentSaved);
            if (studentSaved) {
                int numRows = 0;
                SinhVien* currentSV = cour->lsv->phead;
                while (currentSV != NULL) {
                    numRows++;
                    currentSV = currentSV->next;
                }
                DrawStudentListFromData(cour->lsv, numRows);
            }
            inputstudentActive = false;
        }
        else if (importstudentActive) {
            // Vị trí dưới cùng của cửa sổ
            int bottomMargin = screenHeight - 50;

            // Vị trí ô nhập liệu
            Rectangle AddsvInputBox = { screenWidth / 2 - 150, bottomMargin - 60, 300, 40 };
            DrawRectangleRec(AddsvInputBox, LIGHTGRAY);
            // Vị trí văn bản hướng dẫn
            DrawText("Input file want to read", AddsvInputBox.x, AddsvInputBox.y - 30, 20, DARKGRAY);

            // Vị trí cho ô nhập liệu
            DrawText(AddsvInput, AddsvInputBox.x + 10, AddsvInputBox.y + 10, 20, DARKGRAY);

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePoint, AddsvInputBox)) {
                AddsvInputBoxActive = true;
            }
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
            if (IsKeyPressed(KEY_ENTER)) {
                ListSV* svList = addListSV(AddsvInput);
                if (svList == NULL) {
                    showError = true;
                }
                else {
                    showError = false;
                    if (cour->lsv == NULL) {
                        cour->lsv = svList;
                    }
                    else {
                        SinhVien* temp = cour->lsv->ptail;
                        if (temp == NULL) {
                            cour->lsv->phead = svList->phead;
                        }
                        else {
                            temp->next = svList->phead;
                        }
                    }
                    SinhVien* lastSV = svList->ptail;
                    if (lastSV != NULL) {
                        cour->lsv->ptail = lastSV;
                    }

                    int numRows = 0;
                    SinhVien* currentSV = cour->lsv->phead;
                    while (currentSV != nullptr) {
                        numRows++;
                        currentSV = currentSV->next;
                    }
                    DrawStudentListFromData(cour->lsv, numRows);
                    memset(AddsvInput, 0, 128);
                }
                importstudentActive = false;
                AddsvInputBoxActive = false;
            }
            if (showError) {
                const char* errorMsg = "Unable to open file";
                int fontSize = 20;
                int textWidth = MeasureText(errorMsg, fontSize);
                int posX = GetScreenWidth() - textWidth - 10;
                int posY = GetScreenHeight() - fontSize - 10;

                DrawText(errorMsg, posX, posY, fontSize, RED);
            }
        }
        else if (viewstudentActive) {
            int numRows = 0;
            SinhVien* currentSV = cour->lsv->phead;
            while (currentSV != nullptr) {
                numRows++;
                currentSV = currentSV->next;
            }
            DrawStudentListFromData(cour->lsv, numRows);
            viewstudentActive = false;
        }

        EndDrawing();
    }

    CloseWindow();
}

void createnewstudent(Course* cour, bool& studentSaved) {
    const int screenWidth = 1366;
    const int screenHeight = 768;
    InitWindow(screenWidth, screenHeight, "");

    SetTargetFPS(60);

    struct TextInputField {
        Rectangle rect;
        char text[128];
        bool active;
        const char* label;
        bool numeric;
        int maxLength;
    };
    const int numInputFields = 9;
    TextInputField inputFields[numInputFields] = {
        {{ (float)(screenWidth / 2 - 100), 110, 200, 30 }, "", false, "MSSV", true, 127},      // MSSV
        {{ (float)(screenWidth / 2 - 100), 150, 200, 30 }, "", false, "Ho", false, 127},       // Ho
        {{ (float)(screenWidth / 2 - 100), 190, 200, 30 }, "", false, "Ten", false, 127},      // Ten
        {{ (float)(screenWidth / 2 - 100), 230, 200, 30 }, "", false, "Lop", false, 127},      // Lop
        {{ (float)(screenWidth / 2 - 100), 270, 200, 30 }, "", false, "Gender", false, 127},   // Gender
        {{ (float)(screenWidth / 2 - 100), 310, 200, 30 }, "", false, "Ngay Sinh", true, 2},   // Ngay Sinh
        {{ (float)(screenWidth / 2 - 100), 350, 200, 30 }, "", false, "Thang Sinh", true, 2},  // Thang Sinh
        {{ (float)(screenWidth / 2 - 100), 390, 200, 30 }, "", false, "Nam Sinh", true, 4},    // Nam Sinh
        {{ (float)(screenWidth / 2 - 100), 430, 200, 30 }, "", false, "CCCD", true, 127}       // CCCD
    };

    Rectangle confirmButton = { (float)(screenWidth / 2 - 50), 480, 100, 40 };
    bool isConfirmButtonPressed = false;

    bool isInputValid = true;
    string errorMessage = "";

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < numInputFields; ++i) {
            DrawText(inputFields[i].label, (int)(inputFields[i].rect.x - MeasureText(inputFields[i].label, 20) - 10), (int)(inputFields[i].rect.y + 10), 20, BLACK);
            DrawRectangleRec(inputFields[i].rect, inputFields[i].active ? LIGHTGRAY : GRAY);
            DrawText(inputFields[i].text, (int)(inputFields[i].rect.x + 10), (int)(inputFields[i].rect.y + 10), 20, BLACK);
        }
        DrawRectangleRec(confirmButton, GRAY);
        DrawText("Xac Nhan", (int)(confirmButton.x + 10), (int)(confirmButton.y + 10), 20, BLACK);

        bool displayErrorMessage = false; // Biến kiểm tra xem có hiển thị thông báo lỗi không

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePosition = GetMousePosition();

            for (int i = 0; i < numInputFields; ++i) {
                if (CheckCollisionPointRec(mousePosition, inputFields[i].rect)) {
                    for (int j = 0; j < numInputFields; ++j) {
                        inputFields[j].active = (i == j);
                    }
                    break;
                }
            }

            if (CheckCollisionPointRec(mousePosition, confirmButton)) {
                isConfirmButtonPressed = true;
            }
        }

        for (int i = 0; i < numInputFields; ++i) {
            if (inputFields[i].active) {
                int key = GetKeyPressed();
                int length = strlen(inputFields[i].text);

                if (key == KEY_BACKSPACE) {
                    if (length > 0) {
                        inputFields[i].text[length - 1] = '\0';
                    }
                }
                else if (key == KEY_SPACE) {
                    if (length < inputFields[i].maxLength) {
                        inputFields[i].text[length] = ' ';
                        inputFields[i].text[length + 1] = '\0';
                    }
                }
                else if ((key >= 32 && key <= 125) && (!inputFields[i].numeric || (key >= '0' && key <= '9'))) {
                    if (length < inputFields[i].maxLength) {
                        bool shiftPressed = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
                        char newChar = (char)key;
                        if (shiftPressed && key >= 'a' && key <= 'z') {
                            newChar = key - ('a' - 'A');
                        }
                        else if (!shiftPressed && key >= 'A' && key <= 'Z') {
                            newChar = key + ('a' - 'A');
                        }
                        inputFields[i].text[length] = newChar;
                        inputFields[i].text[length + 1] = '\0';
                    }
                }
            }
        }

        if (isConfirmButtonPressed) {
            isInputValid = true;
            errorMessage.clear();

            for (int i = 0; i < numInputFields; ++i) {
                if (strlen(inputFields[i].text) == 0) {
                    isInputValid = false;
                    errorMessage = "All fields must be filled!";
                    break;
                }
            }
            if (isInputValid) {
                string gender = inputFields[4].text;
                if (gender != "Male" && gender != "Female") {
                    isInputValid = false;
                    errorMessage = "Gender must be Male or Female";
                }
            }
            if (!isInputValid) {
                displayErrorMessage = true;
                isConfirmButtonPressed = false;
            }
            if (isConfirmButtonPressed && isInputValid) {
                SinhVien* newStudent = new SinhVien;
                newStudent->mssv = inputFields[0].text;
                newStudent->ho = inputFields[1].text;
                newStudent->ten = inputFields[2].text;
                newStudent->ClassName = inputFields[3].text;
                newStudent->gender = inputFields[4].text;
                newStudent->birth.day = stoi(inputFields[5].text);
                newStudent->birth.month = stoi(inputFields[6].text);
                newStudent->birth.year = stoi(inputFields[7].text);
                newStudent->cccd = inputFields[8].text;
                add1StudentCourse(cour, newStudent);
                // In thông báo thành công sau khi lưu thông tin
                DrawText("Saved successfully!", screenWidth / 2 - MeasureText("Saved successfully!", 20) / 2, screenHeight - 50, 20, GREEN);
                EndDrawing();
                while (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {}
                EndDrawing();
                studentSaved = true;
                break;
            }
        }

        if (displayErrorMessage) {
            DrawText(errorMessage.c_str(), screenWidth / 2 - MeasureText(errorMessage.c_str(), 20) / 2, screenHeight - 50, 20, RED);
        }

        EndDrawing();
    }

    CloseWindow();
}
void ViewAvailableSignCourses(ListCourses* List, Course* courses, int numRows, ListCourses*& SV) {
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
    int maxDisplayedLines = (screenHeight - startY - cellHeight) / cellHeight;

    int selectedCourse = 0;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_DOWN) && selectedCourse < numRows - 1) {
            selectedCourse++;
        }
        if (IsKeyPressed(KEY_UP) && selectedCourse > 0) {
            selectedCourse--;
        }
        if (IsKeyPressed(KEY_ENTER)) {
            ShowSignCoursesDetails(List, courses[selectedCourse], SV);
        }
        if (selectedCourse * cellHeight < scrollBarYOffset) {
            scrollBarYOffset = selectedCourse * cellHeight;
        }
        if (selectedCourse * cellHeight >= scrollBarYOffset + maxDisplayedLines * cellHeight) {
            scrollBarYOffset = (selectedCourse + 1) * cellHeight - maxDisplayedLines * cellHeight;
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int i = 0; i < numCols; i++) {
            DrawRectangle(startX + i * cellWidth, startY, cellWidth, cellHeight, LIGHTGRAY);
            int textWidth = MeasureText(headers[i], 15 * ((screenRatioX + screenRatioY) / 2));
            int textX = startX + i * cellWidth + (cellWidth - textWidth) / 2;
            DrawText(headers[i], textX, startY + textPadding, 15 * ((screenRatioX + screenRatioY) / 2), BLACK);
        }
        for (int i = 0; i < numRows; i++) {
            if (startY + (i + 1) * cellHeight - scrollBarYOffset < startY + cellHeight) {
                continue;
            }
            if (startY + (i + 1) * cellHeight - scrollBarYOffset > screenHeight - cellHeight) {
                break;
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
        Rectangle scrollBar = { screenWidth - 20, startY + cellHeight, 20, screenHeight - 2 * cellHeight };
        float scrollBarHeight = screenHeight * screenHeight / ((float)numRows * cellHeight);
        float maxScrollBarY = screenHeight - 2 * cellHeight - scrollBarHeight;
        float scrollBarY = ((float)scrollBarYOffset / (numRows * cellHeight)) * maxScrollBarY;
        scrollBar.height = scrollBarHeight;
        scrollBar.y = startY + cellHeight + scrollBarY;
        DrawRectangleRec(scrollBar, GRAY);
        int scroll = GetMouseWheelMove();
        scrollBarYOffset += scroll * 50 * (-1);
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
bool checkappearedcourse(Course& course, ListCourses*& SV)
{
    Course* temp = SV->head;
    while (temp != NULL)
    {
        if (temp->id == course.id)
        {
            return true;
            break;
        }
        temp = temp->next;
    }
    return false;
}
void ShowSignCoursesDetails(ListCourses*& List, Course& course, ListCourses*& SV) {
    const int detailScreenWidth = 1366;
    const int detailScreenHeight = 768;
    InitWindow(detailScreenWidth, detailScreenHeight, "Course Details");
    bool showerror = true;
    bool shouldRegister = false;
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
        DrawText(("Academic Year: " + to_string(course.academicYear)).c_str(), 50, textY, 20, BLACK);
        textY += 30 + textPadding;
        DrawText(("Credits: " + to_string(course.Credits)).c_str(), 50, textY, 20, BLACK);
        textY += 30 + textPadding;
        DrawText(("Week Day: " + course.wDay).c_str(), 50, textY, 20, BLACK);
        textY += 30 + textPadding;
        DrawText(("Session: " + course.session).c_str(), 50, textY, 20, BLACK);

        Rectangle RegisterButton = { detailScreenWidth / 2 - 60, detailScreenHeight - 100, 120, 50 };
        DrawRectangleRec(RegisterButton, GREEN);
        DrawText("Register", detailScreenWidth / 2 - 40, detailScreenHeight - 85, 20, WHITE);

        if (CheckCollisionPointRec(GetMousePosition(), RegisterButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            shouldRegister = true;
        }

        Rectangle CloseButton = { detailScreenWidth - 70, detailScreenHeight - 50, 60, 30 };
        DrawRectangleRec(CloseButton, RED);
        DrawText("Close", detailScreenWidth - 60, detailScreenHeight - 40, 20, WHITE);

        if (CheckCollisionPointRec(GetMousePosition(), CloseButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            shouldClose = true;
        }

        EndDrawing();

        if (shouldRegister)
        {
            if (!checkappearedcourse(course, SV))
            {
                Course* newCourse = InputCourse(course.id, course.courseName, course.ClassName, course.teacherName, course.academicYear, course.Credits, course.wDay, course.session);
                AddCourse(SV, newCourse);
                showerror = false;
                shouldClose = true;
            }
            else
            {
                showerror = true;
            }
            if (showerror)
            {
                DrawText("Error:Course already signed", 10, 10, 20, RED);
            }
        }

        CloseWindow();
    }
}
void DisplayCourseDetails(Course* course, ListCourses*& List_Courses_SV)
{
    const int screenWidth = 1366;
    const int screenHeight = 768;
    InitWindow(screenWidth, screenHeight, "Course Details");

    bool shouldClose = false;
    bool shouldDelete = false;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText(TextFormat("ID: %s", course->id.c_str()), 50, 50, 20, BLACK);
        DrawText(TextFormat("Course Name: %s", course->courseName.c_str()), 50, 100, 20, BLACK);
        DrawText(TextFormat("Class Name: %s", course->ClassName.c_str()), 50, 150, 20, BLACK);
        DrawText(TextFormat("Teacher Name: %s", course->teacherName.c_str()), 50, 200, 20, BLACK);
        DrawText(TextFormat("Academic Year: %d", course->academicYear), 50, 250, 20, BLACK);
        DrawText(TextFormat("Credits: %d", course->Credits), 50, 300, 20, BLACK);
        DrawText(TextFormat("Week Day: %s", course->wDay.c_str()), 50, 350, 20, BLACK);
        DrawText(TextFormat("Session: %s", course->session.c_str()), 50, 400, 20, BLACK);
        Rectangle registerButton = { screenWidth / 2 - 60, screenHeight - 100, 120, 50 };
        DrawRectangleRec(registerButton, GREEN);
        DrawText("Delete", screenWidth / 2 - 40, screenHeight - 85, 20, WHITE);
        if (CheckCollisionPointRec(GetMousePosition(), registerButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            shouldDelete = true;
            shouldClose = true; // Close the window after registering
        }
        Rectangle closeButton = { screenWidth - 70, screenHeight - 50, 60, 30 };
        DrawRectangleRec(closeButton, RED);
        DrawText("Close", screenWidth - 60, screenHeight - 40, 20, WHITE);
        if (CheckCollisionPointRec(GetMousePosition(), closeButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            shouldClose = true;
        }
        EndDrawing();
        if (shouldDelete)
        {
            RemoveCourse(List_Courses_SV, Find_ID(List_Courses_SV, course->id));
        }
        if (shouldClose) {
            break;
        }
    }

    CloseWindow();
}
void ViewSignCourses(ListCourses* List, Course* courses, int numRows, ListCourses*& SV) {
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
    int maxDisplayedLines = (screenHeight - startY - cellHeight) / cellHeight;
    int selectedCourse = 0;
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_DOWN) && selectedCourse < numRows - 1) {
            selectedCourse++;
        }
        if (IsKeyPressed(KEY_UP) && selectedCourse > 0) {
            selectedCourse--;
        }
        if (IsKeyPressed(KEY_ENTER)) {
            showCourseDetails(List, courses[selectedCourse]);
        }
        if (selectedCourse * cellHeight < scrollBarYOffset) {
            scrollBarYOffset = selectedCourse * cellHeight;
        }
        if (selectedCourse * cellHeight >= scrollBarYOffset + maxDisplayedLines * cellHeight) {
            scrollBarYOffset = (selectedCourse + 1) * cellHeight - maxDisplayedLines * cellHeight;
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int i = 0; i < numCols; i++) {
            DrawRectangle(startX + i * cellWidth, startY, cellWidth, cellHeight, LIGHTGRAY);
            int textWidth = MeasureText(headers[i], 15 * ((screenRatioX + screenRatioY) / 2));
            int textX = startX + i * cellWidth + (cellWidth - textWidth) / 2;
            DrawText(headers[i], textX, startY + textPadding, 15 * ((screenRatioX + screenRatioY) / 2), BLACK);
        }
        for (int i = 0; i < numRows; i++) {
            if (startY + (i + 1) * cellHeight - scrollBarYOffset < startY + cellHeight) {
                continue;
            }
            if (startY + (i + 1) * cellHeight - scrollBarYOffset > screenHeight - cellHeight) {
                break;
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
        Rectangle scrollBar = { screenWidth - 20, startY + cellHeight, 20, screenHeight - 2 * cellHeight };
        float scrollBarHeight = screenHeight * screenHeight / ((float)numRows * cellHeight);
        float maxScrollBarY = screenHeight - 2 * cellHeight - scrollBarHeight;
        float scrollBarY = ((float)scrollBarYOffset / (numRows * cellHeight)) * maxScrollBarY;
        scrollBar.height = scrollBarHeight;
        scrollBar.y = startY + cellHeight + scrollBarY;
        DrawRectangleRec(scrollBar, GRAY);
        int scroll = GetMouseWheelMove();
        scrollBarYOffset += scroll * 50 * (-1);
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

void ViewCourses_SV(Course* courses, int numRows, ListCourses*& SV) {
    const int screenWidth = 1366;
    const int screenHeight = 768;
    InitWindow(screenWidth, screenHeight, "Danh sach khoa hoc");
    const float screenRatioX = (float)GetScreenWidth() / screenWidth;
    const float screenRatioY = (float)GetScreenHeight() / screenHeight;

    const int numCols = 8;
    const int cellWidth = (screenWidth - 2 * 50) / numCols * screenRatioX;
    const int cellHeight = 80 * screenRatioY;
    const int textPadding = 10 * ((screenRatioX + screenRatioY) / 2);

    const int startX = (screenWidth - (numCols * cellWidth)) / 2;
    const int startY = 100 * screenRatioY;

    const char* headers[numCols] = { "ID", "Course name", "Class", "Teacher", "School Year", "Credits", "Week Day", "Session" };

    int scrollBarYOffset = 0;
    int maxDisplayedLines = (screenHeight - startY - cellHeight) / cellHeight;

    int selectedCourseIndex = 0;
    Course* selectedCourse = nullptr;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_DOWN) && selectedCourseIndex < numRows - 1) {
            selectedCourseIndex++;
        }
        if (IsKeyPressed(KEY_UP) && selectedCourseIndex > 0) {
            selectedCourseIndex--;
        }
        if (selectedCourseIndex * cellHeight < scrollBarYOffset) {
            scrollBarYOffset = selectedCourseIndex * cellHeight;
        }
        if (selectedCourseIndex * cellHeight >= scrollBarYOffset + maxDisplayedLines * cellHeight) {
            scrollBarYOffset = (selectedCourseIndex + 1) * cellHeight - maxDisplayedLines * cellHeight;
        }

        if (IsKeyPressed(KEY_ENTER)) {
            selectedCourse = &courses[selectedCourseIndex];
            if (selectedCourse != nullptr) {
                DisplayCourseDetails(selectedCourse, SV);
                return;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (int i = 0; i < numCols; i++) {
            DrawRectangle(startX + i * cellWidth, startY, cellWidth, cellHeight, LIGHTGRAY);
            int textWidth = MeasureText(headers[i], 15 * ((screenRatioX + screenRatioY) / 2));
            int textX = startX + i * cellWidth + (cellWidth - textWidth) / 2;
            DrawText(headers[i], textX, startY + textPadding, 15 * ((screenRatioX + screenRatioY) / 2), BLACK);
        }
        for (int i = 0; i < numRows; i++) {
            if (startY + (i + 1) * cellHeight - scrollBarYOffset < startY + cellHeight) {
                continue;
            }
            if (startY + (i + 1) * cellHeight - scrollBarYOffset > screenHeight - cellHeight) {
                break;
            }
            Color rowColor = (i == selectedCourseIndex) ? SKYBLUE : RAYWHITE;
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
        Rectangle scrollBar = { screenWidth - 20, startY + cellHeight, 20, screenHeight - 2 * cellHeight };
        float scrollBarHeight = screenHeight * screenHeight / ((float)numRows * cellHeight);
        float maxScrollBarY = screenHeight - 2 * cellHeight - scrollBarHeight;
        float scrollBarY = ((float)scrollBarYOffset / (numRows * cellHeight)) * maxScrollBarY;
        scrollBar.height = scrollBarHeight;
        scrollBar.y = startY + cellHeight + scrollBarY;
        DrawRectangleRec(scrollBar, GRAY);
        int scroll = GetMouseWheelMove();
        scrollBarYOffset -= scroll * cellHeight;
        if (scrollBarYOffset < 0) scrollBarYOffset = 0;
        if (scrollBarYOffset > (numRows - maxDisplayedLines) * cellHeight) scrollBarYOffset = (numRows - maxDisplayedLines) * cellHeight;

        EndDrawing();
    }

    CloseWindow();
}
void DrawClassNameInputBox(Rectangle& classNameInputBox, char* classNameInput, Vector2 mousePoint, bool& mouseOnText, bool& classNameBoxActive, float screenWidth, float screenHeight, ListClass*& DS, bool& createClassActive) {
    const int inputBoxWidth = 300;
    const int inputBoxHeight = 40;

    // Thiết lập vị trí cho ô nhập liệu
    classNameInputBox = { screenWidth / 2 - inputBoxWidth / 2, screenHeight - 100, inputBoxWidth, inputBoxHeight };

    // Vẽ chữ "Class Name:" ngay phía trên ô nhập liệu
    DrawText("Class Name:", classNameInputBox.x + 10, classNameInputBox.y - 30, 20, DARKGRAY);

    // Vẽ ô nhập liệu
    DrawRectangleRec(classNameInputBox, LIGHTGRAY);

    // Xử lý nhập liệu từ người dùng
    if (CheckCollisionPointRec(mousePoint, classNameInputBox)) {
        mouseOnText = true;
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            classNameBoxActive = true;
        }
    }
    else {
        mouseOnText = false;
    }

    if (classNameBoxActive) {
        DrawRectangleLines(classNameInputBox.x, classNameInputBox.y, classNameInputBox.width, classNameInputBox.height, BLUE);
        int key = GetKeyPressed();
        int length = strlen(classNameInput);
        if (key >= 32 && key <= 125 && length < 127) { // Đảm bảo rằng độ dài chuỗi không vượt quá giới hạn
            classNameInput[length] = (char)key;
            classNameInput[length + 1] = '\0';
        }
        else if (key == KEY_BACKSPACE && length > 0) {
            classNameInput[length - 1] = '\0';
        }
        DrawText(classNameInput, classNameInputBox.x + 10, classNameInputBox.y + 10, 20, DARKGRAY);

        // Kiểm tra việc nhấn phím Enter để tạo lớp mới
        if (IsKeyPressed(KEY_ENTER)) {
            AddNewClassToList(classNameInput, DS);
            classNameBoxActive = false;
            memset(classNameInput, 0, 128); // Xóa bộ đệm nhập liệu
            createClassActive = false;
            saveClassesToCSV(DS, "classes.csv");
        }
    }
    else {
        DrawRectangleLines(classNameInputBox.x, classNameInputBox.y, classNameInputBox.width, classNameInputBox.height, DARKGRAY);
        DrawText(classNameInput, classNameInputBox.x + 10, classNameInputBox.y + 10, 20, DARKGRAY);
    }
}
void saveClassesToCSV(ListClass* classList, const char* filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Không thể mở file: " << filename << endl;
        return;
    }

    // Ghi tiêu đề cho file CSV
    file << "ClassName" << endl;

    // Ghi thông tin các lớp học
    Class* current = classList->head;
    while (current != nullptr) {
        file << current->ClassName << "\n";
        current = current->next;
    }

    file.close();
    cout << "Save file succeed" << endl;
}
void clearClassList(ListClass* classList) {
    Class* current = classList->head;
    while (current != NULL) {
        Class* temp = current;
        current = current->next;
        delete temp;
    }
    classList->head = NULL;
}

void loadClassesFromCSV(ListClass* classList, const char* filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Không thể mở file: " << filename << endl;
        return;
    }

    // Xóa danh sách lớp học hiện tại
    clearClassList(classList);

    string line;
    // Bỏ qua dòng tiêu đề
    getline(file, line);

    while (getline(file, line)) {
        Class* newClass = new Class;
        newClass->ClassName = line;
        newClass->next = nullptr;

        if (classList->head == nullptr) {
            classList->head = newClass;
        }
        else {
            Class* current = classList->head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newClass;
        }
    }

    file.close();
    cout << "Đọc danh sách lớp học từ file " << filename << " thành công!" << endl;
}
void AddNewClassToList(const char* className, ListClass*& DS)
{
    Class* CTT = new Class();
    CTT->ClassName = className;
    CTT->next = NULL;

    if (DS->head == NULL) {
        DS->head = CTT;
    }
    else {
        Class* temp = DS->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = CTT;
    }

    cout << "Da them 1 lop moi vao danh sach cac lop" << endl;
}
void viewClasses(ListClass* classList, ListCourses*& List) {
    const int screenWidth = 1366;
    const int screenHeight = 768;
    InitWindow(screenWidth, screenHeight, "View Classes");

    const float screenRatioX = (float)GetScreenWidth() / screenWidth;
    const float screenRatioY = (float)GetScreenHeight() / screenHeight;
    const int numCols = 1; // Số cột cho thông tin lớp học
    const int cellWidth = (screenWidth - 2 * 50) / numCols * screenRatioX;
    const int cellHeight = 80 * screenRatioY;
    const int textPadding = 10 * ((screenRatioX + screenRatioY) / 2);
    const int startX = (screenWidth - (numCols * cellWidth)) / 2;
    const int startY = 100 * screenRatioY;
    const char* headers[numCols] = { "Classes" };
    int scrollBarYOffset = 0;
    int maxDisplayedLines = (screenHeight - startY - cellHeight) / cellHeight;
    int selectedClass = 0;

    int numRows = 0;
    Class* tempClass = classList->head;
    while (tempClass != nullptr) {
        numRows++;
        tempClass = tempClass->next;
    }
    bool deletepress = false;
    Class* classes = new Class[numRows];
    tempClass = classList->head;
    for (int i = 0; i < numRows; i++) {
        classes[i] = *tempClass;
        tempClass = tempClass->next;
    }
    for (int i = 0; i < numRows; i++) 
    {
        classes[i].ds = new ListSV;
        classes[i].ds->phead = NULL;
        classes[i].ds->ptail = NULL;
    }
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_DOWN) && selectedClass < numRows - 1) {
            selectedClass++;
        }
        if (IsKeyPressed(KEY_UP) && selectedClass > 0) {
            selectedClass--;
        }
        if (IsKeyPressed(KEY_ENTER)) {

            showClassFunctions(List,classList, classes[selectedClass],deletepress);
            if (deletepress)
            {
                break;
            }
        }
        if (selectedClass * cellHeight < scrollBarYOffset) {
            scrollBarYOffset = selectedClass * cellHeight;
        }
        if (selectedClass * cellHeight >= scrollBarYOffset + maxDisplayedLines * cellHeight) {
            scrollBarYOffset = (selectedClass + 1) * cellHeight - maxDisplayedLines * cellHeight;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // In tiêu đề
        for (int i = 0; i < numCols; i++) {
            DrawRectangle(startX + i * cellWidth, startY, cellWidth, cellHeight, LIGHTGRAY);
            int textWidth = MeasureText(headers[i], 15 * ((screenRatioX + screenRatioY) / 2));
            int textX = startX + i * cellWidth + (cellWidth - textWidth) / 2;
            DrawText(headers[i], textX, startY + textPadding, 15 * ((screenRatioX + screenRatioY) / 2), BLACK);
        }

        // In các thông tin lớp học
        for (int i = 0; i < numRows; i++) {
            if (startY + (i + 1) * cellHeight - scrollBarYOffset < startY + cellHeight) {
                continue;
            }
            if (startY + (i + 1) * cellHeight - scrollBarYOffset > screenHeight - cellHeight) {
                break;
            }
            Color rowColor = (i == selectedClass) ? SKYBLUE : RAYWHITE;
            DrawRectangle(startX, startY + (i + 1) * cellHeight - scrollBarYOffset, cellWidth * numCols, cellHeight, rowColor);
            const int fontSize = 15 * ((screenRatioX + screenRatioY) / 2);
            int textWidth = 0;
            int textX = startX + textPadding;
            string textToDraw = classes[i].ClassName;
            textWidth = MeasureText(textToDraw.c_str(), fontSize);
            textX += (cellWidth - textWidth) / 2;
            DrawText(textToDraw.c_str(), textX, startY + (i + 1) * cellHeight - scrollBarYOffset + textPadding, fontSize, DARKGRAY);
        }

        // Vẽ thanh cuộn
        Rectangle scrollBar = { screenWidth - 20, startY + cellHeight, 20, screenHeight - 2 * cellHeight };
        float scrollBarHeight = screenHeight * screenHeight / ((float)numRows * cellHeight);
        float maxScrollBarY = screenHeight - 2 * cellHeight - scrollBarHeight;
        float scrollBarY = ((float)scrollBarYOffset / (numRows * cellHeight)) * maxScrollBarY;
        scrollBar.height = scrollBarHeight;
        scrollBar.y = startY + cellHeight + scrollBarY;
        DrawRectangleRec(scrollBar, GRAY);

        int scroll = GetMouseWheelMove();
        scrollBarYOffset += scroll * 50 * (-1);
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
void viewcoursescore(ListCourses*& List, Course*& courses, int& numRows, Class& selectedClass) {
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
    int maxDisplayedLines = (screenHeight - startY - cellHeight) / cellHeight;
    int selectedCourse = 0;

    while (!WindowShouldClose()) {
        // Xu ly thong tin nhap vao tu ban phim
        if (IsKeyPressed(KEY_DOWN) && selectedCourse < numRows - 1) {
            selectedCourse++;
        }
        if (IsKeyPressed(KEY_UP) && selectedCourse > 0) {
            selectedCourse--;
        }
        if (IsKeyPressed(KEY_ENTER))
        {
            string path = courses[selectedCourse].courseName + "_mark.csv";
            int count = 0;
            string title = "\0\0\0";
            docDiem* diem = docDiemTuFile(path, count, title);
            viewGrade(diem, count, title);
            delete[]diem;
        }
        if (selectedCourse * cellHeight < scrollBarYOffset) {
            scrollBarYOffset = selectedCourse * cellHeight;
        }
        if (selectedCourse * cellHeight >= scrollBarYOffset + maxDisplayedLines * cellHeight) {
            scrollBarYOffset = (selectedCourse + 1) * cellHeight - maxDisplayedLines * cellHeight;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // In tieu de
        for (int i = 0; i < numCols; i++) {
            DrawRectangle(startX + i * cellWidth, startY, cellWidth, cellHeight, LIGHTGRAY);
            int textWidth = MeasureText(headers[i], 15 * ((screenRatioX + screenRatioY) / 2));
            int textX = startX + i * cellWidth + (cellWidth - textWidth) / 2;
            DrawText(headers[i], textX, startY + textPadding, 15 * ((screenRatioX + screenRatioY) / 2), BLACK);
        }

        // In cac thong tin cua tieu de
        for (int i = 0; i < numRows; i++) {
            if (startY + (i + 1) * cellHeight - scrollBarYOffset < startY + cellHeight) {
                continue;
            }
            if (startY + (i + 1) * cellHeight - scrollBarYOffset > screenHeight - cellHeight) {
                break;
            }
            Color rowColor = (i == selectedCourse) ? SKYBLUE : RAYWHITE;
            DrawRectangle(startX, startY + (i + 1) * cellHeight - scrollBarYOffset, cellWidth * numCols, cellHeight, rowColor);
            const int fontSize = 15 * ((screenRatioX + screenRatioY) / 2);
            for (int j = 0; j < 8; j++) {
                int textWidth = 0;
                int textX = startX + j * cellWidth + textPadding;
                string textToDraw;

                switch (j) {
                case 0:
                    textToDraw = courses[i].id;
                    break;
                case 1:
                    textToDraw = courses[i].courseName;
                    break;
                case 2:
                    textToDraw = courses[i].ClassName;
                    break;
                case 3:
                    textToDraw = courses[i].teacherName;
                    break;
                case 4:
                    textToDraw = to_string(courses[i].academicYear);
                    break;
                case 5:
                    textToDraw = to_string(courses[i].Credits);
                    break;
                case 6:
                    textToDraw = courses[i].wDay;
                    break;
                case 7:
                    textToDraw = courses[i].session;
                    break;
                default:
                    break;
                }
                textWidth = MeasureText(textToDraw.c_str(), fontSize);
                textX += (cellWidth - textWidth) / 2;
                DrawText(textToDraw.c_str(), textX, startY + (i + 1) * cellHeight - scrollBarYOffset + textPadding, fontSize, DARKGRAY);
            }
        }
        Rectangle scrollBar = { screenWidth - 20, startY + cellHeight, 20, screenHeight - 2 * cellHeight };
        float scrollBarHeight = screenHeight * screenHeight / ((float)numRows * cellHeight);
        float maxScrollBarY = screenHeight - 2 * cellHeight - scrollBarHeight;
        float scrollBarY = ((float)scrollBarYOffset / (numRows * cellHeight)) * maxScrollBarY;
        scrollBar.height = scrollBarHeight;
        scrollBar.y = startY + cellHeight + scrollBarY;
        DrawRectangleRec(scrollBar, GRAY);
        int scroll = GetMouseWheelMove();
        scrollBarYOffset += scroll * 50 * (-1);
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
void showClassFunctions(ListCourses*& List,ListClass* classList, Class& selectedClass,bool& deletepress) {
    const int screenWidth = 1366;
    const int screenHeight = 768;
    InitWindow(screenWidth, screenHeight, "Class Functions");

    Rectangle buttons[4];
    const char* buttonLabels[4] = {
        "View List Student",
        "Import List Student",
        "Delete Class",
        "View Class Grade"
    };

    for (int i = 0; i < 4; i++) {
        buttons[i].x = (screenWidth - 200) / 2;
        buttons[i].y = 150 + i * 100;
        buttons[i].width = 200;
        buttons[i].height = 50;
    }

    bool viewlistsvActive = false;
    bool importlistsvActive = false;
    bool deleteclassActive = false;
    bool viewClassGrade = false;
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        Vector2 mousePoint = GetMousePosition();
        bool mouseOverButton[4] = { false };

        for (int i = 0; i < 4; i++) {
            mouseOverButton[i] = CheckCollisionPointRec(mousePoint, buttons[i]);
            DrawRectangleRec(buttons[i], mouseOverButton[i] ? LIGHTGRAY : GRAY);
            DrawText(buttonLabels[i], buttons[i].x + (buttons[i].width - MeasureText(buttonLabels[i], 20)) / 2, buttons[i].y + 15, 20, BLACK);
        }

        for (int i = 0; i < 4; i++) {
            if (mouseOverButton[i] && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                switch (i) {
                case 0:
                    viewlistsvActive = true;
                    break;
                case 1:
                    importlistsvActive = true;
                    break;
                case 2:
                    deleteclassActive = true;
                    break;
                case 3:
                    viewClassGrade = true;
                }
                    break;
            }
        }

        if (viewlistsvActive) {
            viewListStudent(selectedClass, screenWidth, screenHeight, viewlistsvActive);
        }

        if (importlistsvActive) {
            importListStudent(selectedClass, screenWidth, screenHeight, importlistsvActive);
        }

        if (deleteclassActive) {
            deleteClass(classList, selectedClass); 
            deleteclassActive = false; 
            deletepress = true;
            CloseWindow();
            return;
        }
        if (viewClassGrade)
        {
            int numRows = 0;
            Course* tempCount = List->head;

            while (tempCount != nullptr) {
                numRows++;
                tempCount = tempCount->next;
            }

            Course* courseArray = new Course[numRows];

            Course* temp = List->head;
            int i;
            for (i = 0; i < numRows && temp != nullptr; i++) {
                courseArray[i] = *temp;
                temp = temp->next;
            }

            viewcoursescore(List, courseArray, numRows, selectedClass);
            delete[] courseArray;
            viewClassGrade = false;
        }
        EndDrawing();
    }

    CloseWindow();
}
void viewListStudent(const Class& selectedClass, int screenWidth, int screenHeight, bool& viewlistsvActive) {
    int numRows = 0;
    SinhVien* currentSV = selectedClass.ds->phead;


    if (selectedClass.ds->phead == nullptr) {
        DrawText("Danh sach lop rong", screenWidth - MeasureText("Danh sach lop rong", 20) - 10, screenHeight - 30, 20, RED);
    }
    else {
        while (currentSV != nullptr) {
            numRows++;
            currentSV = currentSV->next;
        }
        DrawStudentListFromData(selectedClass.ds, numRows);
        viewlistsvActive = false;
    }

    CloseWindow();
}


void importListStudent(Class& selectedClass, int screenWidth, int screenHeight, bool& importlistsvActive) {
    bool inputActive = true; // Bắt đầu với việc nhập liệu ngay khi mở cửa sổ
    bool showError = false;
    bool fileLoaded = false; // Biến để kiểm tra xem file đã được tải thành công hay chưa
    char inputText[128] = "";
    int inputBoxWidth = 300;
    int inputBoxHeight = 40;
    Rectangle inputBox = { (screenWidth - inputBoxWidth) / 2, (screenHeight - inputBoxHeight) / 2, inputBoxWidth, inputBoxHeight };

    while (!WindowShouldClose()) {
        Vector2 mousePoint = GetMousePosition();
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Vẽ ô nhập liệu
        DrawRectangleRec(inputBox, LIGHTGRAY);
        DrawText("Input student file name:", inputBox.x, inputBox.y - 30, 20, DARKGRAY);
        DrawText(inputText, inputBox.x + 10, inputBox.y + 10, 20, DARKGRAY);

        // Xử lý tương tác chuột
        if (CheckCollisionPointRec(mousePoint, inputBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            inputActive = true;
        }

        // Xử lý nhập liệu từ bàn phím
        if (inputActive) {
            int key = GetKeyPressed();
            if ((key >= 32) && (key <= 125)) {
                int length = strlen(inputText);
                if (length < 127) {
                    char newChar = (char)key;
                    if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
                        newChar = toupper(newChar);
                    }
                    else {
                        newChar = tolower(newChar);
                    }
                    inputText[length] = newChar;
                    inputText[length + 1] = '\0';
                }
            }
            if (IsKeyPressed(KEY_BACKSPACE)) {
                int length = strlen(inputText);
                if (length > 0) inputText[length - 1] = '\0';
            }
        }

        // Xử lý nhập liệu từ file khi nhấn phím Enter
        if (IsKeyPressed(KEY_ENTER)) {
            selectedClass.ds = addListSV(inputText);
            if (selectedClass.ds == nullptr) {
                showError = true;
            }
            else {
                memset(inputText, 0, 128);
                inputActive = false; // Ngừng nhập liệu sau khi nhập xong và xử lý thành công
                importlistsvActive = false;
                fileLoaded = true; // Đánh dấu là file đã được tải thành công
            }
        }

        // Kiểm tra nếu file đã được tải thành công thì đóng cửa sổ nhập
        if (fileLoaded) {
            CloseWindow();
            break; // Thoát khỏi vòng lặp
        }

        // Vẽ thông báo lỗi nếu cần thiết
        if (showError) {
            DrawText("Khong the mo file!", screenWidth / 2 - MeasureText("Khong the mo file!", 20) / 2, inputBox.y + 70, 20, RED);
        }

        EndDrawing();
    }
}
void viewcoursescore_SV(ListCourses*& List, Course*& courses, int& numRows,const char* username) {
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
    int maxDisplayedLines = (screenHeight - startY - cellHeight) / cellHeight;
    int selectedCourse = 0;

    while (!WindowShouldClose()) {
        // Xu ly thong tin nhap vao tu ban phim
        if (IsKeyPressed(KEY_DOWN) && selectedCourse < numRows - 1) {
            selectedCourse++;
        }
        if (IsKeyPressed(KEY_UP) && selectedCourse > 0) {
            selectedCourse--;
        }
        if (IsKeyPressed(KEY_ENTER))
        {
            string path = courses[selectedCourse].courseName + "_mark.csv";
            int count = 0;
            string title = "\0\0\0";
            docDiem* diem = docDiemTuFile(path, count, title);
            viewGrade_SV(diem, count, title,username);
            delete[]diem;
        }
        if (selectedCourse * cellHeight < scrollBarYOffset) {
            scrollBarYOffset = selectedCourse * cellHeight;
        }
        if (selectedCourse * cellHeight >= scrollBarYOffset + maxDisplayedLines * cellHeight) {
            scrollBarYOffset = (selectedCourse + 1) * cellHeight - maxDisplayedLines * cellHeight;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // In tieu de
        for (int i = 0; i < numCols; i++) {
            DrawRectangle(startX + i * cellWidth, startY, cellWidth, cellHeight, LIGHTGRAY);
            int textWidth = MeasureText(headers[i], 15 * ((screenRatioX + screenRatioY) / 2));
            int textX = startX + i * cellWidth + (cellWidth - textWidth) / 2;
            DrawText(headers[i], textX, startY + textPadding, 15 * ((screenRatioX + screenRatioY) / 2), BLACK);
        }

        // In cac thong tin cua tieu de
        for (int i = 0; i < numRows; i++) {
            if (startY + (i + 1) * cellHeight - scrollBarYOffset < startY + cellHeight) {
                continue;
            }
            if (startY + (i + 1) * cellHeight - scrollBarYOffset > screenHeight - cellHeight) {
                break;
            }
            Color rowColor = (i == selectedCourse) ? SKYBLUE : RAYWHITE;
            DrawRectangle(startX, startY + (i + 1) * cellHeight - scrollBarYOffset, cellWidth * numCols, cellHeight, rowColor);
            const int fontSize = 15 * ((screenRatioX + screenRatioY) / 2);
            for (int j = 0; j < 8; j++) {
                int textWidth = 0;
                int textX = startX + j * cellWidth + textPadding;
                string textToDraw;

                switch (j) {
                case 0:
                    textToDraw = courses[i].id;
                    break;
                case 1:
                    textToDraw = courses[i].courseName;
                    break;
                case 2:
                    textToDraw = courses[i].ClassName;
                    break;
                case 3:
                    textToDraw = courses[i].teacherName;
                    break;
                case 4:
                    textToDraw = to_string(courses[i].academicYear);
                    break;
                case 5:
                    textToDraw = to_string(courses[i].Credits);
                    break;
                case 6:
                    textToDraw = courses[i].wDay;
                    break;
                case 7:
                    textToDraw = courses[i].session;
                    break;
                default:
                    break;
                }
                textWidth = MeasureText(textToDraw.c_str(), fontSize);
                textX += (cellWidth - textWidth) / 2;
                DrawText(textToDraw.c_str(), textX, startY + (i + 1) * cellHeight - scrollBarYOffset + textPadding, fontSize, DARKGRAY);
            }
        }
        Rectangle scrollBar = { screenWidth - 20, startY + cellHeight, 20, screenHeight - 2 * cellHeight };
        float scrollBarHeight = screenHeight * screenHeight / ((float)numRows * cellHeight);
        float maxScrollBarY = screenHeight - 2 * cellHeight - scrollBarHeight;
        float scrollBarY = ((float)scrollBarYOffset / (numRows * cellHeight)) * maxScrollBarY;
        scrollBar.height = scrollBarHeight;
        scrollBar.y = startY + cellHeight + scrollBarY;
        DrawRectangleRec(scrollBar, GRAY);
        int scroll = GetMouseWheelMove();
        scrollBarYOffset += scroll * 50 * (-1);
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
void viewGrade_SV(docDiem* diem, int& numRows, string title,const char*username) {
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

    const char* headers[numCols] = { "No", "ID", "Ho", "Ten", "Other", "MidTerm", "Final", "Total" };

    // Lọc điểm có tên giống với username
    docDiem* selectedDiem = nullptr;
    for (int i = 0; i < numRows; i++) {
        if (diem[i].id == username) {
            selectedDiem = &diem[i];
            break;
        }
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        const int fontSize = 15 * ((screenRatioX + screenRatioY) / 2);
        int titleTextWidth = MeasureText(title.c_str(), fontSize);
        int titleX = (screenWidth - titleTextWidth) / 2;
        DrawText(title.c_str(), titleX, startY - 40 * screenRatioY, fontSize, BLACK);

        // Vẽ tiêu đề
        for (int i = 0; i < numCols; i++) {
            DrawRectangle(startX + i * cellWidth, startY, cellWidth, cellHeight, LIGHTGRAY);
            int textWidth = MeasureText(headers[i], 15 * ((screenRatioX + screenRatioY) / 2));
            int textX = startX + i * cellWidth + (cellWidth - textWidth) / 2;
            DrawText(headers[i], textX, startY + textPadding, 15 * ((screenRatioX + screenRatioY) / 2), BLACK);
        }

        // Vẽ dữ liệu điểm nếu có
        if (selectedDiem) {
            for (int j = 0; j < numCols; j++) {
                int textWidth = 0;
                int textX = startX + j * cellWidth + textPadding;
                string textToDraw;

                switch (j) {
                case 0:
                    textToDraw = to_string(selectedDiem->No);
                    break;
                case 1:
                    textToDraw = selectedDiem->id;
                    break;
                case 2:
                    textToDraw = selectedDiem->ho;
                    break;
                case 3:
                    textToDraw = selectedDiem->ten;
                    break;
                case 4:
                    textToDraw = to_string(selectedDiem->other);
                    break;
                case 5:
                    textToDraw = to_string(selectedDiem->midterm);
                    break;
                case 6:
                    textToDraw = to_string(selectedDiem->final);
                    break;
                case 7:
                    textToDraw = to_string(selectedDiem->total);
                    break;
                default:
                    break;
                }

                textWidth = MeasureText(textToDraw.c_str(), fontSize);
                textX += (cellWidth - textWidth) / 2;
                DrawText(textToDraw.c_str(), textX, startY + cellHeight + textPadding, fontSize, DARKGRAY);
            }
        }

        EndDrawing();
    }

    CloseWindow();
}
void deleteClass(ListClass* classList, const Class& selectedClass) {
    if (classList == nullptr || classList->head == nullptr) return;

    Class* prevClass = nullptr;
    Class* currentClass = classList->head;
    while (currentClass != nullptr && currentClass->ClassName != selectedClass.ClassName) {
        prevClass = currentClass;
        currentClass = currentClass->next;
    }
    if (currentClass != nullptr) {
        if (prevClass == nullptr) {
            classList->head = currentClass->next;
        }
        else {
            prevClass->next = currentClass->next;
        }
        delete currentClass;
    }
    saveClassesToCSV(classList, "classes.csv");
}
docDiem* docDiemTuFile(string path, int& count, string& title)
{
    ifstream ifile;
    ifile.open(path);
    if (!ifile.is_open())
    {
        cout << "ko mo dc";
        return NULL;
    }
    count = 0;
    string temp;
    //3 vi ki tu dau chua Byte Order Mark
    ifile.seekg(3, ios::beg);
    getline(ifile, title, ',');
    getline(ifile, temp);
    while (ifile.peek() != EOF)
    {
        count++;
        getline(ifile, temp);
    }
    // 2 dong (1 chua mon hoc ,1 chu no,id,ho,ten)
    count = count - 1;
    docDiem* diem = new docDiem[count];
    ifile.seekg(0, ios::beg);
    getline(ifile, temp);
    getline(ifile, temp);
    int i = 0;
    while (ifile.peek() != EOF)
    {
        getline(ifile, temp, ',');

        diem[i].No = stoi(temp);
        getline(ifile, diem[i].id, ',');
        getline(ifile, diem[i].ho, ',');
        getline(ifile, diem[i].ten, ',');

        getline(ifile, temp, ',');
        diem[i].other = stod(temp);

        getline(ifile, temp, ',');
        diem[i].midterm = stod(temp);
        getline(ifile, temp, ',');
        diem[i].final = stod(temp);
        getline(ifile, temp);
        diem[i].total = stod(temp);
        i++;
    }
    ifile.close();
    return diem;
}
void viewGrade(docDiem* diem, int& numRows, string title) {
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

    const char* headers[numCols] = { "No", "ID", "Ho", "Ten", "Other", "MidTerm", "Final", "Total" };

    int scrollBarYOffset = 0;
    int maxDisplayedLines = (screenHeight - startY - cellHeight) / cellHeight;
    int selectedCourse = 0;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        const int fontSize = 15 * ((screenRatioX + screenRatioY) / 2);
        int titleTextWidth = MeasureText(title.c_str(), fontSize);
        int titleX = (screenWidth - titleTextWidth) / 2;
        DrawText(title.c_str(), titleX, startY - 40 * screenRatioY, fontSize, BLACK);
        for (int i = 0; i < numCols; i++) {
            DrawRectangle(startX + i * cellWidth, startY, cellWidth, cellHeight, LIGHTGRAY);
            int textWidth = MeasureText(headers[i], 15 * ((screenRatioX + screenRatioY) / 2));
            int textX = startX + i * cellWidth + (cellWidth - textWidth) / 2;
            DrawText(headers[i], textX, startY + textPadding, 15 * ((screenRatioX + screenRatioY) / 2), BLACK);
        }
        for (int i = 0; i < numRows; i++) {
            if (startY + (i + 1) * cellHeight - scrollBarYOffset < startY + cellHeight) {
                continue;
            }
            if (startY + (i + 1) * cellHeight - scrollBarYOffset > screenHeight - cellHeight) {
                break;
            }
            const int fontSize = 15 * ((screenRatioX + screenRatioY) / 2);
            for (int j = 0; j < 8; j++) {
                int textWidth = 0;
                int textX = startX + j * cellWidth + textPadding;
                string textToDraw;

                switch (j) {
                case 0:
                    textToDraw = to_string(diem[i].No);
                    break;
                case 1:
                    textToDraw = diem[i].id;
                    break;
                case 2:
                    textToDraw = diem[i].ho;
                    break;
                case 3:
                    textToDraw = diem[i].ten;
                    break;
                case 4:
                    textToDraw = to_string(diem[i].other);
                    break;
                case 5:
                    textToDraw = to_string(diem[i].midterm);
                    break;
                case 6:
                    textToDraw = to_string(diem[i].final);
                    break;
                case 7:
                    textToDraw = to_string(diem[i].total);
                    break;
                default:
                    break;
                }

                textWidth = MeasureText(textToDraw.c_str(), fontSize);
                textX += (cellWidth - textWidth) / 2;
                DrawText(textToDraw.c_str(), textX, startY + (i + 1) * cellHeight - scrollBarYOffset + textPadding, fontSize, DARKGRAY);
            }
        }
        Rectangle scrollBar = { screenWidth - 20, startY + cellHeight, 20, screenHeight - 2 * cellHeight };
        float scrollBarHeight = screenHeight * screenHeight / ((float)numRows * cellHeight);
        float maxScrollBarY = screenHeight - 2 * cellHeight - scrollBarHeight;
        float scrollBarY = ((float)scrollBarYOffset / (numRows * cellHeight)) * maxScrollBarY;
        scrollBar.height = scrollBarHeight;
        scrollBar.y = startY + cellHeight + scrollBarY;
        DrawRectangleRec(scrollBar, GRAY);
        int scroll = GetMouseWheelMove();
        scrollBarYOffset += scroll * 50 * (-1);
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
void deletesemester(Semester*& sm)
{
    Semester* temp = sm;
    while (temp != NULL)
    {
        Semester* next = temp->next;
        deleteListCourses(temp->lc);
        delete temp;
        temp = next;
    }
    sm = NULL;
}
void deletelistnamhoc(ListNamHoc& LNH)
{
    NamHoc* temp = LNH.phead;
    while (temp != NULL)
    {
        deletesemester(temp->Hocky);
        NamHoc* pre = temp;
        temp = temp->next;
        delete pre;
    }
    LNH.phead = NULL;
}
void deleteListUser(ListUser* list) {
    if (!list) return;
    User* current = list->phead;
    while (current) {
        User* next = current->next;
        delete current;
        current = next;
    }
    delete list;
}
void deleteListSV(ListSV* list) {
    if (!list) return;
    SinhVien* current = list->phead;
    while (current) {
        SinhVien* next = current->next;
        delete current;
        current = next;
    }
    delete list;
}
void deleteListCourses(ListCourses* list) {
    if (!list) return;
    Course* current = list->head;
    while (current) {
        deleteListSV(current->lsv);  
        Course* next = current->next;
        delete current;
        current = next;
    }
    delete list;
}
