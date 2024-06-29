#include "function.h"

int main() {
    ListClass* Lclass = new ListClass;
    Lclass->head = NULL;

    ListCourses* LC = new ListCourses;
    InitList(LC);

    ListNamHoc LNH = { NULL };

    NamHoc* N = new NamHoc;
    Semester* sm = NULL;

    ListUser* LUR = addListUser("User.csv");

    Semester* s = NULL;

    ListCourses* List_Courses_SV = new ListCourses;
    InitList(List_Courses_SV);

    char username[128] = "\0";
    char password[128] = "\0";
    bool checkstaff = false;

    bool mouseOnText = false;
    bool usernameBoxActive = false;
    bool passwordBoxActive = false;
    bool loginAttempted = false;
    bool loginSuccessful = false;
    bool showError = false;
    bool showInvalidYearError = false;
    bool showsemester = false;

    char classNameInput[128] = "\0"; // Tăng kích thước bộ nhớ
    Rectangle classNameInputBox = { 100, 100, 200, 40 };

    bool courseCreated = false; // Flag to check if a course has been created

    if (Login(LUR, username, password, checkstaff) && checkstaff) {
        const int dashboardWidth = 1366;
        const int dashboardHeight = 768;
        SetWindowSize(dashboardWidth, dashboardHeight);
        SetWindowTitle("staff dashboard");
        SetTargetFPS(60);

        Rectangle buttons[8];
        const char* buttonLabels[8] = {
            "Create New School Year",
            "Create New Semester",
            "Add Course",
            "View and Delete Course",
            "Add Student to Course and View",
            "Change password",
            "Create New Class",
            "View Class"
        };

        bool createNewSchoolYearActive = false;
        char schoolYearInput[128] = "\0";
        Rectangle schoolYearInputBox = { dashboardWidth / 2 - 100, 450, 200, 40 };
        bool schoolYearInputBoxActive = false;

        bool createNewSemesterActive = false;
        bool createNewCourseActive = false;
        bool viewCourseActive = false;
        bool addsvInputBoxActive = false;
        char addsvInput[128] = "\0";
        Rectangle addsvInputBox = { dashboardWidth / 2 - 100, 450, 200, 40 };
        bool classNameBoxActive = false;
        bool changePasswordActive = false;
        bool viewClassActive = false;
        bool createClassActive = false;
        bool viewClassGrade = false;

        for (int i = 0; i < 8; i++) {
            buttons[i].x = (dashboardWidth - 400) / 2;
            buttons[i].y = 50 + i * 60;
            buttons[i].width = 400;
            buttons[i].height = 40;
        }

        while (!WindowShouldClose()) {
            Vector2 mousePoint = GetMousePosition();
            bool mouseOverButton[8] = { false };

            BeginDrawing();
            ClearBackground(RAYWHITE);

            for (int i = 0; i < 8; i++) {
                mouseOverButton[i] = CheckCollisionPointRec(mousePoint, buttons[i]);
                DrawButton(buttons[i], buttonLabels[i], mouseOverButton[i]);

                if (mouseOverButton[i] && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    createNewSchoolYearActive = false;
                    schoolYearInputBoxActive = false;
                    createNewSemesterActive = false;
                    createNewCourseActive = false;
                    viewCourseActive = false;
                    addsvInputBoxActive = false;
                    changePasswordActive = false;
                    viewClassActive = false;
                    createClassActive = false;

                    switch (i) {
                    case 0:
                        createNewSchoolYearActive = true;
                        break;
                    case 1:
                        createNewSemesterActive = true;
                        break;
                    case 2:
                    case 3:
                    case 4:
                        if (LNH.phead == NULL || LNH.phead->Hocky == NULL) {
                            showError = true;
                        }
                        else {
                            if (i == 2) {
                                createNewCourseActive = true;
                                courseCreated = true; 
                            }
                            if (i == 3) viewCourseActive = true;
                            if (i == 4) addsvInputBoxActive = true;
                        }
                        break;
                    case 5:
                        changePasswordActive = true;
                        break;
                    case 6:
                        createClassActive = true;
                        break;
                    case 7:
                        if (courseCreated) { //Kiem tra xem course da duoc tao hay chua
                            viewClassActive = true;
                        }
                        else {
                            showError = true;
                        }
                        break;
                    }
                }
            }

            if (createNewSchoolYearActive) {
                CreateNewSchoolYeabutton(createNewSchoolYearActive, schoolYearInputBoxActive, schoolYearInput, LNH, N, mousePoint, showInvalidYearError);
            }

            if (createNewSemesterActive) {
                s = taohocky(sm, LNH);
                if (s->showsemester) {
                    showsemester = true;
                }
                createNewSemesterActive = false;
            }

            if (showsemester) {
                string hocKyText = "Hoc Ky " + to_string(s->thutu) + " -" + s->namhoc;
                const char* hocKyChar = hocKyText.c_str();
                int hocKyWidth = MeasureText(hocKyChar, 20);
                int hocKyX = 10;
                int hocKyY = 10;
                DrawText(hocKyChar, hocKyX, hocKyY, 20, DARKGRAY);
            }

            if (createNewCourseActive) {
                CloseWindow();
                CourseDashboard(dashboardWidth, dashboardHeight, s->lc);
                createNewCourseActive = false;
            }

            if (viewCourseActive) {
                int numRows = 0;
                Course* tempCount = s->lc->head;

                while (tempCount != nullptr) {
                    numRows++;
                    tempCount = tempCount->next;
                }

                Course* courseArray = new Course[numRows];

                Course* temp = s->lc->head;
                int i;
                for (i = 0; i < numRows && temp != nullptr; i++) {
                    courseArray[i] = *temp;
                    temp = temp->next;
                }

                viewcourse(s->lc, courseArray, numRows);
                delete[] courseArray;

                viewCourseActive = false;
            }

            if (addsvInputBoxActive) {
                AddStudentsbutton(addsvInput, addsvInputBox, addsvInputBoxActive, s->lc, dashboardWidth, dashboardHeight);
            }

            if (changePasswordActive) {
                ChangePassword(LUR, username, password);
                saveListUser(LUR, "User.csv");
                changePasswordActive = false;
            }

            if (createClassActive) {
                DrawClassNameInputBox(classNameInputBox, classNameInput, mousePoint, mouseOnText, classNameBoxActive, dashboardWidth, dashboardHeight, Lclass, createClassActive);
            }

            if (viewClassActive) {
                loadClassesFromCSV(Lclass, "classes.csv");
                viewClasses(Lclass, s->lc);
                viewClassActive = false;
            }

            if (showError) {
                DrawText("Error: No semester or course created yet!", 10, 10, 20, RED);
                if (showsemester) {
                    showError = false;
                }
            }

            EndDrawing();
        }
    }
    else {
        const int dashboardWidth = 1366;
        const int dashboardHeight = 768;
        SetWindowSize(dashboardWidth, dashboardHeight);
        SetWindowTitle("user dashboard");
        SetTargetFPS(60);

        Rectangle buttons[5];
        const char* buttonLabels[5] = {
            "Profile",
            "Change Password",
            "Sign a course",
            "View courses",
            "View score"
        };

        bool viewprofileActive = false;
        bool ChangepasswordActive = false;
        bool dangkicourse = false;
        bool ViewCoursesActive = false;
        bool ViewscoreActive= false;
        for (int i = 0; i < 5; i++) {
            buttons[i].x = (dashboardWidth - 400) / 2;
            buttons[i].y = 50 + i * 60;
            buttons[i].width = 400;
            buttons[i].height = 40;
        }

        while (!WindowShouldClose()) {
            Vector2 mousePoint = GetMousePosition();
            bool mouseOverButton[5] = { false };

            BeginDrawing();
            ClearBackground(RAYWHITE);

            for (int i = 0; i < 5; i++) {
                mouseOverButton[i] = CheckCollisionPointRec(mousePoint, buttons[i]);
                DrawButton(buttons[i], buttonLabels[i], mouseOverButton[i]);

                if (mouseOverButton[i] && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    viewprofileActive = false;
                    ChangepasswordActive = false;

                    switch (i) {
                    case 0:
                        viewprofileActive = true;
                        break;
                    case 1:
                        ChangepasswordActive = true;
                        break;
                    case 2:
                        dangkicourse = true;
                        break;
                    case 3:
                        ViewCoursesActive = true;
                        break;
                    case 4:
                        ViewscoreActive = true;
                        break;
                    }
                }
            }

            if (ChangepasswordActive) {
                ChangePassword(LUR, username, password);
                saveListUser(LUR, "User.csv");
                ChangepasswordActive = false;
            }

            if (viewprofileActive) {
                User* user = timnodeuser(LUR, username, password);
                DisplayProfileInfo(user);
                viewprofileActive = false;
            }
            if (dangkicourse) {
                ImportCourseFile(LC, "Courses.csv");

                int numRows = 0;
                Course* tempCount = LC->head;

                while (tempCount != nullptr) {
                    numRows++;
                    tempCount = tempCount->next;
                }
                Course* courseArray = new Course[numRows];
                Course* temp = LC->head;
                Course* pretemp = NULL;
                int i;
                for (i = 0; i < numRows && temp != nullptr; i++) {
                    courseArray[i] = *temp;
                    temp = temp->next;
                }
                ViewAvailableSignCourses(LC, courseArray, numRows, List_Courses_SV);
                delete[] courseArray;
                dangkicourse = false;
            }
            if (ViewCoursesActive) {
                int numRows = 0;
                Course* tempCount = List_Courses_SV->head;
                while (tempCount != nullptr) {
                    numRows++;
                    tempCount = tempCount->next;
                }
                Course* courseArray = new Course[numRows];
                Course* temp = List_Courses_SV->head;
                int i;
                for (i = 0; i < numRows && temp != nullptr; i++) {
                    courseArray[i] = *temp;
                    temp = temp->next;
                }
                ViewCourses_SV(courseArray, numRows, List_Courses_SV);
                delete[] courseArray;
                ViewCoursesActive = false;
            }
            if (ViewscoreActive)
            {
                int numRows = 0;
                Course* tempCount = List_Courses_SV->head;
                while (tempCount != nullptr) {
                    numRows++;
                    tempCount = tempCount->next;
                }
                Course* courseArray = new Course[numRows];
                Course* temp = List_Courses_SV->head;
                int i;
                for (i = 0; i < numRows && temp != nullptr; i++) {
                    courseArray[i] = *temp;
                    temp = temp->next;
                }
                viewcoursescore_SV(LC, courseArray, numRows,username);
                ViewscoreActive = false;
            }
            EndDrawing();
        }
    }
    clearClassList(Lclass);
    delete Lclass;
    deleteListCourses(LC);
    deletelistnamhoc(LNH);
    deleteListUser(LUR);
    deleteListCourses(List_Courses_SV);
    CloseWindow();
    return 0;
}
